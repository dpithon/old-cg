#include <stdlib.h>

#include "vmath.h"
#include "ipoint.h"
#include "ray.h"
#include "surfaces.h"
#include "painter.h"
#include "stack.h"
#include "misc.h"
#include "debug.h"

struct cone {
	SHAPE_INF;
	double r;
	double h;
	double h2r2;
};


#define H(s)	((struct cone*) s)->h
#define R(s)	((struct cone*) s)->r
#define H2R2(s)	((struct cone*) s)->h2r2

#define V(a)    (ray->v.a)
#define S(a)    (ray->s.a)

#define IN_RANGE(v) ((v) >= 0 && (v) <= H(s))

static bool cone_intersect(struct ipoint *i, const struct ray *ray,
			   const struct shape *s)
{
	double f =  H(s) - S(y);
	double a = H2R2(s) * (V(x) * V(x) + V(z) * V(z)) - V(y) * V(y);
	double b = 2. * (H2R2(s) * (V(x) * S(x) + V(z) * S(z)) + V(y) * f);
	double c = H2R2(s) * (S(x) * S(x) + S(z) * S(z)) - f * f;
	double delta = b * b - 4 * a * c;

	if (delta < 0.)
		return false;

	if (double_equals(delta, 0.)) {
		double k = -b / (2. * a);
		if (k <= 0 || k > i->k)
			return false;

		double y = k * V(y) + S(y);
		if (!IN_RANGE(y)) 
			return false;

		set_ipoint(i, s, (V(y) > 0)? FLAG_INSIDE: FLAG_OUTSIDE, k);
		return true;
	}

	double sqrt_delta = sqrtf(delta);
	double k1 = (-b - sqrt_delta) / (2. * a);
	double k2 = (-b + sqrt_delta) / (2. * a);

	ORDER_FLOAT(k1, k2);
	if (k2 <= 0 || k1 >= i->k)
		return false;

	double y1 = k1 * V(y) + S(y);
	double y2 = k2 * V(y) + S(y);

	if (IN_RANGE(y1) && k1 > 0) {
		set_ipoint(i, s, y2 > H(s)? FLAG_INSIDE: FLAG_OUTSIDE, k1);
		return true;
	}

	if (k2 >= i->k)
		return false;

	if (IN_RANGE(y2) && y1 > H(s)) {
		set_ipoint(i, s, FLAG_OUTSIDE, k2);
		return true;
	}

	if (IN_RANGE(y2) && ((IN_RANGE(y1) && k1 <= 0) || y1 < 0)) {
		set_ipoint(i, s, FLAG_INSIDE, k2);
		return true;
	}

	return false;
}


struct shape *cone(const struct coord *base, const struct coord *apex,
		   double r)
{
	assert_is_point(base);
	assert_is_point(apex);

	double p;
	struct coord vec;
	struct cone *co = malloc(sizeof(struct cone));

	vector(&vec, base, apex);
	unit(&co->cs.j, &vec);
	co->cs.o = *base;

        transform(&co->cs.j);
        transform(&co->cs.o);
	if (is_collinear(&co->cs.j, &vector_j, &p)) {
		if (p > 0.) {
			co->cs.i = vector_i;
			co->cs.k = vector_k;
		} else {
			co->cs.i = vector_k;
			co->cs.k = vector_i;
		}
	} else {
		cross(&co->cs.k, &co->cs.j, &vector_j);
		unit_me(&co->cs.k);
		cross(&co->cs.i, &co->cs.j, &co->cs.k);
	}

	assert_is_cartesian_coord_system(&co->cs.i, &co->cs.j, &co->cs.k);

	change_of_coord_mat(&co->cs);

	co->h          = len(&vec);
	co->r          = r;
	co->h2r2       = (co->h * co->h) / (r * r);
	co->intersect  = cone_intersect;
	co->paint      = default_painter;
	co->paint_data = 0;

	return CAST_SHAPE(co);
}
