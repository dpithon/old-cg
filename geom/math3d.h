#ifndef _MATH3D_H
#define _MATH3D_H

struct hcoord {
	float x, y, z, w;
};


union matrix { /* matrix 4x4 */
	struct rows {
		struct hcoord r1, r2, r3, r4;
	} rows;
	float cell[4][4];
};

#define VECTOR_I  { 1.F, 0.F, 0.F, 0.F }
#define VECTOR_J  { 0.F, 1.F, 0.F, 0.F }
#define VECTOR_K  { 0.F, 0.F, 1.F, 0.F }
#define POINT_O   { 0.F, 0.F, 0.F, 1.F }
#define POINT_I   { 1.F, 0.F, 0.F, 1.F }
#define POINT_J   { 0.F, 1.F, 0.F, 1.F }
#define POINT_K   { 0.F, 0.F, 1.F, 1.F }
#define MATRIX_ID { .rows = { VECTOR_I, VECTOR_J, VECTOR_K, POINT_O } }

extern float vector_len(const struct hcoord*);
extern float vector_len2(const struct hcoord*);
extern struct hcoord *vector_scale(struct hcoord*, float);
extern float vector_dot(const struct hcoord*, const struct hcoord*);
extern struct hcoord *vector_cross(struct hcoord*, 
				   const struct hcoord*, 
				   const struct hcoord*);
extern struct hcoord *vector_unit(struct hcoord*, const struct hcoord*);
extern struct hcoord *vector_unitize(struct hcoord*);
extern struct hcoord *vector_sum(struct hcoord*, 
				 const struct hcoord*,
				 const struct hcoord*);
extern struct hcoord *vector_diff(struct hcoord*, 
				  const struct hcoord*, 
				  const struct hcoord*);
extern struct hcoord *vector_add(struct hcoord*, const struct hcoord*);
extern struct hcoord *vector_sub(struct hcoord*, const struct hcoord*);

extern union matrix *matrix_mul(union matrix*,
				 const union matrix*,
				 const union matrix*);
extern struct hcoord *matrix_apply(struct hcoord*, const union matrix*);
extern union matrix *matrix_transpose(union matrix*, const union matrix*);

#endif /* _MATH3D_H */
