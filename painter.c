#include "painter.h"
#include "shape.h"
#include "ipoint.h"
#include "rgb.h"
#include "plain-color.h"


void plain_color(struct rgb *rgb, const struct ipoint *i)
{
	static const struct rgb def_outside = RGBLightGray;
	static const struct rgb def_inside  = RGBDarkGray;
	static const struct rgb def_over    = RGBLightBlue;
	static const struct rgb def_under   = RGBDarkBlue;

	const struct rgb *outside;
	const struct rgb *inside;
	const struct rgb *over;
	const struct rgb *under;

	if (PLAIN_COLOR(i->shape)) {
		outside = &PLAIN_COLOR(i->shape)->outside;
		inside  = &PLAIN_COLOR(i->shape)->inside;
		over    = &PLAIN_COLOR(i->shape)->over;
		under   = &PLAIN_COLOR(i->shape)->under;
	} else {
		outside = &def_outside;
		inside  = &def_inside;
		over    = &def_over;
		under   = &def_under;
	}

	if (is_inside(i))
		*rgb = *inside;
	else if (is_outside(i))
		*rgb = *outside;
	else if (is_over(i))
		*rgb = *over;
	else
		*rgb = *under;
}
painter default_painter = plain_color;


void set_painter(struct shape *s, painter paint, void *data)
{
	s->paint      = paint;
	s->paint_data = data;
}
