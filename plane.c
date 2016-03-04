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

	if (double_equals(ray->v.y, 0.))
		return false;

	k = - (ray->s.y / ray->v.y);
	if (k > 0 && k < i->k) {
		set_ipoint(i, s, ray->v.y > 0? FLAG_UNDER: FLAG_OVER, k);
		return true;
	}

	return false;
}


struct shape *plane(const struct coord *loc, const struct coord *norm)
{
	double p;
	struct plane *pln = malloc(sizeof(struct plane));

	assert_is_point(loc);
	assert_is_vector(norm);

	unit(&pln->cs.j, norm);
	pln->cs.o = *loc;

	transform(&pln->cs.j);
	transform(&pln->cs.o);

	if (is_collinear(&pln->cs.j, &VectorJ, &p)) {
		if (p > 0.) {
			pln->cs.i = VectorI;
			pln->cs.k = VectorK;
		} else {
			pln->cs.i = VectorK;
			pln->cs.k = VectorI;
		}
	} else {
		cross(&pln->cs.k, &pln->cs.j, &VectorJ);
		unit_me(&pln->cs.k);
		cross(&pln->cs.i, &pln->cs.j, &pln->cs.k);
	}

	change_of_coord_mat(&pln->cs);
	pln->intersect  = plane_intersect;
	pln->paint      = default_painter;
	pln->paint_data = 0;

	return CAST_SHAPE(pln);
}
