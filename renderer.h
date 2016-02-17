#ifndef _RENDERER_H
#define _RENDERER_H

#include "color.h"
#include "ipoint.h"

#define CAST_RENDERER(r) ((void (*)(rgb_t*, const ipoint_t*))(r))

void set_renderer(void (*)(rgb_t*, const ipoint_t*));

extern void (*rendering)(rgb_t*, const ipoint_t*);

#endif /* _RENDERER_H */
