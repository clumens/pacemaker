/*
 * Copyright 2004-2020 the Pacemaker project contributors
 *
 * The version control history for this file may have further details.
 *
 * This source code is licensed under the GNU Lesser General Public License
 * version 2.1 or later (LGPLv2.1+) WITHOUT ANY WARRANTY.
 */

#include <crm_internal.h>
#include <bzlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#include <crm/common/ipc.h>
#include <crm/cluster/internal.h>
#include <crm/common/mainloop.h>
#include <sys/utsname.h>

#include <qb/qbipcc.h>
#include <qb/qbutil.h>

#include <corosync/corodefs.h>
#include <corosync/corotypes.h>
#include <corosync/hdb.h>
#include <corosync/cpg.h>

#include <crm/msg_xml.h>

#include <crm/common/ipc_internal.h>  /* PCMK__SPECIAL_PID* */
#include "crmcluster_private.h"

cpg_handle_t pcmk_cpg_handle = 0; /* TODO: Remove, use cluster.cpg_handle */

static bool cpg_evicted = FALSE;

static void crm_cs_flush(gpointer data);

#define cs_repeat(counter, max, code) do {		\
	code;						\
	if(rc == CS_ERR_TRY_AGAIN || rc == CS_ERR_QUEUE_FULL) {  \
	    counter++;					\
	    crm_debug("Retrying operation after %ds", counter);	\
	    sleep(counter);				\
	} else {                                        \
            break;                                      \
        }                                               \
    } while(counter < max)

void
cluster_disconnect_cpg(crm_cluster_t *cluster)
{
    pcmk_cpg_handle = 0;
    if (cluster->cpg_handle) {
        crm_trace("Disconnecting CPG");
        cpg_leave(cluster->cpg_handle, &cluster->group);
        cpg_finalize(cluster->cpg_handle);
        cluster->cpg_handle = 0;

    } else {
        crm_info("No CPG connection");
    }
}

uint32_t get_local_nodeid(cpg_handle_t handle)
{
    cs_error_t rc = CS_OK;
    int retries = 0;
    static uint32_t local_nodeid = 0;
    cpg_handle_t local_handle = handle;
    cpg_callbacks_t cb = { };
    int fd = -1;
    uid_t found_uid = 0;
    gid_t found_gid = 0;
    pid_t found_pid = 0;
    int rv;

    if(local_nodeid != 0) {
        return local_nodeid;
    }

    if(handle == 0) {
        crm_trace("Creating connection");
        cs_repeat(retries, 5, rc = cpg_initialize(&local_handle, &cb));
        if (rc != CS_OK) {
            crm_err("Could not connect to the CPG API: %s (%d)",
                    cs_strerror(rc), rc);
            return 0;
        }

        rc = cpg_fd_get(local_handle, &fd);
        if (rc != CS_OK) {
            crm_err("Could not obtain the CPG API connection: %s (%d)",
                    cs_strerror(rc), rc);
            goto bail;
        }

        /* CPG provider run as root (in given user namespace, anyway)? */
        if (!(rv = crm_ipc_is_authentic_process(fd, (uid_t) 0,(gid_t) 0, &found_pid,
                                                &found_uid, &found_gid))) {
            crm_err("CPG provider is not authentic:"
                    " process %lld (uid: %lld, gid: %lld)",
                    (long long) PCMK__SPECIAL_PID_AS_0(found_pid),
                    (long long) found_uid, (long long) found_gid);
            goto bail;
        } else if (rv < 0) {
            crm_err("Could not verify authenticity of CPG provider: %s (%d)",
                    strerror(-rv), -rv);
            goto bail;
        }
    }

    if (rc == CS_OK) {
        retries = 0;
        crm_trace("Performing lookup");
        cs_repeat(retries, 5, rc = cpg_local_get(local_handle, &local_nodeid));
    }

    if (rc != CS_OK) {
        crm_err("Could not get local node id from the CPG API: %s (%d)", ais_error2text(rc), rc);
    }

bail:
    if(handle == 0) {
        crm_trace("Closing connection");
        cpg_finalize(local_handle);
    }
    crm_debug("Local nodeid is %u", local_nodeid);
    return local_nodeid;
}


GListPtr cs_message_queue = NULL;
int cs_message_timer = 0;

static gboolean
crm_cs_flush_cb(gpointer data)
{
    cs_message_timer = 0;
    crm_cs_flush(data);
    return FALSE;
}

// Send no more than this many CPG messages in one flush
#define CS_SEND_MAX 200

/*!
 * \internal
 * \brief Send messages in Corosync CPG message queue
 *
 * \param[in] data   CPG handle
 */
static void
crm_cs_flush(gpointer data)
{
    unsigned int sent = 0;
    guint queue_len = 0;
    cs_error_t rc = 0;
    cpg_handle_t *handle = (cpg_handle_t *) data;

    if (*handle == 0) {
        crm_trace("Connection is dead");
        return;
    }

    queue_len = g_list_length(cs_message_queue);
    if (((queue_len % 1000) == 0) && (queue_len > 1)) {
        crm_err("CPG queue has grown to %d", queue_len);

    } else if (queue_len == CS_SEND_MAX) {
        crm_warn("CPG queue has grown to %d", queue_len);
    }

    if (cs_message_timer != 0) {
        /* There is already a timer, wait until it goes off */
        crm_trace("Timer active %d", cs_message_timer);
        return;
    }

    while ((cs_message_queue != NULL) && (sent < CS_SEND_MAX)) {
        struct iovec *iov = cs_message_queue->data;

        rc = cpg_mcast_joined(*handle, CPG_TYPE_AGREED, iov, 1);
        if (rc != CS_OK) {
            break;
        }

        sent++;
        crm_trace("CPG message sent, size=%llu",
                  (unsigned long long) iov->iov_len);

        cs_message_queue = g_list_remove(cs_message_queue, iov);
        free(iov->iov_base);
        free(iov);
    }

    queue_len -= sent;
    if ((sent > 1) || (cs_message_queue != NULL)) {
        crm_info("Sent %u CPG messages  (%d remaining): %s (%d)",
                 sent, queue_len, ais_error2text(rc), (int) rc);
    } else {
        crm_trace("Sent %u CPG messages  (%d remaining): %s (%d)",
                  sent, queue_len, ais_error2text(rc), (int) rc);
    }

    if (cs_message_queue) {
        uint32_t delay_ms = 100;
        if (rc != CS_OK) {
            /* Proportionally more if sending failed but cap at 1s */
            delay_ms = QB_MIN(1000, CS_SEND_MAX + (10 * queue_len));
        }
        cs_message_timer = g_timeout_add(delay_ms, crm_cs_flush_cb, data);
    }
}

static int
pcmk_cpg_dispatch(gpointer user_data)
{
    int rc = 0;
    crm_cluster_t *cluster = (crm_cluster_t*) user_data;

    rc = cpg_dispatch(cluster->cpg_handle, CS_DISPATCH_ONE);
    if (rc != CS_OK) {
        crm_err("Connection to the CPG API failed: %s (%d)", ais_error2text(rc), rc);
        cpg_finalize(cluster->cpg_handle);
        cluster->cpg_handle = 0;
        return -1;

    } else if(cpg_evicted) {
        crm_err("Evicted from CPG membership");
        return -1;
    }
    return 0;
}

static gboolean
check_message_sanity(const AIS_Message *msg)
{
    gboolean sane = TRUE;
    int dest = msg->host.type;
    int tmp_size = msg->header.size - sizeof(AIS_Message);

    if (sane && msg->header.size == 0) {
        crm_warn("Message with no size");
        sane = FALSE;
    }

    if (sane && msg->header.error != CS_OK) {
        crm_warn("Message header contains an error: %d", msg->header.error);
        sane = FALSE;
    }

    if (sane && ais_data_len(msg) != tmp_size) {
        crm_warn("Message payload size is incorrect: expected %d, got %d", ais_data_len(msg),
                 tmp_size);
        sane = FALSE;
    }

    if (sane && ais_data_len(msg) == 0) {
        crm_warn("Message with no payload");
        sane = FALSE;
    }

    if (sane && !msg->is_compressed && (msg->size > 0)) {
        size_t str_size = strlen(msg->data) + 1;

        if (msg->size != str_size) {
            crm_warn("Message payload is corrupted: expected %llu bytes, got %llu",
                     (unsigned long long) msg->size,
                     (unsigned long long) str_size);
            sane = FALSE;
        }
    }

    if (sane == FALSE) {
        crm_err("Invalid message %d: (dest=%s:%s, from=%s:%s.%u, compressed=%d, size=%d, total=%d)",
                msg->id, ais_dest(&(msg->host)), msg_type2text(dest),
                ais_dest(&(msg->sender)), msg_type2text(msg->sender.type),
                msg->sender.pid, msg->is_compressed, ais_data_len(msg), msg->header.size);

    } else {
        crm_trace
            ("Verified message %d: (dest=%s:%s, from=%s:%s.%u, compressed=%d, size=%d, total=%d)",
             msg->id, ais_dest(&(msg->host)), msg_type2text(dest), ais_dest(&(msg->sender)),
             msg_type2text(msg->sender.type), msg->sender.pid, msg->is_compressed,
             ais_data_len(msg), msg->header.size);
    }

    return sane;
}

char *
pcmk_message_common_cs(cpg_handle_t handle, uint32_t nodeid, uint32_t pid, void *content,
                        uint32_t *kind, const char **from)
{
    char *data = NULL;
    AIS_Message *msg = (AIS_Message *) content;

    if(handle) {
        // Do filtering and field massaging
        uint32_t local_nodeid = get_local_nodeid(handle);
        const char *local_name = get_local_node_name();

        if (msg->sender.id > 0 && msg->sender.id != nodeid) {
            crm_err("Nodeid mismatch from %d.%d: claimed nodeid=%u", nodeid, pid, msg->sender.id);
            return NULL;

        } else if (msg->host.id != 0 && (local_nodeid != msg->host.id)) {
            /* Not for us */
            crm_trace("Not for us: %u != %u", msg->host.id, local_nodeid);
            return NULL;
        } else if (msg->host.size != 0 && !pcmk__str_eq(msg->host.uname, local_name, pcmk__str_casei)) {
            /* Not for us */
            crm_trace("Not for us: %s != %s", msg->host.uname, local_name);
            return NULL;
        }

        msg->sender.id = nodeid;
        if (msg->sender.size == 0) {
            crm_node_t *peer = crm_get_peer(nodeid, NULL);

            if (peer == NULL) {
                crm_err("Peer with nodeid=%u is unknown", nodeid);

            } else if (peer->uname == NULL) {
                crm_err("No uname for peer with nodeid=%u", nodeid);

            } else {
                crm_notice("Fixing uname for peer with nodeid=%u", nodeid);
                msg->sender.size = strlen(peer->uname);
                memset(msg->sender.uname, 0, MAX_NAME);
                memcpy(msg->sender.uname, peer->uname, msg->sender.size);
            }
        }
    }

    crm_trace("Got new%s message (size=%d, %d, %d)",
              msg->is_compressed ? " compressed" : "",
              ais_data_len(msg), msg->size, msg->compressed_size);

    if (kind != NULL) {
        *kind = msg->header.id;
    }
    if (from != NULL) {
        *from = msg->sender.uname;
    }

    if (msg->is_compressed && msg->size > 0) {
        int rc = BZ_OK;
        char *uncompressed = NULL;
        unsigned int new_size = msg->size + 1;

        if (!check_message_sanity(msg)) {
            goto badmsg;
        }

        crm_trace("Decompressing message data");
        uncompressed = calloc(1, new_size);
        rc = BZ2_bzBuffToBuffDecompress(uncompressed, &new_size, msg->data, msg->compressed_size, 1, 0);

        if (rc != BZ_OK) {
            crm_err("Decompression failed: %s " CRM_XS " bzerror=%d",
                    bz2_strerror(rc), rc);
            free(uncompressed);
            goto badmsg;
        }

        CRM_ASSERT(rc == BZ_OK);
        CRM_ASSERT(new_size == msg->size);

        data = uncompressed;

    } else if (!check_message_sanity(msg)) {
        goto badmsg;

    } else {
        data = strdup(msg->data);
    }

    // Is this necessary?
    crm_get_peer(msg->sender.id, msg->sender.uname);

    crm_trace("Payload: %.200s", data);
    return data;

  badmsg:
    crm_err("Invalid message (id=%d, dest=%s:%s, from=%s:%s.%d):"
            " min=%d, total=%d, size=%d, bz2_size=%d",
            msg->id, ais_dest(&(msg->host)), msg_type2text(msg->host.type),
            ais_dest(&(msg->sender)), msg_type2text(msg->sender.type),
            msg->sender.pid, (int)sizeof(AIS_Message),
            msg->header.size, msg->size, msg->compressed_size);

    free(data);
    return NULL;
}

static int cmp_member_list_nodeid(const void *first,
                                  const void *second)
{
    const struct cpg_address *const a = *((const struct cpg_address **) first),
                             *const b = *((const struct cpg_address **) second);
    if (a->nodeid < b->nodeid) {
        return -1;
    } else if (a->nodeid > b->nodeid) {
        return 1;
    }
    /* don't bother with "reason" nor "pid" */
    return 0;
}

static const char *
cpgreason2str(cpg_reason_t reason)
{
    switch (reason) {
        case CPG_REASON_JOIN:       return " via cpg_join";
        case CPG_REASON_LEAVE:      return " via cpg_leave";
        case CPG_REASON_NODEDOWN:   return " via cluster exit";
        case CPG_REASON_NODEUP:     return " via cluster join";
        case CPG_REASON_PROCDOWN:   return " for unknown reason";
        default:                    break;
    }
    return "";
}

static inline const char *
peer_name(crm_node_t *peer)
{
    if (peer == NULL) {
        return "unknown node";
    } else if (peer->uname == NULL) {
        return "peer node";
    } else {
        return peer->uname;
    }
}

void
pcmk_cpg_membership(cpg_handle_t handle,
                    const struct cpg_name *groupName,
                    const struct cpg_address *member_list, size_t member_list_entries,
                    const struct cpg_address *left_list, size_t left_list_entries,
                    const struct cpg_address *joined_list, size_t joined_list_entries)
{
    int i;
    gboolean found = FALSE;
    static int counter = 0;
    uint32_t local_nodeid = get_local_nodeid(handle);
    const struct cpg_address *key, **sorted;

    sorted = malloc(member_list_entries * sizeof(const struct cpg_address *));
    CRM_ASSERT(sorted != NULL);

    for (size_t iter = 0; iter < member_list_entries; iter++) {
        sorted[iter] = member_list + iter;
    }
    /* so that the cross-matching multiply-subscribed nodes is then cheap */
    qsort(sorted, member_list_entries, sizeof(const struct cpg_address *),
          cmp_member_list_nodeid);

    for (i = 0; i < left_list_entries; i++) {
        crm_node_t *peer = crm_find_peer(left_list[i].nodeid, NULL);
        const struct cpg_address **rival = NULL;

        /* in CPG world, NODE:PROCESS-IN-MEMBERSHIP-OF-G is an 1:N relation
           and not playing by this rule may go wild in case of multiple
           residual instances of the same pacemaker daemon at the same node
           -- we must ensure that the possible local rival(s) won't make us
           cry out and bail (e.g. when they quit themselves), since all the
           surrounding logic denies this simple fact that the full membership
           is discriminated also per the PID of the process beside mere node
           ID (and implicitly, group ID); practically, this will be sound in
           terms of not preventing progress, since all the CPG joiners are
           also API end-point carriers, and that's what matters locally
           (who's the winner);
           remotely, we will just compare leave_list and member_list and if
           the left process has its node retained in member_list (under some
           other PID, anyway) we will just ignore it as well
           XXX: long-term fix is to establish in-out PID-aware tracking? */
        if (peer) {
            key = &left_list[i];
            rival = bsearch(&key, sorted, member_list_entries,
                            sizeof(const struct cpg_address *),
                            cmp_member_list_nodeid);
        }

        if (rival == NULL) {
            crm_info("Group %s event %d: %s (node %u pid %u) left%s",
                     groupName->value, counter, peer_name(peer),
                     left_list[i].nodeid, left_list[i].pid,
                     cpgreason2str(left_list[i].reason));
            if (peer) {
                crm_update_peer_proc(__func__, peer, crm_proc_cpg,
                                     OFFLINESTATUS);
            }
        } else if (left_list[i].nodeid == local_nodeid) {
            crm_warn("Group %s event %d: duplicate local pid %u left%s",
                     groupName->value, counter,
                     left_list[i].pid, cpgreason2str(left_list[i].reason));
        } else {
            crm_warn("Group %s event %d: "
                     "%s (node %u) duplicate pid %u left%s (%u remains)",
                     groupName->value, counter, peer_name(peer),
                     left_list[i].nodeid, left_list[i].pid,
                     cpgreason2str(left_list[i].reason), (*rival)->pid);
        }
    }
    free(sorted);
    sorted = NULL;

    for (i = 0; i < joined_list_entries; i++) {
        crm_info("Group %s event %d: node %u pid %u joined%s",
                 groupName->value, counter, joined_list[i].nodeid,
                 joined_list[i].pid, cpgreason2str(joined_list[i].reason));
    }

    for (i = 0; i < member_list_entries; i++) {
        crm_node_t *peer = crm_get_peer(member_list[i].nodeid, NULL);

        if (member_list[i].nodeid == local_nodeid
                && member_list[i].pid != getpid()) {
            /* see the note above */
            crm_warn("Group %s event %d: detected duplicate local pid %u",
                     groupName->value, counter, member_list[i].pid);
            continue;
        }
        crm_info("Group %s event %d: %s (node %u pid %u) is member",
                 groupName->value, counter, peer_name(peer),
                 member_list[i].nodeid, member_list[i].pid);

        /* If the caller left auto-reaping enabled, this will also update the
         * state to member.
         */
        peer = crm_update_peer_proc(__func__, peer, crm_proc_cpg,
                                    ONLINESTATUS);

        if (peer && peer->state && strcmp(peer->state, CRM_NODE_MEMBER)) {
            /* The node is a CPG member, but we currently think it's not a
             * cluster member. This is possible only if auto-reaping was
             * disabled. The node may be joining, and we happened to get the CPG
             * notification before the quorum notification; or the node may have
             * just died, and we are processing its final messages; or a bug
             * has affected the peer cache.
             */
            time_t now = time(NULL);

            if (peer->when_lost == 0) {
                // Track when we first got into this contradictory state
                peer->when_lost = now;

            } else if (now > (peer->when_lost + 60)) {
                // If it persists for more than a minute, update the state
                crm_warn("Node %u is member of group %s but was believed offline",
                         member_list[i].nodeid, groupName->value);
                crm_update_peer_state(__func__, peer, CRM_NODE_MEMBER, 0);
            }
        }

        if (local_nodeid == member_list[i].nodeid) {
            found = TRUE;
        }
    }

    if (!found) {
        crm_err("Local node was evicted from group %s", groupName->value);
        cpg_evicted = TRUE;
    }

    counter++;
}

gboolean
cluster_connect_cpg(crm_cluster_t *cluster)
{
    cs_error_t rc;
    int fd = -1;
    int retries = 0;
    uint32_t id = 0;
    crm_node_t *peer = NULL;
    cpg_handle_t handle = 0;
    const char *message_name = pcmk__message_name(crm_system_name);
    uid_t found_uid = 0;
    gid_t found_gid = 0;
    pid_t found_pid = 0;
    int rv;

    struct mainloop_fd_callbacks cpg_fd_callbacks = {
        .dispatch = pcmk_cpg_dispatch,
        .destroy = cluster->destroy,
    };

    cpg_callbacks_t cpg_callbacks = {
        .cpg_deliver_fn = cluster->cpg.cpg_deliver_fn,
        .cpg_confchg_fn = cluster->cpg.cpg_confchg_fn,
        /* .cpg_deliver_fn = pcmk_cpg_deliver, */
        /* .cpg_confchg_fn = pcmk_cpg_membership, */
    };

    cpg_evicted = FALSE;
    cluster->group.length = 0;
    cluster->group.value[0] = 0;

    /* group.value is char[128] */
    strncpy(cluster->group.value, message_name, 127);
    cluster->group.value[127] = 0;
    cluster->group.length = 1 + QB_MIN(127, strlen(cluster->group.value));

    cs_repeat(retries, 30, rc = cpg_initialize(&handle, &cpg_callbacks));
    if (rc != CS_OK) {
        crm_err("Could not connect to the CPG API: %s (%d)",
                cs_strerror(rc), rc);
        goto bail;
    }

    rc = cpg_fd_get(handle, &fd);
    if (rc != CS_OK) {
        crm_err("Could not obtain the CPG API connection: %s (%d)",
                cs_strerror(rc), rc);
        goto bail;
    }

    /* CPG provider run as root (in given user namespace, anyway)? */
    if (!(rv = crm_ipc_is_authentic_process(fd, (uid_t) 0,(gid_t) 0, &found_pid,
                                            &found_uid, &found_gid))) {
        crm_err("CPG provider is not authentic:"
                " process %lld (uid: %lld, gid: %lld)",
                (long long) PCMK__SPECIAL_PID_AS_0(found_pid),
                (long long) found_uid, (long long) found_gid);
        rc = CS_ERR_ACCESS;
        goto bail;
    } else if (rv < 0) {
        crm_err("Could not verify authenticity of CPG provider: %s (%d)",
                strerror(-rv), -rv);
        rc = CS_ERR_ACCESS;
        goto bail;
    }

    id = get_local_nodeid(handle);
    if (id == 0) {
        crm_err("Could not get local node id from the CPG API");
        goto bail;

    }
    cluster->nodeid = id;

    retries = 0;
    cs_repeat(retries, 30, rc = cpg_join(handle, &cluster->group));
    if (rc != CS_OK) {
        crm_err("Could not join the CPG group '%s': %d", message_name, rc);
        goto bail;
    }

    pcmk_cpg_handle = handle;
    cluster->cpg_handle = handle;
    mainloop_add_fd("corosync-cpg", G_PRIORITY_MEDIUM, fd, cluster, &cpg_fd_callbacks);

  bail:
    if (rc != CS_OK) {
        cpg_finalize(handle);
        return FALSE;
    }

    peer = crm_get_peer(id, NULL);
    crm_update_peer_proc(__func__, peer, crm_proc_cpg, ONLINESTATUS);
    return TRUE;
}

gboolean
pcmk__cpg_send_xml(xmlNode *msg, crm_node_t *node, enum crm_ais_msg_types dest)
{
    gboolean rc = TRUE;
    char *data = NULL;

    data = dump_xml_unformatted(msg);
    rc = send_cluster_text(crm_class_cluster, data, FALSE, node, dest);
    free(data);
    return rc;
}

gboolean
send_cluster_text(enum crm_ais_msg_class msg_class, const char *data,
                  gboolean local, crm_node_t *node, enum crm_ais_msg_types dest)
{
    static int msg_id = 0;
    static int local_pid = 0;
    static int local_name_len = 0;
    static const char *local_name = NULL;

    char *target = NULL;
    struct iovec *iov;
    AIS_Message *msg = NULL;
    enum crm_ais_msg_types sender = text2msg_type(crm_system_name);

    switch (msg_class) {
        case crm_class_cluster:
            break;
        default:
            crm_err("Invalid message class: %d", msg_class);
            return FALSE;
    }

    CRM_CHECK(dest != crm_msg_ais, return FALSE);

    if(local_name == NULL) {
        local_name = get_local_node_name();
    }
    if(local_name_len == 0 && local_name) {
        local_name_len = strlen(local_name);
    }

    if (data == NULL) {
        data = "";
    }

    if (local_pid == 0) {
        local_pid = getpid();
    }

    if (sender == crm_msg_none) {
        sender = local_pid;
    }

    msg = calloc(1, sizeof(AIS_Message));

    msg_id++;
    msg->id = msg_id;
    msg->header.id = msg_class;
    msg->header.error = CS_OK;

    msg->host.type = dest;
    msg->host.local = local;

    if (node) {
        if (node->uname) {
            target = strdup(node->uname);
            msg->host.size = strlen(node->uname);
            memset(msg->host.uname, 0, MAX_NAME);
            memcpy(msg->host.uname, node->uname, msg->host.size);
        } else {
            target = crm_strdup_printf("%u", node->id);
        }
        msg->host.id = node->id;
    } else {
        target = strdup("all");
    }

    msg->sender.id = 0;
    msg->sender.type = sender;
    msg->sender.pid = local_pid;
    msg->sender.size = local_name_len;
    memset(msg->sender.uname, 0, MAX_NAME);
    if(local_name && msg->sender.size) {
        memcpy(msg->sender.uname, local_name, msg->sender.size);
    }

    msg->size = 1 + strlen(data);
    msg->header.size = sizeof(AIS_Message) + msg->size;

    if (msg->size < CRM_BZ2_THRESHOLD) {
        msg = pcmk__realloc(msg, msg->header.size);
        memcpy(msg->data, data, msg->size);

    } else {
        char *compressed = NULL;
        unsigned int new_size = 0;
        char *uncompressed = strdup(data);

        if (pcmk__compress(uncompressed, (unsigned int) msg->size, 0,
                           &compressed, &new_size) == pcmk_rc_ok) {

            msg->header.size = sizeof(AIS_Message) + new_size;
            msg = pcmk__realloc(msg, msg->header.size);
            memcpy(msg->data, compressed, new_size);

            msg->is_compressed = TRUE;
            msg->compressed_size = new_size;

        } else {
            // cppcheck seems not to understand the abort logic in pcmk__realloc
            // cppcheck-suppress memleak
            msg = pcmk__realloc(msg, msg->header.size);
            memcpy(msg->data, data, msg->size);
        }

        free(uncompressed);
        free(compressed);
    }

    iov = calloc(1, sizeof(struct iovec));
    iov->iov_base = msg;
    iov->iov_len = msg->header.size;

    if (msg->compressed_size) {
        crm_trace("Queueing CPG message %u to %s (%llu bytes, %d bytes compressed payload): %.200s",
                  msg->id, target, (unsigned long long) iov->iov_len,
                  msg->compressed_size, data);
    } else {
        crm_trace("Queueing CPG message %u to %s (%llu bytes, %d bytes payload): %.200s",
                  msg->id, target, (unsigned long long) iov->iov_len,
                  msg->size, data);
    }
    free(target);

    cs_message_queue = g_list_append(cs_message_queue, iov);
    crm_cs_flush(&pcmk_cpg_handle);

    return TRUE;
}

enum crm_ais_msg_types
text2msg_type(const char *text)
{
    int type = crm_msg_none;

    CRM_CHECK(text != NULL, return type);
    text = pcmk__message_name(text);
    if (pcmk__str_eq(text, "ais", pcmk__str_casei)) {
        type = crm_msg_ais;
    } else if (pcmk__str_eq(text, CRM_SYSTEM_CIB, pcmk__str_casei)) {
        type = crm_msg_cib;
    } else if (pcmk__strcase_any_of(text, CRM_SYSTEM_CRMD, CRM_SYSTEM_DC, NULL)) {
        type = crm_msg_crmd;
    } else if (pcmk__str_eq(text, CRM_SYSTEM_TENGINE, pcmk__str_casei)) {
        type = crm_msg_te;
    } else if (pcmk__str_eq(text, CRM_SYSTEM_PENGINE, pcmk__str_casei)) {
        type = crm_msg_pe;
    } else if (pcmk__str_eq(text, CRM_SYSTEM_LRMD, pcmk__str_casei)) {
        type = crm_msg_lrmd;
    } else if (pcmk__str_eq(text, CRM_SYSTEM_STONITHD, pcmk__str_casei)) {
        type = crm_msg_stonithd;
    } else if (pcmk__str_eq(text, "stonith-ng", pcmk__str_casei)) {
        type = crm_msg_stonith_ng;
    } else if (pcmk__str_eq(text, "attrd", pcmk__str_casei)) {
        type = crm_msg_attrd;

    } else {
        /* This will normally be a transient client rather than
         * a cluster daemon.  Set the type to the pid of the client
         */
        int scan_rc = sscanf(text, "%d", &type);

        if (scan_rc != 1 || type <= crm_msg_stonith_ng) {
            /* Ensure it's sane */
            type = crm_msg_none;
        }
    }
    return type;
}
