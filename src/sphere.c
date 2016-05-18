#include <math.h>

#include "ipoint.h"
#include "ray.h"
#include "quadric.h"


static bool sphere_intersect(struct ipoint *i, const struct ray *ray,
			     const struct shape *s)
{
	double a, b, c, delta, k1, k2, sqrt_delta;

	a = Vx * Vx + Vy * Vy + Vz * Vz;
	b = 2. * (Vx * Sx + Vy * Sy + Vz * Sz);
	c = Sx * Sx + Sy * Sy + Sz * Sz - R2;

	delta = b * b - 4. * a * c;

	if (delta < 0.) {
		return false;

	} else if (delta > 0.) {
		sqrt_delta = sqrt(delta);
		k1 = (-b - sqrt_delta) / (2. * a);
		k2 = (-b + sqrt_delta) / (2. * a);

		if (k1 > 0. && k1 < i->k) {
			set_ipoint(i, s, ray, OUTSIDE, k1);
			return true;
		} else if (k2 > 0. && k2 < i->k) {
			set_ipoint(i, s, ray, INSIDE, k2);
			return true;
		}

	} else {
		k1 = -b / (2. * a);

		if (k1 > 0. && k1 < i->k) {
			set_ipoint(i, s, ray, OUTSIDE, k1);
			return true;
		}
	}

	return false;
}


struct shape *sphere(const struct coord *loc, double r)
{
	return quadric(loc, 0, r, sphere_intersect);
}
