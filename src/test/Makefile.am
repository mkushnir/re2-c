AUTOMAKE_OPTIONS = foreign subdir-objects
CLEANFILES = *.core
#CLEANFILES += *.in

noinst_PROGRAMS=testfoo

distdir = ../../$(PACKAGE)-$(VERSION)/src/test
dist_HEADERS = unittest.h

BUILT_SOURCES = ../diag.c ../diag.h

noinst_HEADERS = ../re2-c.h

if DEBUG
    DEBUG_FLAGS = -g -O0 @CLANG_DEBUG@
else
DEBUG_FLAGS = -DNDEBUG -O3
endif

nodist_testfoo_SOURCES = ../diag.c
testfoo_SOURCES = testfoo.c
testfoo_CFLAGS = $(DEBUG_FLAGS) -Wall -Wextra -Werror -std=c99 -I.. -I$(includedir)
testfoo_CXXFLAGS = $(DEBUG_FLAGS) -Wall -Wextra -Werror -I.. -I$(includedir)
testfoo_LDFLAGS = -L$(libdir) -lmrkcommon -lre2-c

../diag.c ../diag.h: ../diag.txt
	sh ../gen-diag re2_c

testrun: all
	for i in $(noinst_PROGRAMS); do if test -x ./$$i; then LD_LIBRARY_PATH=$(libdir) ./$$i; fi; done;
