#include <stdlib.h>
#include <math.h>

#include "vmath.h"
#include "types.h"
#include "surfaces.h"
#include "scene.h"
#include "ipoint.h"
#include "ray.h"
#include "painter.h"
#include "stack.h"
#include "debug.h"


struct sphere {
	SHAPE_INF;
	double radius;
};


static bool sphere_intersect(struct ipoint *i, const struct ray *ray,
			     const struct shape *s)
{
	double a, b, c, delta;
	double r = ((struct sphere*) s)->radius;

	a = ray->v.x * ray->v.x + ray->v.y * ray->v.y + ray->v.z * ray->v.z;
	b = 2. * (ray->v.x * ray->s.x + ray->v.y * ray->s.y + ray->v.z * ray->s.z);
	c = ray->s.x * ray->s.x + ray->s.y * ray->s.y + ray->s.z * ray->s.z - r * r;

	delta = b * b - 4 * a * c;

	if (double_equals(delta, 0.)) {
		double k = -b / (2. * a);

		if (k > 0 && k < i->k) {
			set_ipoint(i, s, FLAG_OUTSIDE, k);
			return true;
		}
	} else if (delta > 0.) {
		double k1, k2, sqrt_delta;

		sqrt_delta = sqrtf(delta);
		k1 = (-b - sqrt_delta) / (2. * a);
		k2 = (-b + sqrt_delta) / (2. * a);

		if (k1 > 0 && k1 < i->k) {
			set_ipoint(i, s, FLAG_OUTSIDE, k1);
			return true;
		} else if (k2 > 0 && k2 < i->k) {
			set_ipoint(i, s, FLAG_INSIDE, k2);
			return true;
		}
	}

	return false;
}


struct shape *sphere(const struct coord *loc, double radius)
{
	struct sphere *sph = malloc(sizeof(struct sphere));

	assert_is_point(loc);

	sph->radius = radius;
	sph->cs.o   = *loc;
	sph->cs.i   = VectorI;
	sph->cs.j   = VectorJ;
	sph->cs.k   = VectorK;

	transform(&sph->cs.o);

	change_of_coord_mat(&sph->cs);
	sph->intersect  = sphere_intersect;
	sph->paint      = default_painter;
	sph->paint_data = 0;

	return CAST_SHAPE(sph);
}
