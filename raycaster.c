#include "pinhole.h"
#include "scene.h"
#include "pixmap.h"
#include "rgb.h"
#include "ipoint.h"
#include "stack.h"
#include "shape.h"
#include "log.h"
#include "sampler.h"
#include "material.h"

#include <stdio.h>

#define W	512
#define H	512


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
		pattern_circle(s, OUTSIDE, .4, RGBLightGray, RGBDarkBlue);
		pattern_circle(s, INSIDE, .3, RGBOrange, RGBWhite);
		add_shape(s);

		s = paraboloid(&loc1, &loc3, 2.);
		pattern_circle(s, INSIDE, .1, RGBCyan, RGBGreen);
		pattern_circle(s, OUTSIDE, .3, RGBBlack, RGBBlue);
		add_shape(s);
	}

	s = plane(&point_o, &vector_j);
	pattern_checker(s, OVER, 10., RGBCornflowerBlue, RGBSnow);
	pattern_checker(s, UNDER, 5., RGBMediumOrchid1, RGBGrey100);
	add_shape(s);

	s = sphere(&point_o, 4);
	pattern_sphstripes(s, OUTSIDE, 30., RGBLightSteelBlue, RGBDarkSeaGreen4);
	add_shape(s);

}


int main()
{
	char filename[16];
	int iter;
	double x, y, z, angle, step, radius;

	angle = 0.;
	radius = 30.;
	iter = 180;
	step = 2. * M_PI / (double) iter;

	build_scene();

	for (int n = 0; n < iter; n++, angle += step) {
		x = cos(angle) * radius;
		z = sin(angle) * radius;
		y = sin(angle) * 45.;
		set_location(x, y, z);
		set_target(0, 0, 0);
		if (!init_pinhole(W, H, 45.)) {
			fatal("failed to initialize pinhole camera");
			return 1;
		}

		init_pixmap(W, H);

		prepare_shape_matrices(pinhole_coord_system());

		for (int x = 0; x < W; x++)
			for (int y = 0; y < H; y++)
				sampler(x, y);

		sprintf(filename, "a%03d.pnm", n);
		write_pixmap(FORMAT_PPM, filename);
	}

	return 0;
}
