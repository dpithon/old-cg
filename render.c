#include "render.h"
#include "ipoint.h"
#include "shape.h"
#include "material.h"

static void default_render(struct rgb *rgb, const struct ipoint *i)
{
	get_intrinsic(rgb, i);
}
render_f render = default_render;


void set_render(render_f f)
{
	render = f;
}
