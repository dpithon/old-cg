/**
 * pinhole camera.
 *
 */

#include <assert.h>
#include <math.h>

#include "ipoint.h"
#include "log.h"
#include "pinhole.h"
#include "pixmap.h"
#include "ray.h"
#include "render.h"
#include "rgb.h"
#include "sampler.h"
#include "scene.h"
#include "vmath.h"


/* Pinhole cartesian coordinate system */
static struct cs coord_system = STANDARD_CS;

/* Focal length and field of view */
static double focal, fov;
static struct coord camera_location = {100., 100., 100., 1.};
static struct coord camera_target   = POINT_O;


/* Pinhole camera sensor width and height and mapping constants */
static double sqr_edge, fac_xy, off_x, off_y;


/**
 * compute_coordsys - compute pinhole camera coordinate system and
 *                    change-of-coordinates matrices.
 *
 * Any changes on camera_location and/or camera_target implies new
 * change-of-coordinate matrices.
 *
 * return false if s and t are the same point.
 */
static bool compute_coordsys(void)
{
	double p;

	if (is_pequal(&camera_location, &camera_target))
		return error("location and target points coincide", false);

	coord_system.o = camera_location;

	unit_vector(&coord_system.k, &camera_location, &camera_target);
	if (is_collinear(&coord_system.k, &vector_j, &p)) {
		if (p > 0.) {
			coord_system.i = vector_k;
			coord_system.j = vector_i;
		} else {
			coord_system.i = vector_i;
			coord_system.j = vector_k;
		}
	} else {
		cross(&coord_system.i, &coord_system.k, &vector_j);
		normalize_in_place(&coord_system.i);
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
bool set_fov(double f)
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
	if (pixmap_width() < pixmap_height())
		fatal("pixmap_width < pixmap_height");

	sqr_edge = 1. / pixmap_width();
	fac_xy   = - sqr_edge;
	off_x    = 0.5 - sqr_edge;
	off_y    = pixmap_height() / (2. * pixmap_width()) - sqr_edge;
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
	set_point(c,
		((double) x) * fac_xy + off_x,
		((double) y) * fac_xy + off_y,
		-focal
	);
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

	ray.s = point_o;

	map_pixel(&center, px, py);
	center.x += sqr_edge / 2.;
	center.y += sqr_edge / 2.;

	unit_vector(&ray.v, &center, &point_o);
	reset_ipoint(&i);
	if (scene_intersect(&i, &ray)) {
		render(&rgb, &i);
		set_pixel(px, py, &rgb);
	} else {
		set_pixel(px, py, 0); /* 0 is default background color */
	}
}


#define DEFAULT_SAMPLER 0
static sample_f samplers[] = { sampling_center, 0 };

/**
 * setup_pinhole - setup pinhole camera.
 *
 * w:   horizontal resolution of pinhole sensor
 * h:   vertical resolution of pinhole sensor
 * fov: field of view
 *
 */
bool setup_pinhole(void)
{
	init_mapping();

	if (!compute_coordsys())
		return false;

	set_sampler(samplers[DEFAULT_SAMPLER]);

	return true;
}


/**
 *
 */
const struct cs *pinhole_coord_system(void)
{
	return &coord_system;
}


void set_location(double x, double y, double z)
{
	set_point(&camera_location, x, y, z);
}


void set_target(double x, double y, double z)
{
	set_point(&camera_target, x, y, z);
}
