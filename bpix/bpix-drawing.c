#include <assert.h>
#include "bpix-core.h"
#include "bpix-drawing.h"

#define swap(a,b,tmp)	tmp = a; a = b; b = tmp
void bpix_line(struct bpix *bp, struct gctx *gc, 
		int x0, int y0, int x1, int y1)
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

		bpix_set(bp, x, y, gc->fg_r, gc->fg_g, gc->fg_b);
		while (x < x1) {
			++x;
			if (d < 0) {
				d += incE;
			} else {
				d += incNE;
				++y;
			}
			bpix_set(bp, x, y, gc->fg_r, gc->fg_g, gc->fg_b);
		}

	} else if (dy < 0 && dx > -dy) { /* 8th octant */
		dy = -dy;
		incE  = 2 * dy;
		incNE = 2 * (dy - dx);
		d     = 2 * dy - dx;

		bpix_set(bp, x, y, gc->fg_r, gc->fg_g, gc->fg_b);
		while (x < x1) {
			++x;
			if (d < 0) {
				d += incE;
			} else {
				d += incNE;
				y --;
			}
			bpix_set(bp, x, y, gc->fg_r, gc->fg_g, gc->fg_b);
		}

	} else if (dy > 0 && dy > dx) { /* 2nd octant */
		incE  = 2 * dx;
		incNE = 2 * (dx - dy);
		d     = 2 * dx - dy;

		bpix_set(bp, x, y, gc->fg_r, gc->fg_g, gc->fg_b);
		while (y < y1) {
			++y;
			if (d < 0) {
				d += incE;
			} else {
				d += incNE;
				x ++;
			}
			bpix_set(bp, x, y, gc->fg_r, gc->fg_g, gc->fg_b);
		}

	} else if (dy < 0 && -dy > dx) { /* 7th octant */
		dy = -dy;
		incE  = 2 * dx;
		incNE = 2 * (dx - dy);
		d     = 2 * dx - dy;

		bpix_set(bp, x, y, gc->fg_r, gc->fg_g, gc->fg_b);
		while (y > y1) {
			--y;
			if (d < 0) {
				d += incE;
			} else {
				d += incNE;
				x ++;
			}
			bpix_set(bp, x, y, gc->fg_r, gc->fg_g, gc->fg_b);
		}

	} else if (dy == 0) {
		for (x = x0; x <= x1; x++)
			bpix_set(bp, x, y, gc->fg_r, gc->fg_g, gc->fg_b);
		#ifndef NDEBUG
		/* x == x1 + 1. Adjust x for final asserts */
		--x;
		#endif /* NDEBUG */

	} else if (dx == 0) {
		if (y0 > y1) {
			swap(y0, y1, y);
		}

		for (y = y0; y <= y1; y++)
			bpix_set(bp, x, y, gc->fg_r, gc->fg_g, gc->fg_b);

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
			bpix_set(bp, x, y, gc->fg_r, gc->fg_g, gc->fg_b);
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
