#include "pinhole.h"
#include "sampler.h"
#include "renderer.h"
#include "scene.h"
#include "picture.h"
#include "surfaces.h"

void renderer_nil(rgb_t *rgb)
{
	static rgb_t yellow = RGBYellow;
	*rgb = yellow;
}

#define W	320
#define H	240

static rgb_t gray = RGBLightGray;

int main()
{
	set_location(0.F, 15.F, 0.F);
	set_target(10000.F, 0.F, 0.F);
	plane(&PointO, &VectorJ);

	init_pinhole(W, H, 40.F);

	set_renderer(CAST_RENDERER(renderer_nil));
	set_default_color(&gray);

	prepare_shape_matrices(pinhole_ccs());
	for (int x = 0; x < W; x++)
		for (int y = 0; y < H; y++)
			sampling(x, y);
	
	return save_picture("result.pnm");
}	
