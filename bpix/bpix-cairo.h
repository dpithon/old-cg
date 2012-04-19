/**
 * bpix / cairo integration
 */

#ifndef _BPIX_CAIRO_H
#define _BPIX_CAIRO_H

#include <cairo.h>
#include "bpix-core.h"

int bpix_cairo_create_surface_from_bpix(struct bpix*, cairo_surface_t**);
int bpix_cairo_create_bpix_from_surface(cairo_surface_t*, struct bpix*);

#endif /* _BPIX_CAIRO_H */
