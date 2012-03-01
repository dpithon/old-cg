#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include "rgp.h"

#define WIDTH	800
#define HEIGHT	500
#define MIN_SPARKLES 30
#define MAX_SPARKLES 90

#ifndef M_PI
#define M_PI 3.14159265358979323846264338327
#endif /* M_PI */

int my_round(double v)
{
	return (int) floor(v + .5);
}


void circlines(int xc, int yc, int n, int w, int h)
{
	int l0, l1, w1, w2, w3, w4;
	double a;

	w1 = xc;
	w2 = w - xc - 1;
	w3 = yc;
	w4 = h - yc - 1;

	w1 = w1 < w2 ? w1 : w2;
	w3 = w3 < w4 ? w3 : w4;
	w1 = w1 < w3 ? w1 : w3;

	l1 = w1;
	l0 = l1 / 4;

	for (a = 0; a < M_PI * 2.; a += M_PI * 2. / (double) n) {
		int x0 = xc + my_round(l0 * cos(a));
		int y0 = yc + my_round(l0 * sin(a));
		int x1 = xc + my_round(l1 * cos(a));
		int y1 = yc + my_round(l1 * sin(a));

		rgp_line(x0, y0, x1, y1);
	}
}


int main(int argc, char *argv[])
{
	int x, y, n, r, g, b, nr;

	srand(getpid());

	rgp_init(WIDTH, HEIGHT, argc, argv);

	for (n = 0; n < 10; n ++) {
		x = rand() % WIDTH;
		y = rand() % HEIGHT;
		r = rand() % 256;
		g = rand() % 256;
		b = rand() % 256;
		nr = rand() % MAX_SPARKLES + 1;
		nr = nr < MIN_SPARKLES ? MIN_SPARKLES : nr;
		rgp_set_color(r, g, b);
		circlines(x, y, nr, WIDTH, HEIGHT);
	}
	rgp_gui_main();

	return 0;
}
