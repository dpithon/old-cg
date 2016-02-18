#include <stdlib.h>
#include <math.h>

#include "vmath.h"
#include "types.h"
#include "surfaces.h"
#include "scene.h"
#include "ipoint.h"
#include "ray.h"

static bool plane_intersect(struct ipoint *i, const struct ray *r,
			    const struct shape *pln)
{
	struct ray rr;
	float k;

	matcol(&rr.s, &pln->cam_to_shp, &r->s);
	matcol(&rr.v, &pln->cam_to_shp, &r->v);

	if (rr.v.y == 0)
		return false;

	k = - (rr.s.y / rr.v.y);
	if (k > 0) {
		i->flags |= FLAG_DEFINED|FLAG_OUTSIDE;
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
