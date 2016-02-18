#include <assert.h>
#include "scene.h"

coord_t Location = {100.F, 100.F, 100.F, 1.F};
coord_t Target   = POINT_O;

static shape_t *shapes;

void set_location(float x, float y, float z)
{
	Location.x = x;
	Location.y = y;
	Location.z = z;
	Location.w = 1.F;
}


void set_target(float x, float y, float z)
{
	Target.x = x;
	Target.y = y;
	Target.z = z;
	Target.w = 1.F;
}


bool intersect(ipoint_t *i, const ray_t *r)
{
	shape_t *s = shapes;

	RESET_IPOINT(i);

	while (s) {
		s->intersect(i, r, s);
		s = s->next;
	}

	return IS_DEFINED(i);
}


void add_shape(shape_t *shp)
{
	shp->next = 0;
	if (shapes)
		shapes->next = shp;
	else
		shapes = shp;
}


void prepare_shape_matrices(const ccs_t *cam_ccs)
{
	shape_t *s = shapes;
	/* matrix_t id; */

	while (s) {
		matmat(&s->m, &s->ccs.mi, &cam_ccs->m);
		matmat(&s->mi, &cam_ccs->mi, &s->ccs.m);
		/* matmat(&id, &s->m, &s->mi);
		 * assert(is_mequal(&id, &MatrixId)); */
		s = s->next;
	}
}
