#include <math.h>

#include "hit.h"
#include "quadric.h"
#include "ray.h"
#include "vmath.h"


static bool cylinder_intersect(struct hit *i, const struct ray *ray,
			       const struct shape *s)
{
	struct quadratic q = {
		.a = Vx * Vx + Vz * Vz,
		.b = 2. * (Vx * Sx + Vz * Sz),
		.c = Sx * Sx + Sz * Sz - R2
	};
	solve_quadratic(&q);

	switch (q.count) {
	case 1:
		if (q.k1 > 0. && q.k1 < i->k && in_range(q.k1, s, ray)) {
			set_hit(i, s, ray, OUTSIDE, q.k1);
			return true;
		}
		break;
	case 2:
		if (q.k2 <= 0. || q.k1 >= i->k)
			return false;

		if (q.k1 > 0. && in_range(q.k1, s, ray)) {
			set_hit(i, s, ray, OUTSIDE, q.k1);
			return true;
		}

		if (q.k2 < i->k && in_range(q.k2, s, ray)) {
			set_hit(i, s, ray, INSIDE, q.k2);
			return true;
		}
	}

	return false;
}

static void normal(struct coord *norm, const struct coord *i)
{
	set_vector(norm, 2. * i->x, 0., 2. * i->z);
	normalize_in_place(norm);
}


struct shape *cylinder(const struct coord *base, const struct coord *apex,
		       double r)
{
	return quadric(base, apex, r, cylinder_intersect, normal);
}
