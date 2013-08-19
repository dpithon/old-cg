#ifndef _VMATH_CORE_H
#define _VMATH_CORE_H

#ifndef bool
#define bool int
#define true  1
#define false 0
#endif /* bool */

/*** Homogeneous coordinates (w == 0: vector, w != 0: point) */
typedef struct coord {
	float x, y, z, w;
} coord_st;

/*** Matrix (4x4) */
typedef struct matrix {
	float cell[4][4];
} matrix_st;

/*** Initalizer values */
#define VEC_I    { 1.F, 0.F, 0.F, 0.F }
#define VEC_J    { 0.F, 1.F, 0.F, 0.F }
#define VEC_K    { 0.F, 0.F, 1.F, 0.F }
#define PNT_O    { 0.F, 0.F, 0.F, 1.F }
#define PNT_I    { 1.F, 0.F, 0.F, 1.F }
#define PNT_J    { 0.F, 1.F, 0.F, 1.F }
#define PNT_K    { 0.F, 0.F, 1.F, 1.F }
#define MAT_ID   { .cell = { VEC_I, VEC_J, VEC_K, PNT_O } }

extern bool       is_point(const coord_st*);
extern bool       is_vector(const coord_st*);
extern bool       is_zero(const coord_st*);
extern bool       is_unit(const coord_st*);
extern bool       is_ortho(const coord_st*, const coord_st*);

extern float      len(const coord_st*);
extern float      dot(const coord_st*, const coord_st*); 
extern coord_st  *vector(coord_st*, const coord_st*, const coord_st*);
extern coord_st  *scale(coord_st*, coord_st*, float);
extern coord_st  *unit(coord_st*, coord_st*);
extern coord_st  *add(coord_st*, coord_st*, coord_st*);
extern coord_st  *sub(coord_st*, coord_st*, coord_st*);
extern coord_st  *cross(coord_st*, const coord_st*, const coord_st*);
extern coord_st  *homogeneize(coord_st*, coord_st*);
extern coord_st  *mulc(coord_st*, const matrix_st*, coord_st*);
extern matrix_st *mulm(matrix_st*, matrix_st*, matrix_st*);
extern matrix_st *transpose(matrix_st*, matrix_st*);
extern matrix_st *rotationx(matrix_st*, float);
extern matrix_st *rotationy(matrix_st*, float);
extern matrix_st *rotationz(matrix_st*, float);
extern matrix_st *rotation(matrix_st*, const coord_st*, float);
extern matrix_st *scaling(matrix_st*, float, float, float);
extern matrix_st *translation(matrix_st*, coord_st*);

extern const matrix_st matrix_id;
extern const coord_st  vector_i;
extern const coord_st  vector_j;
extern const coord_st  vector_k;
extern const coord_st  point_o;

#ifdef COUNTERS
typedef struct counter {
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
} counter_st;

extern const char *const counter_name[];

void reset_counters(void);
void copy_counters(counter_st*);

#endif /* COUNTERS */

#endif /* _VMATH_CORE_H */
