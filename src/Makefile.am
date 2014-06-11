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

libre2_c_la_CFLAGS = $(DEBUG_FLAGS) -Wall -Wextra -Werror -std=c99 -I$(includedir)
libre2_c_la_CXXFLAGS = $(DEBUG_FLAGS) -Wall -Wextra -Werror -I$(includedir)

libre2_c_la_LDFLAGS = -version-info 0:0:0 -L$(libdir) -lmrkcommon -lre2

SUBDIRS = .

diag.c diag.h: diag.txt
	sh ./gen-diag re2_c

run: all
	for i in $(bin_PROGRAMS); do if test -x ./$$i; then LD_LIBRARY_PATH=$(libdir) ./$$i; fi; done;

testrun:
	for i in $(SUBDIRS); do if test "$$i" != "."; then cd $$i && $(MAKE) testrun && cd ..; fi; done;
