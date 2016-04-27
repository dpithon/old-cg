#include "vmath.h"
#include "types.h"
#include "scene.h"
#include "ipoint.h"
#include "ray.h"
#include "debug.h"
#include "quadric.h"


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
	return quadric(base, apex, r, cylinder_intersect);
}
