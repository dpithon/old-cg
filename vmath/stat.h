#ifndef _VMATH_STAT_H
#define _VMATH_STAT_H

typedef struct vstat {
	unsigned long sto;
	unsigned long cmp;
	unsigned long add;
	unsigned long mul;
	unsigned long abs;
	unsigned long sqr;
	unsigned long trg;
	unsigned long idx;
	unsigned long neg;

	unsigned long is_pnt;
	unsigned long is_vec;
	unsigned long is_0;
	unsigned long is_1;
	unsigned long is_ort;
	unsigned long fn_len;
	unsigned long fn_dot;
	unsigned long fn_vec;
	unsigned long fn_scl;
	unsigned long fn_1;
	unsigned long fn_add;
	unsigned long fn_sub;
	unsigned long fn_x;
	unsigned long fn_hmg;
	unsigned long fn_mxc;
	unsigned long fn_mxm;
	unsigned long fn_t;
	unsigned long fn_rtx;
	unsigned long fn_rty;
	unsigned long fn_rtz;
	unsigned long fn_rot;
	unsigned long fn_tsl;
	unsigned long fn_feq;
} vstat_st;


void reset_stat(void);
void copy_stat(vstat_st*);

#endif /* _VMATH_STAT_H */
