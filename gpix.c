#include "gpix.h"
#include <assert.h>


const char *GPIX_ERRSTR[] = {
	"no error",
	"failed to create cairo surface",
	"surface already freed",
	"out of bound coordinates"
};


int gpix_create(struct gpix *gp)
{
	gp->surface = cairo_image_surface_create(
		CAIRO_FORMAT_RGB24, gp->w, gp->h);

	if (! gp->surface) {
		return gp->error = 1;
	}

	gp->data   = cairo_image_surface_get_data(gp->surface);
	gp->stride = cairo_image_surface_get_stride(gp->surface);
	
	gp->fg_r = GPIX_DEF_FG_R;
	gp->fg_g = GPIX_DEF_FG_G;
	gp->fg_b = GPIX_DEF_FG_B;

	gp->bg_r = GPIX_DEF_BG_R;
	gp->bg_g = GPIX_DEF_BG_G;
	gp->bg_b = GPIX_DEF_BG_B;

	return gp->error = 0;
}


int gpix_create_from_png(struct gpix *gp, const char *fname)
{
	gp->surface = cairo_image_surface_create_from_png(fname);

	if (! gp->surface) {
		return gp->error = 1;
	}

	gp->w      = cairo_image_surface_get_width(gp->surface);
	gp->h      = cairo_image_surface_get_height(gp->surface);
	gp->data   = cairo_image_surface_get_data(gp->surface);
	gp->stride = cairo_image_surface_get_stride(gp->surface);
	
	gp->fg_r = GPIX_DEF_FG_R;
	gp->fg_g = GPIX_DEF_FG_G;
	gp->fg_b = GPIX_DEF_FG_B;

	gp->bg_r = GPIX_DEF_BG_R;
	gp->bg_g = GPIX_DEF_BG_G;
	gp->bg_b = GPIX_DEF_BG_B;

	return gp->error = 0;
}


int gpix_destroy(struct gpix *gp)
{
	if (gp->surface) {
		cairo_surface_destroy(gp->surface);
		gp->surface = 0;
	}

	return gp->error = 2;
}



int gpix_set(struct gpix *gp, int x, int y, cval r, cval g, cval b)
{
	if (x < gp->w && x > -1 && y < gp->h && y > -1) {
		unsigned int offset = gp->stride * y + (x << 2);

		/* data[offset + 3] unused */
		gp->data[offset + 2] = r; 
		gp->data[offset + 1] = g; 
		gp->data[offset]     = b; 
		return gp->error = 0;
	}

	return gp->error = 3;
}


int gpix_get(struct gpix *gp, int x, int y, cval *r, cval *g, cval *b)
{

	if (x < gp->w && x > -1 && y < gp->h && y > -1) {
		unsigned int offset = gp->stride * y + (x << 2);

		*r = gp->data[offset + 2]; 
		*g = gp->data[offset + 1]; 
		*b = gp->data[offset]; 
		return gp->error = 0;
	}

	return gp->error = 3;
}



void gpix_define_fg_color(struct gpix *gp, cval r, cval g, cval b)
{
	gp->fg_r = r;
	gp->fg_g = g;
	gp->fg_b = b;
}


#define swap(a,b,tmp)	tmp = a; a = b; b = tmp
void gpix_line(struct gpix *gp, int x0, int y0, int x1, int y1)
{
	int x, y, dx, dy, incE, incNE, d;

	if (x0 > x1) { /* reverse points order if needed */
		swap(x0, x1, d);
		swap(y0, y1, d);
	}

	x = x0;
	y = y0;
	dx = x1 - x0;
	dy = y1 - y0;

	if (dy > 0 && dx > dy) { /* 1st octant */
		incE  = 2 * dy;
		incNE = 2 * (dy - dx);
		d     = 2 * dy - dx;

		gpix_set(gp, x, y, gp->fg_r, gp->fg_g, gp->fg_b);
		while (x < x1) {
			++x;
			if (d < 0) {
				d += incE;
			} else {
				d += incNE;
				++y;
			}
			gpix_set(gp, x, y, gp->fg_r, gp->fg_g, gp->fg_b);
		}

	} else if (dy < 0 && dx > -dy) { /* 8th octant */
		dy = -dy;
		incE  = 2 * dy;
		incNE = 2 * (dy - dx);
		d     = 2 * dy - dx;

		gpix_set(gp, x, y, gp->fg_r, gp->fg_g, gp->fg_b);
		while (x < x1) {
			++x;
			if (d < 0) {
				d += incE;
			} else {
				d += incNE;
				y --;
			}
			gpix_set(gp, x, y, gp->fg_r, gp->fg_g, gp->fg_b);
		}

	} else if (dy > 0 && dy > dx) { /* 2nd octant */
		incE  = 2 * dx;
		incNE = 2 * (dx - dy);
		d     = 2 * dx - dy;

		gpix_set(gp, x, y, gp->fg_r, gp->fg_g, gp->fg_b);
		while (y < y1) {
			++y;
			if (d < 0) {
				d += incE;
			} else {
				d += incNE;
				x ++;
			}
			gpix_set(gp, x, y, gp->fg_r, gp->fg_g, gp->fg_b);
		}

	} else if (dy < 0 && -dy > dx) { /* 7th octant */
		dy = -dy;
		incE  = 2 * dx;
		incNE = 2 * (dx - dy);
		d     = 2 * dx - dy;

		gpix_set(gp, x, y, gp->fg_r, gp->fg_g, gp->fg_b);
		while (y > y1) {
			--y;
			if (d < 0) {
				d += incE;
			} else {
				d += incNE;
				x ++;
			}
			gpix_set(gp, x, y, gp->fg_r, gp->fg_g, gp->fg_b);
		}

	} else if (dy == 0) {
		for (x = x0; x <= x1; x++)
			gpix_set(gp, x, y, gp->fg_r, gp->fg_g, gp->fg_b);
		#ifndef NDEBUG
		/* x == x1 + 1. Adjust x for final asserts */
		--x;
		#endif /* NDEBUG */

	} else if (dx == 0) {
		if (y0 > y1) {
			swap(y0, y1, y);
		}

		for (y = y0; y <= y1; y++)
			gpix_set(gp, x, y, gp->fg_r, gp->fg_g, gp->fg_b);

		#ifndef NDEBUG
		/* y == y1 + 1. Adjust y for final asserts */
		--y;
		#endif /* NDEBUG */

	} else {
		int slope;

		if (y0 < y1) {
			slope = 1;
		} else {
			slope = -1;
		}

		for (x = x0, y = y0; x <= x1; x++, y += slope) {
			gpix_set(gp, x, y, gp->fg_r, gp->fg_g, gp->fg_b);
		}
		#ifndef NDEBUG
		/* Adjust x and y for final asserts */
		y -= slope;
		--x;
		#endif /* NDEBUG */
	}

	assert(x == x1);
	assert(y == y1);
}
