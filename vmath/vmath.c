#include <math.h>
#include <string.h>
#include <assert.h>
#include "vmath.h" 

#define dot(u,v) ((u)->x * (v)->x + (u)->y * (v)->y + (u)->z * (v)->z)
#define EPSILON 0.001

static float Epsilon = EPSILON;
static bool nearly_equals(float a, float b);

const matrix_st matrix_id = MAT_ID;
const coord_st  vector_i  = VEC_I;
const coord_st  vector_j  = VEC_J;
const coord_st  vector_k  = VEC_K;
const coord_st  point_o   = PNT_O;

coord_st *v_create(coord_st *v, const coord_st *p, const coord_st *q)
{
	assert(c_is_point(p));
	assert(c_is_point(q));

	v->x = q->x - p->x;
	v->y = q->y - p->y;
	v->z = q->z - p->z;
	v->w = 0.F;

	return v;
}


float v_len(const coord_st *v)
{
	assert(c_is_vector(v));

	return (float) sqrt((double) dot(v, v));
}


bool c_is_point(const coord_st *c)
{
	return c->w == 1.F; 
}


bool c_is_vector(const coord_st *c)
{
	return c->w == 0.F; 
}


bool v_is_zero(const coord_st *v)
{
	assert(c_is_vector(v));

	return nearly_equals( v_len(v), 0.F );
}


bool v_is_unit(const coord_st *v)
{
	assert(c_is_vector(v));

	return nearly_equals( v_len(v), 1.F );
}


bool v_is_ortho(const coord_st *u, const coord_st *v)
{
	assert(c_is_vector(u)); /* u, w are vectors */
	assert(c_is_vector(v));

	return nearly_equals( v_dot(u, v), 0.F );
}


coord_st *v_scale(coord_st *v, coord_st *u, float k)
{
	assert(c_is_vector(u));

	v->x = u->x * k;
	v->y = u->y * k;
	v->z = u->z * k;
	v->w = 0.F;

	return v;
}


coord_st *v_unit(coord_st *v, coord_st *u)
{
	assert(c_is_vector(u));

	float l = sqrtf(dot(u, u));

	v->x = u->x / l;
	v->y = u->y / l;
	v->z = u->z / l;
	v->w = 0.F;

	return v;
}


coord_st *v_add(coord_st *v, coord_st *u, coord_st *w)
{
	assert(c_is_vector(u));
	assert(c_is_vector(w));

	v->x = u->x + w->x;
	v->y = u->y + w->y;
	v->z = u->z + w->z;
	v->w = 0.F;

	return v;
}


coord_st *v_sub(coord_st *v, coord_st *u, coord_st *w)
{
	assert(c_is_vector(u));
	assert(c_is_vector(w));

	v->x = u->x - w->x;
	v->y = u->y - w->y;
	v->z = u->z - w->z;
	v->w = 0.F;

	return w;
}


coord_st *v_cross(coord_st *v, const coord_st *u, const coord_st *w)
{
	assert(c_is_vector(u));
	assert(c_is_vector(w));

	v->x = u->y * w->z  -  u->z * w->y;
	v->y = u->z * w->x  -  u->x * w->z;
	v->z = u->x * w->y  -  u->y * w->x;
	v->w = 0.F;

	return v;
}


float v_dot(const coord_st *v, const coord_st *u)
{
	assert(c_is_vector(u));
	assert(c_is_vector(v));

	return dot(u, v);
}


coord_st *p_homogeneize(coord_st *p, coord_st *q)
{
	assert(c_is_point(q));

	p->x /= q->w;
	p->y /= q->w;
	p->z /= q->w;
	p->w = 1.F;

	return p;
}


#define E(m, r, c)	((m)->cell[r][c])
matrix_st *m_mulm(matrix_st *m, matrix_st *m1, matrix_st *m2)
{
	int i, j, k;
	matrix_st tmp, *old = 0;

	if (m == m1 || m == m2) {
		old = m;
		m  = &tmp;
	}

	for ((i) = 0; (i) < 4; (i)++) {
		for ((j) = 0; (j) < 4; (j)++) {
			E(m, i, j) = 0.F;
			for (k = 0; k < 4; k++) {
				E(m, i, j) += E(m1, i, k) * E(m2, k, j);
			}
		}
	}

	if (old) {
		m = old;
		memcpy(m, &tmp, sizeof tmp);
	}

	return m;
}


#define ROW_MUL(m, r, v) E(m, r, 0) * ((v)->x) +\
			 E(m, r, 1) * ((v)->y) +\
			 E(m, r, 2) * ((v)->z) +\
			 E(m, r, 3) * ((v)->w)
coord_st *m_mulc(coord_st *v, const matrix_st *m, coord_st *u)
{
	coord_st tmp;

	if (u == v) {
		memcpy(&tmp, u, sizeof tmp);
		u = &tmp;
	}

	v->x = ROW_MUL(m, 0, u);
	v->y = ROW_MUL(m, 1, u);
	v->z = ROW_MUL(m, 2, u);
	v->w = ROW_MUL(m, 3, u);

	return v;
}


matrix_st *m_transpose(matrix_st *m, matrix_st *n)
{
	int i, j;
	matrix_st tmp;

	if (n == m) {
		memcpy(&tmp, n, sizeof tmp);
		n = &tmp;
	}

	for ((i) = 0; (i) < 4; (i)++) {
		for ((j) = 0; (j) < 4; (j)++) {
			E(m, i, j) = E(n, j, i);
		}
	}

	return m;
}


static bool nearly_equals(float a, float b)
{
	float absA = fabsf(a);
        float absB = fabsf(b);
        float diff = fabsf(a - b);

        if (a == b) { // shortcut, handles infinities
            return true;
        } else if (a * b == 0) { // a or b or both are zero
            // relative error is not meaningful here
            return diff < Epsilon;
        } else { // use relative error
            return diff / (absA + absB) < Epsilon;
        }
}
