#ifndef RENDERER_H
#define RENDERER_H

#include "rgb.h"
#include "ipoint.h"

#define CAST_RENDERER(r) ((void (*)(struct rgb*, const struct ipoint*))(r))

typedef void (*renderer)(struct rgb*, const struct ipoint*);

void set_renderer(renderer);

extern renderer rendering;

#endif /* RENDERER_H */
