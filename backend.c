#include "backend.h"

static unsigned char *data;
static int stride, width, height;
static cairo_surface_t *sf;
static unsigned char red = 255, green = 255, blue = 255;

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


void plot_rgb(int x, int y, unsigned char r, unsigned char g, unsigned char b)
{
	unsigned int offset = stride * y + (x << 2);

	/* data[offset + 3] unused */
	data[offset + 2] = r; 
	data[offset + 1] = g; 
	data[offset] = b; 
}

void set_rgb(unsigned char r, unsigned char g, unsigned char b)
{
	red = r;
	green = g;
	blue = b;
}


void plot(int x, int y)
{
	plot_rgb(x, y, red, green, blue);
}

int get_backend_width(void)
{
	return width;
}

int get_backend_height(void)
{
	return height;
}

