#ifndef _PINHOLE_H
#define _PINHOLE_H

#include "math/vmath.h"
#include "color.h"

bool init_pinhole(const coord_t*, const coord_t*, int, int, float);
bool sampling_center(rgb_t*, int, int);

#endif /* _PINHOLE_H */
