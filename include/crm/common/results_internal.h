/*
 * Copyright 2020-2024 the Pacemaker project contributors
 *
 * The version control history for this file may have further details.
 *
 * This source code is licensed under the GNU Lesser General Public License
 * version 2.1 or later (LGPLv2.1+) WITHOUT ANY WARRANTY.
 */

#ifndef PCMK__COMMON_RESULTS_INTERNAL__H
#define PCMK__COMMON_RESULTS_INTERNAL__H

#include <glib.h>               // GQuark

extern const size_t pcmk__n_rc;

int pcmk__result_bounds(enum pcmk_result_type, int *lower, int *upper);

_Noreturn void pcmk__abort_as(const char *file, const char *function, int line,
                              const char *assert_condition);

#define pcmk__assert(expr) do {                                     \
        if (!(expr)) {                                              \
            pcmk__abort_as(__FILE__, __func__, __LINE__, #expr);    \
        }                                                           \
    } while(0)

/*!
 * \internal
 * \brief Abort without dumping core if a pointer is \c NULL
 *
 * This is intended to check for memory allocation failure, rather than for null
 * pointers in general.
 *
 * \param[in] ptr  Pointer to check
 */
#define pcmk__mem_assert(ptr) do {                                          \
        if ((ptr) == NULL) {                                                \
            crm_abort(__FILE__, __func__, __LINE__, "Out of memory", FALSE, \
                      TRUE);                                                \
            crm_exit(CRM_EX_OSERR);                                         \
        }                                                                   \
    } while (0)

/* Error domains for use with g_set_error */

GQuark pcmk__rc_error_quark(void);
GQuark pcmk__exitc_error_quark(void);

#define PCMK__RC_ERROR       pcmk__rc_error_quark()
#define PCMK__EXITC_ERROR    pcmk__exitc_error_quark()

/* Action results */

typedef struct {
    int exit_status;        // Child exit status
    enum pcmk_exec_status execution_status; // Execution status
    char *exit_reason;      // Brief, human-friendly explanation
    char *action_stdout;    // Action output
    char *action_stderr;    // Action error output
} pcmk__action_result_t;

/*!
 * \internal
 * \brief Static initialization for an action result
 *
 * \note Importantly, this ensures pcmk__reset_result() won't try to free
 *       garbage.
 */
#define PCMK__UNKNOWN_RESULT {                  \
        .exit_status = CRM_EX_OK,               \
        .execution_status = PCMK_EXEC_UNKNOWN,  \
        .exit_reason = NULL,                    \
        .action_stdout = NULL,                  \
        .action_stderr = NULL,                  \
    }

void pcmk__set_result(pcmk__action_result_t *result, int exit_status,
                      enum pcmk_exec_status exec_status,
                      const char *exit_reason);

void pcmk__format_result(pcmk__action_result_t *result, int exit_status,
                         enum pcmk_exec_status exec_status,
                         const char *format, ...) G_GNUC_PRINTF(4, 5);

void pcmk__set_result_output(pcmk__action_result_t *result,
                             char *out, char *err);

void pcmk__reset_result(pcmk__action_result_t *result);

void pcmk__copy_result(const pcmk__action_result_t *src,
                       pcmk__action_result_t *dst);

int pcmk__gaierror2rc(int gai);
int pcmk__bzlib2rc(int bz2);

/*!
 * \internal
 * \brief Check whether a result is OK
 *
 * \param[in] result
 *
 * \return true if the result's exit status is CRM_EX_OK and its
 *         execution status is PCMK_EXEC_DONE, otherwise false
 */
static inline bool
pcmk__result_ok(const pcmk__action_result_t *result)
{
    return (result != NULL) && (result->exit_status == CRM_EX_OK)
            && (result->execution_status == PCMK_EXEC_DONE);
}

#endif // PCMK__COMMON_RESULTS_INTERNAL__H
