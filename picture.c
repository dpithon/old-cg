#include <math.h>
#include "picture.h"
#include "bpix/bpix.h"
#include "rgb.h"

static struct bpix picture;
static struct rgb def_rgb = Black;


bool init_picture(int w, int h)
{
	return bpix_init(&picture, w, h);
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

	bpix_set(&picture, x, y, r, g, b);
}


bool save_picture(const char *fname)
{
	return bpix_pnm_write_to_file(&picture, fname);
}
