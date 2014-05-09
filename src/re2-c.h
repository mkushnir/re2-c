#ifndef RE2_C_H_DEFINED
#define RE2_C_H_DEFINED

#include <mrkcommon/array.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _re2_ctx {
    void *_re2;
    array_t matches;
    array_t mdata;
} re2_ctx_t;

const char *re2_c_diag_str(int);

re2_ctx_t *re2_new(const char *);
void re2_destroy(re2_ctx_t **);
const char *re2_pattern(re2_ctx_t *);
int re2_numgroups(re2_ctx_t *);
const char *re2_error(re2_ctx_t *);
int re2_error_code(re2_ctx_t *);
int re2_program_size(re2_ctx_t *);
int re2_get_group(re2_ctx_t *, int, const char **, int *);


#define RE2_MAX_GROUPS 32
int re2_full_match(re2_ctx_t *, const char *);

#ifdef __cplusplus
}
#endif
#endif /* RE2_C_H_DEFINED */
