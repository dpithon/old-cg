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

#define H(s)	((struct cone*) s)->h
#define R(s)	((struct cone*) s)->r


static bool check(float k, struct ipoint *i, const struct ray *ray,
		  const struct shape *s)
{
	if (k > 0 && k < i->k) {
		float y = k * ray->v.y + ray->s.y;
		if (y >= 0 && y <= H(s))
			return true;
	}
	return false;
}


static bool cone_intersect(struct ipoint *i, const struct ray *ray,
				 const struct shape *s)
{
	float a, b, c, delta;

	float f = (H(s) * H(s)) / (R(s) * R(s));
	float g = ray->s.y - H(s);

	a = f * (ray->v.x * ray->v.x + ray->v.z * ray->v.z) -
	    ray->v.y * ray->v.y;

	b = 2.F * (f * (ray->v.x * ray->s.x + ray->v.z * ray->s.z) +
	    ray->v.y * (H(s) - ray->s.y));

	c = f * (ray->s.x * ray->s.x + ray->s.z * ray->s.z) -
	    g * g;

	delta = b * b - 4 * a * c;

	if (float_equals(delta, 0.F)) {
		float k = -b / (2.F * a);
		if (check(k, i, ray, s)) {
			set_ipoint(i, s, FLAG_OUTSIDE, k);
			return true;
		}
	} else if (delta > 0.F) {
		float k1, k2, sqrt_delta;

		sqrt_delta = sqrtf(delta);
		k1 = (-b - sqrt_delta) / (2.F * a);
		k2 = (-b + sqrt_delta) / (2.F * a);

		if (k2 <= 0 || i->k <= k1)
			return false;

		if (check(k1, i, ray, s)) {
			set_ipoint(i, s, FLAG_OUTSIDE, k1);
			return true;
		}

		if (check(k2, i, ray, s)) {
			/* TODO useless test 'k2 > 0' */
			set_ipoint(i, s, FLAG_INSIDE, k2);
			return true;
		}
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
	co->intersect  = cone_intersect;
	co->paint      = default_painter;
	co->paint_data = 0;

	return CAST_SHAPE(co);
}
