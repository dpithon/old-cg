#include "hit.h"
#include "pool.h"
#include "ray.h"
#include "shape.h"
#include "shape.priv.h"
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

	struct plane *pln = alloc_shape(plane);

	SHAPE(pln)->shape_type = SHAPE_SURF_PLANE;
	set_cs(SHAPE(pln), loc, norm);

	change_of_coord_mat(&SHAPE(pln)->cs);
	register_intersect_function(SHAPE_SURF_PLANE, intersect_);
	register_normal_function(SHAPE_SURF_PLANE, normal_);

	return SHAPE(pln);
}
