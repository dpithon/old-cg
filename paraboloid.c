#include <assert.h>
#include <stdlib.h>

#include "vmath.h"
#include "types.h"
#include "plane.h"
#include "scene.h"
#include "ipoint.h"
#include "ray.h"
#include "paraboloid.h"
#include "painter.h"

#define A(s) ((struct paraboloid*)s)->a
#define B(s) ((struct paraboloid*)s)->b
#define C(s) ((struct paraboloid*)s)->c
#define MAX_Y(s) ((struct paraboloid*)s)->max_y


static bool check(float k, struct ipoint *i, const struct ray *ray, const struct shape *s)
{
	if (k > 0 && k < i->k) {
		if ((k * ray->v.y + ray->s.y) < MAX_Y(s))
			return true;
	}
	return false;
}


#include <stdio.h>
static bool paraboloid_intersect(struct ipoint *i, const struct ray *ray,
				 const struct shape *s)
{
	float a, b, c, delta;
	float pbaa, pbbb;

	pbaa = A(s) * A(s);
	pbbb = B(s) * B(s);

	a = (ray->v.x * ray->v.x / pbaa) + (ray->v.z * ray->v.z / pbbb);
	b = (2.F * ray->v.x * ray->s.x / pbaa) +
	    (2.F * ray->v.z * ray->s.z / pbbb) -
	    (ray->v.y / C(s));
	c = (ray->s.x * ray->s.x / pbaa) +
	    (ray->s.z * ray->s.z / pbbb) -
	    (ray->s.y / C(s));

	delta = b * b - 4 * a * c;

	if (float_equals(delta, 0.F)) {
		float k = -b / (2.F * a);
		if (check(k, i, ray, s)) {
			set_ipoint(i, s, FLAG_OUTSIDE, k);
			return true;
		}
	} else if (delta > 0.F) {
		float k1, k2, sqrt_delta;

		sqrt_delta = sqrtf(delta);
		k1 = (-b - sqrt_delta) / (2.F * a);
		k2 = (-b + sqrt_delta) / (2.F * a);

		if (k1 > 0) {
			if (k1 < i->k) {
				float y = k1 * ray->v.y + ray->s.y;
				if (y < MAX_Y(s)) {
					set_ipoint(i, s, FLAG_OUTSIDE, k1);
					return true;
				} else if (k2 < i->k) {
					y = k2 * ray->v.y + ray->s.y;
					if (y < MAX_Y(s)) {
						set_ipoint(i, s, FLAG_INSIDE, k2);
						return true;
					}
				}
			}
		} else if (k2 > 0) {
			printf("!!!!\n");
			if (k2 < i->k) {
				float y = k2 * ray->v.y + ray->s.y;
				if (y < MAX_Y(s)) {
					set_ipoint(i, s, FLAG_INSIDE, k2);
					return true;
				}
			}
		}
	}

	return false;
}


struct shape *paraboloid(const struct coord *loc, const struct coord *norm,
			 float a, float b, float c, float max_y)
{	
	float p;
	struct paraboloid *pb = malloc(sizeof(struct paraboloid));

	assert(is_point(loc));
	assert(is_vector(norm));

	unit(&pb->cs.j, norm);
	pb->cs.o = *loc;

	if (is_collinear(&pb->cs.j, &VectorJ, &p)) {
		if (p > 0.F) {
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

	assert(is_cartesian_coord_system(&pb->cs.i, &pb->cs.j, &pb->cs.k));

	change_of_coord_mat(&pb->cs);

	pb->a          = a;
	pb->b          = b;
	pb->c          = c;
	pb->max_y      = max_y;
	pb->intersect  = paraboloid_intersect;
	pb->paint      = default_painter;
	pb->paint_data = 0;

	return CAST_SHAPE(pb);
}
