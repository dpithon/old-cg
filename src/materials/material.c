#include "material.h"
#include "pool.h"
#include "rgb.h"

#define MATERIAL_POOL_SZ	(1 * MEGA)

#define PLAIN_COLOR(mat)	((struct plain_color*) mat)
#define ALTERN_COLORS(mat)	((struct altern_colors*) mat)
#define RED(mat)		(PLAIN_COLOR(mat)->rgb.r)
#define GREEN(mat)		(PLAIN_COLOR(mat)->rgb.g)
#define BLUE(mat)		(PLAIN_COLOR(mat)->rgb.b)
#define ALTERN_RED(mat, n)	(ALTERN_COLORS(mat)->rgb[n].r)
#define ALTERN_GREEN(mat, n)	(ALTERN_COLORS(mat)->rgb[n].g)
#define ALTERN_BLUE(mat, n)	(ALTERN_COLORS(mat)->rgb[n].b)
#define SIZE			(ALTERN_COLORS(mat)->size)
#define X			(((struct coord*)i)->x)
#define Z			(((struct coord*)i)->z)


struct plain_color {
	MATERIAL_BASIC;
	struct rgb rgb;
};


struct altern_colors {
	MATERIAL_BASIC;
	double size;
	struct rgb rgb[2];
};


static void *alloc_material(size_t sz)
{
	static int pool_id = -1;

	if (pool_id < 0)
		pool_id = pool_init(MATERIAL_POOL_SZ);

	return pool_alloc(pool_id, sz);
}


static void color(struct rgb *rgb, const struct hit *i,
		  const struct material *mat)
{
	rgb->r = RED(mat);
	rgb->g = GREEN(mat);
	rgb->b = BLUE(mat);

	(void)i; /* prevent gcc "unused argument" warning */
}


static void stripes(struct rgb *rgb, const struct hit *i,
		    const struct material *mat)
{
	int mod_x, sx, n;

	sx = X > 0.;
	mod_x = ((int) trunc(fabs(X) / SIZE)) % 2;
	n = sx? mod_x: !mod_x;

	rgb->r = ALTERN_RED(mat, n);
	rgb->g = ALTERN_GREEN(mat, n);
	rgb->b = ALTERN_BLUE(mat, n);
}


static void checker(struct rgb *rgb, const struct hit *i,
		    const struct material *mat)
{
	int mod_x, mod_z, sx, sz, n;

	sx = X > 0.;
	sz = Z > 0.;
	mod_x = ((int) trunc(fabs(X) / SIZE)) % 2;
	mod_z = ((int) trunc(fabs(Z) / SIZE)) % 2;

	n = (sx == sz)? (mod_x == mod_z): (mod_x != mod_z);
	
	rgb->r = ALTERN_RED(mat, n);
	rgb->g = ALTERN_GREEN(mat, n);
	rgb->b = ALTERN_BLUE(mat, n);
}


static void circles(struct rgb *rgb, const struct hit *i,
		    const struct material *mat)
{
	int mod_r;

	mod_r = ((int) trunc(sqrt(X * X + Z * Z) / SIZE)) % 2;

	rgb->r = ALTERN_RED(mat, mod_r);
	rgb->g = ALTERN_GREEN(mat, mod_r);
	rgb->b = ALTERN_BLUE(mat, mod_r);
}


static void sphstripes(struct rgb *rgb, const struct hit *i,
		       const struct material *mat)
{
	int mod_theta;
	struct sphcoord s;

	cart2sphr(&s, (struct coord*)i);
	mod_theta = ((int) trunc(DEG(s.theta) / SIZE)) % 2;

	rgb->r = ALTERN_RED(mat, mod_theta);
	rgb->g = ALTERN_GREEN(mat, mod_theta);
	rgb->b = ALTERN_BLUE(mat, mod_theta);
}


static void sphchecker(struct rgb *rgb, const struct hit *i,
		       const struct material *mat)
{
	int mod_theta, mod_phy, n;
	struct sphcoord s;

	cart2sphr(&s, (struct coord*)i);
	mod_theta = ((int) trunc(DEG(s.theta) / SIZE)) % 2;
	mod_phy   = ((int) trunc(DEG(s.phy) / SIZE)) % 2;

	n = (mod_theta == mod_phy);

	rgb->r = ALTERN_RED(mat, n);
	rgb->g = ALTERN_GREEN(mat, n);
	rgb->b = ALTERN_BLUE(mat, n);
}


static void set_pattern(struct shape *shp, int side, struct altern_colors *ac, 
			void (*fun)(struct rgb*, const struct hit*,
				    const struct material*))
{
	int n = 0;

	ac->get_intrinsic = fun;

	if (side == UNDER || side == INSIDE)
		n = 1;

	shp->material[n] = CAST_MATERIAL(ac);
}


struct rgb *rgb(double r, double g, double b)
{
	struct rgb *rgb = alloc_material(sizeof(struct rgb));

	rgb->r = r;
	rgb->g = g;
	rgb->b = b;

	return rgb;
}


struct altern_colors *altern_colors(double size, struct rgb *c1, struct rgb *c2)
{
	struct altern_colors *ac = alloc_material(sizeof(struct altern_colors));

	ac->size = size;
	ac->rgb[0] = *c1;
	ac->rgb[1] = *c2;

	return ac;
}


void plain_colors(struct shape *shp, struct rgb *rgb)
{
	plain_color(shp, INSIDE, &rgb[0]);
	plain_color(shp, OUTSIDE, &rgb[1]);
}


void plain_color(struct shape *shp, int side, struct rgb *rgb)
{
	int n = 0;
	struct plain_color *p = alloc_material(sizeof(struct plain_color));

	p->rgb.r = rgb->r;
	p->rgb.g = rgb->g;
	p->rgb.b = rgb->b;

	p->get_intrinsic = color;

	if (side == UNDER || side == INSIDE)
		n = 1;

	shp->material[n] = CAST_MATERIAL(p);
}


void pat_stripes(struct shape *shp, int side, struct altern_colors *ac)
{
	set_pattern(shp, side, ac, stripes);
}


void pat_checker(struct shape *shp, int side, struct altern_colors *ac)
{
	set_pattern(shp, side, ac, checker);
}


void pat_circles(struct shape *shp, int side, struct altern_colors *ac)
{
	set_pattern(shp, side, ac, circles);
}


void pat_sphstripes(struct shape *shp, int side, struct altern_colors *ac)
{
	set_pattern(shp, side, ac, sphstripes);
}


void pat_sphchecker(struct shape *shp, int side, struct altern_colors *ac)
{
	set_pattern(shp, side, ac, sphchecker);
}
