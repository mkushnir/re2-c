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

UNUSED static void
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


static int
mycb(const char *str, size_t sz, unsigned int idx, UNUSED void *udata)
{
    char *s;

    s = malloc(sz + 1);
    memcpy(s, str, sz);
    *(s + sz) = '\0';
    TRACE("match #%d: %s", idx, s);
    //D8(str, sz);
    free(s);
    return 0;
}


static void
do_re(char *pat, char *str)
{
    int res = -1;
    re2_ctx_t *re;

    re = re2_new(pat);
    res = re2_full_match_cb(re, str, mycb, NULL);
    TRACE("res=%d", res);
    res = re2_partial_match_cb(re, str, mycb, NULL);
    TRACE("res=%d", res);
    //dump_groups(re);
    re2_destroy(&re);
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
    UNITTEST_PROLOG_RAND;

    //FOREACHDATA {
    //    TRACE("in=%d expected=%d", CDATA.in, CDATA.expected);
    //    assert(CDATA.in == CDATA.expected);
    //}
    //do_re("^https?://[^/]+([^?]+)?(?:.*)$", "http://test.com/1/2/3/asd-456.m3u8?q=1;b=2");
    //do_re("^.*/([^/]+)(?:_(\\d+))?\\.m3u8$", "/1/2/3/asd-456.m3u8");
    //do_re("^.*/([^/]+?)(?:_(\\d+))?\\.m3u8$", "/1/2/3/asd-456_888.m3u8");
    //do_re("^.*/([^/]+?)(?:_(\\d+))?\\.m3u8$", "/1/2/3/asd-456_888_999.m3u8");
    //do_re("^.*/([^/]+)_(\\d+)Num(\\d+)\\.ts$", "/1/2/3/asd-456_888_999Num12321.ts");
    //do_re(".*/([^/]+)_(\\d+)Num(\\d+)\\.ts", "/1/2/3/asd-456_888_999Num12321.ts");

    do_re("/([^/]+)_(\\d+)Num(\\d+)\\.ts", "http://test.com/1/2/3/asd-456_888_999Num12321.ts");
    do_re("/([^/]+)_(\\d+)Num(\\d+)\\.ts", "http://test.com/1/2/3/asd-456_888_999Num12321.ts?a=1;b=2");
    do_re("/([^/]+)_(\\d+)Num(\\d+)\\.ts", "http://test.com/1/2/3/asd-456_888_999");
}

int
main(void)
{
    test0();
    return 0;
}
