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
#include "debug.h"

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

#define CONES	20
#define RADIUS 15
int main()
{
	struct shape *s;
	struct coord loc1 = POINT_O, loc2 = POINT_O, loc3 = POINT_O, vec1, vec2;
	double angle = (2. * M_PI) / (double) CONES;

	s = plane(&PointO, &VectorJ);
	set_plain_colors(s, RGBLightBlue);
	//add_shape(s);

	loc2.y = 1.;
	for (int n = 0; n < CONES; n++) {
		double nangle = angle * (double) n;
		loc1.x = cos(nangle) * RADIUS;
		loc1.z = sin(nangle) * RADIUS;
		loc2.x = cos(nangle) * (RADIUS + 1.);
		loc2.z = sin(nangle) * (RADIUS + 1.);

		unit_vector(&vec1, &loc2, &loc1);
		scale_me(&vec1, 4.);
		sub(&loc3, &loc2, &vec1);
		s = cone(&loc3, &vec1, 2., 4.);
		set_plain_color(s, FLAG_OUTSIDE, RGBYellow);
		set_plain_color(s, FLAG_INSIDE, RGBDarkGray);
		add_shape(s);

		loc3.x = cos(nangle) * (RADIUS - 1);
		loc3.z = sin(nangle) * (RADIUS - 1);
		loc3.y = 0.;
		unit_vector(&vec2, &loc3, &loc1);
		scale_me(&vec2, 4.);
		loc3 = loc2;
		add_me(&loc3, &vec1);
		print_coord("loc1", &loc1);
		print_coord("loc3", &loc3);
		sub_me(&loc3, &vec2);
		s = cone(&loc3, &vec2, 2., 4.);
		set_plain_color(s, FLAG_OUTSIDE, RGBOrange);
		set_plain_color(s, FLAG_INSIDE, RGBDarkGray);
		add_shape(s);
	}

	set_location(40, 0, 40);
	set_target(0, 0, 0);
	init_pinhole(W, H, 40.);
	init_pixmap(W, H);

	prepare_shape_matrices(pinhole_coord_system());

	for (int x = 0; x < W; x++)
		for (int y = 0; y < H; y++)
			sampling(x, y);

	return write_pixmap(FORMAT_PPM, "a.pnm");
}
