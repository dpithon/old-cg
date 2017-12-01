#include "log.h"
#include "sampler.h"


static void no_sampler()
{
	fatal("no pixel sampler!");
}
sample_f sampler = no_sampler;


void set_sampler(sample_f f)
{
	sampler = f;
}
