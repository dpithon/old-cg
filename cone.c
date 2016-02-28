#include <assert.h>
#include <stdlib.h>

#include "vmath.h"
#include "types.h"
#include "plane.h"
#include "scene.h"
#include "ipoint.h"
#include "ray.h"
#include "cone.h"
#include "painter.h"
#include "stack.h"
#include "misc.h"

struct cone {
	SHAPE_INF;
	float r;
	float h;
	float h2r2;
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
	float f =  H(s) - S(y);
	float a = H2R2(s) * (V(x) * V(x) + V(z) * V(z)) - V(y) * V(y);
	float b = 2.F * (H2R2(s) * (V(x) * S(x) + V(z) * S(z)) + V(y) * f);
	float c = H2R2(s) * (S(x) * S(x) + S(z) * S(z)) - f * f;
	float delta = b * b - 4 * a * c;

	if (delta < 0.)
		return false;

	if (float_equals(delta, 0.F)) {
		float k = -b / (2.F * a);
		if (k <= 0 || k > i->k)
			return false;

		float y = k * V(y) + S(y);
		if (!IN_RANGE(y)) 
			return false;

		set_ipoint(i, s, (V(y) > 0)? FLAG_INSIDE: FLAG_OUTSIDE, k);
		return true;
	}

	float sqrt_delta = sqrtf(delta);
	float k1 = (-b - sqrt_delta) / (2.F * a);
	float k2 = (-b + sqrt_delta) / (2.F * a);

	ORDER_FLOAT(k1, k2);
	if (k2 <= 0 || k1 >= i->k)
		return false;

	float y1 = k1 * V(y) + S(y);
	float y2 = k2 * V(y) + S(y);

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


struct shape *cone(const struct coord *loc, const struct coord *norm,
		   float r, float h)
{
	float p;
	struct cone *co = malloc(sizeof(struct cone));

	assert(is_point(loc));
	assert(is_vector(norm));

	unit(&co->cs.j, norm);
	co->cs.o = *loc;

        transform(&co->cs.j);
        transform(&co->cs.o);
	if (is_collinear(&co->cs.j, &VectorJ, &p)) {
		if (p > 0.F) {
			co->cs.i = VectorI;
			co->cs.k = VectorK;
		} else {
			co->cs.i = VectorK;
			co->cs.k = VectorI;
		}
	} else {
		cross(&co->cs.k, &co->cs.j, &VectorJ);
		unit_me(&co->cs.k);
		cross(&co->cs.i, &co->cs.j, &co->cs.k);
	}

	assert(is_cartesian_coord_system(&co->cs.i, &co->cs.j, &co->cs.k));

	change_of_coord_mat(&co->cs);

	co->h          = h;
	co->r          = r;
	co->h2r2       = (h * h) / (r * r);
	co->intersect  = cone_intersect;
	co->paint      = default_painter;
	co->paint_data = 0;

	return CAST_SHAPE(co);
}
