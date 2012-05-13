#include <math.h>
#include "math3d.h" 


#define dot(u,v) ((u)->x * (v)->x + (u)->y * (v)->y + (u)->z * (v)->z)
#define EPSILON 0.0001


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


float vector_len(const struct hcoord *v)
{
	return (float) sqrt((double) dot(v, v));
}


float vector_len2(const struct hcoord *v)
{
	return dot(v, v);
}


struct hcoord *vector_scale(struct hcoord *v, float k)
{
	v->x *= k;
	v->y *= k;
	v->z *= k;

	return v;
}


float vector_dot(const struct hcoord *u, const struct hcoord *v)
{
	return dot(u, v);
}


struct hcoord *vector_cross(struct hcoord *w, 
			    const struct hcoord *u,
			    const struct hcoord *v)
{
	w->x = u->y * v->z  -  u->z * v->y;
	w->y = u->z * v->x  -  u->x * v->z;
	w->z = u->x * v->y  -  u->y * v->x;
	w->w = 0.F;

	return w;
}


struct hcoord *vector_unit(struct hcoord *w, const struct hcoord *u)
{
	float l = (float) sqrt((double) dot(u, u));

	w->x = u->x / l;
	w->y = u->y / l;
	w->z = u->z / l;
	w->w = u->w;

	return w;
}


struct hcoord *vector_unitize(struct hcoord *u)
{
	float l = (float) sqrt((double) dot(u, u));

	u->x = u->x / l;
	u->y = u->y / l;
	u->z = u->z / l;

	return u;
}


struct hcoord *vector_sum(struct hcoord *w,
			  const struct hcoord *u,
			  const struct hcoord *v)
{
	w->x = u->x + v->x;
	w->y = u->y + v->y;
	w->z = u->z + v->z;
	w->w = 1.F;

	return w;
}


struct hcoord *vector_diff(struct hcoord *w,
			   const struct hcoord *u,
			   const struct hcoord *v)
{
	w->x = u->x - v->x;
	w->y = u->y - v->y;
	w->z = u->z - v->z;
	w->w = 1.F;

	return w;
}


struct hcoord *vector_add(struct hcoord *u, const struct hcoord *v)
{
	u->x += v->x;
	u->y += v->y;
	u->z += v->z;

	return u;
}


struct hcoord *vector_sub(struct hcoord *u, const struct hcoord *v)
{
	u->x -= v->x;
	u->y -= v->y;
	u->z -= v->z;

	return u;
}


#define FOR_EACH_CELL(i,j) for ((i) = 0; (i) < 4; (i)++) \
				for ((j) = 0; (j) < 4; (j)++)
#define CELL(m,r,c)	((m)->cell[r][c])
union matrix *matrix_mul(union matrix *m,
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


#define ROW_MUL(m, r, w) CELL(m, r, 0) * ((w).x) +\
			 CELL(m, r, 1) * ((w).y) +\
			 CELL(m, r, 2) * ((w).z) +\
			 CELL(m, r, 3) * ((w).w)
struct hcoord *matrix_apply(struct hcoord *v, const union matrix *m)
{
	struct hcoord w = *v;

	v->x = ROW_MUL(m, 0, w);
	v->y = ROW_MUL(m, 1, w);
	v->z = ROW_MUL(m, 2, w);
	v->w = ROW_MUL(m, 3, w);

	return v;
}


union matrix *matrix_transpose(union matrix *r, const union matrix *m)
{
	int row, col;

	FOR_EACH_CELL(row, col) {
		CELL(r, row, col) = CELL(m, col, row);
	}

	return r;
}
