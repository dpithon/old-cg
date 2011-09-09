#include <math.h>
#include "backend.h"

static unsigned char *data;
static int stride, width, height;
static cairo_surface_t *sf;
static struct rgb color = WHITE;


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


void set_rgb(unsigned char r, unsigned char g, unsigned char b)
{
	color.r = r;
	color.g = g;
	color.b = b;
}


void plot(int x, int y)
{
	plot_rgb(x, y, &color);
}


int get_backend_width(void)
{
	return width;
}

int get_backend_height(void)
{
	return height;
}

