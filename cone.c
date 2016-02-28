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
		if (k <= 0 || k > i->k)
			return false;

		float y = k * ray->v.y + ray->s.y;
		if (y < 0 || y > H(s)) 
			return false;

		if (ray->v.y > 0)
			set_ipoint(i, s, FLAG_INSIDE, k);
		else
			set_ipoint(i, s, FLAG_OUTSIDE, k);
		return true;

	} else if (delta > 0.F) {
		float ka, kb, k1, k2, sqrt_delta;
		float y1, y2;

		sqrt_delta = sqrtf(delta);
		ka = (-b - sqrt_delta) / (2.F * a);
		kb = (-b + sqrt_delta) / (2.F * a);
		k1 = (ka < kb)? ka: kb;
		k2 = (ka > kb)? ka: kb;

		if (k2 <= 0 || k1 >= i->k)
			return false;

		y1 = k1 * ray->v.y + ray->s.y;
		y2 = k2 * ray->v.y + ray->s.y;

		bool e1 = (y1 >= 0) && (y1 <= H(s));
		bool s1 = k1 > 0;
		bool e2M = y2 <= H(s);
		if (e1 && s1 && e2M) {
			set_ipoint(i, s, FLAG_OUTSIDE, k1);
			return true;
		}

		bool e2p = y2 > H(s);
		if (e1 && e2p && s1) {
			set_ipoint(i, s, FLAG_INSIDE, k1);
			return true;
		}

		if (k2 >= i->k)
			return false;

		bool e2 = (y2 >= 0) && (y2 <= H(s));
		bool e1p = y1 > H(s);
		if (e2 && e1p) {
			set_ipoint(i, s, FLAG_OUTSIDE, k2);
			return true;
		}

		bool e1m = y1 < 0;
		if (e2 && ((e1 && (!s1)) || e1m)) {
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
