#include <assert.h>
#include <string.h>
#include <math.h>

#define _MATH_INTERNALS

#include "core.h"
#include "settings.p"

#define DOT(u,v) 	 ((u)->x * (v)->x + (u)->y * (v)->y + (u)->z * (v)->z)
#define E(m, r, c)	 ((m)->cell[r][c])
#define ROW_MUL(m, r, v) E(m, r, 0) * ((v)->x) +\
			 E(m, r, 1) * ((v)->y) +\
			 E(m, r, 2) * ((v)->z) +\
			 E(m, r, 3) * ((v)->w)


static bool float_equals(float a, float b);

const matrix_t MatrixId = MATRIX_ID;
const coord_t  VectorI  = VECTOR_I;
const coord_t  VectorJ  = VECTOR_J;
const coord_t  VectorK  = VECTOR_K;
const coord_t  PointO   = POINT_O;


bool is_point(const coord_t *c)
{
	return c->w != 0.F;
}


bool is_vector(const coord_t *c)
{
	return c->w == 0.F;
}


bool is_vzero(const coord_t *v)
{
	assert(is_vector(v));

	return float_equals(v->x, 0.F) && float_equals(v->y, 0.F) &&
		float_equals(v->z, 0.F);
}


bool is_vunit(const coord_t *v)
{
	assert(is_vector(v));

	return float_equals(len(v), 1.F);
}


bool is_vortho(const coord_t *u, const coord_t *v)
{
	assert(is_vector(u)); /* u, w are vectors */
	assert(is_vector(v));

	return float_equals(DOT(u, v), 0.F);
}


bool is_vequal(const coord_t *u, const coord_t *v)
{
	assert(is_vector(u)); /* u, w are vectors */
	assert(is_vector(v));

	return float_equals(u->x, v->x) && float_equals(u->y, v->y) &&
	       float_equals(u->z, v->z) && float_equals(u->w, v->w);
}


bool is_pequal(const coord_t *u, const coord_t *v)
{
	assert(is_point(u)); /* u, w are points */
	assert(is_point(v));

	return float_equals(u->x, v->x) && float_equals(u->y, v->y) &&
	       float_equals(u->z, v->z) && float_equals(u->w, v->w);
}


bool is_mequal(const matrix_t *m, const matrix_t *n)
{
	int i, j;

	for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++)
			if (!float_equals(m->cell[i][j], n->cell[i][j]))
				return false;
	return true;
}


bool is_collinear(const coord_t *u, const coord_t *v, float *k)
{
	coord_t w;
	float tmp;

	if (k == NULL)
		k = &tmp;

	assert(is_vector(u));
	assert(is_vector(v));

	if (is_vzero(u) || is_vzero(v))
		return true;

	if (! float_equals(v->x, 0.F))
		*k = u->x / v->x;
	else if (! float_equals(v->y, 0.F))
		*k = u->y / v->y;
	else
		*k = u->z / v->z;

	return is_vequal(scale(&w, (coord_t*) v, *k), u);
}


bool is_pccs(const coord_t *i, const coord_t *j, const coord_t *k)
{
	coord_t t;

	return is_vunit(i) && is_vunit(j) && is_vunit(k) &&
	       is_vequal(i, cross(&t, j, k)) &&
	       is_vequal(j, cross(&t, k, i)) &&
	       is_vequal(k, cross(&t, i, j));
}


float len(const coord_t *v)
{
	assert(is_vector(v));

	return sqrtf(DOT(v, v));
}


float dot(const coord_t *v, const coord_t *u)
{
	assert(is_vector(u));
	assert(is_vector(v));

	return DOT(u, v);
}


coord_t *vector(coord_t *v, const coord_t *p, const coord_t *q)
{
	assert(is_point(p));
	assert(is_point(q));

	v->x = q->x / q->w - p->x / p->w;
	v->y = q->y / q->w - p->y / p->w;
	v->z = q->z / q->w - p->z / p->w;
	v->w = 0.F;

	return v;
}


coord_t *unit_vector(coord_t *v, const coord_t *p, const coord_t *q)
{
	return unit_me(vector(v, p, q));
}


coord_t *scale(coord_t *v, const coord_t *u, float k)
{
	v->x = u->x * k;
	v->y = u->y * k;
	v->z = u->z * k;

	return v;
}


coord_t *scale_me(coord_t *v, float k)
{
	v->x *= k;
	v->y *= k;
	v->z *= k;

	return v;
}


coord_t *unit(coord_t *v, const coord_t *u)
{
	assert(is_vector(u));
	assert(! is_vzero(u));

	float l = sqrtf(DOT(u, u));

	v->x = u->x / l;
	v->y = u->y / l;
	v->z = u->z / l;
	v->w = 0.F;

	return v;
}


coord_t *unit_me(coord_t *v)
{
	assert(is_vector(v));
	assert(! is_vzero(v));

	float l = sqrtf(DOT(v, v));

	v->x /= l;
	v->y /= l;
	v->z /= l;
	v->w = 0.F;

	return v;
}


coord_t *add(coord_t *v, const coord_t *u, const coord_t *w)
{
	v->x = u->x + w->x;
	v->y = u->y + w->y;
	v->z = u->z + w->z;

	return v;
}


coord_t *add_me(coord_t *v, const coord_t *u)
{
	v->x += u->x;
	v->y += u->y;
	v->z += u->z;

	return v;
}


coord_t *sub(coord_t *v, const coord_t *u, const coord_t *w)
{
	v->x = u->x - w->x;
	v->y = u->y - w->y;
	v->z = u->z - w->z;

	return v;
}


coord_t *sub_me(coord_t *v, const coord_t *u)
{
	v->x -= u->x;
	v->y -= u->y;
	v->z -= u->z;

	return v;
}


coord_t *cross(coord_t *v, const coord_t *u, const coord_t *w)
{
	assert(is_vector(u));
	assert(is_vector(w));

	v->x = u->y * w->z  -  u->z * w->y;
	v->y = u->z * w->x  -  u->x * w->z;
	v->z = u->x * w->y  -  u->y * w->x;
	v->w = 0.F;

	return v;
}


coord_t *matcol(coord_t *v, const matrix_t *m, coord_t *u)
{
	coord_t tmp;

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


coord_t *homogeneize(coord_t *p, const coord_t *q)
{
	assert(is_point(q));

	p->x = q->x / q->w;
	p->y = q->y / q->w;
	p->z = q->z / q->w;
	p->w = 1.F;

	return p;
}


coord_t *homogeneize_me(coord_t *p)
{
	assert(is_point(p));

	p->x /= p->w;
	p->y /= p->w;
	p->z /= p->w;
	p->w = 1.F;

	return p;
}


matrix_t *matrix(matrix_t *m, const coord_t *i, const coord_t *j,
		 const coord_t *k, const coord_t *o)
{
	m->cell[0][0] = i->x;
	m->cell[1][0] = i->y;
	m->cell[2][0] = i->z;
	m->cell[3][0] = i->w;

	m->cell[0][1] = j->x;
	m->cell[1][1] = j->y;
	m->cell[2][1] = j->z;
	m->cell[3][1] = j->w;

	m->cell[0][2] = k->x;
	m->cell[1][2] = k->y;
	m->cell[2][2] = k->z;
	m->cell[3][2] = k->w;

	m->cell[0][3] = o->x;
	m->cell[1][3] = o->y;
	m->cell[2][3] = o->z;
	m->cell[3][3] = o->w;

	return m;
}


matrix_t *matrixr(matrix_t *m, const coord_t *i, const coord_t *j,
		  const coord_t *k, const coord_t *o)
{
	m->cell[0][0] = i->x;
	m->cell[0][1] = i->y;
	m->cell[0][2] = i->z;
	m->cell[0][3] = i->w;

	m->cell[1][0] = j->x;
	m->cell[1][1] = j->y;
	m->cell[1][2] = j->z;
	m->cell[1][3] = j->w;

	m->cell[2][0] = k->x;
	m->cell[2][1] = k->y;
	m->cell[2][2] = k->z;
	m->cell[2][3] = k->w;

	m->cell[3][0] = o->x;
	m->cell[3][1] = o->y;
	m->cell[3][2] = o->z;
	m->cell[3][3] = o->w;

	return m;
}


matrix_t *matmat(matrix_t *m, const matrix_t *m1, const matrix_t *m2)
{
	int i, j, k;
	matrix_t tmp, *old = 0;

	if (m == m1 || m == m2) {
		old = m;
		m  = &tmp;
	}

	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
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


matrix_t *transpose(matrix_t *m, matrix_t *n)
{
	int i, j;
	matrix_t tmp;

	if (n == m) {
		memcpy(&tmp, n, sizeof tmp);
		n = &tmp;
	}

	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			E(m, i, j) = E(n, j, i);
		}
	}

	return m;
}


matrix_t *rotationx(matrix_t *m, float a)
{
	float ca = cosf(a);
	float sa = sinf(a);

	E(m, 0, 0) = 1.F;
	E(m, 0, 1) = 0.F;
	E(m, 0, 2) = 0.F;
	E(m, 0, 3) = 0.F;

	E(m, 1, 0) = 0.F;
	E(m, 1, 1) = ca;
	E(m, 1, 2) = -sa;
	E(m, 1, 3) = 0.F;

	E(m, 2, 0) = 0.F;
	E(m, 2, 1) = sa;
	E(m, 2, 2) = ca;
	E(m, 2, 3) = 0.F;

	E(m, 3, 0) = 0.F;
	E(m, 3, 1) = 0.F;
	E(m, 3, 2) = 0.F;
	E(m, 3, 3) = 1.F;

	return m;
}


matrix_t *rotationy(matrix_t *m, float a)
{
	float ca = cosf(a);
	float sa = sinf(a);

	E(m, 0, 0) = ca;
	E(m, 0, 1) = 0.F;
	E(m, 0, 2) = sa;
	E(m, 0, 3) = 0.F;

	E(m, 1, 0) = 0.F;
	E(m, 1, 1) = 1.F;
	E(m, 1, 2) = 0.F;
	E(m, 1, 3) = 0.F;

	E(m, 2, 0) = -sa;
	E(m, 2, 1) = 0.F;
	E(m, 2, 2) = ca;
	E(m, 2, 3) = 0.F;

	E(m, 3, 0) = 0.F;
	E(m, 3, 1) = 0.F;
	E(m, 3, 2) = 0.F;
	E(m, 3, 3) = 1.F;

	return m;
}


matrix_t *rotationz(matrix_t *m, float a)
{
	float ca = cosf(a);
	float sa = sinf(a);

	E(m, 0, 0) = ca;
	E(m, 0, 1) = -sa;
	E(m, 0, 2) = 0.F;
	E(m, 0, 3) = 0.F;

	E(m, 1, 0) = sa;
	E(m, 1, 1) = ca;
	E(m, 1, 2) = 0.F;
	E(m, 1, 3) = 0.F;

	E(m, 2, 0) = 0.F;
	E(m, 2, 1) = 0.F;
	E(m, 2, 2) = 1.F;
	E(m, 2, 3) = 0.F;

	E(m, 3, 0) = 0.F;
	E(m, 3, 1) = 0.F;
	E(m, 3, 2) = 0.F;
	E(m, 3, 3) = 1.F;

	return m;
}


matrix_t *rotation(matrix_t *m, const coord_t *v, float a)
{
	assert(is_vunit(v));

	float c = cosf(a);
	float s = sinf(a);
	float x = v->x;
	float y = v->y;
	float z = v->z;
	float xy = v->x * v->y;
	float xz = v->x * v->z;
	float yz = v->y * v->z;
	float x2 = v->x * v->x;
	float y2 = v->y * v->y;
	float z2 = v->z * v->z;

	E(m, 0, 0) = x2 + (1 - x2) * c;
	E(m, 0, 1) = xy * (1 - c) - s * z;
	E(m, 0, 2) = xz * (1 - c) + s * y;
	E(m, 0, 3) = 0.F;

	E(m, 1, 0) = xy * (1 - c) + s * z;
	E(m, 1, 1) = y2 + (1 - y2) * c;
	E(m, 1, 2) = yz * (1 - c) - s * x;
	E(m, 1, 3) = 0.F;

	E(m, 2, 0) = xz * (1 - c) - s * y;
	E(m, 2, 1) = yz * (1 - c) + s * x;
	E(m, 2, 2) = z2 + (1 - z2) * c;
	E(m, 2, 3) = 0.F;

	E(m, 3, 0) = 0.F;
	E(m, 3, 1) = 0.F;
	E(m, 3, 2) = 0.F;
	E(m, 3, 3) = 1.F;

	return m;
}


matrix_t *translation(matrix_t *m, coord_t *v)
{
	E(m, 0, 0) = 1.F;
        E(m, 0, 1) = 0.F;
        E(m, 0, 2) = 0.F;
        E(m, 0, 3) = v->x;

        E(m, 1, 0) = 0.F;
        E(m, 1, 1) = 1.F;
        E(m, 1, 2) = 0.F;
        E(m, 1, 3) = v->y;

        E(m, 2, 0) = 0.F;
        E(m, 2, 1) = 0.F;
        E(m, 2, 2) = 1.F;
        E(m, 2, 3) = v->z;

        E(m, 3, 0) = 0.F;
        E(m, 3, 1) = 0.F;
        E(m, 3, 2) = 0.F;
        E(m, 3, 3) = 1.F;

	return m;
}


bool change_of_coord_mat(ccs_t *ccs)
{
	matrix_t rot, tsl;
	coord_t minus_os;

	matrix(&ccs->m, &ccs->i, &ccs->j, &ccs->k, &ccs->o);

	translation(&tsl, scale(&minus_os, &ccs->o, -1.F));
	matrixr(&rot, &ccs->i, &ccs->j, &ccs->k, &PointO);
	matmat(&ccs->mi, &rot, &tsl);

	return is_pccs(&ccs->i, &ccs->j, &ccs->k);
}


static bool float_equals(float a, float b)
{
	float absA = fabsf(a);
        float absB = fabsf(b);
        float diff = fabsf(a - b);

        if (a == b) { // shortcut, handles infinities
		return true;

        } else if (a * b == 0) { // a or b or both are zero
		// relative error is not meaningful here
		return diff < vmset_eps;

        } else { // use relative error
            return diff / (absA + absB) < vmset_eps;
        }
}
