#ifndef _VMATH_STAT_H
#define _VMATH_STAT_H

#include <stdint.h>

typedef struct vstat {
	uint32_t sto;
	uint32_t cmp;
	uint32_t add;
	uint32_t mul;
	uint32_t abs;
	uint32_t sqr;
	uint32_t trg;
	uint32_t idx;
	uint32_t neg;

	uint32_t is_pnt;
	uint32_t is_vec;
	uint32_t is_0;
	uint32_t is_1;
	uint32_t is_ort;
	uint32_t fn_len;
	uint32_t fn_dot;
	uint32_t fn_vec;
	uint32_t fn_scl;
	uint32_t fn_1;
	uint32_t fn_add;
	uint32_t fn_sub;
	uint32_t fn_x;
	uint32_t fn_hmg;
	uint32_t fn_mxc;
	uint32_t fn_mxm;
	uint32_t fn_t;
	uint32_t fn_rtx;
	uint32_t fn_rty;
	uint32_t fn_rtz;
	uint32_t fn_rot;
	uint32_t fn_tsl;
	uint32_t fn_feq;
} vstat_st;


void reset_stat(void);
void copy_stat(vstat_st*);

#endif /* _VMATH_STAT_H */
