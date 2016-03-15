#include "vmath.h"
#include "shape.h"
#include "ipoint.h"
#include "ray.h"
#include "debug.h"

struct coord camera_location = {100., 100., 100., 1.};
struct coord camera_target   = POINT_O;

static struct shape *list_head;
static struct shape *list_tail;


void set_location(double x, double y, double z)
{
	camera_location.x = x;
	camera_location.y = y;
	camera_location.z = z;
	camera_location.w = 1.;
}


void set_target(double x, double y, double z)
{
	camera_target.x = x;
	camera_target.y = y;
	camera_target.z = z;
	camera_target.w = 1.;
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

	while (s) {
		matmat(&s->cam_to_shp, &s->cs.mi, &cam_cs->m);
		matmat(&s->shp_to_cam, &cam_cs->mi, &s->cs.m);

		#ifndef NDEBUG
		struct matrix id;
		matmat(&id, &s->cam_to_shp, &s->shp_to_cam);
		assert_is_mequal(&id, &matrix_id);
		#endif /* NDEBUG */

		s = s->next;
	}
}
