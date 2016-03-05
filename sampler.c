#include "sampler.h"
#include "debug.h"


static void no_sampler()
{
	fatal("no pixel sampler!");
}
sampler pixel_sampling = no_sampler;


void set_sampler(sampler f)
{
	pixel_sampling = f;
}
