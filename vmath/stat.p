#ifndef _VMATH_STAT_PRIVATE_H
#define _VMATH_STAT_PRIVATE_H

#ifndef _VMATH_INTERNALS
#error _VMATH_INTERNALS not defined !
#endif /* _VMATH_INTERNALS */

#ifdef VSTAT
extern vstat_t vmath_tat;
extern const char *const vstat_tr[];

#define STO(v)		vmath_tat.sto += (v)
#define CMP(v)		vmath_tat.cmp += (v)
#define ADD(v)		vmath_tat.add += (v)
#define MUL(v)		vmath_tat.mul += (v)
#define ABS(v)		vmath_tat.abs += (v)
#define SQR(v)		vmath_tat.sqr += (v)
#define TRG(v)		vmath_tat.trg += (v)
#define IDX(v)		vmath_tat.idx += (v)
#define NEG(v)		vmath_tat.neg += (v)

#define IS_PNT(v)	vmath_tat.is_pnt += (v)
#define IS_VEC(v)	vmath_tat.is_vec += (v)
#define IS_0(v)		vmath_tat.is_0   += (v)
#define IS_1(v)		vmath_tat.is_1   += (v)
#define IS_ORT(v)	vmath_tat.is_ort += (v)
#define FN_LEN(v)	vmath_tat.fn_len += (v)
#define FN_DOT(v)	vmath_tat.fn_dot += (v)
#define FN_VEC(v)	vmath_tat.fn_vec += (v)
#define FN_SCL(v)	vmath_tat.fn_scl += (v)
#define FN_1(v)		vmath_tat.fn_1   += (v)
#define FN_ADD(v)	vmath_tat.fn_add += (v)
#define FN_SUB(v)	vmath_tat.fn_sub += (v)
#define FN_X(v)		vmath_tat.fn_x   += (v)
#define FN_HMG(v)	vmath_tat.fn_hmg += (v)
#define FN_MXC(v)	vmath_tat.fn_mxc += (v)
#define FN_MXM(v)	vmath_tat.fn_mxm += (v)
#define FN_T(v)		vmath_tat.fn_t   += (v)
#define FN_RTX(v)	vmath_tat.fn_rtx += (v)
#define FN_RTY(v)	vmath_tat.fn_rty += (v)
#define FN_RTZ(v)	vmath_tat.fn_rtz += (v)
#define FN_ROT(v)	vmath_tat.fn_rot += (v)
#define FN_TSL(v)	vmath_tat.fn_tsl += (v)
#define FN_FEQ(v)	vmath_tat.fn_feq += (v)

#else  /* VSTAT */

#define STO(v)
#define CMP(v)
#define ADD(v)
#define MUL(v)
#define ABS(v)
#define SQR(v)
#define TRG(v)
#define IDX(v)
#define NEG(v)

#define IS_PNT(v)
#define IS_VEC(v)
#define IS_0(v)
#define IS_1(v)
#define IS_ORT(v) 
#define FN_LEN(v) 
#define FN_DOT(v) 
#define FN_VEC(v) 
#define FN_SCL(v) 
#define FN_1(v) 
#define FN_ADD(v) 
#define FN_SUB(v) 
#define FN_X(v) 
#define FN_HMG(v) 
#define FN_MXC(v)
#define FN_MXM(v)
#define FN_T(v)
#define FN_RTX(v)
#define FN_RTY(v)
#define FN_RTZ(v)
#define FN_ROT(v)
#define FN_TSL(v)
#define FN_FEQ(v)

#endif /* VSTAT */
#endif /* _VMATH_STAT_PRIVATE_H */
// vim: syntax=c
