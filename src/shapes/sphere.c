#include <math.h>

#include "hit.h"
#include "quadric.h"
#include "ray.h"
#include "shape.i"


static bool sphere_intersect(struct hit *i, const struct ray *ray,
			     const struct shape *s)
{
	struct quadratic q = {
		.a = Vx * Vx + Vy * Vy + Vz * Vz,
		.b = 2. * (Vx * Sx + Vy * Sy + Vz * Sz),
		.c = Sx * Sx + Sy * Sy + Sz * Sz - R2
	};
	solve_quadratic(&q);

	if (q.count == 2) {
		if (q.k1 > 0. && q.k1 < i->k) {
			set_hit(i, s, ray, OUTSIDE, q.k1);
			return true;
		} else if (q.k2 > 0. && q.k2 < i->k) {
			set_hit(i, s, ray, INSIDE, q.k2);
			return true;
		}

	} else if (q.count == 1) {
		if (q.k1 > 0. && q.k1 < i->k) {
			set_hit(i, s, ray, OUTSIDE, q.k1);
			return true;
		}
	}

	return false;
}


static void normal_vec(struct coord *norm, const struct coord *i)
{
	set_vector(norm, 2. * i->x, 2. * i->y, 2. * i->z);
	normalize_in_place(norm);
}


struct shape *sphere(const struct coord *loc, double r)
{
	return quadric(SHAPE_SURF_SPHERE, loc, 0, r, sphere_intersect, normal_vec);
}
