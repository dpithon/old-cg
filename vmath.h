#ifndef VMATH_H
#define VMATH_H

#include <math.h>
#include "types.h"

#ifndef M_PI
#define M_PI 3.141592653589793238462643383
#endif /* M_PI */

struct coord {
	double x, y, z, w;
};

struct matrix {
	double cell[4][4];
};

struct coord_system {
	struct coord o;
	struct coord i;
	struct coord j;
	struct coord k;

	struct matrix m;  /* local to standard */
	struct matrix mi; /* standard to local */
};

#define MATROW(m, i) ((struct coord*) &(m->cell[i]))

/*** Initalizer values */
#define VECTOR_I    { 1., 0., 0., 0. }
#define VECTOR_J    { 0., 1., 0., 0. }
#define VECTOR_K    { 0., 0., 1., 0. }
#define POINT_O     { 0., 0., 0., 1. }
#define MATRIX_ID   { .cell = { VECTOR_I, VECTOR_J, VECTOR_K, POINT_O } }
#define STANDARD_CS { .o = POINT_O,\
		      .i = VECTOR_I,\
		      .j = VECTOR_J,\
		      .k = VECTOR_K,\
		      .m = MATRIX_ID,\
		      .mi = MATRIX_ID\
		 }

extern bool double_equals(double a, double b);
extern bool is_point(const struct coord*);
extern bool is_vector(const struct coord*);
extern bool is_vzero(const struct coord*);
extern bool is_vunit(const struct coord*);
extern bool is_vortho(const struct coord*, const struct coord*);
extern bool is_vequal(const struct coord*, const struct coord*);
extern bool is_pequal(const struct coord*, const struct coord*);
extern bool is_mequal(const struct matrix*, const struct matrix*);
extern bool is_collinear(const struct coord*, const struct coord*, double*);
extern bool is_cartesian_coord_system(const struct coord*, const struct coord*,
				      const struct coord*);

extern double len(const struct coord*);
extern double dot(const struct coord*, const struct coord*);

extern struct coord *vector(struct coord*, const struct coord*,
			    const struct coord*);
extern struct coord *unit_vector(struct coord*, const struct coord*,
				 const struct coord*);

extern struct coord *scale(struct coord*, const struct coord*, double);
extern struct coord *scale_me(struct coord*, double);
extern struct coord *unit(struct coord*, const struct coord*);
extern struct coord *unit_me(struct coord*);
extern struct coord *add(struct coord*, const struct coord*,
			 const struct coord*);
extern struct coord *add_me(struct coord*, const struct coord*);
extern struct coord *sub(struct coord*, const struct coord*,
			 const struct coord*);
extern struct coord *sub_me(struct coord*, const struct coord*);
extern struct coord *cross(struct coord*, const struct coord*,
			   const struct coord*);

extern struct coord *matcol(struct coord*, const struct matrix*,
			    const struct coord*);
extern struct coord *matcol_me(struct coord*, const struct matrix*);
extern struct coord *homogeneize(struct coord*, const struct coord*);
extern struct coord *homogeneize_me(struct coord*);

extern struct matrix *matrix(struct matrix*,
			     const struct coord*, const struct coord*,
			     const struct coord*, const struct coord*);
extern struct matrix *matrixr(struct matrix*,
			      const struct coord*, const struct coord*,
			      const struct coord*, const struct coord*);

extern struct matrix *matmat(struct matrix*,
			     const struct matrix*, const struct matrix*);

extern struct matrix *transpose(struct matrix*, struct matrix*);
extern struct matrix *rotationx(struct matrix*, double);
extern struct matrix *rotationy(struct matrix*, double);
extern struct matrix *rotationz(struct matrix*, double);
extern struct matrix *rotation(struct matrix*, const struct coord*, double);
extern struct matrix *scaling(struct matrix*, double, double, double);
extern struct matrix *translation(struct matrix*, struct coord*);

extern bool change_of_coord_mat(struct coord_system*);

extern void random_point(struct coord*);
extern void random_vector(struct coord*);


extern const struct matrix MatrixId;
extern const struct coord  VectorI;
extern const struct coord  VectorJ;
extern const struct coord  VectorK;
extern const struct coord  PointO;

#include "iomath.h"

#endif /* MATH_H */
