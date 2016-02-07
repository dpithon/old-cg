#include <assert.h>
#include <string.h>
#include <math.h>

#define _VMATH_INTERNALS

#include "core.h"
#include "stat.h"
#include "stat.p"
#include "settings.p"

#define DOT(u,v) 	 ((u)->x * (v)->x + (u)->y * (v)->y + (u)->z * (v)->z)
#define E(m, r, c)	 ((m)->cell[r][c])
#define ROW_MUL(m, r, v) E(m, r, 0) * ((v)->x) +\
			 E(m, r, 1) * ((v)->y) +\
			 E(m, r, 2) * ((v)->z) +\
			 E(m, r, 3) * ((v)->w)


static bool float_equals(float a, float b);

const matrix_t matrix_id = MAT_ID;
const coord_t  vector_i  = VEC_I;
const coord_t  vector_j  = VEC_J;
const coord_t  vector_k  = VEC_K;
const coord_t  point_o   = PNT_O;


bool is_point(const coord_t *c) 
{
	IS_PNT(1);
	CMP(1);

	return c->w != 0.F; 
}


bool is_vector(const coord_t *c)
{
	IS_VEC(1);
	CMP(1);

	return c->w == 0.F; 
}


bool is_vzero(const coord_t *v)
{
	IS_0(1);

	assert(is_vector(v));

	return float_equals(len(v), 0.F);
}


bool is_vunit(const coord_t *v)
{
	IS_1(1);

	assert(is_vector(v));

	return float_equals(len(v), 1.F);
}


bool is_vortho(const coord_t *u, const coord_t *v)
{
	IS_ORT(1); 
	ADD(2); MUL(3);

	assert(is_vector(u)); /* u, w are vectors */
	assert(is_vector(v));

	return float_equals(DOT(u, v), 0.F);
}


float len(const coord_t *v)
{
	FN_LEN(1); 
	SQR(1); ADD(2); MUL(3);

	assert(is_vector(v));

	return sqrtf(DOT(v, v));
}


float dot(const coord_t *v, const coord_t *u)
{
	FN_DOT(1); 
	ADD(2); MUL(3);

	assert(is_vector(u));
	assert(is_vector(v));

	return DOT(u, v);
}


coord_t *vector(coord_t *v, const coord_t *p, const coord_t *q)
{
	FN_VEC(1); 
	ADD(3); STO(4);

	assert(is_point(p));
	assert(is_point(q));

	v->x = q->x / q->w - p->x / p->w;
	v->y = q->y / q->w - p->y / p->w;
	v->z = q->z / q->w - p->z / p->w;
	v->w = 0.F;

	return v;
}


coord_t *scale(coord_t *v, coord_t *u, float k)
{
	FN_SCL(1); 
	STO(4); MUL(3);

	assert(is_vector(u));

	v->x = u->x * k;
	v->y = u->y * k;
	v->z = u->z * k;
	v->w = 0.F;

	return v;
}


coord_t *unit(coord_t *v, coord_t *u)
{
	FN_1(1); 
	STO(5); SQR(1); MUL(6); ADD(2);

	assert(is_vector(u));
	assert(! is_vzero(u));

	float l = sqrtf(DOT(u, u));

	v->x = u->x / l;
	v->y = u->y / l;
	v->z = u->z / l;
	v->w = 0.F;

	return v;
}


coord_t *add(coord_t *v, coord_t *u, coord_t *w)
{
	FN_ADD(1); 
	STO(4); ADD(3);

	assert(is_vector(u));
	assert(is_vector(w));

	v->x = u->x + w->x;
	v->y = u->y + w->y;
	v->z = u->z + w->z;
	v->w = 0.F;

	return v;
}


coord_t *sub(coord_t *v, coord_t *u, coord_t *w)
{
	FN_SUB(1); 
	STO(4); ADD(3);

	assert(is_vector(u));
	assert(is_vector(w));

	v->x = u->x - w->x;
	v->y = u->y - w->y;
	v->z = u->z - w->z;
	v->w = 0.F;

	return w;
}


coord_t *cross(coord_t *v, const coord_t *u, const coord_t *w)
{
	FN_X(1); 
	STO(4); MUL(6); ADD(3);

	assert(is_vector(u));
	assert(is_vector(w));

	v->x = u->y * w->z  -  u->z * w->y;
	v->y = u->z * w->x  -  u->x * w->z;
	v->z = u->x * w->y  -  u->y * w->x;
	v->w = 0.F;

	return v;
}


coord_t *homogeneize(coord_t *p, coord_t *q)
{
	FN_HMG(1); 
	STO(1); MUL(3);

	assert(is_point(q));

	p->x /= q->w;
	p->y /= q->w;
	p->z /= q->w;
	p->w = 1.F;

	return p;
}


coord_t *mulc(coord_t *v, const matrix_t *m, coord_t *u)
{
	FN_MXC(1);
	CMP(1); IDX(16); MUL(16); ADD(12); STO((u == v) ? 9 : 4);

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
 

matrix_t *mulm(matrix_t *m, matrix_t *m1, matrix_t *m2)
{
	FN_MXM(1);
	ADD(148); MUL(64); IDX(208);
	CMP((m == m1) ? 107 : 108);
	STO((m == m1) || (m == m2) ? 35 : 16);

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
	FN_T(1);
	CMP(26); STO(n == m ? 38 : 21); ADD(20); IDX(32);

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
	FN_RTX(1);
	TRG(2); STO(18); NEG(1); IDX(16);

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
	FN_RTY(1);
	TRG(2); STO(18); NEG(1); IDX(16);

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
	FN_RTZ(1);
	TRG(2); STO(18); NEG(1); IDX(16);

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
	FN_ROT(1);
	TRG(2); STO(27); MUL(21); ADD(18); IDX(16);

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
	FN_TSL(1);
	IDX(16); STO(16);

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


static bool float_equals(float a, float b)
{
	FN_FEQ(1);
	STO(3); ADD(1); ABS(3);

	float absA = fabsf(a);
        float absB = fabsf(b);
        float diff = fabsf(a - b);

        if (a == b) { // shortcut, handles infinities
		CMP(1);

		return true;

        } else if (a * b == 0) { // a or b or both are zero
		CMP(2); MUL(1);

		// relative error is not meaningful here
		return diff < vmset_eps;

        } else { // use relative error
		CMP(3); MUL(1); ADD(1);

            return diff / (absA + absB) < vmset_eps;
        }
}
