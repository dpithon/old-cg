#include "render.h"
#include "ipoint.h"
#include "shape.h"

static void default_render(struct rgb *rgb, const struct ipoint *i)
{
	i->shape->paint(rgb, i);
}
render_f render = default_render;


void set_render(render_f f)
{
	render = f;
}
