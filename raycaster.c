#include "bpix/bpix.h"
#include "pinhole.h"
#include "ipoint.h"
#include "color.h"
#include "math/vmath.h"

bool intersect()
{
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
	coord_t s = { 0.F, 5.F, 0.F, 1.F }, t = PNT_O;
	rgb_t rgb;

	bpix_init(&pix, W, H);
	init_pinhole(&s, &t, W, H, 40.F);

	for (int x = 0; x < W; x++)
		for (int y = 0; y < H; y++) {
			if (sampling_center(&rgb, x, y))
				bpix_set(&pix, x, y, rgb.r, rgb.g, rgb.b);
			else
				bpix_set(&pix, x, y, 0, 0, 0);
		}
	
	bpix_pnm_write_to_file(&pix, "result.pnm");
	return 0;
}	
