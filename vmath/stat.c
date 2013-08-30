#include <stdio.h>
#include <string.h>
#include "stat.h"

vstat_st vmath_stat;
const char *const vstat_str[] = {
	"sto", "cmp", "add", "mul", "abs",
	"sqr", "trg", "idx", "neg", "is_pnt",
	"is_vec", "is_0", "is_1", "is_ort", "fn_len",
	"fn_dot", "fn_vec", "fn_scl", "fn_1", "fn_add",
	"fn_sub", "fn_x", "fn_hmg", "fn_mxc", "fn_mxm",
	"fn_t", "fn_rtx", "fn_rty", "fn_rtz", "fn_rot",
	"fn_tsl", "fn_feq", 0
};


void reset_stat(void)
{
	memset(&vmath_stat, 0, sizeof vmath_stat);
}


void copy_stat(vstat_st *dst)
{
	memcpy(dst, &vmath_stat, sizeof vmath_stat); 
}


void print_stat(vstat_st *stat)
{
        uint32_t *ul;

        if (! stat) {
                stat = &vmath_stat;
        }

        ul = (uint32_t*) stat;

        for (int i = 0; vstat_str[i]; i++) {
                printf("%6d ..... %s\n", ul[i], vstat_str[i]);
        }
}
