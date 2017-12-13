#include "hit.h"
#include "dlist.h"
#include "log.h"
#include "ray.h"
#include "scene.h"
#include "shape.h"
#include "vmath.h"


struct scene {
	struct dlist shape_list;
};


static struct scene scene;


bool scene_intersect(struct hit *hit, const struct ray *ray_cam)
{
	struct ray ray_shp;
	struct shape *shape;

	foreach_shape (shape, &scene) {
		matcol(&ray_shp.s, &shape->cam_to_shp, &ray_cam->s);
		matcol(&ray_shp.v, &shape->cam_to_shp, &ray_cam->v);

		shape->intersect(hit, &ray_shp, shape);
	}

	return is_defined(hit);
}


void add_shape(struct shape *shp)
{
	dlist_append(&scene, shp);
}


void prepare_shape_matrices(const struct cs *cam_cs)
{
	struct shape *s;

	foreach_shape (s, &scene) {
		matmat(&s->cam_to_shp, &s->cs.mi, &cam_cs->m);
		matmat(&s->shp_to_cam, &cam_cs->mi, &s->cs.m);

		#ifndef NDEBUG
		struct matrix id;
		matmat(&id, &s->cam_to_shp, &s->shp_to_cam);
		assert_is_mequal(&id, &matrix_id);
		#endif /* NDEBUG */
	}
}
