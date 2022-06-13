/*
 * Copyright 2004-2022 the Pacemaker project contributors
 *
 * The version control history for this file may have further details.
 *
 * This source code is licensed under the GNU General Public License version 2
 * or later (GPLv2+) WITHOUT ANY WARRANTY.
 */

#include <crm_internal.h>

#include <stdbool.h>

#include <crm/msg_xml.h>
#include <pacemaker-internal.h>

#include "libpacemaker_private.h"

extern gboolean DeleteRsc(pe_resource_t *rsc, const pe_node_t *node,
                          gboolean optional, pe_working_set_t *data_set);

/*!
 * \internal
 * \brief Add migration source and target meta-attributes to an action
 *
 * \param[in,out] action  Action to add meta-attributes to
 * \param[in]     source  Node to add as migration source
 * \param[in]     target  Node to add as migration target
 */
static void
add_migration_meta(pe_action_t *action, const pe_node_t *source,
                   const pe_node_t *target)
{
    add_hash_param(action->meta, XML_LRM_ATTR_MIGRATE_SOURCE,
                   source->details->uname);

    add_hash_param(action->meta, XML_LRM_ATTR_MIGRATE_TARGET,
                   target->details->uname);
}

/*!
 * \internal
 * \brief Create internal migration actions for a migrateable resource
 *
 * \param[in,out] rsc      Resource to create migration actions for
 * \param[in]     current  Node that resource is originally active on
 */
void
pcmk__create_migration_actions(pe_resource_t *rsc, const pe_node_t *current)
{
    pe_action_t *migrate_to = NULL;
    pe_action_t *migrate_from = NULL;
    pe_action_t *start = NULL;
    pe_action_t *stop = NULL;

    pe_rsc_trace(rsc, "Creating actions to %smigrate %s from %s to %s",
                 ((rsc->partial_migration_target == NULL)? "" : "partially "),
                 rsc->id, pe__node_name(current),
                 pe__node_name(rsc->allocated_to));
    start = start_action(rsc, rsc->allocated_to, TRUE);
    stop = stop_action(rsc, current, TRUE);

    if (rsc->partial_migration_target == NULL) {
        migrate_to = custom_action(rsc, pcmk__op_key(rsc->id, RSC_MIGRATE, 0),
                                   RSC_MIGRATE, current, TRUE, TRUE,
                                   rsc->cluster);
    }
    migrate_from = custom_action(rsc, pcmk__op_key(rsc->id, RSC_MIGRATED, 0),
                                 RSC_MIGRATED, rsc->allocated_to, TRUE, TRUE,
                                 rsc->cluster);

    if ((migrate_from != NULL)
        && ((migrate_to != NULL) || (rsc->partial_migration_target != NULL))) {

        pe__set_action_flags(start, pe_action_migrate_runnable);
        pe__set_action_flags(stop, pe_action_migrate_runnable);

        // This is easier than trying to delete it from the graph
        pe__set_action_flags(start, pe_action_pseudo);

        if (rsc->partial_migration_target == NULL) {
            pe__set_action_flags(migrate_from, pe_action_migrate_runnable);
            pe__set_action_flags(migrate_to, pe_action_migrate_runnable);
            migrate_to->needs = start->needs;

            // Probe -> migrate_to -> migrate_from
            pcmk__new_ordering(rsc, pcmk__op_key(rsc->id, RSC_STATUS, 0), NULL,
                               rsc, pcmk__op_key(rsc->id, RSC_MIGRATE, 0),
                               NULL, pe_order_optional, rsc->cluster);
            pcmk__new_ordering(rsc, pcmk__op_key(rsc->id, RSC_MIGRATE, 0), NULL,
                               rsc, pcmk__op_key(rsc->id, RSC_MIGRATED, 0),
                               NULL,
                               pe_order_optional|pe_order_implies_first_migratable,
                               rsc->cluster);
        } else {
            pe__set_action_flags(migrate_from, pe_action_migrate_runnable);
            migrate_from->needs = start->needs;

            // Probe -> migrate_from (migrate_to already completed)
            pcmk__new_ordering(rsc, pcmk__op_key(rsc->id, RSC_STATUS, 0), NULL,
                               rsc, pcmk__op_key(rsc->id, RSC_MIGRATED, 0),
                               NULL, pe_order_optional, rsc->cluster);
        }

        // migrate_from before stop or start
        pcmk__new_ordering(rsc, pcmk__op_key(rsc->id, RSC_MIGRATED, 0), NULL,
                           rsc, pcmk__op_key(rsc->id, RSC_STOP, 0), NULL,
                           pe_order_optional|pe_order_implies_first_migratable,
                           rsc->cluster);
        pcmk__new_ordering(rsc, pcmk__op_key(rsc->id, RSC_MIGRATED, 0), NULL,
                           rsc, pcmk__op_key(rsc->id, RSC_START, 0), NULL,
                           pe_order_optional|pe_order_implies_first_migratable|pe_order_pseudo_left,
                           rsc->cluster);
    }

    if (migrate_to != NULL) {
        add_migration_meta(migrate_to, current, rsc->allocated_to);

        if (!rsc->is_remote_node) {
            /* migrate_to takes place on the source node, but can affect the
             * target node depending on how the agent is written. Because of
             * this, pending migrate_to actions must be recorded in the CIB,
             * in case the source node loses membership while the migrate_to
             * action is still in flight.
             *
             * However we know Pacemaker Remote connection resources don't
             * require this, so we skip this for them. (Although it wouldn't
             * hurt, and now that record-pending defaults to true, skipping it
             * matters even less.)
             */
            add_hash_param(migrate_to->meta, XML_OP_ATTR_PENDING, "true");
        }
    }

    if (migrate_from != NULL) {
        add_migration_meta(migrate_from, current, rsc->allocated_to);
    }
}

/*!
 * \internal
 * \brief Abort a dangling migration by scheduling a stop (and possibly cleanup)
 *
 * \param[in]     data       Source node of dangling migration
 * \param[in,out] user_data  Resource involved in dangling migration
 */
void
pcmk__abort_dangling_migration(void *data, void *user_data)
{
    const pe_node_t *dangling_source = (const pe_node_t *) data;
    pe_resource_t *rsc = (pe_resource_t *) user_data;

    pe_action_t *stop = NULL;
    bool cleanup = pcmk_is_set(rsc->cluster->flags, pe_flag_remove_after_stop);

    pe_rsc_trace(rsc,
                 "Scheduling stop%s for %s on %s due to dangling migration",
                 (cleanup? " and cleanup" : ""), rsc->id,
                 pe__node_name(dangling_source));
    stop = stop_action(rsc, dangling_source, FALSE);
    pe__set_action_flags(stop, pe_action_dangle);
    if (cleanup) {
        DeleteRsc(rsc, dangling_source, FALSE, rsc->cluster);
    }
}

/*!
 * \internal
 * \brief Check whether a resource can migrate
 *
 * \param[in] rsc   Resource to check
 * \param[in] node  Resource's current node
 *
 * \return true if \p rsc can migrate, otherwise false
 */
bool
pcmk__rsc_can_migrate(const pe_resource_t *rsc, const pe_node_t *current)
{
    CRM_CHECK(rsc != NULL, return false);

    if (!pcmk_is_set(rsc->flags, pe_rsc_allow_migrate)) {
        pe_rsc_trace(rsc, "%s cannot migrate because "
                          "the configuration does not allow it",
                     rsc->id);
        return false;
    }

    if (!pcmk_is_set(rsc->flags, pe_rsc_managed)) {
        pe_rsc_trace(rsc, "%s cannot migrate because it is not managed",
                     rsc->id);
        return false;
    }

    if (pcmk_is_set(rsc->flags, pe_rsc_failed)) {
        pe_rsc_trace(rsc, "%s cannot migrate because it is failed",
                     rsc->id);
        return false;
    }

    if (pcmk_is_set(rsc->flags, pe_rsc_start_pending)) {
        pe_rsc_trace(rsc, "%s cannot migrate because it has a start pending",
                     rsc->id);
        return false;
    }

    if ((current == NULL) || current->details->unclean) {
        pe_rsc_trace(rsc, "%s cannot migrate because "
                          "its current node (%s) is unclean",
                     rsc->id, pe__node_name(current));
        return false;
    }

    if ((rsc->allocated_to == NULL) || rsc->allocated_to->details->unclean) {
        pe_rsc_trace(rsc, "%s cannot migrate because "
                          "its next node (%s) is unclean",
                     rsc->id, pe__node_name(rsc->allocated_to));
        return false;
    }

    return true;
}
