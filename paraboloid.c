#include <stdlib.h>
#include <math.h>

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
	double a, b, c;
	double h;
};


#define A(s) ((struct paraboloid*)s)->a
#define B(s) ((struct paraboloid*)s)->b
#define C(s) ((struct paraboloid*)s)->c
#define H(s) ((struct paraboloid*)s)->h


#define Y(k)	(k * ray->v.y + ray->s.y)
static bool paraboloid_intersect(struct ipoint *i, const struct ray *ray,
				 const struct shape *s)
{
	double a, b, c, delta;
	double pbaa, pbbb;

	pbaa = A(s) * A(s);
	pbbb = B(s) * B(s);

	a = (ray->v.x * ray->v.x / pbaa) + (ray->v.z * ray->v.z / pbbb);
	b = (2. * ray->v.x * ray->s.x / pbaa) +
	    (2. * ray->v.z * ray->s.z / pbbb) -
	    (ray->v.y / C(s));
	c = (ray->s.x * ray->s.x / pbaa) +
	    (ray->s.z * ray->s.z / pbbb) -
	    (ray->s.y / C(s));

	delta = b * b - 4 * a * c;

	if (delta < 0.)
		return false;

	if (double_equals(delta, 0.)) {
		double k = -b / (2. * a);
		if (k > 0 && k < i->k && Y(k) < H(s)) {
			set_ipoint(i, s, FLAG_OUTSIDE, k);
			return true;
		}
		return false;
	}

	double k1, k2, sqrt_delta;

	sqrt_delta = sqrtf(delta);
	k1 = (-b - sqrt_delta) / (2. * a);
	k2 = (-b + sqrt_delta) / (2. * a);

	if (k2 <= 0 || i->k < k1)
		return false;

	if (k1 > 0 && Y(k1) < H(s)) {
		set_ipoint(i, s, FLAG_OUTSIDE, k1);
		return true;
	}

	if (k2 < i->k && Y(k2) < H(s)) {
		set_ipoint(i, s, FLAG_INSIDE, k2);
		return true;
	}

	return false;
}


struct shape *paraboloid(const struct coord *loc, const struct coord *norm,
			 double a, double b, double c, double h)
{
	double p;
	struct paraboloid *pb = malloc(sizeof(struct paraboloid));

	assert_is_point(loc);
	assert_is_vector(norm);

	unit(&pb->cs.j, norm);
	pb->cs.o = *loc;

	transform(&pb->cs.j);
	transform(&pb->cs.o);

	if (is_collinear(&pb->cs.j, &VectorJ, &p)) {
		if (p > 0.) {
			pb->cs.i = VectorI;
			pb->cs.k = VectorK;
		} else {
			pb->cs.i = VectorK;
			pb->cs.k = VectorI;
		}
	} else {
		cross(&pb->cs.k, &pb->cs.j, &VectorJ);
		unit_me(&pb->cs.k);
		cross(&pb->cs.i, &pb->cs.j, &pb->cs.k);
	}

	assert_is_cartesian_coord_system(&pb->cs.i, &pb->cs.j, &pb->cs.k);

	change_of_coord_mat(&pb->cs);

	pb->a          = a;
	pb->b          = b;
	pb->c          = c;
	pb->h          = h;
	pb->intersect  = paraboloid_intersect;
	pb->paint      = default_painter;
	pb->paint_data = 0;

	return CAST_SHAPE(pb);
}
