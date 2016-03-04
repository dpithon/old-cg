#include "debug.h"
#include "shape.h"
#include "ipoint.h"
#include "plain-color.h"


static void paint_with_plain_color(struct rgb *rgb, const struct ipoint *i)
{
	int c = 0;

	if (!PLAIN_COLOR(i->shape))
		fatal("plain color not defined");

	if (is_outside(i) || is_over(i))
		c = 1;

	*rgb = PLAIN_COLOR(i->shape)->rgb[c];
}
painter default_painter = paint_with_plain_color;


void set_painter(struct shape *s, painter paint, void *data)
{
	s->paint      = paint;
	s->paint_data = data;
}
