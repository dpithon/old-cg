#ifndef SCENE_H
#define SCENE_H

#include "macros.h"
#include "types.h"

#define foreach_shape(s, scene) \
		struct slist_iterator UNIQUE_NAME(iter);\
		init_slist_iterator(&UNIQUE_NAME(iter), SLIST(scene));\
		foreach (SHAPE, s, &UNIQUE_NAME(iter))

extern bool scene_intersect(struct hit*, const struct ray*);
extern void add_shape(struct shape*);
extern void prepare_shape_matrices(const struct cs*);

#endif /* SCENE_H */
