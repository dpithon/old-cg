#ifndef TYPES_H
#define TYPES_H

#include <stdbool.h>

struct ipoint;
struct ray;
struct rgb;
struct shape;
struct coord;
struct sphcoord;
struct cs;
struct matrix;
struct material;

typedef void (*render_f)(struct rgb*, const struct ipoint*);
typedef void (*sample_f)(int, int);
typedef void (*intrinsic_f)(struct rgb*, const struct ipoint*,
			    const struct material*);
typedef bool (*intersect_f)(struct ipoint*, const struct ray*,
			    const struct shape*);
typedef void (*normal_f)(struct coord*, const struct coord*);

#endif /* TYPES_H */
