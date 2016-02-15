/**
 * pinhole camera.
 *
 */

#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <rt/vmath.h>

/* Pinhole camera coordinates system. */
static coord_t pcs_os = PNT_O,
	       pcs_is = VEC_I,
	       pcs_js = VEC_J,
	       pcs_ks = VEC_K;

/** Change-of-coordinates matrices.
 *
 *   m: camera to world,
 *  mi: world to camera
 */
static matrix_t pcs_m  = MAT_ID,
		pcs_mi = MAT_ID;

/* Focal length and field of view */
static float focal, fov = 40.F;

/* Pinhole camera sensor width and height and mapping constants */
static int width, height;
static float sqr_edge, fac_xy, off_x, off_y;


/**
 * compute_coordsys - compute pinhole camera coordinate system and
 *                    change-of-coordinates matrices.
 * 
 * Any changes on coordinate systems implies new matrices.
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

	matrix_t rot, tsl;
	coord_t minus_os;
	float p;

	if (is_pequal(s, t))
		return false;

	memcpy(&pcs_os, s, sizeof(coord_t));

	unit_vector(&pcs_ks, s, t);
	if (is_collinear(&pcs_ks, &vector_j, &p)) {
		if (p > 0.F) {
			memcpy(&pcs_is, &vector_k, sizeof(coord_t));
			memcpy(&pcs_js, &vector_i, sizeof(coord_t));
		} else {
			memcpy(&pcs_is, &vector_i, sizeof(coord_t));
			memcpy(&pcs_js, &vector_k, sizeof(coord_t));
		}
	} else {
		cross(&pcs_is, &pcs_ks, &vector_j);
		unit_me(&pcs_is);
		cross(&pcs_js, &pcs_ks, &pcs_is);
	}

	matrix(&pcs_m, &pcs_is, &pcs_js, &pcs_ks, &pcs_os);

	translation(&tsl, scale(&minus_os, &pcs_os, -1.F));
	matrixr(&rot, &pcs_is, &pcs_js, &pcs_ks, &point_o);
	matmat(&pcs_mi, &rot, &tsl);

	return true;
}


/** set_fov: set field of view and compute associated focal length.
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


/** init_mapping - compute constants to map pixel on "sensor" surface.
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


/** map_pixel - map pixel on "sensor" surface.
 *
 * c1: coordinates of lower left corner of mapped pixel
 * c2: coordinates of upper right corner of mapped pixel
 * x:  pixel x in [0:W-1]
 * y:  pixel y in [0:H-1]
 *
 */
void map_pixel(coord_t *c1, coord_t *c2, int x, int y)
{
	assert(x >= 0 && y >= 0 && x < width && y < height);

	c1->x = ((float) x) * fac_xy + off_x;
	c1->y = ((float) y) * fac_xy + off_y;
	c1->z = c2->z = - focal;
	c1->w = c2->w = 1.F;

	c2->x = c1->x + sqr_edge;
	c2->y = c1->y + sqr_edge;
}


/*********************************************************************/

int main()
{
	coord_t s, t, v, vv, w;
	matrix_t id;

	random_point(&s);
	random_point(&t);
	random_vector(&v);

	if (!init_pinhole(&s, &t, 4, 4, 65.F))
		return 1;

	for (int x = 0; x < 4; x++)
		for (int y = 0; y < 4; y++) {
			map_pixel(&v, &vv, x, y);
			print_coord(NULL, &v);
			print_coord(NULL, &vv);
			printf("\n");
		}

	assert(is_pccs(&pcs_is, &pcs_js, &pcs_ks));

	matmat(&id, &pcs_m, &pcs_mi);
	if (!is_mequal(&id, &matrix_id)) {
		printf("m.mi != id\n");
		print_coord("S", &s);
		print_coord("T", &s);
		return 1;
	}

	matcol(&w, &pcs_m, &v);
	matcol(&vv, &pcs_mi, &w);

	if (!is_vequal(&v, &vv)) {
		printf("mp.m.v != v\n");
		print_coord("S", &s);
		print_coord("T", &s);
		return 1;
	}

	print_coord("V ", &v);
	print_coord("W ", &w);
	print_coord("V'", &vv);

	printf("%f\n",  focal);
	return 0;
}
