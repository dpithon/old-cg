#include "hit.h"
#include "pool.h"
#include "ray.h"
#include "shape.h"
#include "stack.h"
#include "types.h"
#include "vmath.h"


struct plane {
	struct shape shape;
};


static bool intersect_(struct hit *i, const struct ray *ray, const struct shape *s)
{
	double k;

	if (double_equals(Vy, 0.))
		return false;

	k = - (Sy / Vy);
	if (k > 0 && k < i->k) {
		set_hit(i, s, ray, Vy > 0? UNDER: OVER, k);
		return true;
	}

	return false;
}


static void normal_(struct coord *norm, const struct coord *i)
{
	set_vector(norm, 0., 1., 0.);
	(void) i;
}


struct shape *plane(const struct coord *loc, const struct coord *norm)
{
	// TODO Merge with quadric.c::set_cs()
	
	assert_is_point(loc);
	assert_is_vector(norm);

	double f;
	struct plane *pln = alloc_shape(plane);

	SHAPE(pln)->shape_type = SHAPE_SURF_PLANE;
	normalize(&SHAPE(pln)->cs.j, norm);
	SHAPE(pln)->cs.o = *loc;

	transform(&SHAPE(pln)->cs.j);
	transform(&SHAPE(pln)->cs.o);

	if (is_collinear(&SHAPE(pln)->cs.j, &vector_j, &f)) {
		if (f > 0.) {
			SHAPE(pln)->cs.i = vector_i;
			SHAPE(pln)->cs.k = vector_k;
		} else {
			SHAPE(pln)->cs.i = vector_k;
			SHAPE(pln)->cs.k = vector_i;
		}
	} else {
		cross(
			&SHAPE(pln)->cs.k, 
			&SHAPE(pln)->cs.j,
			&vector_j
		);
		normalize_in_place(&SHAPE(pln)->cs.k);
		cross(&SHAPE(pln)->cs.i, &SHAPE(pln)->cs.j, &SHAPE(pln)->cs.k);
	}

	change_of_coord_mat(&SHAPE(pln)->cs);
	register_intersect_function(SHAPE_SURF_PLANE, intersect_);
	register_normal_function(SHAPE_SURF_PLANE, normal_);

	return SHAPE(pln);
}
