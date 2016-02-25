#include "pinhole.h"
#include "sampler.h"
#include "renderer.h"
#include "scene.h"
#include "pixmap.h"
#include "sphere.h"
#include "cone.h"
#include "paraboloid.h"
#include "cylinder.h"
#include "plane.h"
#include "rgb.h"
#include "ipoint.h"
#include "plain-color.h"

#define W	640
#define H	480

int main()
{
	struct shape *s;
	struct coord cone_o = {0, 10, 10, 1};

	set_location(50, -10, 0);
	set_target(0, 10, 0);
	init_pinhole(W, H, 40.F);
	init_pixmap(W, H);

	s = cone(&cone_o, &VectorJ, 5.F, 10.F);
	set_plain_color(s, FLAG_OUTSIDE, RGBLightGray);
	set_plain_color(s, FLAG_INSIDE, RGBDarkGray);
	add_shape(s);

	s = cylinder(&PointO, &VectorJ, 5.F, 10.F);
	set_plain_color(s, FLAG_OUTSIDE, RGBLightGray);
	set_plain_color(s, FLAG_INSIDE, RGBDarkGray);
	add_shape(s);

	s = plane(&PointO, &VectorJ);
	set_plain_colors(s, RGBRed);
	//add_shape(s);

	s = sphere(&PointO, 5.F);
	set_plain_colors(s, RGBRed);
	add_shape(s);

	prepare_shape_matrices(pinhole_coord_system());

	for (int x = 0; x < W; x++)
		for (int y = 0; y < H; y++)
			sampling(x, y);

	return write_pixmap(FORMAT_PPM, "a.pnm");
}
