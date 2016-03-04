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

#define W	400
#define H	400

void axes(void)
{
	struct shape *s;

	s = cylinder(&PointO, &VectorI, .3, 100.);
	set_plain_colors(s, RGBRed);
	add_shape(s);

	s = cylinder(&PointO, &VectorJ, .3, 100.);
	set_plain_colors(s, RGBGreen);
	add_shape(s);

	s = cylinder(&PointO, &VectorK, .3, 100.);
	set_plain_colors(s, RGBBlue);
	add_shape(s);
}

void cones()
{
	struct shape *s;

	axes();

	for (int a = 0.; a < 360.; a += 30.) {
		rotate_y(-1. * a);
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

	//set_location(20, 90, 30);
	//set_target(0, 10, 0);
}

int main()
{
	struct shape *s;

	translate(0, -0.01, 0);
	s = plane(&PointO, &VectorJ);
	set_plain_colors(s, RGBLightBlue);
	add_shape(s);

	reset();
	translate(15, 0, 0);
	s = cylinder(&PointO, &VectorJ, 4, 10);
	set_plain_color(s, FLAG_INSIDE, RGBDarkGray);
	set_plain_color(s, FLAG_OUTSIDE, RGBLightGray);
	add_shape(s);

	reset();
	s = cone(&PointO, &VectorJ, 5, 10);
	set_plain_color(s, FLAG_OUTSIDE, RGBGreen);
	set_plain_color(s, FLAG_INSIDE, RGBCyan);
	add_shape(s);

	reset();
	translate(14, 4, 15);
	s = sphere(&PointO, 4);
	set_plain_colors(s, RGBYellow);
	add_shape(s);

	reset();
	translate(3, 0, 13);
	s = paraboloid(&PointO, &VectorJ, 5, 5, 5., 5.);
	set_plain_color(s, FLAG_OUTSIDE, RGBMagenta);
	set_plain_color(s, FLAG_INSIDE, RGBRed);
	add_shape(s);

	reset();
	struct coord mj;
	scale(&mj, &VectorJ, -1.);
	translate(-5, 10, 5);
	s = cone(&PointO, &mj, 5, 10);
	set_plain_color(s, FLAG_OUTSIDE, RGBGreen);
	set_plain_color(s, FLAG_INSIDE, RGBCyan);
	add_shape(s);

	set_location(33, 17, 40);
	set_target(10, 5, 9);
	init_pinhole(W, H, 40.);
	init_pixmap(W, H);

	prepare_shape_matrices(pinhole_coord_system());

	for (int x = 0; x < W; x++)
		for (int y = 0; y < H; y++)
			sampling(x, y);

	return write_pixmap(FORMAT_PPM, "a.pnm");
}
