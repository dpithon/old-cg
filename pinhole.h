#ifndef PINHOLE_H
#define PINHOLE_H

#include "types.h"

bool init_pinhole(int, int, int, double);
const struct cs *pinhole_coord_system(void);
void cleanup_pinhole(void);

#endif /* PINHOLE_H */
