#include "pinhole.h"
#include "sampler.h"
#include "renderer.h"
#include "scene.h"
#include "picture.h"
#include "surfaces.h"
#include "rgb.h"

void renderer_nil(struct rgb *rgb)
{
	static struct rgb yellow = RGBYellow;
	*rgb = yellow;
}

#define W	640
#define H	480

static struct rgb gray = RGBLightGray;

int main()
{
	set_location(10.F, 10.F, 10.F);
	set_target(0.F, 0.F, 0.F);

	sphere(&PointO, 2.F);

	init_pinhole(W, H, 40.F);

	set_renderer(CAST_RENDERER(renderer_nil));
	set_default_color(&gray);

	prepare_shape_matrices(pinhole_coord_system());
	for (int x = 0; x < W; x++)
		for (int y = 0; y < H; y++)
			sampling(x, y);
	
	return save_picture("result.pnm");
}	
