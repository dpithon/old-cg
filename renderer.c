#include "renderer.h"
#include "ipoint.h"
#include "shape.h"

static void default_rendering(struct rgb *rgb, const struct ipoint *i)
{
	i->shape->paint(rgb, i);
}
renderer rendering = default_rendering;


void set_renderer(renderer f)
{
	rendering = f;
}
