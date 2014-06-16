#include <stdlib.h>

#include <re2/re2.h>
#include <re2/stringpiece.h>

#include <mrkcommon/dumpm.h>
#include <mrkcommon/util.h>

#include <re2-c.h>

#include "diag.h"

extern "C" {

using re2::RE2;
using re2::StringPiece;

#define RE2WRAP(re) ((RE2 *)(re))

static int
mdata_fini(StringPiece **sp)
{
    if (*sp != NULL) {
        delete *sp;
        *sp = NULL;
    }
    return 0;
}


static int
matches_fini(RE2::Arg **a)
{
    if (*a != NULL) {
        delete *a;
        *a = NULL;
    }
    return 0;
}


re2_ctx_t *
re2_new(const char *pattern)
{
    re2_ctx_t *res;

    if ((res = (re2_ctx_t *)malloc(sizeof(re2_ctx_t))) == NULL) {
        FAIL("malloc");
    }

    res->_re2 = (void *) new RE2(pattern);

    if (re2_error_code(res) == 0) {
        int ngroups;
        RE2::Arg **a;
        array_iter_t it;

        ngroups = RE2WRAP(res->_re2)->NumberOfCapturingGroups();
        array_init(&res->mdata,
                   sizeof(StringPiece *),
                   ngroups,
                   NULL,
                   (array_finalizer_t)mdata_fini);
        array_init(&res->matches,
                   sizeof(RE2::Arg *),
                   ngroups,
                   NULL,
                   (array_finalizer_t)matches_fini);

        for (a = (RE2::Arg **)array_first(&res->matches, &it);
             a != NULL;
             a = (RE2::Arg **)array_next(&res->matches, &it)) {

            StringPiece **sp;

            if ((sp = (StringPiece **)array_get(&res->mdata,
                                                it.iter)) == NULL) {
                FAIL("array_get");
            }
            *sp = new StringPiece();
            *a = new RE2::Arg(*sp);
        }

    }

    //TRACE("pat='%s' grp=%d err=%s errno=%d sz=%d",
    //      re2_pattern(res),
    //      re2_numgroups(res),
    //      re2_error(res),
    //      re2_error_code(res),
    //      re2_program_size(res));

    return res;
}


int
re2_get_group(re2_ctx_t *re, int idx, const char **ptr, int *len)
{
    StringPiece **sp;

    if ((sp = (StringPiece **)array_get(&re->mdata, idx)) == NULL) {
        return -1;
    }
    *ptr = (*sp)->data();
    *len = (*sp)->length();
    return 0;
}


void
re2_destroy(re2_ctx_t **re)
{
    if (*re != NULL) {
        delete RE2WRAP((*re)->_re2);
        array_fini(&(*re)->matches);
        array_fini(&(*re)->mdata);
        free(*re);
        *re = NULL;
    }
}


const char *
re2_pattern(re2_ctx_t *re)
{
    return (const char *)&RE2WRAP(re->_re2)->pattern();
}


int
re2_full_match(re2_ctx_t *re, const char *text, re2_match_cb cb, void *udata)
{
    int res = 1;
    RE2::Arg **args;
    const StringPiece& sp = StringPiece(text);

    args = (RE2::Arg **)array_get(&re->matches, 0);

    if (RE2::FullMatchN(sp,
                        (RE2 &)(*(RE2 *)(re->_re2)),
                        args,
                        re->matches.elnum)) {

        StringPiece **sp;
        array_iter_t it;

        for (sp = (StringPiece **)array_first(&re->mdata, &it);
             sp != NULL;
             sp = (StringPiece **)array_next(&re->mdata, &it)) {

            if (cb((*sp)->data(), (*sp)->length(), it.iter, udata) != 0) {
                break;
            }

            //TRACE("m='%s' l=%d", (*sp)->data(), (*sp)->length());
        }
        res = 0;
    }
    return res;
}

int
re2_numgroups(re2_ctx_t *re)
{
    return RE2WRAP(re->_re2)->NumberOfCapturingGroups();
}


const char *
re2_error(re2_ctx_t *re)
{
    return (const char *)&RE2WRAP(re->_re2)->error();
}


int
re2_error_code(re2_ctx_t *re)
{
    return RE2WRAP(re->_re2)->error_code();
}


int
re2_program_size(re2_ctx_t *re)
{
    return RE2WRAP(re->_re2)->ProgramSize();
}


}
