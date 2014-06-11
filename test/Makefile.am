AUTOMAKE_OPTIONS = foreign subdir-objects
CLEANFILES = *.core
#CLEANFILES += *.in

noinst_PROGRAMS=testfoo

distdir = ../$(PACKAGE)-$(VERSION)/test
dist_HEADERS = unittest.h

BUILT_SOURCES = ../src/diag.c ../src/diag.h

noinst_HEADERS = ../src/re2-c.h

if DEBUG
    DEBUG_FLAGS = -g -O0 @CLANG_DEBUG@
else
DEBUG_FLAGS = -DNDEBUG -O3
endif

nodist_testfoo_SOURCES = ../src/diag.c
testfoo_SOURCES = testfoo.c
testfoo_CFLAGS = $(DEBUG_FLAGS) -Wall -Wextra -Werror -std=c99 -I.. -I$(includedir)
testfoo_CXXFLAGS = $(DEBUG_FLAGS) -Wall -Wextra -Werror -I.. -I$(includedir)
testfoo_LDFLAGS = -L$(libdir) -lmrkcommon -lre2-c

../src/diag.c ../src/diag.h: ../src/diag.txt
	sh ../src/gen-diag re2_c

testrun: all
	for i in $(noinst_PROGRAMS); do if test -x ./$$i; then LD_LIBRARY_PATH=$(libdir) ./$$i; fi; done;
