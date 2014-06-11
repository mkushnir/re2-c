#include <assert.h>
#include <stdlib.h>
#include <time.h>

#include "unittest.h"
#include <mrkcommon/dumpm.h>
#include <mrkcommon/util.h>

#include <re2-c.h>

#ifndef NDEBUG
const char *_malloc_options = "AJ";
#endif

static void
dump_groups(re2_ctx_t *re)
{
    int i;
    for (i = 0; i < re2_numgroups(re); ++i) {
        const char *ptr;
        int len;

        if (re2_get_group(re, i, &ptr, &len) == 0) {
            D8(ptr, len);
        }
    }
}

static void
test0(void)
{
    struct {
        long rnd;
        int in;
        int expected;
    } data[] = {
        {0, 0, 0},
    };
    int res = -1;
    re2_ctx_t *re;
    UNITTEST_PROLOG_RAND;

    //FOREACHDATA {
    //    TRACE("in=%d expected=%d", CDATA.in, CDATA.expected);
    //    assert(CDATA.in == CDATA.expected);
    //}
    re = re2_new("(\\d*) ([a-z]* )?(\\d*)");
    res = re2_full_match(re, "111 22222");
    TRACE("res=%d", res);
    dump_groups(re);
    res = re2_full_match(re, "33 qw 45");
    TRACE("res=%d", res);
    dump_groups(re);
    re2_destroy(&re);

    re = re2_new("https?://(.*)\\.foo\\.com(/.*)");
    res = re2_full_match(re, "http://test.foo.com/");
    TRACE("res=%d", res);
    dump_groups(re);
    res = re2_full_match(re, "https://test.foo.com/path/to");
    TRACE("res=%d", res);
    dump_groups(re);
    re2_destroy(&re);
}

int
main(void)
{
    test0();
    return 0;
}
