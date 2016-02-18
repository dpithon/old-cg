#include <stdlib.h>

#include "vmath.h"
#include "types.h"
#include "surfaces.h"
#include "scene.h"
#include "ipoint.h"
#include "ray.h"

static bool plane_intersect(struct ipoint *i, const struct ray *ray,
			    const struct shape *pln)
{
	float k;

	(void)(pln);

	if (ray->v.y == 0)
		return false;

	k = - (ray->s.y / ray->v.y);
	if (k > 0 && k < i->k) {
		if (ray->v.y > 0.F)
			i->flags |= FLAG_DEFINED|FLAG_UNDER;
		else
			i->flags |= FLAG_DEFINED|FLAG_OVER;
		return true;
	}

	return false;
}


void plane(const struct coord *loc, const struct coord *norm)
{	
	float p;
	struct plane *pln = malloc(sizeof(struct plane));

	unit(&pln->cs.j, norm);
	pln->cs.o = *loc;

	if (is_collinear(&pln->cs.j, &VectorJ, &p)) {
		if (p > 0.F) {
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
	pln->intersect = plane_intersect;
	add_shape(CAST_SHAPE(pln));
}
