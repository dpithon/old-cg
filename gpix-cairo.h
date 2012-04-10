/**
 * gpix / cairo integration
 */

#ifndef _GPIX_CAIRO_H
#define _GPIX_CAIRO_H

#include <cairo.h>
#include "gpix.h"

int gpix_cairo_create_surface_from_gpix(struct gpix*, cairo_surface_t**);
int gpix_cairo_create_gpix_from_surface(cairo_surface_t*, struct gpix*);

#endif /* _GPIX_CAIRO_H */
