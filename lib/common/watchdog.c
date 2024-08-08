/*
 * Copyright 2013-2024 the Pacemaker project contributors
 *
 * The version control history for this file may have further details.
 *
 * This source code is licensed under the GNU Lesser General Public License
 * version 2.1 or later (LGPLv2.1+) WITHOUT ANY WARRANTY.
 */

#include <crm_internal.h>

#include <sched.h>
#include <sys/ioctl.h>
#include <sys/reboot.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <ctype.h>
#include <dirent.h>
#include <signal.h>

static pid_t sbd_pid = 0;

/*!
 * \internal
 * \brief Trigger a sysrq command if supported on current platform
 *
 * \param[in] t  Sysrq command to trigger
 */
static void
sysrq_trigger(char t)
{
#if HAVE_LINUX_PROCFS
    // Root can always write here, regardless of kernel.sysrq value
    FILE *procf = fopen("/proc/sysrq-trigger", "a");

    if (procf == NULL) {
        crm_warn("Could not open sysrq-trigger: %s", strerror(errno));
    } else {
        fprintf(procf, "%c\n", t);
        fclose(procf);
    }
#endif // HAVE_LINUX_PROCFS
}

/*!
 * \internal
 * \brief Tell pacemakerd to panic the local host
 *
 * \param[in] ppid  Process ID of parent process
 */
static void
panic_local_nonroot(pid_t ppid)
{
    if (ppid > 1) { // pacemakerd is still our parent
        crm_emerg("Escalating panic to " PCMK__SERVER_PACEMAKERD "[%lld]",
                  (long long) ppid);
    } else { // Signal (non-parent) pacemakerd if possible
#if HAVE_LINUX_PROCFS
        ppid = pcmk__procfs_pid_of(PCMK__SERVER_PACEMAKERD);
        if (ppid > 0) {
            union sigval signal_value;

            crm_emerg("Signaling " PCMK__SERVER_PACEMAKERD "[%lld] to panic",
                      (long long) ppid);
            memset(&signal_value, 0, sizeof(signal_value));
            if (sigqueue(ppid, SIGQUIT, signal_value) < 0) {
                crm_emerg("Exiting after signal failure: %s", strerror(errno));
            }
        } else {
#endif
            crm_emerg("Exiting with no known " PCMK__SERVER_PACEMAKERD
                      "process");
#if HAVE_LINUX_PROCFS
        }
#endif
    }
    crm_exit(CRM_EX_PANIC);
}

/*!
 * \internal
 * \brief Panic the local host (if root) or tell pacemakerd to do so
 */
static void
panic_local(void)
{
    const char *full_panic_action = pcmk__env_option(PCMK__ENV_PANIC_ACTION);
    const char *panic_action = full_panic_action;
    int reboot_cmd = RB_AUTOBOOT; // Default panic action is reboot

    if (geteuid() != 0) { // Non-root caller such as the controller
        panic_local_nonroot(getppid());
        return;
    }

    if (pcmk__starts_with(full_panic_action, "sync-")) {
        panic_action += sizeof("sync-") - 1;
        sync();
    }

    if (pcmk__str_empty(full_panic_action)
        || pcmk__str_eq(panic_action, "reboot", pcmk__str_none)) {
        sysrq_trigger('b');

    } else if (pcmk__str_eq(panic_action, "crash", pcmk__str_none)) {
        sysrq_trigger('c');

    } else if (pcmk__str_eq(panic_action, "off", pcmk__str_none)) {
        sysrq_trigger('o');
#ifdef RB_POWER_OFF
        reboot_cmd = RB_POWER_OFF;
#elif defined(RB_POWEROFF)
        reboot_cmd = RB_POWEROFF;
#endif
    } else {
        crm_warn("Using default 'reboot' for local option PCMK_"
                 PCMK__ENV_PANIC_ACTION " because '%s' is not a valid value",
                 full_panic_action);
        sysrq_trigger('b');
    }

    // sysrq failed or is not supported on this platform, so fall back to reboot
    reboot(reboot_cmd);

    // Even reboot failed, nothing left to do but exit
    crm_emerg("Exiting after reboot failed: %s", strerror(errno));
    if (getppid() > 1) { // pacemakerd is parent process
        crm_exit(CRM_EX_PANIC);
    } else { // This is pacemakerd, or an orphaned subdaemon
        crm_exit(CRM_EX_FATAL);
    }
}

/*!
 * \internal
 * \brief Tell sbd to kill the local host, then exit
 */
static void
panic_sbd(void)
{
    union sigval signal_value;
    pid_t ppid = getppid();

    crm_emerg("Signaling sbd[%lld] to panic", (long long) sbd_pid);

    memset(&signal_value, 0, sizeof(signal_value));
    /* TODO: Arrange for a slightly less brutal option? */
    if(sigqueue(sbd_pid, SIGKILL, signal_value) < 0) {
        crm_perror(LOG_EMERG, "Cannot signal sbd[%lld] to terminate",
                   (long long) sbd_pid);
        panic_local();
    }

    if(ppid > 1) {
        /* child daemon */
        crm_exit(CRM_EX_PANIC);
    } else {
        /* pacemakerd or orphan child */
        crm_exit(CRM_EX_FATAL);
    }
}

/*!
 * \internal
 * \brief Panic the local host
 *
 * Panic the local host either by sbd (if running), directly, or by asking
 * pacemakerd. If trace logging this function, exit instead.
 *
 * \param[in] origin   Function caller (for logging only)
 */
void
pcmk__panic(const char *origin)
{
    /* Ensure sbd_pid is set */
    (void) pcmk__locate_sbd();

    pcmk__if_tracing(
        {
            // getppid() == 1 means our original parent no longer exists
            crm_emerg("Shutting down instead of panicking the node "
                      QB_XS " origin=%s sbd=%lld parent=%d",
                      origin, (long long) sbd_pid, getppid());
            crm_exit(CRM_EX_FATAL);
            return;
        },
        {}
    );

    if(sbd_pid > 1) {
        crm_emerg("Signaling sbd[%lld] to panic the system: %s",
                  (long long) sbd_pid, origin);
        panic_sbd();

    } else {
        crm_emerg("Panicking the system directly: %s", origin);
        panic_local();
    }
}

/*!
 * \internal
 * \brief Return the process ID of sbd (or 0 if it is not running)
 */
pid_t
pcmk__locate_sbd(void)
{
    char *pidfile = NULL;
    char *sbd_path = NULL;
    int rc;

    if(sbd_pid > 1) {
        return sbd_pid;
    }

    /* Look for the pid file */
    pidfile = crm_strdup_printf(PCMK_RUN_DIR "/sbd.pid");
    sbd_path = crm_strdup_printf("%s/sbd", SBIN_DIR);

    /* Read the pid file */
    rc = pcmk__pidfile_matches(pidfile, 0, sbd_path, &sbd_pid);
    if (rc == pcmk_rc_ok) {
        crm_trace("SBD detected at pid %lld (via PID file %s)",
                  (long long) sbd_pid, pidfile);

#if HAVE_LINUX_PROCFS
    } else {
        /* Fall back to /proc for systems that support it */
        sbd_pid = pcmk__procfs_pid_of("sbd");
        crm_trace("SBD detected at pid %lld (via procfs)",
                  (long long) sbd_pid);
#endif // HAVE_LINUX_PROCFS
    }

    if(sbd_pid < 0) {
        sbd_pid = 0;
        crm_trace("SBD not detected");
    }

    free(pidfile);
    free(sbd_path);

    return sbd_pid;
}

long
pcmk__get_sbd_watchdog_timeout(void)
{
    static long sbd_timeout = -2;

    if (sbd_timeout == -2) {
        sbd_timeout = crm_get_msec(getenv("SBD_WATCHDOG_TIMEOUT"));
    }
    return sbd_timeout;
}

bool
pcmk__get_sbd_sync_resource_startup(void)
{
    static int sync_resource_startup = PCMK__SBD_SYNC_DEFAULT;
    static bool checked_sync_resource_startup = false;

    if (!checked_sync_resource_startup) {
        const char *sync_env = getenv("SBD_SYNC_RESOURCE_STARTUP");

        if (sync_env == NULL) {
            crm_trace("Defaulting to %sstart-up synchronization with sbd",
                      (PCMK__SBD_SYNC_DEFAULT? "" : "no "));

        } else if (crm_str_to_boolean(sync_env, &sync_resource_startup) < 0) {
            crm_warn("Defaulting to %sstart-up synchronization with sbd "
                     "because environment value '%s' is invalid",
                     (PCMK__SBD_SYNC_DEFAULT? "" : "no "), sync_env);
        }
        checked_sync_resource_startup = true;
    }
    return sync_resource_startup != 0;
}

long
pcmk__auto_stonith_watchdog_timeout(void)
{
    long sbd_timeout = pcmk__get_sbd_watchdog_timeout();

    return (sbd_timeout <= 0)? 0 : (2 * sbd_timeout);
}

bool
pcmk__valid_stonith_watchdog_timeout(const char *value)
{
    /* @COMPAT At a compatibility break, accept either negative values or a
     * specific string like "auto" (but not both) to mean "auto-calculate the
     * timeout." Reject other values that aren't parsable as timeouts.
     */
    long st_timeout = value? crm_get_msec(value) : 0;

    if (st_timeout < 0) {
        st_timeout = pcmk__auto_stonith_watchdog_timeout();
        crm_debug("Using calculated value %ld for "
                  PCMK_OPT_STONITH_WATCHDOG_TIMEOUT " (%s)",
                  st_timeout, value);
    }

    if (st_timeout == 0) {
        crm_debug("Watchdog may be enabled but "
                  PCMK_OPT_STONITH_WATCHDOG_TIMEOUT " is disabled (%s)",
                  value? value : "default");

    } else if (pcmk__locate_sbd() == 0) {
        crm_emerg("Shutting down: " PCMK_OPT_STONITH_WATCHDOG_TIMEOUT
                  " configured (%s) but SBD not active",
                  pcmk__s(value, "auto"));
        crm_exit(CRM_EX_FATAL);
        return false;

    } else {
        long sbd_timeout = pcmk__get_sbd_watchdog_timeout();

        if (st_timeout < sbd_timeout) {
            crm_emerg("Shutting down: " PCMK_OPT_STONITH_WATCHDOG_TIMEOUT
                      " (%s) too short (must be >%ldms)",
                      value, sbd_timeout);
            crm_exit(CRM_EX_FATAL);
            return false;
        }
        crm_info("Watchdog configured with " PCMK_OPT_STONITH_WATCHDOG_TIMEOUT
                 " %s and SBD timeout %ldms",
                 value, sbd_timeout);
    }
    return true;
}
