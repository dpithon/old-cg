#include <math.h>
#include "picture.h"
#include "pixmap.h"
#include "rgb.h"

static struct rgb def_rgb = Black;


bool init_picture(int w, int h)
{
	return pixmap_init(w, h);
}


void set_default_color(const struct rgb *rgb)
{
	def_rgb = *rgb;
}


void set_pixel(int x, int y, const struct rgb *rgb)
{
	unsigned char r, g, b;

	if (!rgb)
		rgb = &def_rgb;

	r = (unsigned char) roundf(255.F * rgb->r);
	g = (unsigned char) roundf(255.F * rgb->g);
	b = (unsigned char) roundf(255.F * rgb->b);

	pixmap_set(x, y, r, g, b);
}


bool save_picture(const char *fname)
{
	return pixmap_write(FORMAT_PPM, fname);
}
