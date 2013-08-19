#ifndef _CORE_PRIVATE_H
#define _CORE_PRIVATE_H

#ifdef COUNTERS

#define STO(v)	cnt.sto += (v)
#define CMP(v)	cnt.cmp += (v)
#define ADD(v)	cnt.add += (v)
#define MUL(v)	cnt.mul += (v)
#define ABS(v)	cnt.abs += (v)
#define SQR(v)	cnt.sqr += (v)
#define TRG(v)	cnt.trg += (v)
#define IDX(v)	cnt.idx += (v)
#define NEG(v)	cnt.neg += (v)

extern counters_st cnt;

#else  /* COUNTERS */

#define STO(v)
#define CMP(v)
#define ADD(v)
#define MUL(v)
#define ABS(v)
#define SQR(v)
#define TRG(v)
#define IDX(v)
#define NEG(v)

#endif /* COUNTERS */

#endif /* _CORE_PRIVATE_H */
