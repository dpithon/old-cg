#ifndef _MATH3D_H
#define _MATH3D_H

/*
 * Homogeneous coordinates
 *  w == 0 for vectors
 *  w != 0 for points
 */
struct hcoord {
	float x, y, z, w;
};


/* 4x4 matrix */
union matrix {
	struct rows {
		struct hcoord r1, r2, r3, r4;
	} rows;
	float cell[4][4];
};

/* Initalizer values */
#define VEC_I  { 1.F, 0.F, 0.F, 0.F }
#define VEC_J  { 0.F, 1.F, 0.F, 0.F }
#define VEC_K  { 0.F, 0.F, 1.F, 0.F }
#define PNT_O  { 0.F, 0.F, 0.F, 1.F }
#define PNT_I  { 1.F, 0.F, 0.F, 1.F }
#define PNT_J  { 0.F, 1.F, 0.F, 1.F }
#define PNT_K  { 0.F, 0.F, 1.F, 1.F }

#define MAT_ID { .rows = {\
	{ 1.F, 0.F, 0.F, 0.F },\
	{ 0.F, 1.F, 0.F, 0.F },\
	{ 0.F, 0.F, 1.F, 0.F },\
	{ 0.F, 0.F, 0.F, 1.F } } }

extern float Epsilon;
extern int nearly_equals(float, float);

/* vector observer functions */
extern float vec_len(const struct hcoord*);
extern int   vec_is_null(const struct hcoord*);
extern int   vec_is_unit(const struct hcoord*);
extern int   vec_is_ortho(const struct hcoord*, const struct hcoord*);

/* basic vector operations */
extern struct hcoord *vec_scale(
		struct hcoord*, 
		const struct hcoord*, 
		float);
extern struct hcoord *vec_unit(
		struct hcoord*, 
		const struct hcoord*);
extern struct hcoord *vec_add(
		struct hcoord*, 
		const struct hcoord*,
		const struct hcoord*);
extern struct hcoord *vec_sub(
		struct hcoord*, 
		const struct hcoord*, 
		const struct hcoord*);
extern struct hcoord *vec_cross(
		struct hcoord*, 
		const struct hcoord*, 
		const struct hcoord*);
extern float vec_dot(
		const struct hcoord*, 
		const struct hcoord*);

/* in-place vector operations */
extern struct hcoord *vec_scale_self(struct hcoord*, float);
extern struct hcoord *vec_unit_self(struct hcoord*);
extern struct hcoord *vec_add_self(struct hcoord*, const struct hcoord*);
extern struct hcoord *vec_sub_self(struct hcoord*, const struct hcoord*);

/* matrix operations */
extern union matrix *mat_x_mat(
		union matrix*,
		const union matrix*,
		const union matrix*);
extern struct hcoord *mat_x_vec(
		struct hcoord*, 
		const union matrix*,
		const struct hcoord*);
extern union matrix *mat_transpose(
		union matrix*, 
		const union matrix*);


#endif /* _MATH3D_H */
