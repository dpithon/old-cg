#include <string.h>
#include <math.h>

#include "log.h"
#include "vmath.h"

#define DOT(u,v) 	 ((u)->x * (v)->x + (u)->y * (v)->y + (u)->z * (v)->z)
#define E(m, r, c)	 ((m)->cell[r][c])
#define ROW_MUL(m, r, v) E(m, r, 0) * ((v)->x) +\
			 E(m, r, 1) * ((v)->y) +\
			 E(m, r, 2) * ((v)->z) +\
			 E(m, r, 3) * ((v)->w)


const struct matrix matrix_id = MATRIX_ID;
const struct coord  vector_i  = VECTOR_I;
const struct coord  vector_j  = VECTOR_J;
const struct coord  vector_k  = VECTOR_K;
const struct coord  point_o   = POINT_O;


const double epsilon=1e-4;


bool double_equals(double a, double b)
{
	double absA = fabs(a);
        double absB = fabs(b);
        double diff = fabs(a - b);

        if (a == b) { // shortcut, handles infinities
		return true;

        } else if (a * b == 0) { // a or b or both are zero
		// relative error is not meaningful here
		return diff < epsilon;

        } else { // use relative error
            return diff / (absA + absB) < epsilon;
        }
}


bool is_point(const struct coord *c)
{
	return c->w != 0.;
}


bool is_vector(const struct coord *c)
{
	return c->w == 0.;
}


bool is_vzero(const struct coord *v)
{
	assert_is_vector(v);

	return double_equals(v->x, 0.) && double_equals(v->y, 0.) &&
		double_equals(v->z, 0.);
}


bool is_vunit(const struct coord *v)
{
	assert_is_vector(v);

	return double_equals(len(v), 1.);
}


bool is_vortho(const struct coord *u, const struct coord *v)
{
	assert_is_vector(u); /* u, w are vectors */
	assert_is_vector(v);

	return double_equals(DOT(u, v), 0.);
}


bool is_vequal(const struct coord *u, const struct coord *v)
{
	assert_is_vector(u); /* u, w are vectors */
	assert_is_vector(v);

	return double_equals(u->x, v->x) && double_equals(u->y, v->y) &&
	       double_equals(u->z, v->z) && double_equals(u->w, v->w);
}


bool is_pequal(const struct coord *u, const struct coord *v)
{
	assert_is_point(u); /* u, w are points */
	assert_is_point(v);

	return double_equals(u->x, v->x) && double_equals(u->y, v->y) &&
	       double_equals(u->z, v->z) && double_equals(u->w, v->w);
}


bool is_mequal(const struct matrix *m, const struct matrix *n)
{
	int i, j;

	for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++)
			if (!double_equals(m->cell[i][j], n->cell[i][j]))
				return false;
	return true;
}


bool is_collinear(const struct coord *u, const struct coord *v, double *k)
{
	struct coord w;
	double tmp;

	assert_is_vector(u);
	assert_is_vector(v);

	if (k == NULL)
		k = &tmp;

	if (is_vzero(u) || is_vzero(v))
		return true;

	if (! double_equals(v->x, 0.)) {
		*k = u->x / v->x;
	} else if (! double_equals(v->y, 0.)) {
		*k = u->y / v->y;
	} else {
		*k = u->z / v->z;
	}

	return is_vequal(scale(&w, v, *k), u);
}


bool is_cartesian_coord_system(const struct coord *i, const struct coord *j,
			       const struct coord *k)
{
	struct coord t;

	return is_vunit(i) && is_vunit(j) && is_vunit(k) &&
	       is_vequal(i, cross(&t, j, k)) &&
	       is_vequal(j, cross(&t, k, i)) &&
	       is_vequal(k, cross(&t, i, j));
}


double len(const struct coord *v)
{
	assert_is_vector(v);

	return sqrtf(DOT(v, v));
}


double dot(const struct coord *v, const struct coord *u)
{
	assert_is_vector(u);
	assert_is_vector(v);

	return DOT(u, v);
}


struct coord *vector(struct coord *v, const struct coord *p,
		     const struct coord *q)
{
	assert_is_point(p);
	assert_is_point(q);

	v->x = q->x / q->w - p->x / p->w;
	v->y = q->y / q->w - p->y / p->w;
	v->z = q->z / q->w - p->z / p->w;
	v->w = 0.;

	return v;
}


struct coord *unit_vector(struct coord *v, const struct coord *p,
			  const struct coord *q)
{
	return normalize_in_place(vector(v, p, q));
}


struct coord *scale(struct coord *v, const struct coord *u, double k)
{
	v->x = u->x * k;
	v->y = u->y * k;
	v->z = u->z * k;
	v->w = u->w;

	return v;
}


struct coord *scale_in_place(struct coord *v, double k)
{
	v->x *= k;
	v->y *= k;
	v->z *= k;

	return v;
}


struct coord *normalize(struct coord *v, const struct coord *u)
{
	assert_is_vector(u);
	assert_is_not_vzero(u);

	double l = sqrtf(DOT(u, u));

	v->x = u->x / l;
	v->y = u->y / l;
	v->z = u->z / l;
	v->w = 0.;

	return v;
}


struct coord *normalize_in_place(struct coord *v)
{
	assert_is_vector(v);
	assert_is_not_vzero(v);

	double l = sqrtf(DOT(v, v));

	v->x /= l;
	v->y /= l;
	v->z /= l;
	v->w = 0.;

	return v;
}


struct coord *add(struct coord *v, const struct coord *u, const struct coord *w)
{
	v->x = u->x + w->x;
	v->y = u->y + w->y;
	v->z = u->z + w->z;

	return v;
}


struct coord *add_in_place(struct coord *v, const struct coord *u)
{
	v->x += u->x;
	v->y += u->y;
	v->z += u->z;

	return v;
}


struct coord *sub(struct coord *v, const struct coord *u, const struct coord *w)
{
	v->x = u->x - w->x;
	v->y = u->y - w->y;
	v->z = u->z - w->z;

	return v;
}


struct coord *sub_in_place(struct coord *v, const struct coord *u)
{
	v->x -= u->x;
	v->y -= u->y;
	v->z -= u->z;

	return v;
}


struct coord *cross(struct coord *v, const struct coord *u,
		    const struct coord *w)
{
	assert_is_vector(u);
	assert_is_vector(w);

	v->x = u->y * w->z  -  u->z * w->y;
	v->y = u->z * w->x  -  u->x * w->z;
	v->z = u->x * w->y  -  u->y * w->x;
	v->w = 0.;

	return v;
}


struct coord *matcol(struct coord *v, const struct matrix *m,
		     const struct coord *u)
{
	v->x = ROW_MUL(m, 0, u);
	v->y = ROW_MUL(m, 1, u);
	v->z = ROW_MUL(m, 2, u);
	v->w = ROW_MUL(m, 3, u);

	return v;
}


struct coord *matcol_in_place(struct coord *v, const struct matrix *m)
{
	struct coord u = *v;

	v->x = ROW_MUL(m, 0, &u);
	v->y = ROW_MUL(m, 1, &u);
	v->z = ROW_MUL(m, 2, &u);
	v->w = ROW_MUL(m, 3, &u);

	return v;
}


struct coord *homogeneize(struct coord *p, const struct coord *q)
{
	assert_is_point(q);

	p->x = q->x / q->w;
	p->y = q->y / q->w;
	p->z = q->z / q->w;
	p->w = 1.;

	return p;
}


struct coord *homogeneize_in_place(struct coord *p)
{
	assert_is_point(p);

	p->x /= p->w;
	p->y /= p->w;
	p->z /= p->w;
	p->w = 1.;

	return p;
}


struct matrix *matrix(struct matrix *m, const struct coord *i,
		      const struct coord *j, const struct coord *k,
		      const struct coord *o)
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


struct matrix *matrixr(struct matrix *m, const struct coord *i,
		       const struct coord *j, const struct coord *k,
		       const struct coord *o)
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


struct matrix *matmat(struct matrix *m, const struct matrix *m1,
		      const struct matrix *m2)
{
	int i, j, k;
	struct matrix tmp, *old = 0;

	if (m == m1 || m == m2) {
		old = m;
		m  = &tmp;
	}

	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			E(m, i, j) = 0.;
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


struct matrix *transpose(struct matrix *m, struct matrix *n)
{
	int i, j;
	struct matrix tmp;

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


struct matrix *rotationx(struct matrix *m, double a)
{
	double ca = cos(a);
	double sa = sin(a);

	E(m, 0, 0) = 1.;
	E(m, 0, 1) = 0.;
	E(m, 0, 2) = 0.;
	E(m, 0, 3) = 0.;

	E(m, 1, 0) = 0.;
	E(m, 1, 1) = ca;
	E(m, 1, 2) = -sa;
	E(m, 1, 3) = 0.;

	E(m, 2, 0) = 0.;
	E(m, 2, 1) = sa;
	E(m, 2, 2) = ca;
	E(m, 2, 3) = 0.;

	E(m, 3, 0) = 0.;
	E(m, 3, 1) = 0.;
	E(m, 3, 2) = 0.;
	E(m, 3, 3) = 1.;

	return m;
}


struct matrix *rotationy(struct matrix *m, double a)
{
	double ca = cos(a);
	double sa = sin(a);

	E(m, 0, 0) = ca;
	E(m, 0, 1) = 0.;
	E(m, 0, 2) = sa;
	E(m, 0, 3) = 0.;

	E(m, 1, 0) = 0.;
	E(m, 1, 1) = 1.;
	E(m, 1, 2) = 0.;
	E(m, 1, 3) = 0.;

	E(m, 2, 0) = -sa;
	E(m, 2, 1) = 0.;
	E(m, 2, 2) = ca;
	E(m, 2, 3) = 0.;

	E(m, 3, 0) = 0.;
	E(m, 3, 1) = 0.;
	E(m, 3, 2) = 0.;
	E(m, 3, 3) = 1.;

	return m;
}


struct matrix *rotationz(struct matrix *m, double a)
{
	double ca = cos(a);
	double sa = sin(a);

	E(m, 0, 0) = ca;
	E(m, 0, 1) = -sa;
	E(m, 0, 2) = 0.;
	E(m, 0, 3) = 0.;

	E(m, 1, 0) = sa;
	E(m, 1, 1) = ca;
	E(m, 1, 2) = 0.;
	E(m, 1, 3) = 0.;

	E(m, 2, 0) = 0.;
	E(m, 2, 1) = 0.;
	E(m, 2, 2) = 1.;
	E(m, 2, 3) = 0.;

	E(m, 3, 0) = 0.;
	E(m, 3, 1) = 0.;
	E(m, 3, 2) = 0.;
	E(m, 3, 3) = 1.;

	return m;
}


struct matrix *rotation(struct matrix *m, const struct coord *v, double a)
{
	assert_is_vunit(v);

	double c = cos(a);
	double s = sin(a);
	double x = v->x;
	double y = v->y;
	double z = v->z;
	double xy = v->x * v->y;
	double xz = v->x * v->z;
	double yz = v->y * v->z;
	double x2 = v->x * v->x;
	double y2 = v->y * v->y;
	double z2 = v->z * v->z;

	E(m, 0, 0) = x2 + (1 - x2) * c;
	E(m, 0, 1) = xy * (1 - c) - s * z;
	E(m, 0, 2) = xz * (1 - c) + s * y;
	E(m, 0, 3) = 0.;

	E(m, 1, 0) = xy * (1 - c) + s * z;
	E(m, 1, 1) = y2 + (1 - y2) * c;
	E(m, 1, 2) = yz * (1 - c) - s * x;
	E(m, 1, 3) = 0.;

	E(m, 2, 0) = xz * (1 - c) - s * y;
	E(m, 2, 1) = yz * (1 - c) + s * x;
	E(m, 2, 2) = z2 + (1 - z2) * c;
	E(m, 2, 3) = 0.;

	E(m, 3, 0) = 0.;
	E(m, 3, 1) = 0.;
	E(m, 3, 2) = 0.;
	E(m, 3, 3) = 1.;

	return m;
}


struct matrix *translation(struct matrix *m, struct coord *v)
{
	E(m, 0, 0) = 1.;
        E(m, 0, 1) = 0.;
        E(m, 0, 2) = 0.;
        E(m, 0, 3) = v->x;

        E(m, 1, 0) = 0.;
        E(m, 1, 1) = 1.;
        E(m, 1, 2) = 0.;
        E(m, 1, 3) = v->y;

        E(m, 2, 0) = 0.;
        E(m, 2, 1) = 0.;
        E(m, 2, 2) = 1.;
        E(m, 2, 3) = v->z;

        E(m, 3, 0) = 0.;
        E(m, 3, 1) = 0.;
        E(m, 3, 2) = 0.;
        E(m, 3, 3) = 1.;

	return m;
}


void change_of_coord_mat(struct coord_system *cs)
{
	struct matrix rot, tsl;
	struct coord minus_os;

	matrix(&cs->m, &cs->i, &cs->j, &cs->k, &cs->o);

	translation(&tsl, scale(&minus_os, &cs->o, -1.));
	matrixr(&rot, &cs->i, &cs->j, &cs->k, &point_o);
	matmat(&cs->mi, &rot, &tsl);
}


/*************************************************************/
#ifndef NDEBUG

#include <stdio.h>
#include <stdlib.h>

#include "ansicodes.h"

#define WIDTH	10
#define PREC	 6
#define F(v)	WIDTH, PREC, v


void print_matrix(const char *pfx, const struct matrix *m)
{
	if (pfx)
		printf("%s\n", pfx);
	printf("---------------------------\n");

	for (int r = 0; r < 4; r++) {
		for (int c = 0; c < 4; c++) {
			printf("%*.*f ", F(m->cell[r][c]));
		}
		printf("\n");
	}
}


void print_coord(const char *pfx, const struct coord *c)
{
	if (pfx)
		printf("%s: ", pfx);
	printf("%*.*f, %*.*f, %*.*f, %*.*f\n",
		F(c->x), F(c->y), F(c->z), F(c->w));
}


void assert__is_mequal(const struct matrix *m1, const struct matrix *m2,
		      int line, char *file)
{
	if (!is_mequal(m1, m2)) {
		fprintf(stderr, RED "%s:%d assert_is_mequal(m1(%p), m2(%p)) "
			"failed!\n" NOHL, file, line, (void*)m1, (void*)m2);
		print_matrix("m1", m1);
		print_matrix("m2", m2);
		exit(1);
	}
}


void assert__is_vector(const struct coord *c, int line, char *file)
{
	if (!is_vector(c)) {
		fprintf(stderr, RED "%s:%d assert_is_vector(c(%p)) failed!\n"
			NOHL, file, line, (void*)c);
		print_coord("c", c);
		exit(1);
	}
}


void assert__is_point(const struct coord *c, int line, char *file)
{
	if (!is_point(c)) {
		fprintf(stderr, RED "%s:%d assert_is_point(c(%p)) failed!\n"
			NOHL, file, line, (void*)c);
		print_coord("c", c);
		exit(1);
	}
}

void assert__is_not_vzero(const struct coord *c, int line, char *file)
{
	if (is_vzero(c)) {
		fprintf(stderr, RED "%s:%d assert_is_not_vzero(c(%p)) failed!\n"
			NOHL, file, line, (void*)c);
		print_coord("c", c);
		exit(1);
	}
}


void assert__is_vunit(const struct coord *c, int line, char *file)
{
	if (!is_vunit(c)) {
		fprintf(stderr, RED "%s:%d assert_is_vunit(c(%p)) failed!\n"
			NOHL, file, line, (void*)c);
		print_coord("c", c);
		exit(1);
	}
}


void assert__is_cartesian_coord_system(const struct coord *i,
				       const struct coord *j,
				       const struct coord *k,
				       int line, char *file)
{
	if (!is_cartesian_coord_system(i, j, k)) {
		fprintf(stderr, RED "%s:%d assert_is_cartesian_coord_system"
			"(i(%p), j(%p), k(%p)) failed!\n" NOHL, file, line,
			(void*)i, (void*)j, (void*)k);
		print_coord("i", i);
		print_coord("j", j);
		print_coord("k", k);
		exit(1);
	}
}
#endif
