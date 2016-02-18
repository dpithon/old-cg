#include <stdio.h>
#include <stdlib.h>
#include <vmath.h>
#include <unistd.h>
#include "rt/bpix.h"

#define WIDTH	500
#define HEIGHT	500
#define MIN_SPARKLES 80
#define MAX_SPARKLES 300
#define NR	10

#ifndef M_PI
#define M_PI 3.14159265358979323846264338327
#endif /* M_PI */

int my_round(double v)
{
	return (int) floor(v + .5);
}


void circlines(struct bpix *gp, struct gctx *gc, 
		int xc, int yc, int n, int w, int h)
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

		bpix_draw_linei(gp, gc, x0, y0, x1, y1);
	}
}


int main()
{
	int x, y, n, r, g, b, nr;
	struct bpix gp;
	struct gctx gc;

	if (bpix_init(&gp, WIDTH, HEIGHT)) {
		return gp.errno;
	}

	srand(getpid());
	for (n = 0; n < NR; n ++) {
		x = rand() % WIDTH;
		y = rand() % HEIGHT;
		r = rand() % 256;
		g = rand() % 256;
		b = rand() % 256;
		nr = rand() % MAX_SPARKLES + 1;
		nr = nr < MIN_SPARKLES ? MIN_SPARKLES : nr;
		gc.fg_r = r;
		gc.fg_g = g;
		gc.fg_b = b;
		circlines(&gp, &gc, x, y, nr, WIDTH, HEIGHT);
	}

	if (bpix_pnm_write_to_file(&gp, "circles.pnm")) {
		return gp.errno;
	}

	bpix_cleanup(&gp);
	return 0;
}
