#include "pool.h"
#include "vmath.h"
#include "types.h"
#include "ipoint.h"
#include "ray.h"
#include "shape.h"
#include "stack.h"


struct plane {
	SHAPE_BASIC;
};


static bool plane_intersect(struct ipoint *i, const struct ray *ray,
			    const struct shape *s)
{
	double k;

	if (double_equals(Vy, 0.))
		return false;

	k = - (Sy / Vy);
	if (k > 0 && k < i->k) {
		set_ipoint(i, s, ray, Vy > 0? UNDER: OVER, k);
		return true;
	}

	return false;
}


static void normal(struct coord *norm, const struct coord *i)
{
	set_vector(norm, 0., 1., 0.);
	(void) i;
}


struct shape *plane(const struct coord *loc, const struct coord *norm)
{
	assert_is_point(loc);
	assert_is_vector(norm);

	double f;
	struct plane *pln = alloc_struct(plane);

	normalize(&pln->cs.j, norm);
	pln->cs.o = *loc;

	transform(&pln->cs.j);
	transform(&pln->cs.o);

	if (is_collinear(&pln->cs.j, &vector_j, &f)) {
		if (f > 0.) {
			pln->cs.i = vector_i;
			pln->cs.k = vector_k;
		} else {
			pln->cs.i = vector_k;
			pln->cs.k = vector_i;
		}
	} else {
		cross(&pln->cs.k, &pln->cs.j, &vector_j);
		normalize_in_place(&pln->cs.k);
		cross(&pln->cs.i, &pln->cs.j, &pln->cs.k);
	}

	change_of_coord_mat(&pln->cs);
	pln->intersect  = plane_intersect;
	pln->normal_vector  = normal;

	return CAST_SHAPE(pln);
}
