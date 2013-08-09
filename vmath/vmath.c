#include <math.h>
#include <string.h>
#include <assert.h>
#include "vmath.h" 

#define DOT(u,v) ((u)->x * (v)->x + (u)->y * (v)->y + (u)->z * (v)->z)
#define EPSILON 0.001

static float Epsilon = EPSILON;
static bool nearly_equals(float a, float b);

const matrix_st matrix_id = MAT_ID;
const coord_st  vector_i  = VEC_I;
const coord_st  vector_j  = VEC_J;
const coord_st  vector_k  = VEC_K;
const coord_st  point_o   = PNT_O;

mstack_st mstack = {
	.i = 0,
	.m = { MAT_ID }
};

bool is_point(const coord_st *c) 
{
	return c->w == 1.F; 
}


bool is_vector(const coord_st *c)
{
	return c->w == 0.F; 
}


bool is_zero(const coord_st *v)
{
	assert(is_vector(v));

	return nearly_equals( len(v), 0.F );
}


bool is_unit(const coord_st *v)
{
	assert(is_vector(v));

	return nearly_equals( len(v), 1.F );
}


bool is_ortho(const coord_st *u, const coord_st *v)
{
	assert(is_vector(u)); /* u, w are vectors */
	assert(is_vector(v));

	return nearly_equals( DOT(u, v), 0.F );
}


float len(const coord_st *v)
{
	assert(is_vector(v));

	return sqrtf(DOT(v, v));
}


float dot(const coord_st *v, const coord_st *u)
{
	assert(is_vector(u));
	assert(is_vector(v));

	return DOT(u, v);
}


coord_st *vector(coord_st *v, const coord_st *p, const coord_st *q)
{
	assert(is_point(p));
	assert(is_point(q));

	v->x = q->x - p->x;
	v->y = q->y - p->y;
	v->z = q->z - p->z;
	v->w = 0.F;

	return v;
}


coord_st *scale(coord_st *v, coord_st *u, float k)
{
	assert(is_vector(u));

	v->x = u->x * k;
	v->y = u->y * k;
	v->z = u->z * k;
	v->w = 0.F;

	return v;
}


coord_st *unit(coord_st *v, coord_st *u)
{
	assert(is_vector(u));
	assert(! is_zero(u));

	float l = sqrtf(DOT(u, u));

	v->x = u->x / l;
	v->y = u->y / l;
	v->z = u->z / l;
	v->w = 0.F;

	return v;
}


coord_st *add(coord_st *v, coord_st *u, coord_st *w)
{
	assert(is_vector(u));
	assert(is_vector(w));

	v->x = u->x + w->x;
	v->y = u->y + w->y;
	v->z = u->z + w->z;
	v->w = 0.F;

	return v;
}


coord_st *sub(coord_st *v, coord_st *u, coord_st *w)
{
	assert(is_vector(u));
	assert(is_vector(w));

	v->x = u->x - w->x;
	v->y = u->y - w->y;
	v->z = u->z - w->z;
	v->w = 0.F;

	return w;
}


coord_st *cross(coord_st *v, const coord_st *u, const coord_st *w)
{
	assert(is_vector(u));
	assert(is_vector(w));

	v->x = u->y * w->z  -  u->z * w->y;
	v->y = u->z * w->x  -  u->x * w->z;
	v->z = u->x * w->y  -  u->y * w->x;
	v->w = 0.F;

	return v;
}


coord_st *homogeneize(coord_st *p, coord_st *q)
{
	assert(is_point(q));

	p->x /= q->w;
	p->y /= q->w;
	p->z /= q->w;
	p->w = 1.F;

	return p;
}


#define E(m, r, c)	((m)->cell[r][c])
#define ROW_MUL(m, r, v) E(m, r, 0) * ((v)->x) +\
			 E(m, r, 1) * ((v)->y) +\
			 E(m, r, 2) * ((v)->z) +\
			 E(m, r, 3) * ((v)->w)
coord_st *mulc(coord_st *v, const matrix_st *m, coord_st *u)
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


matrix_st *mulm(matrix_st *m, matrix_st *m1, matrix_st *m2)
{
	int i, j, k;
	matrix_st tmp, *old = 0;

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


matrix_st *transpose(matrix_st *m, matrix_st *n)
{
	int i, j;
	matrix_st tmp;

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


matrix_st *rotationx(matrix_st *m, float a)
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


matrix_st *rotationy(matrix_st *m, float a)
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


matrix_st *rotationz(matrix_st *m, float a)
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


matrix_st *rotation(matrix_st *m, const coord_st *v, float a)
{
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

	assert(is_unit(v));

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


matrix_st *translation(matrix_st *m, coord_st *v)
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


void stack_init_r(mstack_st *s)
{
	s->i = 0;
	memcpy(&(s->m[0]), &matrix_id, sizeof matrix_id);
}


bool stack_push_r(mstack_st *s, const matrix_st *m) 
{
	if (s->i + 1 == MAX_STACK_SIZE) {
		return 1;
	}

	mulm(&(s->m[s->i + 1]), &(s->m[s->i]), (matrix_st*) m);
	++ s->i;

	return 0;
}


bool stack_pop_r(mstack_st *s)
{
	if (s->i) {
		-- s->i;
		return 0;
	}

	return 1;
}


const matrix_st *stack_peek_r(mstack_st *s)
{
	return (const matrix_st*) &(s->m[s->i]);
}



bool stack_push(const matrix_st *s)
{
	return stack_push_r(&mstack, s);
}


bool stack_pop(void)
{
	return stack_pop_r(&mstack);
}


const matrix_st *stack_peek(void)
{
	return stack_peek_r(&mstack);
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
