#include <stdlib.h>
#include "math/math.h"
#include "surfaces.h"
#include "scene.h"
#include "ipoint.h"

#include <math.h>

static bool plane_intersect(ipoint_t *i, const ray_t *r, const shape_t *pln)
{
	ray_t rr;
	float k;

	matcol(&rr.s, &pln->mi, &r->s);
	matcol(&rr.v, &pln->mi, &r->v);

	if (rr.v.y == 0)
		return false;

	k = - (rr.s.y / rr.v.y);
	if (k > 0) {
		i->flags |= FLAG_DEFINED|FLAG_OUTSIDE;
		return true;
	}

	return false;
}

void plane(const coord_t *loc, const coord_t *norm)
{	
	float p;
	plane_t *pln = malloc(sizeof(plane_t));

	unit(&pln->ccs.j, norm);
	pln->ccs.o = *loc;

	if (is_collinear(&pln->ccs.j, &VectorJ, &p)) {
		if (p > 0.F) {
			pln->ccs.i = VectorI;
			pln->ccs.k = VectorK;
		} else {
			pln->ccs.i = VectorK;
			pln->ccs.k = VectorI;
		}
	} else {
		cross(&pln->ccs.k, &pln->ccs.j, &VectorJ);
		unit_me(&pln->ccs.k);
		cross(&pln->ccs.i, &pln->ccs.j, &pln->ccs.j);
	}

	matrix_t my;
	rotationz(&my, 45.F * M_PI / 180.F);
	matcol_me(&pln->ccs.i, &my);
	matcol_me(&pln->ccs.j, &my);
	matcol_me(&pln->ccs.k, &my);
	change_of_coord_mat(&pln->ccs);
	pln->intersect = plane_intersect;
	add_shape(CAST_SHAPE(pln));
}
