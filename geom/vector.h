#ifndef _VECTOR_H
#define _VECTOR_H

struct vector {
	float x, y, z, w;
};

#define VECTOR_I { 1.F, 0.F, 0.F, 0.F }
#define VECTOR_J { 0.F, 1.F, 0.F, 0.F }
#define VECTOR_K { 0.F, 0.F, 1.F, 0.F }

float vector_len(const struct vector*);
float vector_len2(const struct vector*);
float vector_dot(const struct vector*, const struct vector*);
struct vector *vector_cross(struct vector*, 
			    const struct vector*, 
			    const struct vector*);
struct vector *vector_unit(struct vector*, const struct vector*);
struct vector *vector_unit_self(struct vector*);
struct vector *vector_sum(struct vector*, 
			  const struct vector*,
			  const struct vector*);
struct vector *vector_diff(struct vector*, 
			   const struct vector*, 
			   const struct vector*);
struct vector *vector_add(struct vector*, const struct vector*);
struct vector *vector_sub(struct vector*, const struct vector*);

#endif /* _VECTOR_H */
