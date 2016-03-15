#include <stdlib.h>

#include "vmath.h"
#include "types.h"
#include "scene.h"
#include "ipoint.h"
#include "ray.h"
#include "surfaces.h"
#include "painter.h"
#include "stack.h"
#include "debug.h"


struct plane {
	SHAPE_INF;
};


static bool plane_intersect(struct ipoint *i, const struct ray *ray,
			    const struct shape *s)
{
	double k;

	if (double_equals(Vy, 0.))
		return false;

	k = - (Sy / Vy);
	if (k > 0 && k < i->k) {
		set_ipoint(i, s, Vy > 0? FLAG_UNDER: FLAG_OVER, k);
		return true;
	}

	return false;
}


struct shape *plane(const struct coord *loc, const struct coord *norm)
{
	assert_is_point(loc);
	assert_is_vector(norm);

	double f;
	struct plane *pln = malloc(sizeof(struct plane));

	unit(&pln->cs.j, norm);
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
		unit_me(&pln->cs.k);
		cross(&pln->cs.i, &pln->cs.j, &pln->cs.k);
	}

	change_of_coord_mat(&pln->cs);
	pln->intersect  = plane_intersect;
	pln->paint      = default_painter;
	pln->paint_data = 0;

	return CAST_SHAPE(pln);
}
