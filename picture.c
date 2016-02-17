#include "math/math.h"
#include "bpix/bpix.h"
#include "color.h"

static struct bpix picture;
static rgb_t def_rgb = RGBBlack;

bool init_picture(int w, int h, const rgb_t *rgb)
{
	if (rgb)
		def_rgb = *rgb;
	return bpix_init(&picture, w, h);
}

	
void set_pixel(int x, int y, const rgb_t *rgb)
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
