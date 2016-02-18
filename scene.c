#include <assert.h>
#include "scene.h"

struct coord Location = {100.F, 100.F, 100.F, 1.F};
struct coord Target   = POINT_O;

static struct shape *shapes;


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


bool intersect(struct ipoint *i, const struct ray *r)
{
	struct shape *s = shapes;

	RESET_IPOINT(i);

	while (s) {
		s->intersect(i, r, s);
		s = s->next;
	}

	return IS_DEFINED(i);
}


void add_shape(struct shape *shp)
{
	shp->next = 0;
	if (shapes)
		shapes->next = shp;
	else
		shapes = shp;
}


void prepare_shape_matrices(const struct coord_system *cam_ccs)
{
	struct shape *s = shapes;
	/* matrix_t id; */

	while (s) {
		matmat(&s->m, &s->ccs.mi, &cam_ccs->m);
		matmat(&s->mi, &cam_ccs->mi, &s->ccs.m);
		/* matmat(&id, &s->m, &s->mi);
		 * assert(is_mequal(&id, &MatrixId)); */
		s = s->next;
	}
}
