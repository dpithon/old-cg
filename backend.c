#include <cairo.h>
#include <assert.h>
#include <math.h>


#ifndef ubyte
#define ubyte unsigned char
#endif /* ubyte */

static ubyte *data;
static int stride, width, height;
static cairo_surface_t *sf;


cairo_surface_t *be_init(int w, int h)
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

void be_release(void)
{
	cairo_surface_destroy(sf);
}



int be_get_width(void)
{
	return width;
}


int be_get_height(void)
{
	return height;
}


void be_set_pixel(int x, int y, ubyte r, ubyte g, ubyte b)
{
	unsigned int offset = stride * y + (x << 2);

	assert(x < width && x > -1);
	assert(y < height && y > -1);

	/* data[offset + 3] unused */
	data[offset + 2] = r; 
	data[offset + 1] = g; 
	data[offset]     = b; 
}


void be_get_pixel(int x, int y, ubyte *r, ubyte *g, ubyte *b)
{
	unsigned int offset = stride * y + (x << 2);

	assert(x < width && x > -1);
	assert(y < height && y > -1);

	*r = data[offset + 2]; 
	*g = data[offset + 1]; 
	*b = data[offset]; 
}
