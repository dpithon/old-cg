/**
 * pinhole camera.
 *
 */

#include <assert.h>
#include <string.h>
#include <math.h>
#include <rt/vmath.h>

#include "color.h"
#include "ipoint.h"

extern bool intersect(ipoint_t*, const coord_t*);
extern void render(rgb_t*, const ipoint_t*);

/* Pinhole cartesian coordinate system */
static ccs_t ccs = CCS;

/* Focal length and field of view */
static float focal, fov = 40.F;

/* Pinhole camera sensor width and height and mapping constants */
static int width, height;
static float sqr_edge, fac_xy, off_x, off_y;


/**
 * compute_coordsys - compute pinhole camera coordinate system and
 *                    change-of-coordinates matrices.
 * 
 * Any changes on coordinate systems implies new change-of-coordinate
 * matrices.
 *
 * s: pinhole focal point in world coordinate system.
 * t: target point in world coordinate system.
 *
 * return false if s and t are the same point.
 */
static bool compute_coordsys(const coord_t *s, const coord_t *t)
{
	assert(is_point(s));
	assert(is_point(t));

	float p;

	if (is_pequal(s, t))
		return false;

	memcpy(&ccs.o, s, sizeof(coord_t));

	unit_vector(&ccs.k, s, t);
	if (is_collinear(&ccs.k, &vector_j, &p)) {
		if (p > 0.F) {
			memcpy(&ccs.i, &vector_k, sizeof(coord_t));
			memcpy(&ccs.j, &vector_i, sizeof(coord_t));
		} else {
			memcpy(&ccs.i, &vector_i, sizeof(coord_t));
			memcpy(&ccs.j, &vector_k, sizeof(coord_t));
		}
	} else {
		cross(&ccs.i, &ccs.k, &vector_j);
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
static void map_pixel(coord_t *c, int x, int y)
{
	assert(x >= 0 && y >= 0 && x < width && y < height);

	c->x = ((float) x) * fac_xy + off_x;
	c->y = ((float) y) * fac_xy + off_y;
	c->z = - focal;
	c->w = 1.F;
}


/**
 * init_pinhole - initialize pinhole camera.
 *
 * s:   pinhole focal point in world coordinate system.
 * t:   target point in world coordinate system.
 * w:   horizontal resolution of pinhole sensor
 * h:   vertical resolution of pinhole sensor
 * fov: field of view
 *
 */
bool init_pinhole(const coord_t *s, const coord_t* t,
		  int w, int h, float fov)
{
	if (!set_fov(fov))
		return false;

	if (!compute_coordsys(s, t))
		return false;

	if (!init_mapping(w, h))
		return false;

	return true;
}


/** 
 * sampling_center - shoot ray from center of sampling surface.
 *
 * rgb: resulting color of sampling
 * px:   pixel x coordinate
 * py:   pixel y coordinate
 *
 * return true if ray intersect a shape, false otherwise
 */
bool sampling_center(rgb_t* rgb, int px, int py)
{
	coord_t s;
	coord_t r;
	ipoint_t i;

	map_pixel(&s, px, py);
	s.x += sqr_edge / 2.F;
	s.y += sqr_edge / 2.F;

	unit_vector(&r, &s, &point_o);
	if (intersect(&i, &r)) {
		render(rgb, &i);
		return true;
	}

	return false;
}
