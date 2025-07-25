/*
 * Copyright 2006-2025 the Pacemaker project contributors
 *
 * The version control history for this file may have further details.
 *
 * This source code is licensed under the GNU Lesser General Public License
 * version 2.1 or later (LGPLv2.1+) WITHOUT ANY WARRANTY.
 */

#ifndef PCMK__CRM_COMMON_OPTIONS_INTERNAL__H
#define PCMK__CRM_COMMON_OPTIONS_INTERNAL__H

#ifndef PCMK__CONFIG_H
#define PCMK__CONFIG_H
#include <config.h>   // _Noreturn
#endif

#include <glib.h>     // GHashTable
#include <stdbool.h>  // bool

#include <crm/common/strings.h>             // pcmk_parse_interval_spec()
#include <crm/common/output_internal.h>     // pcmk__output_t

#ifdef __cplusplus
extern "C" {
#endif

_Noreturn void pcmk__cli_help(void);


/*
 * Environment variable option handling
 */

const char *pcmk__env_option(const char *option);
void pcmk__set_env_option(const char *option, const char *value, bool compat);
bool pcmk__env_option_enabled(const char *daemon, const char *option);


/*
 * Cluster option handling
 */

/*!
 * \internal
 * \brief Option flags
 */
enum pcmk__opt_flags {
    pcmk__opt_none       = 0U,          //!< No additional information

    /*!
     * \brief In CIB manager metadata
     *
     * \deprecated This flag will be removed with CIB manager metadata
     */
    pcmk__opt_based      = (1U << 0),

    /*!
     * \brief In controller metadata
     *
     * \deprecated This flag will be removed with controller metadata
     */
    pcmk__opt_controld   = (1U << 1),

    /*!
     * \brief In scheduler metadata
     *
     * \deprecated This flag will be removed with scheduler metadata
     */
    pcmk__opt_schedulerd = (1U << 2),

    pcmk__opt_advanced   = (1U << 3),   //!< Advanced use only
    pcmk__opt_generated  = (1U << 4),   //!< Generated by Pacemaker
    pcmk__opt_deprecated = (1U << 5),   //!< Option is deprecated
    pcmk__opt_fencing    = (1U << 6),   //!< Common fencing resource parameter
    pcmk__opt_primitive  = (1U << 7),   //!< Primitive resource meta-attribute
};

typedef struct pcmk__cluster_option_s {
    const char *name;
    const char *alt_name;
    const char *type;
    const char *values;
    const char *default_value;

    bool (*is_valid)(const char *);

    uint32_t flags;                 //!< Group of <tt>enum pcmk__opt_flags</tt>

    const char *description_short;
    const char *description_long;

} pcmk__cluster_option_t;

const char *pcmk__cluster_option(GHashTable *options, const char *name);

int pcmk__output_cluster_options(pcmk__output_t *out, const char *name,
                                 const char *desc_short, const char *desc_long,
                                 uint32_t filter, bool all);
int pcmk__output_fencing_params(pcmk__output_t *out, const char *name,
                                const char *desc_short, const char *desc_long,
                                bool all);
int pcmk__output_primitive_meta(pcmk__output_t *out, const char *name,
                                const char *desc_short, const char *desc_long,
                                bool all);

int pcmk__daemon_metadata(pcmk__output_t *out, const char *name,
                          const char *short_desc, const char *long_desc,
                          enum pcmk__opt_flags filter);

void pcmk__validate_cluster_options(GHashTable *options);

bool pcmk__valid_interval_spec(const char *value);
bool pcmk__valid_boolean(const char *value);
bool pcmk__valid_int(const char *value);
bool pcmk__valid_positive_int(const char *value);
bool pcmk__valid_no_quorum_policy(const char *value);
bool pcmk__valid_percentage(const char *value);
bool pcmk__valid_placement_strategy(const char *value);

// from watchdog.c
long pcmk__get_sbd_watchdog_timeout(void);
bool pcmk__get_sbd_sync_resource_startup(void);
long pcmk__auto_stonith_watchdog_timeout(void);
bool pcmk__valid_stonith_watchdog_timeout(const char *value);

// Constants for environment variable names
#define PCMK__ENV_AUTHKEY_LOCATION          "authkey_location"
#define PCMK__ENV_BLACKBOX                  "blackbox"
#define PCMK__ENV_CA_FILE                   "ca_file"
#define PCMK__ENV_CALLGRIND_ENABLED         "callgrind_enabled"
#define PCMK__ENV_CERT_FILE                 "cert_file"
#define PCMK__ENV_CLUSTER_TYPE              "cluster_type"
#define PCMK__ENV_CRL_FILE                  "crl_file"
#define PCMK__ENV_DEBUG                     "debug"
#define PCMK__ENV_DH_MAX_BITS               "dh_max_bits"
#define PCMK__ENV_FAIL_FAST                 "fail_fast"
#define PCMK__ENV_IPC_TYPE                  "ipc_type"
#define PCMK__ENV_KEY_FILE                  "key_file"
#define PCMK__ENV_LOGFACILITY               "logfacility"
#define PCMK__ENV_LOGFILE                   "logfile"
#define PCMK__ENV_LOGFILE_MODE              "logfile_mode"
#define PCMK__ENV_LOGPRIORITY               "logpriority"
#define PCMK__ENV_NODE_ACTION_LIMIT         "node_action_limit"
#define PCMK__ENV_NODE_START_STATE          "node_start_state"
#define PCMK__ENV_PANIC_ACTION              "panic_action"
#define PCMK__ENV_REMOTE_ADDRESS            "remote_address"
#define PCMK__ENV_REMOTE_SCHEMA_DIRECTORY   "remote_schema_directory"
#define PCMK__ENV_REMOTE_PID1               "remote_pid1"
#define PCMK__ENV_REMOTE_PORT               "remote_port"
#define PCMK__ENV_RESPAWNED                 "respawned"
#define PCMK__ENV_SCHEMA_DIRECTORY          "schema_directory"
#define PCMK__ENV_SERVICE                   "service"
#define PCMK__ENV_STDERR                    "stderr"
#define PCMK__ENV_TLS_PRIORITIES            "tls_priorities"
#define PCMK__ENV_TRACE_BLACKBOX            "trace_blackbox"
#define PCMK__ENV_TRACE_FILES               "trace_files"
#define PCMK__ENV_TRACE_FORMATS             "trace_formats"
#define PCMK__ENV_TRACE_FUNCTIONS           "trace_functions"
#define PCMK__ENV_TRACE_TAGS                "trace_tags"
#define PCMK__ENV_VALGRIND_ENABLED          "valgrind_enabled"

// Constants for meta-attribute names
#define PCMK__META_CLONE                    "clone"
#define PCMK__META_CONTAINER                "container"
#define PCMK__META_DIGESTS_ALL              "digests-all"
#define PCMK__META_DIGESTS_SECURE           "digests-secure"
#define PCMK__META_INTERNAL_RSC             "internal_rsc"
#define PCMK__META_MIGRATE_SOURCE           "migrate_source"
#define PCMK__META_MIGRATE_TARGET           "migrate_target"
#define PCMK__META_ON_NODE                  "on_node"
#define PCMK__META_ON_NODE_UUID             "on_node_uuid"
#define PCMK__META_OP_NO_WAIT               "op_no_wait"
#define PCMK__META_OP_TARGET_RC             "op_target_rc"
#define PCMK__META_PHYSICAL_HOST            "physical-host"
#define PCMK__META_STONITH_ACTION           "stonith_action"

/* @TODO Plug these in. Currently, they're never set. These are op attrs for use
 * with https://projects.clusterlabs.org/T382.
 */
#define PCMK__META_CLEAR_FAILURE_OP         "clear_failure_op"
#define PCMK__META_CLEAR_FAILURE_INTERVAL   "clear_failure_interval"

// @COMPAT Deprecated alias for PCMK__META_PROMOTED_MAX since 2.0.0
#define PCMK__META_PROMOTED_MAX_LEGACY      "master-max"

// @COMPAT Deprecated alias for PCMK__META_PROMOTED_NODE_MAX since 2.0.0
#define PCMK__META_PROMOTED_NODE_MAX_LEGACY "master-node-max"

// Constants for enumerated values
#define PCMK__VALUE_ATTRD                   "attrd"
#define PCMK__VALUE_BOLD                    "bold"
#define PCMK__VALUE_BROADCAST               "broadcast"
#define PCMK__VALUE_CIB                     "cib"
#define PCMK__VALUE_CIB_DIFF_NOTIFY         "cib_diff_notify"
#define PCMK__VALUE_CIB_NOTIFY              "cib_notify"
#define PCMK__VALUE_CIB_POST_NOTIFY         "cib_post_notify"
#define PCMK__VALUE_CIB_PRE_NOTIFY          "cib_pre_notify"
#define PCMK__VALUE_CIB_UPDATE_CONFIRMATION "cib_update_confirmation"
#define PCMK__VALUE_CLUSTER                 "cluster"
#define PCMK__VALUE_CRMD                    "crmd"
#define PCMK__VALUE_EN                      "en"
#define PCMK__VALUE_EPOCH                   "epoch"
#define PCMK__VALUE_HEALTH_RED              "health_red"
#define PCMK__VALUE_HEALTH_YELLOW           "health_yellow"
#define PCMK__VALUE_INIT                    "init"
#define PCMK__VALUE_LOCAL                   "local"
#define PCMK__VALUE_LOST                    "lost"
#define PCMK__VALUE_LRMD                    "lrmd"
#define PCMK__VALUE_MAINT                   "maint"
#define PCMK__VALUE_OUTPUT                  "output"
#define PCMK__VALUE_PASSWORD                "password"
#define PCMK__VALUE_PRIMITIVE               "primitive"
#define PCMK__VALUE_REFRESH                 "refresh"
#define PCMK__VALUE_REQUEST                 "request"
#define PCMK__VALUE_RESPONSE                "response"
#define PCMK__VALUE_RSC_FAILED              "rsc-failed"
#define PCMK__VALUE_RSC_FAILURE_IGNORED     "rsc-failure-ignored"
#define PCMK__VALUE_RSC_MANAGED             "rsc-managed"
#define PCMK__VALUE_RSC_MULTIPLE            "rsc-multiple"
#define PCMK__VALUE_RSC_OK                  "rsc-ok"
#define PCMK__VALUE_RUNNING                 "running"
#define PCMK__VALUE_SCHEDULER               "scheduler"
#define PCMK__VALUE_SHUTDOWN_COMPLETE       "shutdown_complete"
#define PCMK__VALUE_SHUTTING_DOWN           "shutting_down"
#define PCMK__VALUE_ST_ASYNC_TIMEOUT_VALUE  "st-async-timeout-value"
#define PCMK__VALUE_ST_NOTIFY               "st_notify"
#define PCMK__VALUE_ST_NOTIFY_DISCONNECT    "st_notify_disconnect"
#define PCMK__VALUE_ST_NOTIFY_FENCE         "st_notify_fence"
#define PCMK__VALUE_ST_NOTIFY_HISTORY       "st_notify_history"
#define PCMK__VALUE_ST_NOTIFY_HISTORY_SYNCED    "st_notify_history_synced"
#define PCMK__VALUE_STARTING_DAEMONS        "starting_daemons"
#define PCMK__VALUE_STONITH_NG              "stonith-ng"
#define PCMK__VALUE_WAIT_FOR_PING           "wait_for_ping"
#define PCMK__VALUE_WARNING                 "warning"

/* @COMPAT Deprecated since 2.1.7 (used with PCMK__XA_ORDERING attribute of
 * resource sets)
 */
#define PCMK__VALUE_GROUP                   "group"

// @COMPAT Drop when daemon metadata commands are dropped
#define PCMK__VALUE_TIME                    "time"

#ifdef __cplusplus
}
#endif

#endif // PCMK__OPTIONS_INTERNAL__H
