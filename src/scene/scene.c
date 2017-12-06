#include "hit.h"
#include "list.h"
#include "log.h"
#include "ray.h"
#include "shape.h"
#include "vmath.h"


static struct list scene;


bool scene_intersect(struct hit *i, const struct ray *ray_cam)
{
	struct ray ray_shp;
	struct list_iterator itr;
	struct shape *s;

	init_list_iterator(&itr, &scene);

	for (s = iter_init(&itr, SHAPE); s; s = iterate(&itr, SHAPE)) {
		matcol(&ray_shp.s, &s->cam_to_shp, &ray_cam->s);
		matcol(&ray_shp.v, &s->cam_to_shp, &ray_cam->v);

		s->intersect(i, &ray_shp, s);
	}
	iter_cleanup(&itr); 

	return is_defined(i);
}


void add_shape(struct shape *shp)
{
	list_append(&scene, shp);
}


void prepare_shape_matrices(const struct cs *cam_cs)
{
	struct list_iterator iter;
	struct shape *s;

	init_list_iterator(&iter, &scene);

	s = iter_init(&iter, SHAPE); 
	while (s) {
		matmat(&s->cam_to_shp, &s->cs.mi, &cam_cs->m);
		matmat(&s->shp_to_cam, &cam_cs->mi, &s->cs.m);

		#ifndef NDEBUG
		struct matrix id;
		matmat(&id, &s->cam_to_shp, &s->shp_to_cam);
		assert_is_mequal(&id, &matrix_id);
		#endif /* NDEBUG */
		s = iterate(&iter, SHAPE);
	}
	iter_cleanup(&iter); 
}
