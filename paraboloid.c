#include <assert.h>
#include <math.h>

#include "ipoint.h"
#include "ray.h"
#include "quadric.h"


#define WHICH_SIDE	((Vy > 0.)? FLAG_OUTSIDE: FLAG_INSIDE)
static bool paraboloid_intersect(struct ipoint *i, const struct ray *ray,
				 const struct shape *s)
{
	double a, b, c, delta, sqrt_delta, k1, k2;

	a = HR2 * (Vx * Vx + Vz * Vz);
	if (a < epsilon) {
		assert(fabs(Vy) > epsilon);
		k1 = (HR2 / Vy) * (Sx * Sx + Sz * Sz) - (Sy / Vy);
		if (k1 > 0. && k1 < i->k && in_range(k1, s, ray)) {
			set_ipoint(i, s, WHICH_SIDE, k1);
			return true;
		}
		return false;
	}

	b = 2. * HR2 * (Vx * Sx + Vz * Sz) - Vy;
	c = HR2 * (Sx * Sx + Sz * Sz) - Sy;
	delta = b * b - 4. * a * c;

	if (delta < 0.) {
		return false;

	} else if (delta > 0.) {
		sqrt_delta = sqrt(delta);
		k1 = (-b - sqrt_delta) / (2. * a);
		k2 = (-b + sqrt_delta) / (2. * a);

		if (k2 <= 0. || i->k <= k1)
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
			set_ipoint(i, s, WHICH_SIDE, k1);
			return true;
		}
	}

	return false;
}


struct shape *paraboloid(const struct coord *base, const struct coord *apex,
			 double r)
{
	return quadric(base, apex, r, paraboloid_intersect);
}
