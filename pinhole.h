#ifndef _PINHOLE_H
#define _PINHOLE_H

#include "math/math.h"
#include "color.h"

bool init_pinhole(int, int, float);
bool sampling_center(rgb_t*, int, int);
const ccs_t *pinhole_ccs(void);

#endif /* _PINHOLE_H */
