#
# Copyright 2023-2025 the Pacemaker project contributors
#
# The version control history for this file may have further details.
#
# This source code is licensed under the GNU General Public License version 2
# or later (GPLv2+) WITHOUT ANY WARRANTY.
#

include $(top_srcdir)/mk/common.mk

AM_CPPFLAGS += $(PYTHON_CFLAGS)

pkgpython_PYTHON = __init__.py 		\
		   _library.py          \
		   errors.py            \
		   exitstatus.py

nodist_pkgpython_PYTHON = buildoptions.py

SUBDIRS = _cts

pkgpyexec_LTLIBRARIES = resource.la

resource_la_SOURCES = resource.c
resource_la_LDFLAGS = $(AM_LDFLAGS) $(PYTHON_LDFLAGS) -module -avoid-version
resource_la_LIBADD = $(PYTHON_LIBS)
