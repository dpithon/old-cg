#include "mm.h"
#include "vmath.h"
#include "ipoint.h"
#include "ray.h"
#include "surfaces.h"
#include "painter.h"
#include "stack.h"
#include "misc.h"
#include "debug.h"

struct cone {
	SHAPE_INF;
	double r;
	double h;
	double h2r2;
};


#define H	((struct cone*) s)->h
#define R	((struct cone*) s)->r
#define H2R2	((struct cone*) s)->h2r2


static bool in_range(double k, const struct shape *s, const struct ray *ray)
{
	double y = k * Vy + Sy;
	return (y >= 0. && y <= H);
}


static bool ci_main(struct ipoint *i, const struct ray *ray,
		    const struct shape *s, double k1, double k2)
{
	if (k2 <= 0. || i->k <= k1)
		return false;
	
	if (k1 <= 0. && k2 < i->k && in_range(k2, s, ray)) {
		int side = (k1 * Vy + Sy > H)? FLAG_OUTSIDE: FLAG_INSIDE;
		set_ipoint(i, s, side, k2);
		return true;
	} else if (k1 <= 0.) {
		return false;
	} else if (in_range(k1, s, ray)) {
		int side = (k2 * Vy + Sy <= H)? FLAG_OUTSIDE: FLAG_INSIDE;
		set_ipoint(i, s, side, k1);
		return true;
	} else if (k2 < i->k && in_range(k2, s, ray)) {
		int side = (k1 * Vy + Sy > H)? FLAG_OUTSIDE: FLAG_INSIDE;
		set_ipoint(i, s, side, k2);
		return true;
	}

	return false;
}


static bool ci_delta0(struct ipoint *i, const struct ray *ray,
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

		int side = (xk2 + zk2 >= rho_y2)? FLAG_OUTSIDE: FLAG_INSIDE;
		set_ipoint(i, s, side, k);
		return true;
	}

	return false;
}


static bool ci_linear(struct ipoint *i, const struct ray *ray,
		      const struct shape *s, double b, double c)
{
	if (b != 0.) {
		double k = -c/b;
		if (k > 0 && k < i->k && in_range(k, s, ray)) {
			int side = (Vy > 0)? FLAG_INSIDE: FLAG_OUTSIDE;
			set_ipoint(i, s, side, k);
			return true;
		} 
	}

	return false;
}


static bool cone_intersect(struct ipoint *i, const struct ray *ray,
			   const struct shape *s)
{
	double f =  Sy - H;
	double a = Vy * Vy - H2R2 * (Vx * Vx + Vz * Vz);
	double b = 2. * (Vy * f - H2R2 * (Vx * Sx + Vz * Sz));
	double c = f * f - H2R2 * (Sx * Sx + Sz * Sz);

	if (a != 0.) { 
		double delta = b * b - 4 * a * c;
		if (delta < 0.) {
			return false;
		} if (delta > 0.) {
			double sqrt_delta = sqrt(delta);
			double k1 = (-b - sqrt_delta) / (2. * a);
			double k2 = (-b + sqrt_delta) / (2. * a);
			ORDER_FLOAT(k1, k2);
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


struct shape *cone(const struct coord *base, const struct coord *apex,
		   double r)
{
	assert_is_point(base);
	assert_is_point(apex);

	double p;
	struct coord vec;
	struct cone *co = alloc_struct(cone);

	vector(&vec, base, apex);
	normalize(&co->cs.j, &vec);
	co->cs.o = *base;

        transform(&co->cs.j);
        transform(&co->cs.o);
	if (is_collinear(&co->cs.j, &vector_j, &p)) {
		if (p > 0.) {
			co->cs.i = vector_i;
			co->cs.k = vector_k;
		} else {
			co->cs.i = vector_k;
			co->cs.k = vector_i;
		}
	} else {
		cross(&co->cs.k, &co->cs.j, &vector_j);
		normalize_in_place(&co->cs.k);
		cross(&co->cs.i, &co->cs.j, &co->cs.k);
	}

	assert_is_cartesian_coord_system(&co->cs.i, &co->cs.j, &co->cs.k);

	change_of_coord_mat(&co->cs);

	co->h          = len(&vec);
	co->r          = r;
	co->h2r2       = (co->h * co->h) / (r * r);
	co->intersect  = cone_intersect;
	co->paint      = default_painter;
	co->paint_data = 0;

	return CAST_SHAPE(co);
}
