#include <math.h>
#include "backend.h"

static unsigned char *data;
static int stride, width, height;
static cairo_surface_t *sf;
static struct rgb color = WHITE;

const struct rgb Black = BLACK, White = WHITE, Red = RED, Green = GREEN,
		 Blue = BLUE, Yellow = YELLOW, Cyan = CYAN, Magenta = MAGENTA;

cairo_surface_t *init_backend(int w, int h)
{
	sf = cairo_image_surface_create(CAIRO_FORMAT_RGB24, w, h);
	if (! sf) {
		return 0;
	}

	data = cairo_image_surface_get_data(sf);
	stride = cairo_image_surface_get_stride(sf);
	width = w;
	height = h;

	return sf;
}


void release_backend(void)
{
	cairo_surface_destroy(sf);
}


int get_backend_width(void)
{
	return width;
}


int get_backend_height(void)
{
	return height;
}


void set_color(unsigned char r, unsigned char g, unsigned char b)
{
	color.r = r;
	color.g = g;
	color.b = b;
}


void plot_rgb(int x, int y, struct rgb *col)
{
	unsigned int offset = stride * y + (x << 2);

	/* data[offset + 3] unused */
	data[offset + 2] = col->r; 
	data[offset + 1] = col->g; 
	data[offset]     = col->b; 
}


void plot_rgbd(int x, int y, struct rgbd *col)
{
	unsigned int offset = stride * y + (x << 2);

	/* data[offset + 3] unused */
	data[offset + 2] = (unsigned char) floor(col->r + .5);
	data[offset + 1] = (unsigned char) floor(col->g + .5);
	data[offset]     = (unsigned char) floor(col->b + .5);
}


void plot(int x, int y)
{
	plot_rgb(x, y, &color);
}


void shade4(const struct rgb *c1, const struct rgb *c2, 
	    const struct rgb *c3, const struct rgb *c4)
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

void fill(const struct rgb *col)
{
	register int x, y;
	for (y = 0; y < height; y++)
		for (x = 0; x < width; x++)
			plot_rgb(x, y, col);
}

