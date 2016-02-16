#ifndef _VMATH_CORE_H
#define _VMATH_CORE_H

#ifndef bool
typedef enum { false = 0, true = 1 } bool;
#endif /* bool */

/*** Homogeneous coordinates (w == 0: vector, w != 0: point) */
typedef struct coord {
	float x, y, z, w;
} coord_t;

/*** Matrix (4x4) */
typedef struct matrix {
	float cell[4][4];
} matrix_t;

typedef struct ccs {
	coord_t o;
	coord_t i;
	coord_t j;
	coord_t k;

	matrix_t m;
	matrix_t mi;
} ccs_t;

#define MATROW(m, i) ((coord_t*) &(m->cell[i]))

/*** Initalizer values */
#define VEC_I    { 1.F, 0.F, 0.F, 0.F }
#define VEC_J    { 0.F, 1.F, 0.F, 0.F }
#define VEC_K    { 0.F, 0.F, 1.F, 0.F }
#define PNT_O    { 0.F, 0.F, 0.F, 1.F }
#define PNT_I    { 1.F, 0.F, 0.F, 1.F }
#define PNT_J    { 0.F, 1.F, 0.F, 1.F }
#define PNT_K    { 0.F, 0.F, 1.F, 1.F }
#define MAT_ID   { .cell = { VEC_I, VEC_J, VEC_K, PNT_O } }
#define CCS 	 { .o = PNT_O,\
		   .i = VEC_I,\
		   .j = VEC_J,\
		   .k = VEC_K,\
		   .m = MAT_ID,\
		   .mi = MAT_ID\
		 }

extern bool      is_point(const coord_t*);
extern bool      is_vector(const coord_t*);
extern bool      is_vzero(const coord_t*);
extern bool      is_vunit(const coord_t*);
extern bool      is_vortho(const coord_t*, const coord_t*);
extern bool      is_vequal(const coord_t*, const coord_t*);
extern bool      is_pequal(const coord_t*, const coord_t*);
extern bool      is_mequal(const matrix_t*, const matrix_t*);
extern bool      is_collinear(const coord_t*, const coord_t*, float*);
extern bool      is_pccs(const coord_t*, const coord_t*, const coord_t*);

extern float     len(const coord_t*);
extern float     dot(const coord_t*, const coord_t*);
extern coord_t  *vector(coord_t*, const coord_t*, const coord_t*);
extern coord_t  *unit_vector(coord_t*, const coord_t*, const coord_t*);
extern coord_t  *scale(coord_t*, const coord_t*, float);
extern coord_t  *scale_me(coord_t*, float);
extern coord_t  *unit(coord_t*, const coord_t*);
extern coord_t  *unit_me(coord_t*);
extern coord_t  *add(coord_t*, const coord_t*, const coord_t*);
extern coord_t  *add_me(coord_t*, const coord_t*);
extern coord_t  *sub(coord_t*, const coord_t*, const coord_t*);
extern coord_t  *sub_me(coord_t*, const coord_t*);
extern coord_t  *cross(coord_t*, const coord_t*, const coord_t*);
extern coord_t  *matcol(coord_t*, const matrix_t*, coord_t*);
extern coord_t  *homogeneize(coord_t*, const coord_t*);
extern coord_t  *homogeneize_me(coord_t*);
extern matrix_t *matrix(matrix_t*, const coord_t*, const coord_t*,
			const coord_t*, const coord_t*);
extern matrix_t *matrixr(matrix_t*, const coord_t*, const coord_t*,
			 const coord_t*, const coord_t*);
extern matrix_t *matmat(matrix_t*, const matrix_t*, const matrix_t*);
extern matrix_t *transpose(matrix_t*, matrix_t*);
extern matrix_t *rotationx(matrix_t*, float);
extern matrix_t *rotationy(matrix_t*, float);
extern matrix_t *rotationz(matrix_t*, float);
extern matrix_t *rotation(matrix_t*, const coord_t*, float);
extern matrix_t *scaling(matrix_t*, float, float, float);
extern matrix_t *translation(matrix_t*, coord_t*);
extern bool      change_of_coord_mat(ccs_t*);

extern const matrix_t matrix_id;
extern const coord_t  vector_i;
extern const coord_t  vector_j;
extern const coord_t  vector_k;
extern const coord_t  point_o;

#endif /* _VMATH_CORE_H */
