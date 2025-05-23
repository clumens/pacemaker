#
# Copyright 2003-2025 the Pacemaker project contributors
#
# The version control history for this file may have further details.
#
# This source code is licensed under the GNU General Public License version 2
# or later (GPLv2+) WITHOUT ANY WARRANTY.
#
include $(top_srcdir)/mk/common.mk

# Define release- and upload-related variables
include $(top_srcdir)/mk/release.mk
include $(top_srcdir)/mk/uploads.mk

# What formats to use for book uploads (i.e. "make www";
# use BOOK_FORMATS in sphinx subdirectory to change local builds)
BOOK_FORMATS		?= html 	\
			   singlehtml 	\
			   pdf 		\
			   epub

# SNMP MIB
mibdir		= $(datadir)/snmp/mibs
dist_mib_DATA	= PCMK-MIB.txt

noinst_SCRIPTS		= abi-check

SUBDIRS		= sphinx

EXTRA_DIST	= clusterlabs-logo-55x55.png

# For Makefile debugging
.PHONY: vars
vars:
	@echo LAST_RELEASE=\'$(LAST_RELEASE)\'
	@echo TAG=\'$(TAG)\'
	@echo RSYNC_DEST=\'$(RSYNC_DEST)\'
	@echo RSYNC_PACKAGE_DEST=\'$(RSYNC_PACKAGE_DEST)\'


# Annotated source code as HTML

# Cleaning first ensures we don't index unrelated stuff like RPM sources
.PHONY: global
global:
	$(MAKE) $(AM_MAKEFLAGS) -C .. clean-generic
	$(MAKE) $(AM_MAKEFLAGS) -C ../rpm rpm-clean
	cd .. && gtags -q && htags -sanhIT doc

.PHONY: global-upload
global-upload: global
	rsync $(RSYNC_OPTS) HTML/ "$(RSYNC_PACKAGE_DEST)/global/$(TAG)/"

.PHONY: global-clean
global-clean:
	-rm -rf HTML


# Man pages as HTML

MANPAGE_DIRS = ../agents ../daemons ../tools

%.8.html: %.8
	groff -mandoc `man -w ./$<` -T html > $@

%.7.html: %.7
	groff -mandoc `man -w ./$<` -T html > $@

.PHONY: manhtml
manhtml:
	$(MAKE) $(AM_MAKEFLAGS) -C .. all
	find $(MANPAGE_DIRS) -name "[a-z]*.[78]"	\
		-exec $(MAKE) $(AM_MAKEFLAGS) \{\}.html \;

.PHONY: manhtml-upload
manhtml-upload: manhtml
	find $(MANPAGE_DIRS) -name "[a-z]*.[78].html" -exec \
		rsync $(RSYNC_OPTS) \{\} "$(RSYNC_PACKAGE_DEST)/man/" \;

.PHONY: manhtml-clean
manhtml-clean:
	-find $(MANPAGE_DIRS) -name "[a-z]*.[78].html" -exec rm \{\} \;


# API documentation as HTML

.PHONY: doxygen
doxygen: Doxyfile
	doxygen Doxyfile

.PHONY: doxygen-upload
doxygen-upload: doxygen
	rsync $(RSYNC_OPTS) api/html/ "$(RSYNC_PACKAGE_DEST)/doxygen/$(TAG)/"

.PHONY: doxygen-clean
doxygen-clean:
	-rm -rf api


# ABI compatibility report as HTML

.PHONY: abi
abi: abi-check
	./abi-check $(PACKAGE) $(LAST_RELEASE) $(TAG)

.PHONY: abi-www
abi-www:
	export RSYNC_PACKAGE_DEST=$(RSYNC_PACKAGE_DEST);	\
		./abi-check -u $(PACKAGE) $(LAST_RELEASE) $(TAG)

.PHONY: abi-clean
abi-clean:
	-rm -rf abi


# The main documentation books (which are actually in the sphinx subdirectory)
.PHONY: books-upload
books-upload:
	$(MAKE) $(AM_MAKEFLAGS)	-C sphinx clean
	$(MAKE) $(AM_MAKEFLAGS)	-C sphinx	\
		RSYNC_DEST="$(RSYNC_DEST)"	\
		BOOK_FORMATS="$(BOOK_FORMATS)"	\
		books-upload


# All online documentation (except ABI compatibility, which is run separately)
.PHONY: www
www: clean-local manhtml-upload global-upload doxygen-upload books-upload

.PHONY: clean-local
clean-local: global-clean manhtml-clean doxygen-clean abi-clean

# "make check" will cause "make all" to be run, which means docs will get built
# as a part of running tests if they haven't already.  That seems unnecessary, so
# override the default check-recursive rule with this one that just returns.  If
# we ever need to add tests to this directory, this rule will have to come out.
.PHONY: check-recursive
check-recursive:
	@true
