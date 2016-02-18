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

#define W	320
#define H	240

static struct rgb gray = RGBLightGray;

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
