#include <stdlib.h>
#include "plain-color.h"

void set_plain_colors(struct shape *s, unsigned char r, unsigned char g,
		      unsigned char b )
{
	if (!s->paint_data)
		s->paint_data = malloc(sizeof(struct plain_color));

	PLAIN_COLOR(s)->rgb[0].r = PLAIN_COLOR(s)->rgb[1].r = r;
	PLAIN_COLOR(s)->rgb[0].g = PLAIN_COLOR(s)->rgb[1].g = g;
	PLAIN_COLOR(s)->rgb[0].b = PLAIN_COLOR(s)->rgb[1].b = b;
}
