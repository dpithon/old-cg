#include <assert.h>
#include "scene.h"
#include "vmath.h"
#include "shape.h"
#include "ipoint.h"
#include "ray.h"

struct coord Location = {100., 100., 100., 1.};
struct coord Target   = POINT_O;

static struct shape *list_head;
static struct shape *list_tail;


void set_location(double x, double y, double z)
{
	Location.x = x;
	Location.y = y;
	Location.z = z;
	Location.w = 1.;
}


void set_target(double x, double y, double z)
{
	Target.x = x;
	Target.y = y;
	Target.z = z;
	Target.w = 1.;
}


bool intersect(struct ipoint *i, const struct ray *ray_cam)
{
	struct shape *s = list_head;
	struct ray ray_shp;

	while (s) {
		matcol(&ray_shp.s, &s->cam_to_shp, &ray_cam->s);
		matcol(&ray_shp.v, &s->cam_to_shp, &ray_cam->v);

		s->intersect(i, &ray_shp, s);
		s = s->next;
	}

	return is_defined(i);
}


void add_shape(struct shape *shp)
{
	shp->next = 0;

	if (!list_head) {
		list_head = list_tail = shp;
	} else {
		list_tail->next = shp;
		list_tail = shp;
	}
}


void prepare_shape_matrices(const struct coord_system *cam_cs)
{
	struct shape *s = list_head;
	struct matrix id;

	while (s) {
		matmat(&s->cam_to_shp, &s->cs.mi, &cam_cs->m);
		matmat(&s->shp_to_cam, &cam_cs->mi, &s->cs.m);
		matmat(&id, &s->cam_to_shp, &s->shp_to_cam);
		assert(is_mequal(&id, &MatrixId));

		s = s->next;
	}
}
