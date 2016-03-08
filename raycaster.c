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

#define W	500
#define H	500


#define CONES	12
#define RADIUS 15
void build_scene(void)
{
	struct shape *s;
	struct coord loc1 = POINT_O, loc2 = POINT_O, loc3 = POINT_O;
	double angle = (2. * M_PI) / (double) CONES;

	loc2.y = 4.;
	loc3.y = 1.;
	for (int n = 0; n < CONES; n++) {
		double nangle = angle * (double) n;
		loc1.x = cos(nangle) * RADIUS;
		loc1.z = sin(nangle) * RADIUS;
		loc2.x = cos(nangle) * (RADIUS + 4.);
		loc2.z = sin(nangle) * (RADIUS + 4.);
		loc3.x = cos(nangle) * (RADIUS - 4.);
		loc3.z = sin(nangle) * (RADIUS - 4.);

		s = cylinder(&loc2, &loc1, 2.);
		set_plain_color(s, FLAG_OUTSIDE, RGBYellow);
		set_plain_color(s, FLAG_INSIDE, RGBDarkGray);
		add_shape(s);

		s = cylinder(&loc3, &loc1, 2.);
		set_plain_color(s, FLAG_OUTSIDE, RGBOrange);
		set_plain_color(s, FLAG_INSIDE, RGBDarkGray);
		add_shape(s);
	}
}


int main()
{
	set_location(30, -30, 30);
	set_target(0, 10, 0);
	set_location(0, 120, 0);
	set_target(100, 100, 100);
	if (!init_pinhole(W, H, 45.)) {
		fatal("failed to initialize pinhole camera");
		return 1;
	}

	init_pixmap(W, H);

	// build_scene();
	struct coord base = {100, 0, 100, 1};
	struct coord apex = {80, 100, 80, 1};
	struct shape *s = cylinder(&base, &apex, 10.);
	set_plain_color(s, FLAG_INSIDE, RGBWhite);
	set_plain_color(s, FLAG_OUTSIDE, RGBBlue);
	add_shape(s);
	prepare_shape_matrices(pinhole_coord_system());

	for (int x = 0; x < W; x++)
		for (int y = 0; y < H; y++)
			pixel_sampling(x, y);

	return write_pixmap(FORMAT_PPM, "a.pnm");
}
