#include "renderer.h"
#include "fatal.h"

static void no_renderer()
{
	fatal("no renderer!");
}
renderer rendering = no_renderer;


void set_renderer(renderer f)
{
	rendering = f;
}
