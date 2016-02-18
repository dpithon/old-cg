#include "vmath.h"
#include "bpix/bpix.h"
#include "rgb.h"

static struct bpix picture;
static struct rgb def_rgb = RGBBlack;


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
	if (rgb)
		bpix_set(&picture, x, y, rgb->r, rgb->g, rgb->b);
	else
		bpix_set(&picture, x, y, def_rgb.r, def_rgb.g, def_rgb.b);
}


bool save_picture(const char *fname)
{
	return bpix_pnm_write_to_file(&picture, fname);
}
