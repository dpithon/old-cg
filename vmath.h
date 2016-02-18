#ifndef VMATH_H
#define VMATH_H

#include <math.h>

#ifndef bool
typedef enum { false = 0, true = 1 } bool;
#endif /* bool */

/*** Homogeneous coordinates (w == 0: vector, w != 0: point) */
struct coord {
	float x, y, z, w;
};

/*** Matrix (4x4) */
typedef struct matrix {
	float cell[4][4];
} matrix_t;

struct coord_system {
	struct coord o;
	struct coord i;
	struct coord j;
	struct coord k;

	matrix_t m;
	matrix_t mi;
};

#define MATROW(m, i) ((struct coord*) &(m->cell[i]))

/*** Initalizer values */
#define VECTOR_I    { 1.F, 0.F, 0.F, 0.F }
#define VECTOR_J    { 0.F, 1.F, 0.F, 0.F }
#define VECTOR_K    { 0.F, 0.F, 1.F, 0.F }
#define POINT_O    { 0.F, 0.F, 0.F, 1.F }
#define MATRIX_ID   { .cell = { VECTOR_I, VECTOR_J, VECTOR_K, POINT_O } }
#define CCS 	 { .o = POINT_O,\
		   .i = VECTOR_I,\
		   .j = VECTOR_J,\
		   .k = VECTOR_K,\
		   .m = MATRIX_ID,\
		   .mi = MATRIX_ID\
		 }

extern bool      float_equals(float a, float b);
extern bool      is_point(const struct coord*);
extern bool      is_vector(const struct coord*);
extern bool      is_vzero(const struct coord*);
extern bool      is_vunit(const struct coord*);
extern bool      is_vortho(const struct coord*, const struct coord*);
extern bool      is_vequal(const struct coord*, const struct coord*);
extern bool      is_pequal(const struct coord*, const struct coord*);
extern bool      is_mequal(const matrix_t*, const matrix_t*);
extern bool      is_collinear(const struct coord*, const struct coord*, float*);
extern bool      is_cartesian_coord_system(const struct coord*, const struct coord*,
					   const struct coord*);

extern float     len(const struct coord*);
extern float     dot(const struct coord*, const struct coord*);

extern struct coord  *vector(struct coord*, const struct coord*,
			     const struct coord*);
extern struct coord  *unit_vector(struct coord*, const struct coord*,
				  const struct coord*);

extern struct coord  *scale(struct coord*, const struct coord*, float);
extern struct coord  *scale_me(struct coord*, float);
extern struct coord  *unit(struct coord*, const struct coord*);
extern struct coord  *unit_me(struct coord*);
extern struct coord  *add(struct coord*, const struct coord*,
			  const struct coord*);
extern struct coord  *add_me(struct coord*, const struct coord*);
extern struct coord  *sub(struct coord*, const struct coord*,
			  const struct coord*);
extern struct coord  *sub_me(struct coord*, const struct coord*);
extern struct coord  *cross(struct coord*, const struct coord*,
			    const struct coord*);

extern struct coord  *matcol(struct coord*, const matrix_t*,
			     const struct coord*);
extern struct coord  *matcol_me(struct coord*, const matrix_t*);
extern struct coord  *homogeneize(struct coord*, const struct coord*);
extern struct coord  *homogeneize_me(struct coord*);

extern matrix_t *matrix(matrix_t*, const struct coord*, const struct coord*,
			const struct coord*, const struct coord*);
extern matrix_t *matrixr(matrix_t*, const struct coord*, const struct coord*,
			 const struct coord*, const struct coord*);

extern matrix_t *matmat(matrix_t*, const matrix_t*, const matrix_t*);

extern matrix_t *transpose(matrix_t*, matrix_t*);
extern matrix_t *rotationx(matrix_t*, float);
extern matrix_t *rotationy(matrix_t*, float);
extern matrix_t *rotationz(matrix_t*, float);
extern matrix_t *rotation(matrix_t*, const struct coord*, float);
extern matrix_t *scaling(matrix_t*, float, float, float);
extern matrix_t *translation(matrix_t*, struct coord*);

extern bool      change_of_coord_mat(struct coord_system*);

extern void      random_point(struct coord*);
extern void      random_vector(struct coord*);


extern const matrix_t MatrixId;
extern const struct coord  VectorI;
extern const struct coord  VectorJ;
extern const struct coord  VectorK;
extern const struct coord  PointO;

#endif /* MATH_H */
