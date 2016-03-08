#include <stdlib.h>

#include "vmath.h"
#include "types.h"
#include "scene.h"
#include "ipoint.h"
#include "ray.h"
#include "surfaces.h"
#include "painter.h"
#include "stack.h"
#include "debug.h"


struct cylinder {
	SHAPE_INF;
	double radius;
	double h;
};


#define H(s)		((struct cylinder*) s)->h
#define RADIUS(s)	((struct cylinder*) s)->radius


static bool check(double k, struct ipoint *i, const struct ray *ray,
		  const struct shape *s)
{
	if (k > 0 && k < i->k) {
		double y = k * ray->v.y + ray->s.y;
		if (y >= 0 && y <= H(s))
			return true;
	}
	return false;
}


static bool cylinder_intersect(struct ipoint *i, const struct ray *ray,
				 const struct shape *s)
{
	double a, b, c, delta;

	a = ray->v.x * ray->v.x + ray->v.z * ray->v.z;
	b = 2. * (ray->v.x * ray->s.x + ray->v.z * ray->s.z);
	c = ray->s.x * ray->s.x + ray->s.z * ray->s.z - RADIUS(s) * RADIUS(s);;

	delta = b * b - 4 * a * c;

	if (double_equals(delta, 0.)) {
		double k = -b / (2. * a);
		if (check(k, i, ray, s)) {
			set_ipoint(i, s, FLAG_OUTSIDE, k);
			return true;
		}
	} else if (delta > 0.) {
		double k1, k2, sqrt_delta;

		sqrt_delta = sqrtf(delta);
		k1 = (-b - sqrt_delta) / (2. * a);
		k2 = (-b + sqrt_delta) / (2. * a);

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


struct shape *cylinder(const struct coord *base, const struct coord *apex,
			double radius)
{
	double p;
	struct coord vec;
	struct cylinder *cy = malloc(sizeof(struct cylinder));

	assert_is_point(base);
	assert_is_point(apex);

	vector(&vec, base, apex);

	unit(&cy->cs.j, &vec);
	cy->cs.o = *base;

	transform(&cy->cs.j);
	transform(&cy->cs.o);

	if (is_collinear(&cy->cs.j, &VectorJ, &p)) {
		if (p > 0.) {
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

	assert_is_cartesian_coord_system(&cy->cs.i, &cy->cs.j, &cy->cs.k);

	change_of_coord_mat(&cy->cs);

	cy->h          = len(&vec);
	cy->radius     = radius;
	cy->intersect  = cylinder_intersect;
	cy->paint      = default_painter;
	cy->paint_data = 0;

	return CAST_SHAPE(cy);
}
