#include <assert.h>
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
	double r;
	double r2;
	double h;
};


#define H	((struct cylinder*) s)->h
#define R2	((struct cylinder*) s)->r2


static bool in_range(double k, const struct shape *s, const struct ray *ray)
{
	double y = k * Vy + Sy;
	return (y >= 0. && y <= H);
}


static bool cylinder_intersect(struct ipoint *i, const struct ray *ray,
			       const struct shape *s)
{
	double a, b, c, delta, k1, k2, sqrt_delta;

	a = Vx * Vx + Vz * Vz;
	if (a < epsilon)
		return false;

	b = 2. * (Vx * Sx + Vz * Sz);
	c = Sx * Sx + Sz * Sz - R2;
	delta = b * b - 4 * a * c;

	if (delta < 0.) {
		return false;

	} else if (delta > 0.) {
		sqrt_delta = sqrt(delta);
		k1 = (-b - sqrt_delta) / (2. * a);
		k2 = (-b + sqrt_delta) / (2. * a);

		if (k2 <= 0. || k1 >= i->k)
			return false;

		if (k1 > 0. && in_range(k1, s, ray)) {
			set_ipoint(i, s, FLAG_OUTSIDE, k1);
			return true;
		}

		if (k2 < i->k && in_range(k2, s, ray)) {
			set_ipoint(i, s, FLAG_INSIDE, k2);
			return true;
		}

	} else {
		k1 = -b / (2. * a);
		if (k1 > 0. && k1 < i->k && in_range(k1, s, ray)) {
			set_ipoint(i, s, FLAG_OUTSIDE, k1);
			return true;
		}
	}

	return false;
}


struct shape *cylinder(const struct coord *base, const struct coord *apex,
			double r)
{
	assert_is_point(base);
	assert_is_point(apex);
	assert(r > 0.);

	double f;
	struct coord vec;
	struct cylinder *cy = malloc(sizeof(struct cylinder));

	vector(&vec, base, apex);

	unit(&cy->cs.j, &vec);
	cy->cs.o = *base;

	transform(&cy->cs.j);
	transform(&cy->cs.o);

	if (is_collinear(&cy->cs.j, &VectorJ, &f)) {
		if (f > 0.) {
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

	cy->h  = len(&vec);
	cy->r  = r;
	cy->r2 = r * r;
	cy->intersect  = cylinder_intersect;
	cy->paint      = default_painter;
	cy->paint_data = 0;

	return CAST_SHAPE(cy);
}
