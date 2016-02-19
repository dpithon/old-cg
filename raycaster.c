#include "pinhole.h"
#include "sampler.h"
#include "renderer.h"
#include "scene.h"
#include "picture.h"
#include "sphere.h"
#include "plane.h"
#include "rgb.h"
#include "plain-color.h"

#define W	640
#define H	480

int main()
{
	struct shape *s;
	struct shape *t;
	struct shape *p;
	struct coord c = {-50.F, 0.F, -50.F, 1.F };

	set_location(90.F, 30.F, 90.F);
	set_target(-50.F, 0.F, -50.F);
	init_pinhole(W, H, 40.F);

	p = plane(&PointO, &VectorJ);
	set_plain_colors(p, RGBLightBlue);

	s = sphere(&PointO, 180.F);
	set_plain_colors(s, RGBDarkBlue);

	t = sphere(&c, 35.F);
	set_plain_colors(t, RGBLightGray);

	add_shape(p);
	add_shape(s);
	add_shape(t);

	prepare_shape_matrices(pinhole_coord_system());
	for (int x = 0; x < W; x++)
		for (int y = 0; y < H; y++)
			sampling(x, y);
	
	return save_picture("a.pnm");
}
