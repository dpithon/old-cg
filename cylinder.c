#include <assert.h>
#include <stdlib.h>

#include "vmath.h"
#include "types.h"
#include "scene.h"
#include "ipoint.h"
#include "ray.h"
#include "surfaces.h"
#include "painter.h"


struct cylinder {
	SHAPE_INF;
	float radius;
	float h;
};


#define H(s)		((struct cylinder*) s)->h
#define RADIUS(s)	((struct cylinder*) s)->radius


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


static bool cylinder_intersect(struct ipoint *i, const struct ray *ray,
				 const struct shape *s)
{
	float a, b, c, delta;

	a = ray->v.x * ray->v.x + ray->v.z * ray->v.z;
	b = 2.F * (ray->v.x * ray->s.x + ray->v.z * ray->s.z);
	c = ray->s.x * ray->s.x + ray->s.z * ray->s.z - RADIUS(s) * RADIUS(s);;

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


struct shape *cylinder(const struct coord *loc, const struct coord *norm,
			float radius, float h)
{
	float p;
	struct cylinder *cy = malloc(sizeof(struct cylinder));

	assert(is_point(loc));
	assert(is_vector(norm));

	unit(&cy->cs.j, norm);
	cy->cs.o = *loc;

	if (is_collinear(&cy->cs.j, &VectorJ, &p)) {
		if (p > 0.F) {
			cy->cs.i = VectorI;
			cy->cs.k = VectorK;
		} else {
			cy->cs.i = VectorK;
			cy->cs.k = VectorI;
		}
	} else {
		cross(&cy->cs.k, &cy->cs.j, &VectorJ);
		unit_me(&cy->cs.k);
		cross(&cy->cs.i, &cy->cs.j, &cy->cs.k);
	}

	assert(is_cartesian_coord_system(&cy->cs.i, &cy->cs.j, &cy->cs.k));

	change_of_coord_mat(&cy->cs);

	cy->h          = h;
	cy->radius     = radius;
	cy->intersect  = cylinder_intersect;
	cy->paint      = default_painter;
	cy->paint_data = 0;

	return CAST_SHAPE(cy);
}
