#ifndef VMATH_H
#define VMATH_H

#include <math.h>
#include "types.h"

#ifndef M_PI
#define M_PI 3.141592653589793238462643383
#endif /* M_PI */

extern const double epsilon;

struct coord {
	double x, y, z, w;
};

struct matrix {
	double cell[4][4];
};

struct cs {
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

extern const struct matrix matrix_id;
extern const struct coord  vector_i;
extern const struct coord  vector_j;
extern const struct coord  vector_k;
extern const struct coord  point_o;

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
extern struct coord *scale_in_place(struct coord*, double);
extern struct coord *normalize(struct coord*, const struct coord*);
extern struct coord *normalize_in_place(struct coord*);
extern struct coord *add(struct coord*, const struct coord*,
			 const struct coord*);
extern struct coord *add_in_place(struct coord*, const struct coord*);
extern struct coord *sub(struct coord*, const struct coord*,
			 const struct coord*);
extern struct coord *sub_in_place(struct coord*, const struct coord*);
extern struct coord *cross(struct coord*, const struct coord*,
			   const struct coord*);

extern struct coord *matcol(struct coord*, const struct matrix*,
			    const struct coord*);
extern struct coord *matcol_in_place(struct coord*, const struct matrix*);
extern struct coord *homogeneize(struct coord*, const struct coord*);
extern struct coord *homogeneize_in_place(struct coord*);

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

extern void change_of_coord_mat(struct cs*);

extern void random_point(struct coord*);
extern void random_vector(struct coord*);

#ifndef NDEBUG
#define assert_is_mequal(m1, m2) assert__is_mequal(m1, m2, __LINE__, __FILE__)
#define assert_is_vector(c)	 assert__is_vector(c, __LINE__, __FILE__)
#define assert_is_point(c)	 assert__is_point(c, __LINE__, __FILE__)
#define assert_is_not_vzero(c)   assert__is_not_vzero(c, __LINE__, __FILE__)
#define assert_is_vunit(c)	 assert__is_vunit(c, __LINE__, __FILE__)
#define assert_is_cartesian_coord_system(i, j, k)\
		assert__is_cartesian_coord_system(i, j, k, __LINE__, __FILE__)

extern void print_matrix(const char*, const struct matrix*);
extern void print_coord(const char*, const struct coord*);

extern void assert__is_vector(const struct coord*, int, char*);
extern void assert__is_point(const struct coord*, int, char*);
extern void assert__is_not_vzero(const struct coord*, int, char*);
extern void assert__is_vunit(const struct coord*, int, char*);
extern void assert__is_cartesian_coord_system(const struct coord*,
				       const struct coord*,
				       const struct coord*,
				       int, char*);
extern void assert__is_mequal(const struct matrix*, const struct matrix*,
			      int, char*);

#else  /* ! NDEBUG */

#define NOOP ((void)0)
#define assert_is_mequal(m1, m2) NOOP
#define assert_is_vector(c)	 NOOP
#define assert_is_point(c)	 NOOP
#define assert_is_not_vzero(c)   NOOP
#define assert_is_vunit(c)	 NOOP
#define assert_is_cartesian_coord_system(i, j, k) NOOP
#endif /* ! NDEBUG */

#endif /* MATH_H */
