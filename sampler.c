#include "fatal.h"

static void no_sampler()
{
	fatal("no sampler!");
}
	

void (*sampling)(int, int) = no_sampler;


void set_sampler(void (*f)(int, int))
{
	sampling = f;
}
