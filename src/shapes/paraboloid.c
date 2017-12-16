#include <math.h>

#include "hit.h"
#include "quadric.h"
#include "ray.h"
#include "shape.priv.h"


#define WHICH_SIDE	((Vy > 0.)? OUTSIDE: INSIDE)
static bool intersect_(struct hit *i, const struct ray *ray, const struct shape *s)
{
	double a, b, c, delta, sqrt_delta, k1, k2;

	a = HR2 * (Vx * Vx + Vz * Vz);
	if (a < epsilon) {
		k1 = (HR2 / Vy) * (Sx * Sx + Sz * Sz) - (Sy / Vy);
		if (k1 > 0. && k1 < i->k && in_range(k1, s, ray)) {
			set_hit(i, s, ray, WHICH_SIDE, k1);
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
			set_hit(i, s, ray, OUTSIDE, k1);
			return true;
		}

		if (k2 < i->k && in_range(k2, s, ray)) {
			set_hit(i, s, ray, INSIDE, k2);
			return true;
		}

	} else {
		k1 = -b / (2. * a);
		if (k1 > 0. && k1 < i->k && in_range(k1, s, ray)) {
			set_hit(i, s, ray, WHICH_SIDE, k1);
			return true;
		}
	}

	return false;
}


static void normal_(struct coord *norm, const struct coord *i)
{
	set_vector(norm, 2. * i->x, -1, 2. * i->z);
	normalize_in_place(norm);
}



struct shape *paraboloid(const struct coord *base, const struct coord *apex,
			 double r)
{
	return quadric(SHAPE_SURF_PARABOLOID, base, apex, r, intersect_, normal_);
}
