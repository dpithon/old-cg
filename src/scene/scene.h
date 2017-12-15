#ifndef SCENE_H
#define SCENE_H

#include "macros.h"
#include "types.h"

extern bool scene_intersect(struct hit*, const struct ray*);

extern void add_shape(struct shape*);
extern void prepare_shape_matrices(const struct cs*);

#endif /* SCENE_H */
