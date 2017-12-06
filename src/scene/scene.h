#ifndef SCENE_H
#define SCENE_H

#include "types.h"

#define foreach_shape(s, scene) \
		struct dlist_iterator iter;\
		init_dlist_iterator(&iter, scene);\
		foreach (SHAPE, s, &iter)

extern bool scene_intersect(struct hit*, const struct ray*);
extern void add_shape(struct shape*);
extern void prepare_shape_matrices(const struct cs*);

#endif /* SCENE_H */
