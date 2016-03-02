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

typedef void (*renderer)(struct rgb*, const struct ipoint*);
typedef void (*sampler)(int, int);
typedef void (*painter)(struct rgb*, const struct ipoint*);
typedef bool (*intersector)(struct ipoint*, const struct ray*,
			    const struct shape*);

#endif /* TYPES_H */
