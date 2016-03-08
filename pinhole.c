/**
 * pinhole camera.
 *
 */

#include <assert.h>
#include <math.h>

#include "debug.h"
#include "pinhole.h"
#include "vmath.h"
#include "scene.h"
#include "ray.h"
#include "rgb.h"
#include "ipoint.h"
#include "pixmap.h"
#include "sampler.h"
#include "renderer.h"


/* Pinhole cartesian coordinate system */
static struct coord_system coord_system = STANDARD_CS;

/* Focal length and field of view */
static double focal, fov = 40.;

/* Pinhole camera sensor width and height and mapping constants */
static int width, height;
static double sqr_edge, fac_xy, off_x, off_y;


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
	double p;

	if (is_pequal(&Location, &Target))
		return error("Location and target points coincide", false);

	coord_system.o = Location;

	unit_vector(&coord_system.k, &Location, &Target);
	if (is_collinear(&coord_system.k, &VectorJ, &p)) {
		if (p > 0.) {
			coord_system.i = VectorK;
			coord_system.j = VectorI;
		} else {
			coord_system.i = VectorI;
			coord_system.j = VectorK;
		}
	} else {
		cross(&coord_system.i, &coord_system.k, &VectorJ);
		unit_me(&coord_system.i);
		cross(&coord_system.j, &coord_system.k, &coord_system.i);
	}

	assert_is_cartesian_coord_system(
		&coord_system.i,
		&coord_system.j,
		&coord_system.k
	);

	change_of_coord_mat(&coord_system);
	return true;
}


/** set_fov - set field of view and compute matching focal length.
 *
 * f: field of view in degrees
 *
 * return false if field of view is invalid.
 */
static bool set_fov(double f)
{
	if (f <= 0. || f >= 180.)
		return error("fov is out of range", false);

	fov = f;
	focal = 1. / (2. * tan(f * M_PI / 360.));
	return true;
}


/**
 * init_mapping - compute constants to map pixel on "sensor" surface.
 *
 */
static void init_mapping(void)
{
	assert(width >= height);

	sqr_edge = 1. / ((double) width);
	fac_xy   = - sqr_edge;
	off_x    = 0.5 - sqr_edge;
	off_y    = ((double) height) / ((double) (2. * width)) - sqr_edge;
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
	c->x = ((double) x) * fac_xy + off_x;
	c->y = ((double) y) * fac_xy + off_y;
	c->z = - focal;
	c->w = 1.;
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
	center.x += sqr_edge / 2.;
	center.y += sqr_edge / 2.;

	unit_vector(&ray.v, &center, &PointO);
	reset_ipoint(&i);
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
bool init_pinhole(int w, int h, double fov)
{
	if (h > w || w <= 0 || h <= 0)
		return false;

	width  = w;
	height = h;
	init_mapping();

	if (!set_fov(fov))
		return false;

	if (!compute_coordsys())
		return false;

	set_sampler(samplers[DEFAULT_SAMPLER]);

	return true;
}


/**
 *
 */
const struct coord_system *pinhole_coord_system(void)
{
	return &coord_system;
}
