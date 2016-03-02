#ifndef PINHOLE_H
#define PINHOLE_H

#include "types.h"

bool init_pinhole(int, int, double);
const struct coord_system *pinhole_coord_system(void);

#endif /* PINHOLE_H */
