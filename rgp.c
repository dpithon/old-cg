#include <assert.h>
#include "gui.h"
#include "backend.h"

#ifndef ubyte
#define ubyte unsigned char
#endif /* ubyte */

#ifndef ABS
#define ABS(v)	(((v) < 0) ? (-(v)) : (v))
#endif /* ABS */

static void rgp_vline(int, int, int);
static void rgp_hline(int, int, int);
static void rgp_dline(int, int, int, int);

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


void rgp_point(int x, int y)
{
	be_set_pixel(x, y, Red, Green, Blue);
}


void rgp_line(int x0, int y0, int x1, int y1)
{
	int dx = x1 - x0;
	int dy = y1 - y0;

	if (dx < 0) {
		int t;
		t = x0; x0 = x1; x1 = t;
		t = y0; y0 = y1; y1 = t;
		dx = -dx;
		dy = -dy;
	} else if (dx == 0) {
		rgp_vline(x0, y0, y1);
		return;
	} 
	/* dx > 0 ! */

	if (dy == 0) {
		rgp_hline(y0, x0, x1);
	} else if (ABS(dy) == ABS(dx)) {
		rgp_dline(x0, y0, x1, y1);
	} else if (dy > 0 && dx > dy) {
		/* 1st octant */
		int x = x0;
		int y = y0;

		int incE  = 2 * dy;
		int incNE = 2 * (dy - dx);

		int d = 2 * dy - dx;

		be_set_pixel(x, y, Red, Green, Blue);
		while (x < x1) {
			if (d < 0) {
				d += incE;
				x ++;
			} else {
				d += incNE;
				x ++;
				y ++;
			}
			be_set_pixel(x, y, Red, Green, Blue);
		}

		assert(y == y1);

	} else if (dy < 0 && dx > -dy) {
		/* 8th octant */
		int x = x0;
		int y = y0;

		dy = -dy;
		int incE  = 2 * dy;
		int incNE = 2 * (dy - dx);

		int d = 2 * dy - dx;

		be_set_pixel(x, y, Red, Green, Blue);
		while (x < x1) {
			if (d < 0) {
				d += incE;
				x ++;
			} else {
				d += incNE;
				x ++;
				y --;
			}
			be_set_pixel(x, y, Red, Green, Blue);
		}

		assert(y == y1);


	} else if (dy > 0 && dy > dx) {
		/* 2nd octant */
		int x = x0;
		int y = y0;

		int incE  = 2 * dx;
		int incNE = 2 * (dx - dy);

		int d = 2 * dx - dy;

		be_set_pixel(x, y, Red, Green, Blue);
		while (y < y1) {
			if (d < 0) {
				d += incE;
				y ++;
			} else {
				d += incNE;
				y ++;
				x ++;
			}
			be_set_pixel(x, y, Red, Green, Blue);
		}

		assert(x == x1);

	} else if (dy < 0 && -dy > dx) {
		/* 7th octant */
		int x = x0;
		int y = y0;

		dy = -dy;
		int incE  = 2 * dx;
		int incNE = 2 * (dx - dy);

		int d = 2 * dx - dy;

		be_set_pixel(x, y, Red, Green, Blue);
		while (y > y1) {
			if (d < 0) {
				d += incE;
				y --;
			} else {
				d += incNE;
				y --;
				x ++;
			}
			be_set_pixel(x, y, Red, Green, Blue);
		}

		assert(x == x1);
	}
}

static void rgp_vline(int x, int y0, int y1)
{
	int y;

	if (y0 > y1) {
		y = y0;
		y0 = y1; y1 = y; 
	}

	for (y = y0; y <= y1; y++)
		be_set_pixel(x, y, Red, Green, Blue);
}

static void rgp_hline(int y, int x0, int x1)
{
	int x;

	if (x0 > x1) {
		x = x0;
		x0 = x1; x1 = x; 
	}

	for (x = x0; x <= x1; x++)
		be_set_pixel(x, y, Red, Green, Blue);
}

static void rgp_dline(int x0, int y0, int x1, int y1)
{
	int x, y, slope;
	
	assert(x0 < x1);

	if (y0 < y1) {
		slope = 1;
	} else {
		slope = -1;
	}

	for (x = x0, y = y0; x <= x1; x++, y += slope) {
		be_set_pixel(x, y, Red, Green, Blue);
	}
	
}
