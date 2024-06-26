/*
 * Copyright 2020-2024 the Pacemaker project contributors
 *
 * The version control history for this file may have further details.
 *
 * This source code is licensed under the GNU Lesser General Public License
 * version 2.1 or later (LGPLv2.1+) WITHOUT ANY WARRANTY.
 */

#ifndef PCMK__CRM_COMMON_LISTS_INTERNAL__H
#define PCMK__CRM_COMMON_LISTS_INTERNAL__H

#include <glib.h>

#ifdef __cplusplus
extern "C" {
#endif

/*!
 * \internal
 * \brief Return the list that is \p from - \p items
 *
 * \param[in] from  Source list
 * \param[in] items List containing items to remove from \p from
 * \param[in] cmp   Function used to compare list elements
 *
 * \return Newly allocated list
 */
GList *pcmk__subtract_lists(GList *from, const GList *items,
                            GCompareFunc cmp);

#ifdef __cplusplus
}
#endif

#endif // PCMK__CRM_COMMON_LISTS_INTERNAL__H
