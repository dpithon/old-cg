#include <stdlib.h>
#include "plain-color.h"
#include "ipoint.h"

void set_plain_colors(struct shape *s, float r, float g, float b)
{
	if (!s->paint_data)
		s->paint_data = malloc(sizeof(struct plain_color));

	PLAIN_COLOR(s)->rgb[0].r = PLAIN_COLOR(s)->rgb[1].r = r;
	PLAIN_COLOR(s)->rgb[0].g = PLAIN_COLOR(s)->rgb[1].g = g;
	PLAIN_COLOR(s)->rgb[0].b = PLAIN_COLOR(s)->rgb[1].b = b;
}


void set_plain_color(struct shape *s, int side, float r, float g, float b)
{
	int c = 0;

	if (!s->paint_data)
		s->paint_data = malloc(sizeof(struct plain_color));

	if (side == FLAG_OUTSIDE || side == FLAG_OVER)
		c = 1;

	PLAIN_COLOR(s)->rgb[c].r = r;
	PLAIN_COLOR(s)->rgb[c].g = g;
	PLAIN_COLOR(s)->rgb[c].b = b;
}
