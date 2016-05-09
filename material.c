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
#define X			(((struct coord*)i)->x)
#define Z			(((struct coord*)i)->z)
#define SIZE			(((struct stripes*) mat)->size)


static void color(struct rgb *rgb, const struct ipoint *i,
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
	int mod_x, sx, n;

	sx = X > 0.;
	mod_x = ((int) trunc(fabs(X) / SIZE)) % 2;
	n = sx? mod_x: !mod_x;

	rgb->r = STRIPES(mat)->rgb[n].r;
	rgb->g = STRIPES(mat)->rgb[n].g;
	rgb->b = STRIPES(mat)->rgb[n].b;
}


static void checker(struct rgb *rgb, const struct ipoint *i,
		    const struct material *mat)
{
	int mod_x, mod_z, sx, sz, n;

	sx = X > 0.;
	sz = Z > 0.;
	mod_x = ((int) trunc(fabs(X) / SIZE)) % 2;
	mod_z = ((int) trunc(fabs(Z) / SIZE)) % 2;

	n = (sx == sz)? (mod_x == mod_z): (mod_x != mod_z);
	
	rgb->r = STRIPES(mat)->rgb[n].r;
	rgb->g = STRIPES(mat)->rgb[n].g;
	rgb->b = STRIPES(mat)->rgb[n].b;
}


static void circles(struct rgb *rgb, const struct ipoint *i,
		    const struct material *mat)
{
	int mod_r;

	mod_r = ((int) trunc(sqrt(X * X + Z * Z) / SIZE)) % 2;

	rgb->r = STRIPES(mat)->rgb[mod_r].r;
	rgb->g = STRIPES(mat)->rgb[mod_r].g;
	rgb->b = STRIPES(mat)->rgb[mod_r].b;
}


void plain_colors(struct shape *shp,
		  double r1, double g1, double b1,
		  double r2, double g2, double b2)
{
	plain_color(shp, INSIDE, r1, g1, b1);
	plain_color(shp, OUTSIDE, r2, g2, b2);
}


void plain_color(struct shape *shp, int side, double r, double g, double b)
{
	int n = 0;
	struct plain_color *p = alloc_struct(plain_color);

	p->rgb.r = r;
	p->rgb.g = g;
	p->rgb.b = b;

	p->get_intrinsic = color;

	if (side == UNDER || side == INSIDE)
		n = 1;

	shp->material[n] = CAST_MATERIAL(p);
}


void pattern_stripes(struct shape *shp, int side, double s,
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

	if (side == UNDER || side == INSIDE)
		n = 1;

	shp->material[n] = CAST_MATERIAL(m);
}


void pattern_checker(struct shape *shp, int side, double s,
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

	m->get_intrinsic = checker;

	if (side == UNDER || side == INSIDE)
		n = 1;

	shp->material[n] = CAST_MATERIAL(m);
}


void pattern_circle(struct shape *shp, int side, double s,
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

	m->get_intrinsic = circles;

	if (side == UNDER || side == INSIDE)
		n = 1;

	shp->material[n] = CAST_MATERIAL(m);
}
