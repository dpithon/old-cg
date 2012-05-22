#include <math.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
            return diff < Epsilon;
        } else { // use relative error
            return diff / (absA + absB) < Epsilon;
        }
}


struct hcoord *homogeneize(struct hcoord *c)
{
	assert(! nearly_equals(c->w, 0.F));

	c->x /= c->w;
	c->y /= c->w;
	c->z /= c->w;
	c->w = 1.F;

	return c;
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

#define STACK_SZ	50
#define STACK_MAX	(STACK_SZ - 1)
static union matrix stack[STACK_SZ];
static union matrix transf, bufmtx;
static int stcki = -1;
#ifndef M_PI
#define M_PI 3.14159265358979323846F
#endif /* M_PI */

static void stack_error(void)
{
	fprintf(stderr, "stack overflow\n");
	exit(EXIT_FAILURE);
}


void model_push(void)
{
	int n;

	if (stcki < STACK_MAX) {
		n = stcki + 1;
		memcpy(&stack[n], &stack[stcki], sizeof(union matrix));
		stcki = n;
	} else {
		stack_error();
	}
}


void model_pop(void)
{
	if (stcki > -1) {
		stcki --;
	} else {
		stack_error();
	}
}


void model_load_id(void)
{
	int row, col;
	if (stcki < STACK_MAX) {
		stcki ++;
		FOR_EACH_CELL(row, col) {
			CELL(&stack[stcki], row, col) = row == col ? 1.F : 0.F;
		}
	} else {
		stack_error();
	}
}


void model_translate(float tx, float ty, float tz)
{
	if (stcki > -1) {
		transf.cell[0][0] = 1.F;
		transf.cell[0][1] = 0.F;
		transf.cell[0][2] = 0.F;
		transf.cell[0][3] = tx;

		transf.cell[1][0] = 0.F;
		transf.cell[1][1] = 1.F;
		transf.cell[1][2] = 0.F;
		transf.cell[1][3] = ty;

		transf.cell[2][0] = 0.F;
		transf.cell[2][1] = 0.F;
		transf.cell[2][2] = 1.F;
		transf.cell[2][3] = tz;

		transf.cell[3][0] = 0.F;
		transf.cell[3][1] = 0.F;
		transf.cell[3][2] = 0.F;
		transf.cell[3][3] = 1.F;

		mat_mulm(&bufmtx, &stack[stcki], &transf);
		memcpy(&stack[stcki], &bufmtx, sizeof bufmtx);
	} else {
		stack_error();
	}
}


void model_scale(float sx, float sy, float sz)
{
	if (stcki > -1) {
		transf.cell[0][0] = sx;
		transf.cell[0][1] = 0.F;
		transf.cell[0][2] = 0.F;
		transf.cell[0][3] = 0.F;

		transf.cell[1][0] = 0.F;
		transf.cell[1][1] = sy;
		transf.cell[1][2] = 0.F;
		transf.cell[1][3] = 0.F;

		transf.cell[2][0] = 0.F;
		transf.cell[2][1] = 0.F;
		transf.cell[2][2] = sz;
		transf.cell[2][3] = 0.F;

		transf.cell[3][0] = 0.F;
		transf.cell[3][1] = 0.F;
		transf.cell[3][2] = 0.F;
		transf.cell[3][3] = 1.F;

		mat_mulm(&bufmtx, &stack[stcki], &transf);
		memcpy(&stack[stcki], &bufmtx, sizeof bufmtx);
	} else {
		stack_error();
	}
}


void model_rotate_x(float deg)
{
	if (stcki > -1) {

		float rad = M_PI * deg / 180.F;
		float sin = sinf(rad);
		float cos = cosf(rad);

		transf.cell[0][0] = 1.F;
		transf.cell[0][1] = 0.F;
		transf.cell[0][2] = 0.F;
		transf.cell[0][3] = 0.F;

		transf.cell[1][0] = 0.F;
		transf.cell[1][1] = cos;
		transf.cell[1][2] = -sin;
		transf.cell[1][3] = 0.F;

		transf.cell[2][0] = 0.F;
		transf.cell[2][1] = sin;
		transf.cell[2][2] = cos;
		transf.cell[2][3] = 0.F;

		transf.cell[3][0] = 0.F;
		transf.cell[3][1] = 0.F;
		transf.cell[3][2] = 0.F;
		transf.cell[3][3] = 1.F;

		mat_mulm(&bufmtx, &stack[stcki], &transf);
		memcpy(&stack[stcki], &bufmtx, sizeof bufmtx);
	} else {
		stack_error();
	}
}


void model_rotate_y(float deg)
{
	if (stcki > -1) {

		float rad = M_PI * deg / 180.F;
		float sin = sinf(rad);
		float cos = cosf(rad);

		transf.cell[0][0] = cos;
		transf.cell[0][1] = 0.F;
		transf.cell[0][2] = sin;
		transf.cell[0][3] = 0.F;

		transf.cell[1][0] = 0.F;
		transf.cell[1][1] = 1.F;
		transf.cell[1][2] = 0.F;
		transf.cell[1][3] = 0.F;

		transf.cell[2][0] = -sin;
		transf.cell[2][1] = 0.F;
		transf.cell[2][2] = cos;
		transf.cell[2][3] = 0.F;

		transf.cell[3][0] = 0.F;
		transf.cell[3][1] = 0.F;
		transf.cell[3][2] = 0.F;
		transf.cell[3][3] = 1.F;

		mat_mulm(&bufmtx, &stack[stcki], &transf);
		memcpy(&stack[stcki], &bufmtx, sizeof bufmtx);
	} else {
		stack_error();
	}
}


void model_rotate_z(float deg)
{
	if (stcki > -1) {
		float rad = M_PI * deg / 180.F;
		float sin = sinf(rad);
		float cos = cosf(rad);

		transf.cell[0][0] = cos;
		transf.cell[0][1] = -sin;
		transf.cell[0][2] = 0.F;
		transf.cell[0][3] = 0.F;

		transf.cell[1][0] = sin;
		transf.cell[1][1] = cos;
		transf.cell[1][2] = 0.F;
		transf.cell[1][3] = 0.F;

		transf.cell[2][0] = 0.F;
		transf.cell[2][1] = 0.F;
		transf.cell[2][2] = 1.F;
		transf.cell[2][3] = 0.F;

		transf.cell[3][0] = 0.F;
		transf.cell[3][1] = 0.F;
		transf.cell[3][2] = 0.F;
		transf.cell[3][3] = 1.F;

		mat_mulm(&bufmtx, &stack[stcki], &transf);
		memcpy(&stack[stcki], &bufmtx, sizeof bufmtx);
	} else {
		stack_error();
	}
}


void model_multiply(const union matrix *m)
{
	if (stcki > -1) {
		mat_mulm(&bufmtx, &stack[stcki], m);
		memcpy(&stack[stcki], &bufmtx, sizeof bufmtx);
	} else {
		stack_error();
	}
}


void model_vertex(struct hcoord* c)
{
	static struct hcoord tmp;

	mat_mulv(&tmp, &stack[stcki], c);
	memcpy(c, &tmp, sizeof tmp);
}
