#include "backend.h"

void shade4(struct rgb *c1, struct rgb *c2, 
	    struct rgb *c3, struct rgb *c4)
{
	int x, y;
	struct rgbd d13, d24, left, right, dlr, col;

	int w = get_backend_width();
	int h = get_backend_height();

	d13.r = (c3->r - c1->r) / (double) h;
	d13.g = (c3->g - c1->g) / (double) h;
	d13.b = (c3->b - c1->b) / (double) h;

	d24.r = (c4->r - c2->r) / (double) h;
	d24.g = (c4->g - c2->g) / (double) h;
	d24.b = (c4->b - c2->b) / (double) h;
	
	left.r  = (double) c1->r;
	left.g  = (double) c1->g;
	left.b  = (double) c1->b;

	right.r = (double) c2->r;
	right.g = (double) c2->g;
	right.b = (double) c2->b;

	for (y = 0; y < h; y ++) {
		dlr.r = (right.r - left.r) / (double) w;
		dlr.g = (right.g - left.g) / (double) w;
		dlr.b = (right.b - left.b) / (double) w;

		col.r = left.r;
		col.g = left.g;
		col.b = left.b;
		for (x = 0; x < w; x ++) {
			plot_rgbd(x, y, &col);
			col.r += dlr.r;
			col.g += dlr.g;
			col.b += dlr.b;
		}

		left.r  += d13.r;
		left.g  += d13.g;
		left.b  += d13.b;

		right.r += d24.r;
		right.g += d24.g;
		right.b += d24.b;
	}
}
