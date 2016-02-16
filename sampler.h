#ifndef _SAMPLER_H
#define _SAMPLER_H

#include "color.h"

void set_sampler(bool (*)(rgb_t*, int, int));
bool sampling(rgb_t*, int, int);

#endif /* _SAMPLER_H */
