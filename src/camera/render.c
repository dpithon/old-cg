#include "material.h"
#include "ray.h"
#include "rgb.h"

void default_render(struct rgb *rgb, const struct hit *i)
{
	get_intrinsic(rgb, i);
}


void phong_render(struct rgb *rgb, const struct hit *i)
{
	static struct coord world_light = { 1000., 1000., 1000., 1. };
	static double ka = .3, kd = .5, ks = .2, m = 100.;
	struct coord light_loc, light_vec, norm_vec, r_vec;
	double cs, cd;

	matcol(&light_loc, &i->shape->cs.mi, &world_light);
	unit_vector(&light_vec, (struct coord*) i, &light_loc);
	i->shape->normal_vector(&norm_vec, (struct coord*)i);
	get_intrinsic(rgb, i);

	cd = dot(&norm_vec, &light_vec);
	scale(&r_vec, &norm_vec, 2. * cd);
	sub_in_place(&r_vec, &light_vec);
	cs = pow(dot(&r_vec, &i->ray.v), m);

	if (cd > 0.) {
		rgb->r = rgb->r * ka + rgb->r * kd * cd + rgb->r * ks * cs;
		rgb->g = rgb->g * ka + rgb->g * kd * cd + rgb->g * ks * cs;
		rgb->b = rgb->b * ka + rgb->b * kd * cd + rgb->b * ks * cs;
	} else {
		rgb->r = rgb->r * ka;
		rgb->g = rgb->g * ka;
		rgb->b = rgb->b * ka;
	}
}


render_f render = phong_render;


void set_render(render_f f)
{
	render = f;
}


