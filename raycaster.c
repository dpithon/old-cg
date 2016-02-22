#include "pinhole.h"
#include "sampler.h"
#include "renderer.h"
#include "scene.h"
#include "picture.h"
#include "sphere.h"
#include "paraboloid.h"
#include "plane.h"
#include "rgb.h"
#include "ipoint.h"
#include "plain-color.h"

#define W	640
#define H	480

int main()
{
	struct shape *s;
	struct shape *p1, *p2;

	set_location(90.F, 45.F, 90.F);
	set_target(0.F, 0.F, 0.F);
	init_pinhole(W, H, 30.F);

	s = paraboloid(&PointO, &VectorJ, 6, 3, 1, 15);
	set_plain_color(s, FLAG_INSIDE, RGBWhite);
	set_plain_color(s, FLAG_OUTSIDE, RGBBlue);
	add_shape(s);

	p1 = plane(&PointO, &VectorJ);
	p2 = plane(&PointO, &VectorI);
	set_plain_colors(p1, RGBRed);
	set_plain_colors(p2, RGBYellow);
	add_shape(p1);
	add_shape(p2);

	prepare_shape_matrices(pinhole_coord_system());
	for (int x = 0; x < W; x++)
		for (int y = 0; y < H; y++)
			sampling(x, y);
	
	return save_picture("a.pnm");
}
