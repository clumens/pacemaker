/*
 * Copyright 2026 the Pacemaker project contributors
 *
 * The version control history for this file may have further details.
 *
 * This source code is licensed under the GNU Lesser General Public License
 * version 2.1 or later (LGPLv2.1+) WITHOUT ANY WARRANTY.
 */

#include <crm_internal.h>

#include <signal.h>                 // SIG*
#include <stddef.h>                 // NULL
#include <stdbool.h>                // bool, false, true
#include <time.h>                   // time

#include <glib.h>                   // g_clear_pointer, g_main_loop_*

#include <crm/common/ipc.h>         // crm_ipc_*, pcmk_ipc_api_t, pcmk_*_ipc_api
#include <crm/common/logging.h>     // CRM_CHECK
#include <crm/common/results.h>     // CRM_EX_*, crm_exit, pcmk_rc_*

/*!
 * \internal
 * \brief Initialize a previously allocated daemon object
 *
 * \param[in,out] srv The daemon object
 *
 * \return Standard Pacemaker return code
 */
int
pcmk__daemon_init(pcmk__daemon_t *srv)
{
    srv->start_time = time(NULL);

    srv->mainloop = g_main_loop_new(NULL, false);
    return pcmk_rc_ok;
}

/*!
 * \internal
 * \brief Determine if an instance of an IPC server is already running
 *
 * \param[in,out] srv The daemon object
 *
 * \return \c true if an instance of \p srv is already running, and \c false if not
 *
 * \note This function can be used to determine if a daemon is up and running
 *       since all daemons use IPC.
 *
 * \note This function only works for those daemons that have been converted
 *       to use \c pcmk_ipc_api_t as the client interface.  Older daemons will
 *       have to use their own daemon specific method to figure this out.
 */
bool
pcmk__daemon_ipc_running(pcmk__daemon_t *srv)
{
    pcmk_ipc_api_t *old_instance = NULL;
    int rc = pcmk_rc_ok;

    rc = pcmk_new_ipc_api(&old_instance, srv->type);
    if (rc != pcmk_rc_ok) {
        return false;
    }

    rc = pcmk__connect_ipc(old_instance, pcmk_ipc_dispatch_sync, 2);
    if (rc != pcmk_rc_ok) {
        pcmk__debug("No existing %s instance found: %s",
                    pcmk_ipc_name(old_instance, true), pcmk_rc_str(rc));
        pcmk_free_ipc_api(old_instance);
        return false;
    }

    pcmk_disconnect_ipc(old_instance);
    pcmk_free_ipc_api(old_instance);
    return true;
}

/*!
 * \internal
 * \brief Quit the daemon's main loop
 *
 * \param[in,out] srv  The daemon object
 * \param[in]     ec   The exit code to assign to the daemon
 */
void
pcmk__daemon_quit(pcmk__daemon_t *srv, crm_exit_t ec)
{
    if (srv->shutting_down) {
        return;
    }

    if ((srv->fns != NULL) && (srv->fns->quit != NULL)) {
        if (!srv->fns->quit(srv)) {
            return;
        }
    }

    pcmk__info("Shutting down %s", pcmk__server_log_name(srv->type));

    // Tell various functions not to do anything
    srv->shutting_down = true;

    srv->ec = ec;

    // Don't respond to signals while shutting down
    mainloop_destroy_signal(SIGTERM);
    mainloop_destroy_signal(SIGCHLD);
    mainloop_destroy_signal(SIGPIPE);
    mainloop_destroy_signal(SIGUSR1);
    mainloop_destroy_signal(SIGUSR2);
    mainloop_destroy_signal(SIGTRAP);

    CRM_CHECK((srv->mainloop != NULL) && g_main_loop_is_running(srv->mainloop),
              return);

    g_main_loop_quit(srv->mainloop);
}

/*!
 * \internal
 * \brief Run a daemon
 *
 * \param[in,out] srv The daemon object
 */
void
pcmk__daemon_run(pcmk__daemon_t *srv)
{
    pcmk__notice("Pacemaker %s successfully started and accepting connections",
                 pcmk__server_log_name(srv->type));
    g_main_loop_run(srv->mainloop);
    g_clear_pointer(&srv->mainloop, g_main_loop_unref);
}

/*!
 * \internal
 * \brief Determine if an instance of an IPC server is already running
 *
 * \param[in,out] srv The daemon object
 *
 * \return \c true if an instance of \p srv is already running, and \c false if not
 *
 * \note This function only works for older daemons that have not yet been
 *       converted to use the \c pcmk_ipc_api_t client interface.  Once all have
 *       been updated, this function can be removed.
 */
bool
pcmk__generic_ipc_running(pcmk__daemon_t *srv)
{
    const char *ipc_name = pcmk__server_ipc_name(srv->type);
    crm_ipc_t *old_instance = NULL;
    int rc = pcmk_rc_ok;

    old_instance = crm_ipc_new(ipc_name, 0);
    if (old_instance == NULL) {
        /* This is an error - memory allocation failed, etc. - but crm_ipc_new
         * will have already logged an error message.
         */
        return false;
    }

    rc = pcmk__connect_generic_ipc(old_instance);
    if (rc != pcmk_rc_ok) {
        pcmk__debug("No existing %s instance found: %s", ipc_name,
                    pcmk_rc_str(rc));
        crm_ipc_destroy(old_instance);
        return false;
    }

    crm_ipc_close(old_instance);
    crm_ipc_destroy(old_instance);
    return true;
}
