#include "sampler.h"
#include "debug.h"


static void no_sampler()
{
	fatal("no sampler!");
}
sampler sampling = no_sampler;


void set_sampler(sampler f)
{
	sampling = f;
}
