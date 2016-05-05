#include "material.h"
#include "rgb.h"
#include "mm.h"

struct plain_color {
	MATERIAL_BASIC;
	struct rgb rgb;
};

struct plain_colors {
	MATERIAL_BASIC;
	struct rgb rgb[2];
};


#define PLAIN_COLOR(mat)	((struct plain_color*) mat)
#define PLAIN_COLORS(mat)	((struct plain_colors*) mat)


static void plain_color(struct rgb *rgb, const struct ipoint *i,
			const struct material *mat)
{
	rgb->r = PLAIN_COLOR(mat)->rgb.r;
	rgb->g = PLAIN_COLOR(mat)->rgb.g;
	rgb->b = PLAIN_COLOR(mat)->rgb.b;
	(void)i;
}


static void plain_colors(struct rgb *rgb, const struct ipoint *i,
			 const struct material *mat)
{
	int n = 1;

	if (is_outside(i) || is_over(i))
		n = 0;

	rgb->r = PLAIN_COLORS(mat)->rgb[n].r;
	rgb->g = PLAIN_COLORS(mat)->rgb[n].g;
	rgb->b = PLAIN_COLORS(mat)->rgb[n].b;
}


void set_material_plain_color(struct shape *shp, double r, double g, double b)
{
	struct plain_color *p = alloc_struct(plain_color);

	p->rgb.r = r;
	p->rgb.g = g;
	p->rgb.b = b;

	p->get_intrinsic = plain_color;

	shp->material = CAST_MATERIAL(p);
}


void set_material_plain_colors(struct shape *shp,
			       double r1, double g1, double b1,
			       double r2, double g2, double b2)
{
	struct plain_colors *p = alloc_struct(plain_colors);

	p->rgb[0].r = r1;
	p->rgb[0].g = g1;
	p->rgb[0].b = b1;
	p->rgb[1].r = r2;
	p->rgb[1].g = g2;
	p->rgb[1].b = b2;

	p->get_intrinsic = plain_colors;

	shp->material = CAST_MATERIAL(p);
}








