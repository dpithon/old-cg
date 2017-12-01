#include "pool.h"
#include "rgb.h"

struct rgb *rgb(double r, double g, double b)
{
	struct rgb *rgb = alloc_struct(rgb);

	rgb->r = r;
	rgb->g = g;
	rgb->b = b;

	return rgb;
}
