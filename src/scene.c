#include "shapes/shape.h"

#include "vmath.h"
#include "ipoint.h"
#include "ray.h"
#include "log.h"


static struct shape *list_head;
static struct shape *list_tail;


bool scene_intersect(struct ipoint *i, const struct ray *ray_cam)
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


void prepare_shape_matrices(const struct cs *cam_cs)
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
