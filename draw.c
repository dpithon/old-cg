#include "backend.h"


void draw(void)
{
	int x;
	int w = get_backend_width();
	int h = get_backend_height();

	set_rgb(200, 100, 50);
	for (x = 0; x <= (w < h ? w : h); x ++)
		plot(x, x);
}
