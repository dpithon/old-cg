#include <math.h>
#include "rgp.h"

#define WIDTH	768
#define HEIGHT	768

#ifndef M_PI
#define M_PI 3.14159265F
#endif /* M_PI */

int main(int argc, char *argv[])
{
	int x0, y0, l;
	float a;

	rgp_init(WIDTH, HEIGHT, argc, argv);

	x0 = WIDTH / 2;
	y0 = HEIGHT / 2;
	l  = (2 * (WIDTH > HEIGHT ? HEIGHT : WIDTH)) / 6;

	rgp_set_color(0, 200, 50);
	for (a = 0; a < M_PI * 2; a += M_PI / 180.) {
		int x1 = x0 + (float) l * cos(a);
		int y1 = y0 + (float) l * sin(a);

		rgp_line(x0, y0, x1, y1);
	}

	rgp_gui_main();

	return 0;
}
