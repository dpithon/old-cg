#include <assert.h>
#include <math.h>

#include "mm.h"
#include "vmath.h"
#include "types.h"
#include "scene.h"
#include "ipoint.h"
#include "ray.h"
#include "surfaces.h"
#include "painter.h"
#include "stack.h"
#include "debug.h"


struct paraboloid {
	SHAPE_INF;
	double r;
	double h;
	double hr2;
};


#define H		((struct paraboloid*) s)->h
#define HR2		((struct paraboloid*) s)->hr2
#define WHICH_SIDE	((Vy > 0.)? FLAG_OUTSIDE: FLAG_INSIDE)
#define Y_IN_RANGE(k)	((k * Vy + Sy) <= H)


static bool paraboloid_intersect(struct ipoint *i, const struct ray *ray,
				 const struct shape *s)
{
	double a, b, c, delta, sqrt_delta, k1, k2;

	a = HR2 * (Vx * Vx + Vz * Vz);
	if (a < epsilon) {
		assert(fabs(Vy) > epsilon);
		k1 = (HR2 / Vy) * (Sx * Sx + Sz * Sz) - (Sy / Vy);
		if (k1 > 0 && k1 < i->k && Y_IN_RANGE(k1)) {
			set_ipoint(i, s, WHICH_SIDE, k1);
			return true;
		}
		return false;
	}

	b = 2. * HR2 * (Vx * Sx + Vz * Sz) - Vy;
	c = HR2 * (Sx * Sx + Sz * Sz) - Sy;
	delta = b * b - 4 * a * c;

	if (delta < 0.) {
		return false;

	} else if (delta > 0.) {
		sqrt_delta = sqrt(delta);
		k1 = (-b - sqrt_delta) / (2. * a);
		k2 = (-b + sqrt_delta) / (2. * a);

		if (k2 <= 0 || i->k <= k1)
			return false;

		if (k1 > 0 && Y_IN_RANGE(k1)) {
			set_ipoint(i, s, FLAG_OUTSIDE, k1);
			return true;
		}

		if (k2 < i->k && Y_IN_RANGE(k2)) {
			set_ipoint(i, s, FLAG_INSIDE, k2);
			return true;
		}

	} else {
		k1 = -b / (2. * a);
		if (k1 > 0 && k1 < i->k && Y_IN_RANGE(k1)) {
			set_ipoint(i, s, WHICH_SIDE, k1);
			return true;
		}
	}

	return false;
}


struct shape *paraboloid(const struct coord *base, const struct coord *apex,
			 double r)
{
	assert_is_point(base);
	assert_is_point(apex);
	assert(r > 0.);

	double f;
	struct coord vec;
	struct paraboloid *pb = alloc_struct(paraboloid);

	vector(&vec, base, apex);

	normalize(&pb->cs.j, &vec);
	pb->cs.o = *base;

	transform(&pb->cs.j);
	transform(&pb->cs.o);

	if (is_collinear(&pb->cs.j, &vector_j, &f)) {
		if (f > 0.) {
			pb->cs.i = vector_i;
			pb->cs.k = vector_k;
		} else {
			pb->cs.i = vector_k;
			pb->cs.k = vector_i;
		}
	} else {
		cross(&pb->cs.k, &pb->cs.j, &vector_j);
		normalize_in_place(&pb->cs.k);
		cross(&pb->cs.i, &pb->cs.j, &pb->cs.k);
	}

	assert_is_cartesian_coord_system(&pb->cs.i, &pb->cs.j, &pb->cs.k);

	change_of_coord_mat(&pb->cs);

	pb->r          = r;
	pb->h          = len(&vec);
	pb->hr2	       = pb->h / (r * r);
	pb->intersect  = paraboloid_intersect;
	pb->paint      = default_painter;
	pb->paint_data = 0;

	return CAST_SHAPE(pb);
}
