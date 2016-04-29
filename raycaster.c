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
#include "log.h"

#define W	750
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

		s = cone(&loc2, &loc1, 2.);
		set_plain_color(s, FLAG_OUTSIDE, RGBLightBlue);
		set_plain_color(s, FLAG_INSIDE, RGBDarkBlue);
		add_shape(s);

		s = paraboloid(&loc1, &loc3, 2.);
		set_plain_color(s, FLAG_OUTSIDE, RGBLightGray);
		set_plain_color(s, FLAG_INSIDE, RGBDarkGray);
		add_shape(s);
	}
}



void build_scene2(void)
{
	struct shape *s;
	struct coord apex = { 0, 10, 0, 1};

	s = paraboloid(&point_o, &apex, 5.);
	set_plain_color(s, FLAG_OUTSIDE, RGBLightBlue);
	set_plain_color(s, FLAG_INSIDE, RGBDarkBlue);
	add_shape(s);
}


void build_scene3(void)
{
	struct shape *s;
	struct coord apex = { 0, 10, 0, 1};

	s = cone(&point_o, &apex, 10.);
	set_plain_color(s, FLAG_OUTSIDE, RGBLightBlue);
	set_plain_color(s, FLAG_INSIDE, RGBDarkBlue);
	add_shape(s);
}


int main()
{
	set_location(30, 30, 30);
	set_target(0, 0, 0);
	if (!init_pinhole(W, H, 45.)) {
		fatal("failed to initialize pinhole camera");
		return 1;
	}

	init_pixmap(W, H);

	build_scene();
	prepare_shape_matrices(pinhole_coord_system());

	for (int x = 0; x < W; x++)
		for (int y = 0; y < H; y++)
			pixel_sampling(x, y);

	return write_pixmap(FORMAT_PPM, "a.pnm");
}
