#include <math.h>
#include "math3d.h" 


#define dot(u,v) ((u)->x * (v)->x + (u)->y * (v)->y + (u)->z * (v)->z)
#define EPSILON 0.001


float Epsilon = EPSILON;

int nearly_equals(float a, float b)
{
	float absA = fabsf(a);
        float absB = fabsf(b);
        float diff = fabsf(a - b);

        if (a == b) { // shortcut, handles infinities
            return 1;
        } else if (a * b == 0) { // a or b or both are zero
            // relative error is not meaningful here
            return diff < (Epsilon * Epsilon);
        } else { // use relative error
            return diff / (absA + absB) < Epsilon;
        }
}


float vec_len(const struct hcoord *v)
{
	return (float) sqrt((double) dot(v, v));
}


struct hcoord *vec_from_point(struct hcoord *u,
			      struct hcoord *a,
			      struct hcoord *b)
{
	u->x = b->x - a->x;
	u->y = b->y - a->y;
	u->z = b->z - a->z;
	u->w = 0.F;

	return u;
}


struct hcoord *vec_scale_self(struct hcoord *v, float k)
{
	v->x *= k;
	v->y *= k;
	v->z *= k;

	return v;
}


float vec_dot(const struct hcoord *u, const struct hcoord *v)
{
	return dot(u, v);
}


struct hcoord *vec_cross(struct hcoord *w, 
			    const struct hcoord *u,
			    const struct hcoord *v)
{
	w->x = u->y * v->z  -  u->z * v->y;
	w->y = u->z * v->x  -  u->x * v->z;
	w->z = u->x * v->y  -  u->y * v->x;
	w->w = 0.F;

	return w;
}


struct hcoord *vec_unit(struct hcoord *w, const struct hcoord *u)
{
	float l = (float) sqrt((double) dot(u, u));

	w->x = u->x / l;
	w->y = u->y / l;
	w->z = u->z / l;
	w->w = u->w;

	return w;
}


struct hcoord *vec_unit_self(struct hcoord *u)
{
	float l = (float) sqrt((double) dot(u, u));

	u->x = u->x / l;
	u->y = u->y / l;
	u->z = u->z / l;

	return u;
}


struct hcoord *vec_add(struct hcoord *w,
			  const struct hcoord *u,
			  const struct hcoord *v)
{
	w->x = u->x + v->x;
	w->y = u->y + v->y;
	w->z = u->z + v->z;
	w->w = 0.F;

	return w;
}


struct hcoord *vec_sub(struct hcoord *w,
			   const struct hcoord *u,
			   const struct hcoord *v)
{
	w->x = u->x - v->x;
	w->y = u->y - v->y;
	w->z = u->z - v->z;
	w->w = 0.F;

	return w;
}


struct hcoord *vec_add_self(struct hcoord *u, const struct hcoord *v)
{
	u->x += v->x;
	u->y += v->y;
	u->z += v->z;

	return u;
}


struct hcoord *vec_sub_self(struct hcoord *u, const struct hcoord *v)
{
	u->x -= v->x;
	u->y -= v->y;
	u->z -= v->z;

	return u;
}


int vec_is_null(const struct hcoord *v)
{
	return nearly_equals( vec_len(v), 0.F );
}


int vec_is_unit(const struct hcoord *v)
{
	return nearly_equals( vec_len(v), 1.F );
}


int vec_is_ortho(const struct hcoord *u, const struct hcoord *v)
{
	return nearly_equals( vec_dot(u, v), 0.F );
}


#define FOR_EACH_CELL(i,j) for ((i) = 0; (i) < 4; (i)++) \
				for ((j) = 0; (j) < 4; (j)++)
#define CELL(m,r,c)	((m)->cell[r][c])
union matrix *mat_mulm(union matrix *m,
			 const union matrix *a, 
			 const union matrix *b)
{
	int row, col, k;

	FOR_EACH_CELL(row, col) {
		CELL(m, row, col) = 0.F;
		for (k = 0; k < 4; k++) {
			CELL(m, row, col) += 
				CELL(a, row, k) * CELL(b, k, col);
		}
	}

	return m;
}


#define ROW_MUL(m, r, v) CELL(m, r, 0) * ((v)->x) +\
			 CELL(m, r, 1) * ((v)->y) +\
			 CELL(m, r, 2) * ((v)->z) +\
			 CELL(m, r, 3) * ((v)->w)
struct hcoord *mat_mulv(struct hcoord *u, 
			    const union matrix *m, 
			    const struct hcoord *v)
{
	u->x = ROW_MUL(m, 0, v);
	u->y = ROW_MUL(m, 1, v);
	u->z = ROW_MUL(m, 2, v);
	u->w = ROW_MUL(m, 3, v);

	return u;
}


union matrix *mat_transpose(union matrix *r, const union matrix *m)
{
	int row, col;

	FOR_EACH_CELL(row, col) {
		CELL(r, row, col) = CELL(m, col, row);
	}

	return r;
}
