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
#include <stdbool.h>                // false
#include <stddef.h>                 // NULL

#include <glib.h>                   // g_clear_pointer, g_main_loop_*

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
    srv->mainloop = g_main_loop_new(NULL, false);
    return pcmk_rc_ok;
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
