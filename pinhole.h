#ifndef PINHOLE_H
#define PINHOLE_H

#include "vmath.h"
#include "rgb.h"

bool init_pinhole(int, int, float);
bool sampling_center(struct rgb*, int, int);
const struct coord_system *pinhole_ccs(void);

#endif /* PINHOLE_H */
