#include "material.h"
#include "rgb.h"
#include "mm.h"

struct plain_color {
	MATERIAL_BASIC;
	struct rgb rgb;
};

struct stripes {
	MATERIAL_BASIC;
	double size;
	struct rgb rgb[2];
};


#define PLAIN_COLOR(mat)	((struct plain_color*) mat)
#define STRIPES(mat)		((struct stripes*) mat)


static void plain_color(struct rgb *rgb, const struct ipoint *i,
			const struct material *mat)
{
	rgb->r = PLAIN_COLOR(mat)->rgb.r;
	rgb->g = PLAIN_COLOR(mat)->rgb.g;
	rgb->b = PLAIN_COLOR(mat)->rgb.b;

	(void)i; /* prevent gcc "unused argument" warning */
}


static void stripes(struct rgb *rgb, const struct ipoint *i,
		    const struct material *mat)
{
	int x, n = 0;

	x = ((int) trunc(((struct coord*)i)->x / STRIPES(mat)->size)) % 2;
	if (x == 0)
		n = 1;

	if (((struct coord*)i)->x < 0.)
		n = n?0:1;

	rgb->r = STRIPES(mat)->rgb[n].r;
	rgb->g = STRIPES(mat)->rgb[n].g;
	rgb->b = STRIPES(mat)->rgb[n].b;
}


static void circle_stripes(struct rgb *rgb, const struct ipoint *i,
			   const struct material *mat)
{
	int r, n = 0;

	r = ((int) trunc(sqrt(((struct coord*)i)->x * ((struct coord*)i)->x +
			     ((struct coord*)i)->z * ((struct coord*)i)->z) / STRIPES(mat)->size)) % 2;

	if (r == 0)
		n = 1;

	rgb->r = STRIPES(mat)->rgb[n].r;
	rgb->g = STRIPES(mat)->rgb[n].g;
	rgb->b = STRIPES(mat)->rgb[n].b;
}


void set_material_plain_colors(struct shape *shp, double r1, double g1, double b1, double r2, double g2, double b2)
{
	set_material_plain_color(shp, FLAG_INSIDE, r1, g1, b1);
	set_material_plain_color(shp, FLAG_OUTSIDE, r2, g2, b2);
}


void set_material_plain_color(struct shape *shp, int side, double r, double g, double b)
{
	int n = 0;
	struct plain_color *p = alloc_struct(plain_color);

	p->rgb.r = r;
	p->rgb.g = g;
	p->rgb.b = b;

	p->get_intrinsic = plain_color;

	if (side == FLAG_UNDER || side == FLAG_INSIDE)
		n = 1;

	shp->material[n] = CAST_MATERIAL(p);
}


void set_material_stripes(struct shape *shp, int side, double s,
			  double r1, double g1, double b1,
			  double r2, double g2, double b2)
{
	int n = 0;
	struct stripes *m = alloc_struct(stripes);

	m->size     = s;
	m->rgb[0].r = r1;
	m->rgb[0].g = g1;
	m->rgb[0].b = b1;
	m->rgb[1].r = r2;
	m->rgb[1].g = g2;
	m->rgb[1].b = b2;

	m->get_intrinsic = stripes;

	if (side == FLAG_UNDER || side == FLAG_INSIDE)
		n = 1;

	shp->material[n] = CAST_MATERIAL(m);
}


void set_material_circle_stripes(struct shape *shp, int side, double s,
				 double r1, double g1, double b1,
				 double r2, double g2, double b2)
{
	int n = 0;
	struct stripes *m = alloc_struct(stripes);

	m->size     = s;
	m->rgb[0].r = r1;
	m->rgb[0].g = g1;
	m->rgb[0].b = b1;
	m->rgb[1].r = r2;
	m->rgb[1].g = g2;
	m->rgb[1].b = b2;

	m->get_intrinsic = circle_stripes;

	if (side == FLAG_UNDER || side == FLAG_INSIDE)
		n = 1;

	shp->material[n] = CAST_MATERIAL(m);
}
