#include "fatal.h"
#include "rgb.h"
#include "ipoint.h"
#include "renderer.h"

static void no_renderer()
{
	fatal("no renderer!");
}
renderer rendering = no_renderer;


void set_renderer(renderer f)
{
	rendering = f;
}
