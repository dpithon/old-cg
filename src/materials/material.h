#ifndef MATERIAL_H
#define MATERIAL_H

#include "ipoint.h"
#include "shape.h"
#include "types.h"

#define CAST_MATERIAL(m)	((struct material*)m)
#define MATERIAL_BASIC		intrinsic_f get_intrinsic

struct material {
	MATERIAL_BASIC;
};


extern struct altern_colors *altern_colors(double, struct rgb*, struct rgb*);

extern void plain_color(struct shape*, int, struct rgb*);
extern void plain_colors(struct shape*, struct rgb*);

extern void pat_stripes(struct shape*, int, struct altern_colors*);
extern void pat_checker(struct shape*, int, struct altern_colors*);
extern void pat_circles(struct shape*, int, struct altern_colors*);
extern void pat_sphstripes(struct shape*, int, struct altern_colors*);
extern void pat_sphchecker(struct shape*, int, struct altern_colors*);

static inline void get_intrinsic(struct rgb *rgb, const struct ipoint *i)
{
	int n = 0;

	if (is_inside(i) || is_under(i))
		n = 1;

	i->shape->material[n]->get_intrinsic(
		rgb, i, i->shape->material[n]
	);
}

#endif /* MATERIAL_H */
