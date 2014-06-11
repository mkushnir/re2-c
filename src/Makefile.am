AUTOMAKE_OPTIONS = foreign subdir-objects

distdir = ../$(PACKAGE)-$(VERSION)/src
dist_HEADERS =

BUILT_SOURCES = diag.c diag.h
EXTRA_DIST = diag.txt gen-diag
CLEANFILES = $(BUILT_SOURCES) *.core
#CLEANFILES += *.in

lib_LTLIBRARIES = libre2-c.la

nobase_include_HEADERS = re2-c.h

noinst_HEADERS =

libre2_c_la_SOURCES = re2-c.cc
nodist_libre2_c_la_SOURCES = diag.c

if DEBUG
DEBUG_FLAGS = -g -O0 @CLANG_DEBUG@
else
DEBUG_FLAGS = -DNDEBUG -O3
endif

libre2_c_la_CFLAGS = $(DEBUG_FLAGS) -Wall -Wextra -Werror -std=c99 -I$(includedir) @MRKCOMMON_LOCAL_CFLAGS@ @RE2_LOCAL_CFLAGS@ $(DEBUG_FLAGS)
libre2_c_la_CXXFLAGS = -Wall -Wextra -Werror -I$(includedir) @MRKCOMMON_LOCAL_CFLAGS@ @RE2_LOCAL_CFLAGS@ $(DEBUG_FLAGS)

libre2_c_la_LDFLAGS = -version-info 0:0:0 -L$(libdir) -lmrkcommon @MRKCOMMON_LOCAL_LDFLAGS@ -lre2 @RE2_LOCAL_LDFLAGS@

SUBDIRS = .

diag.c diag.h: diag.txt
	sh ./gen-diag re2_c

run: all
	for i in $(bin_PROGRAMS); do if test -x ./$$i; then LD_LIBRARY_PATH=$(libdir) ./$$i; fi; done;

testrun:
	for i in $(SUBDIRS); do if test "$$i" != "."; then cd $$i && $(MAKE) testrun && cd ..; fi; done;
