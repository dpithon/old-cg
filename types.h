#ifndef TYPES_H
#define TYPES_H

#include <stdbool.h>

struct ipoint;
struct ray;
struct rgb;
struct shape;
struct plane;
struct coord;
struct coord_system;
struct matrix;
struct plain_color;

typedef void (*render_f)(struct rgb*, const struct ipoint*);
typedef void (*sample_f)(int, int);
typedef void (*paint_f)(struct rgb*, const struct ipoint*);
typedef bool (*intersect_f)(struct ipoint*, const struct ray*,
			    const struct shape*);

#endif /* TYPES_H */
