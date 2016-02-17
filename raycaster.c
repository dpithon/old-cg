#include "math/math.h"
#include "bpix/bpix.h"
#include "pinhole.h"
#include "ipoint.h"
#include "color.h"
#include "sampler.h"
#include "scene.h"

bool intersect(ipoint_t *i, coord_t *r)
{
	i->flags = 0;
	if (r->y > .0F && r->x < 0.F)
		return true;
	return false;
}

void render(rgb_t *rgb)
{
	rgb->r = 0xFF;
	rgb->g = 0xFF;
	rgb->b = 0x00;
}

#define W	320
#define H	240

int main()
{
	struct bpix pix;
	rgb_t rgb;

	bpix_init(&pix, W, H);

	set_location(1.F, 1.F, 1.F);
	set_target(0.F, 0.F, 0.F);

	init_pinhole(W, H, 40.F);

	for (int x = 0; x < W; x++)
		for (int y = 0; y < H; y++) {
			if (sampling(&rgb, x, y))
				bpix_set(&pix, x, y, rgb.r, rgb.g, rgb.b);
			else
				bpix_set(&pix, x, y, 0, 0, 0);
		}
	
	bpix_pnm_write_to_file(&pix, "result.pnm");
	return 0;
}	
