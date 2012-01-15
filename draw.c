#include "backend.h"

void draw(void)
{
	int v;

	shade4(&Yellow, &Red, &Green, &Blue);
	set_color(0., 0., 0.);

	for (v = 10; v < 200; v += 5)
		line(10, v, 200, v);
	for (v = 10; v < 200; v += 5)
		line(v, 10, v, 200);
}
