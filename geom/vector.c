#include <math.h>
#include "vector.h" 


#define dot(u,v) ((u)->x * (v)->x + (u)->y * (v)->y + (u)->z * (v)->z)


float vector_len(const struct vector *v)
{
	return (float) sqrt((double) dot(v, v));
}


float vector_len2(const struct vector *v)
{
	return dot(v, v);
}


float vector_dot(const struct vector *u, const struct vector *v)
{
	return dot(u, v);
}


struct vector *vector_cross(struct vector *w, 
			    const struct vector *u,
			    const struct vector *v)
{
	w->x = u->y * v->z  -  u->z * v->y;
	w->y = u->z * v->x  -  u->x * v->z;
	w->z = u->x * v->y  -  u->y * v->x;
	w->w = 1.F;

	return w;
}


struct vector *vector_unit(struct vector *w, const struct vector *u)
{
	float l = (float) sqrt((double) dot(u, u));

	w->x = u->x / l;
	w->y = u->y / l;
	w->z = u->z / l;
	w->w = u->w;

	return w;
}


struct vector *vector_unit_self(struct vector *u)
{
	float l = (float) sqrt((double) dot(u, u));

	u->x = u->x / l;
	u->y = u->y / l;
	u->z = u->z / l;

	return u;
}


struct vector *vector_sum(struct vector *w,
			  const struct vector *u,
			  const struct vector *v)
{
	w->x = u->x + v->x;
	w->y = u->y + v->y;
	w->z = u->z + v->z;
	w->w = 1.F;

	return w;
}


struct vector *vector_diff(struct vector *w,
			   const struct vector *u,
			   const struct vector *v)
{
	w->x = u->x - v->x;
	w->y = u->y - v->y;
	w->z = u->z - v->z;
	w->w = 1.F;

	return w;
}


struct vector *vector_add(struct vector *u, const struct vector *v)
{
	u->x += v->x;
	u->y += v->y;
	u->z += v->z;

	return u;
}


struct vector *vector_sub(struct vector *u, const struct vector *v)
{
	u->x -= v->x;
	u->y -= v->y;
	u->z -= v->z;

	return u;
}
