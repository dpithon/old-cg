#ifndef SCENE_H
#define SCENE_H

#include "types.h"

extern void set_location(float, float, float);
extern void set_target(float, float, float);
extern bool intersect(struct ipoint*, const struct ray*);
extern void add_shape(struct shape*);
extern void prepare_shape_matrices(const struct coord_system*);

extern struct coord Location;
extern struct coord Target;

#endif /* SCENE_H */
