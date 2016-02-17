#include "fatal.h"
#include "color.h"
#include "ipoint.h"

static void no_renderer()
{
	fatal("no renderer!");
}
	

void (*rendering)(rgb_t*, ipoint_t*) = no_renderer;


void set_renderer(void (*f)(rgb_t*, ipoint_t*))
{
	rendering = f;
}
