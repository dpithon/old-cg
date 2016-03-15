#ifndef SCENE_H
#define SCENE_H

#include "types.h"

extern void set_location(double, double, double);
extern void set_target(double, double, double);
extern bool intersect(struct ipoint*, const struct ray*);
extern void add_shape(struct shape*);
extern void prepare_shape_matrices(const struct coord_system*);

extern const struct coord camera_location;
extern const struct coord camera_target;

#endif /* SCENE_H */
