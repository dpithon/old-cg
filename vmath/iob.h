#ifndef _VMATH_IOB_H
#define _VMATH_IOB_H

#define VMIOB_ASC	0
#define VMIOB_HEX	1

#define VMIOB_ERR_OK	0 /* no error         */
#define VMIOB_ERR_OVR	1 /* buffer overflow  */
#define VMIOB_ERR_CNV	2 /* conversion error */
#define VMIOB_ERR_FMT	3 /* unknown format   */

/**
 * input/output structure to dump and load objects
 */
typedef struct vmiob {
	char *buf;
	int sz, of;
	int err, fmt;
} vmiob_st;

#define init_iob(iob, b, s)	(iob)->buf    = (b);          \
				(iob)->sz     = (s);          \
				(iob)->of     = 0;            \
				(iob)->err    = VMIOB_ERR_OK; \
				(iob)->fmt    = VMIOB_ASC

#define reset_iob(iob)		(iob)->of = (iob)->err = 0
#define switch_iob(iob)		(iob)->fmt = (iob)->fmt? VMIOB_ASC: VMIOB_HEX

/**
 * dump_xxxx(vmiob_st *iob, const xxx_st *obj):
 *   dump obj into string (ascii or hexa) controlled by iob
 *
 * load_xxxx(const xxx_st *obj, vmiob_st *iob):
 *   load obj from string (ascii or hexa) controlled by iob
 *
 * for mstack and vstat, null pointer means vmath_mstak/vmath_vstat
 */
extern char *dump_coord(vmiob_st*, const coord_st*);
extern char *dump_matrix(vmiob_st*, const matrix_st*);
extern char *dump_mstack(vmiob_st*, const mstack_st*);
extern char *dump_vstat(vmiob_st*, const vstat_st*);
extern int   load_coord(coord_st*, vmiob_st*);
extern int   load_matrix(matrix_st*, vmiob_st*);
extern int   load_mstack(mstack_st*, vmiob_st*);
extern int   load_vstat(vstat_st*, vmiob_st*);

#endif /* _VMATH_IOB_H */
