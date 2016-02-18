/**
 * pinhole camera.
 *
 */

#include <math.h>

#include "pinhole.h"
#include "vmath.h"
#include "scene.h"
#include "ray.h"
#include "rgb.h"
#include "ipoint.h"
#include "picture.h"
#include "sampler.h"
#include "renderer.h"


/* Pinhole cartesian coordinate system */
static struct coord_system ccs = CCS;

/* Focal length and field of view */
static float focal, fov = 40.F;

/* Pinhole camera sensor width and height and mapping constants */
static int width, height;
static float sqr_edge, fac_xy, off_x, off_y;


/**
 * compute_coordsys - compute pinhole camera coordinate system and
 *                    change-of-coordinates matrices.
 * 
 * Any changes on Location and/or Target implies new change-of-coordinate
 * matrices.
 *
 * return false if s and t are the same point.
 */
static bool compute_coordsys(void)
{
	float p;

	if (is_pequal(&Location, &Target))
		return false;

	ccs.o = Location;

	unit_vector(&ccs.k, &Location, &Target);
	if (is_collinear(&ccs.k, &VectorJ, &p)) {
		if (p > 0.F) {
			ccs.i = VectorK;
			ccs.j = VectorI;
		} else {
			ccs.i = VectorI;
			ccs.j = VectorK;
		}
	} else {
		cross(&ccs.i, &ccs.k, &VectorJ);
		unit_me(&ccs.i);
		cross(&ccs.j, &ccs.k, &ccs.i);
	}

	return change_of_coord_mat(&ccs);
}


/** set_fov - set field of view and compute matching focal length.
 *
 * f: field of view in degrees
 *
 * return false if field of view is invalid.
 */
static bool set_fov(float f)
{
	if (f <= 0.F || f >= 180.F)
		return false;

	fov = f;
	focal = 1.F / (2.F * tanf(f * M_PI / 360.F));
	return true;
}


/**
 * init_mapping - compute constants to map pixel on "sensor" surface.
 *
 * w: horizontal resolution (width of final picture)
 * h: vertical resolution (height of final picture)
 *
 * return false if resolution is not valid
 */
static bool init_mapping(int w, int h)
{
	if (h > w || w <= 0 || h <= 0)
		return false;

	width  = w;
	height = h;

	sqr_edge = 1.F / ((float) width);
	fac_xy   = - sqr_edge;
	off_x    = 0.5F - sqr_edge;
	off_y    = ((float) height) / ((float) (2 * width)) - sqr_edge;

	return true;
}


/**
 * map_pixel - map pixel on "sensor" surface.
 *
 * c: coordinates of lower left corner of mapped pixel
 * x: pixel x in [0:W-1]
 * y: pixel y in [0:H-1]
 *
 */
static void map_pixel(struct coord *c, int x, int y)
{
	c->x = ((float) x) * fac_xy + off_x;
	c->y = ((float) y) * fac_xy + off_y;
	c->z = - focal;
	c->w = 1.F;
}


/** 
 * sampling_center - shoot ray from center of sampling surface.
 *
 * px:   pixel x coordinate
 * py:   pixel y coordinate
 */
static void sampling_center(int px, int py)
{
	struct ray ray;
	struct coord center;
	struct ipoint i;
	struct rgb rgb;

	ray.s = PointO;
	
	map_pixel(&center, px, py);
	center.x += sqr_edge / 2.F;
	center.y += sqr_edge / 2.F;

	unit_vector(&ray.v, &center, &PointO);
	if (intersect(&i, &ray)) {
		rendering(&rgb, &i);
		set_pixel(px, py, &rgb);
	} else {
		set_pixel(px, py, 0);
	}
}


#define DEFAULT_SAMPLER 0
static void (*samplers[])(int, int) = { sampling_center, 0 };
	
/**
 * init_pinhole - initialize pinhole camera.
 *
 * w:   horizontal resolution of pinhole sensor
 * h:   vertical resolution of pinhole sensor
 * fov: field of view
 *
 */
bool init_pinhole(int w, int h, float fov)
{
	if (!set_fov(fov))
		return false;

	if (!compute_coordsys())
		return false;

	if (!init_mapping(w, h))
		return false;

	if (init_picture(w, h))
		return false;

	set_sampler(samplers[DEFAULT_SAMPLER]);

	return true;
}


/**
 *
 */
const struct coord_system *pinhole_ccs(void)
{
	return &ccs;
}
