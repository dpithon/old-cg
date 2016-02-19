#include "pinhole.h"
#include "sampler.h"
#include "renderer.h"
#include "scene.h"
#include "picture.h"
#include "sphere.h"
#include "plane.h"
#include "rgb.h"
#include "ipoint.h"
#include "plain-color.h"

#define W	640
#define H	480

int main()
{
	struct shape *s;
	struct shape *t;
	struct shape *p, *q;
	struct coord c = {-50.F, 0.F, -50.F, 1.F };
	struct coord mi = {-1,0,0,0};

	set_location(90.F, 30.F, 90.F);
	set_target(-50.F, 0.F, -50.F);
	init_pinhole(W, H, 40.F);

	p = plane(&PointO, &VectorJ);
	set_plain_color(p, FLAG_OVER, RGBRed);

	q = plane(&c, &mi);
	set_plain_color(q, FLAG_OVER, RGBCyan);
	set_plain_color(q, FLAG_UNDER, RGBWhite);

	s = sphere(&PointO, 180.F);
	set_plain_color(s, FLAG_INSIDE, RGBGreen);

	t = sphere(&c, 35.F);
	set_plain_color(t, FLAG_OUTSIDE, RGBBlue);

	add_shape(p);
	add_shape(q);
	add_shape(s);
	add_shape(t);

	prepare_shape_matrices(pinhole_coord_system());
	for (int x = 0; x < W; x++)
		for (int y = 0; y < H; y++)
			sampling(x, y);
	
	return save_picture("a.pnm");
}
