#
# Copyright 2020-2024 the Pacemaker project contributors
#
# The version control history for this file may have further details.
#
# This source code is licensed under the GNU General Public License version 2
# or later (GPLv2+) WITHOUT ANY WARRANTY.
#

include $(top_srcdir)/mk/common.mk
include $(top_srcdir)/mk/tap.mk
include $(top_srcdir)/mk/unittest.mk

# Add "_test" to the end of all test program names to simplify .gitignore.
check_PROGRAMS = pcmk__clear_flags_as_test	\
		 pcmk__set_flags_as_test	\
		 pcmk_all_flags_set_test	\
		 pcmk_any_flags_set_test

TESTS = $(check_PROGRAMS)
