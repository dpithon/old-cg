#include <assert.h>
#include <stdlib.h>

#include "vmath.h"
#include "types.h"
#include "surfaces.h"
#include "scene.h"
#include "ipoint.h"
#include "ray.h"
#include "painter.h"
#include "stack.h"
#include "debug.h"


struct sphere {
	SHAPE_INF;
	double r;
	double r2;
};


#define R2	((struct sphere*)s)->r2


static bool sphere_intersect(struct ipoint *i, const struct ray *ray,
			     const struct shape *s)
{
	double a, b, c, delta, k1, k2, sqrt_delta;

	a = Vx * Vx + Vy * Vy + Vz * Vz;
	b = 2. * (Vx * Sx + Vy * Sy + Vz * Sz);
	c = Sx * Sx + Sy * Sy + Sz * Sz - R2;

	delta = b * b - 4 * a * c;

	if (delta < 0.) {
		return false;

	} else if (delta > 0.) {
		sqrt_delta = sqrt(delta);
		k1 = (-b - sqrt_delta) / (2. * a);
		k2 = (-b + sqrt_delta) / (2. * a);

		if (k1 > 0 && k1 < i->k) {
			set_ipoint(i, s, FLAG_OUTSIDE, k1);
			return true;
		} else if (k2 > 0 && k2 < i->k) {
			set_ipoint(i, s, FLAG_INSIDE, k2);
			return true;
		}

	} else {
		k1 = -b / (2. * a);

		if (k1 > 0 && k1 < i->k) {
			set_ipoint(i, s, FLAG_OUTSIDE, k1);
			return true;
		}
	}

	return false;
}


struct shape *sphere(const struct coord *loc, double r)
{
	assert_is_point(loc);
	assert(r > 0.);

	struct sphere *sph = malloc(sizeof(struct sphere));

	sph->cs.o   = *loc;
	sph->cs.i   = VectorI;
	sph->cs.j   = VectorJ;
	sph->cs.k   = VectorK;

	transform(&sph->cs.o);
	change_of_coord_mat(&sph->cs);

	sph->r  = r;
	sph->r2 = r * r;
	sph->intersect  = sphere_intersect;
	sph->paint      = default_painter;
	sph->paint_data = 0;

	return CAST_SHAPE(sph);
}
