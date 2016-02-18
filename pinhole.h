#ifndef PINHOLE_H
#define PINHOLE_H

#include "types.h"

bool init_pinhole(int, int, float);
const struct coord_system *pinhole_ccs(void);

#endif /* PINHOLE_H */
