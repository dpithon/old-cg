#ifndef PINHOLE_H
#define PINHOLE_H

#include "types.h"

void set_location(double x, double y, double z);
void set_target(double x, double y, double z);
bool set_fov(double f);
bool setup_pinhole(void);
const struct cs *pinhole_coord_system(void);

#endif /* PINHOLE_H */
