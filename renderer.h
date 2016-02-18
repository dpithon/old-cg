#ifndef RENDERER_H
#define RENDERER_H

#include "types.h"

#define CAST_RENDERER(r) ((renderer)(r))

void set_renderer(renderer);

extern renderer rendering;

#endif /* RENDERER_H */
