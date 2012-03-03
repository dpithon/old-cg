#include <stdio.h>
#include <assert.h>
#include "gui.h"
#include "backend.h"

#ifndef ubyte
#define ubyte unsigned char
#endif /* ubyte */

#define rgp_point(x, y) be_set_pixel(x, y, Red, Green, Blue);
#define swap(a,b,tmp)	tmp = a; a = b; b = tmp

static ubyte Red   = 255;
static ubyte Green = 255;
static ubyte Blue  = 255;

void rgp_init(int width, int height, int argc, char *argv[])
{
	gui_init(width, height, argc, argv);
}


void rgp_gui_main(void)
{
	gui_main();
}


void rgp_set_color(ubyte r, ubyte g, ubyte b)
{
	Red   = r;
	Green = g;
	Blue  = b;
}


void rgp_line(int x0, int y0, int x1, int y1)
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

		rgp_point(x, y);
		while (x < x1) {
			++x;
			if (d < 0) {
				d += incE;
			} else {
				d += incNE;
				++y;
			}
			rgp_point(x, y);
		}

	} else if (dy < 0 && dx > -dy) { /* 8th octant */
		dy = -dy;
		incE  = 2 * dy;
		incNE = 2 * (dy - dx);
		d     = 2 * dy - dx;

		rgp_point(x, y);
		while (x < x1) {
			x ++;
			if (d < 0) {
				d += incE;
			} else {
				d += incNE;
				y --;
			}
			rgp_point(x, y);
		}

	} else if (dy > 0 && dy > dx) { /* 2nd octant */
		incE  = 2 * dx;
		incNE = 2 * (dx - dy);
		d     = 2 * dx - dy;

		rgp_point(x, y);
		while (y < y1) {
			y ++;
			if (d < 0) {
				d += incE;
			} else {
				d += incNE;
				x ++;
			}
			rgp_point(x, y);
		}

	} else if (dy < 0 && -dy > dx) { /* 7th octant */
		dy = -dy;
		incE  = 2 * dx;
		incNE = 2 * (dx - dy);
		d     = 2 * dx - dy;

		rgp_point(x, y);
		while (y > y1) {
			y --;
			if (d < 0) {
				d += incE;
			} else {
				d += incNE;
				x ++;
			}
			rgp_point(x, y);
		}

	} else if (dy == 0) {
		for (x = x0; x <= x1; x++)
			rgp_point(x, y);
		#ifndef NDEBUG
		/* x == x1 + 1. Adjust x for final asserts */
		--x;
		#endif /* NDEBUG */

	} else if (dx == 0) {
		if (y0 > y1) {
			swap(y0, y1, y);
		}

		for (y = y0; y <= y1; y++)
			rgp_point(x, y);

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
			rgp_point(x, y);
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
