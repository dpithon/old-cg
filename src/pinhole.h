#ifndef PINHOLE_H
#define PINHOLE_H

#include "types.h"

extern void set_location(double x, double y, double z);
extern void set_target(double x, double y, double z);
extern bool set_fov(double f);
extern bool setup_pinhole(void);
extern const struct cs *pinhole_coord_system(void);

#endif /* PINHOLE_H */
