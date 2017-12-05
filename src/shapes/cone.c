#include <math.h>

#include "hit.h"
#include "log.h"
#include "macros.h"
#include "quadric.h"
#include "ray.h"


static bool ci_main(struct hit *i, const struct ray *ray,
		    const struct shape *s, double k1, double k2)
{
	if (k2 <= 0. || i->k <= k1)
		return false;
	
	if (k1 <= 0. && k2 < i->k && in_range(k2, s, ray)) {
		int side = (k1 * Vy + Sy > H)? OUTSIDE: INSIDE;
		set_hit(i, s, ray, side, k2);
		return true;
	} else if (k1 <= 0.) {
		return false;
	} else if (in_range(k1, s, ray)) {
		int side = (k2 * Vy + Sy <= H)? OUTSIDE: INSIDE;
		set_hit(i, s, ray, side, k1);
		return true;
	} else if (k2 < i->k && in_range(k2, s, ray)) {
		int side = (k1 * Vy + Sy > H)? OUTSIDE: INSIDE;
		set_hit(i, s, ray, side, k2);
		return true;
	}

	return false;
}


static bool ci_delta0(struct hit *i, const struct ray *ray,
		    const struct shape *s, double k)
{
	if (k < i->k && in_range(k, s, ray)) {
		double xk = k * Vx + Sx;
		double yk = k * Vy + Sy;
		double zk = k * Vz + Sz;
		double rho_y = -(R / H) * yk + R;
		double xk2 = xk * xk;
		double zk2 = zk * zk;
		double rho_y2 = rho_y * rho_y;

		int side = (xk2 + zk2 >= rho_y2)? OUTSIDE: INSIDE;
		set_hit(i, s, ray, side, k);
		return true;
	}

	return false;
}


static bool ci_linear(struct hit *i, const struct ray *ray,
		      const struct shape *s, double b, double c)
{
	if (b != 0.) {
		double k = -c/b;
		if (k > 0. && k < i->k && in_range(k, s, ray)) {
			int side = (Vy > 0.)? INSIDE: OUTSIDE;
			set_hit(i, s, ray, side, k);
			return true;
		} 
	}

	return false;
}


static bool cone_intersect(struct hit *i, const struct ray *ray,
			   const struct shape *s)
{
	double f = Sy - H;
	double a = Vy * Vy - H2R2 * (Vx * Vx + Vz * Vz);
	double b = 2. * (Vy * f - H2R2 * (Vx * Sx + Vz * Sz));
	double c = f * f - H2R2 * (Sx * Sx + Sz * Sz);

	if (a != 0.) { 
		double delta = b * b - 4. * a * c;

		if (delta < 0.) {
			return false;
		} if (delta > 0.) {
			double sqrt_delta = sqrt(delta);
			double k1 = (-b - sqrt_delta) / (2. * a);
			double k2 = (-b + sqrt_delta) / (2. * a);
			SORT(k1, k2);
			return ci_main(i, ray, s, k1, k2);
		} else {
			warning("cone_intersect: delta == 0");
			return ci_delta0(i, ray, s, -b / (2. * a));
		}
	} else {
		warning("cone_intersect: a == 0");
		return ci_linear(i, ray, s, b, c);
	}
}


static void normal(struct coord *norm, const struct coord *i)
{
	set_vector(norm, 2. * i->x, 0., 2. * i->z);
	normalize_in_place(norm);
}


struct shape *cone(const struct coord *base, const struct coord *apex,
		   double r)
{
	return quadric(base, apex, r, cone_intersect, normal);
}
