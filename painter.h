#ifndef PAINTER_H
#define PAINTER_H

#include "types.h"

extern void set_painter(struct shape*, paint_f, void*);

extern paint_f default_painter;

#endif /* PAINTER_H */
