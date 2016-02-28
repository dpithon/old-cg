#include "pinhole.h"
#include "sampler.h"
#include "renderer.h"
#include "scene.h"
#include "pixmap.h"
#include "rgb.h"
#include "ipoint.h"
#include "plain-color.h"
#include "stack.h"
#include "surfaces.h"

#define W	500
#define H	500

void axes(void)
{
	struct shape *s;

	s = cylinder(&PointO, &VectorI, .3F, 100.F);
	set_plain_colors(s, RGBRed);
	add_shape(s);

	s = cylinder(&PointO, &VectorJ, .3F, 100.F);
	set_plain_colors(s, RGBGreen);
	add_shape(s);

	s = cylinder(&PointO, &VectorK, .3F, 100.F);
	set_plain_colors(s, RGBBlue);
	add_shape(s);
}
	
int main()
{
	struct shape *s;

	axes();

	for (int a = 0.F; a < 360.F; a += 30.F) {
		rotate_y(-1.F * a);
		translate(25, 0, 0);
		rotate_z(a);
		s = cone(&PointO, &VectorI, 5, 10);
		//s = paraboloid(&PointO, &VectorI, 2, 2, 2, 10);
		//s = sphere(&PointO, 5);
		set_plain_color(s, FLAG_OUTSIDE, RGBLightGray);
		set_plain_color(s, FLAG_INSIDE, RGBDarkGray);
		add_shape(s);
		reset();
	}

	set_location(20, 90, 30);
	set_target(0, 10, 0);
	init_pinhole(W, H, 50.F);
	init_pixmap(W, H);

	/*
	s = cone(&cone_o, &VectorJ, 5.F, 10.F);
	set_plain_color(s, FLAG_OUTSIDE, RGBLightGray);
	set_plain_color(s, FLAG_INSIDE, RGBDarkGray);
	add_shape(s);

	s = cylinder(&PointO, &VectorJ, 5.F, 10.F);
	set_plain_color(s, FLAG_OUTSIDE, RGBLightGray);
	set_plain_color(s, FLAG_INSIDE, RGBDarkGray);
	add_shape(s);

	rotate_z(-15);
	translate(0, -3, 0);
	s = plane(&PointO, &VectorJ);
	set_plain_colors(s, RGBRed);
	add_shape(s);

	reset();
	s = sphere(&PointO, 5.F);
	set_plain_colors(s, RGBBlue);
	add_shape(s);

*/

	prepare_shape_matrices(pinhole_coord_system());

	for (int x = 0; x < W; x++)
		for (int y = 0; y < H; y++)
			sampling(x, y);

	return write_pixmap(FORMAT_PPM, "a.pnm");
}
