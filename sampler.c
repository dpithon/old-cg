#include "math/math.h"
#include "color.h"

static bool (*sampler)(rgb_t*, int, int);

void set_sampler(bool (*f)(rgb_t*, int, int))
{
	sampler = f;
}


bool sampling(rgb_t *rgb, int px, int py)
{
	return (*sampler)(rgb, px, py);
}
