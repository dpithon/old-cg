#include "pinhole.h"
#include "sampler.h"
#include "renderer.h"
#include "scene.h"
#include "picture.h"

void renderer_nil(rgb_t *rgb)
{
	static rgb_t yellow = RGBYellow;
	*rgb = yellow;
}

#define W	320
#define H	240

int main()
{
	set_location(1.F, 1.F, 1.F);
	set_target(0.F, 0.F, 0.F);
	init_pinhole(W, H, 40.F);
	set_renderer(CAST_RENDERER(renderer_nil));

	for (int x = 0; x < W; x++)
		for (int y = 0; y < H; y++)
			sampling(x, y);
	
	return save_picture("result.pnm");
}	
