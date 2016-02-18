#ifndef TYPES_H
#define TYPES_H

#ifndef bool
typedef enum { false = 0, true = 1 } bool;
#endif /* bool */

struct ipoint;
struct ray;
struct rgb;
struct shape;
struct plane;
struct coord;
struct coord_system;
struct matrix;

typedef void (*renderer)(struct rgb*, const struct ipoint*);
typedef void (*sampler)(int, int);

#endif /* TYPES_H */
