/**
 * Simple Gtk pixmap module.
 *
 * Create a cairo surface, give direct access to raw pixels plus basic
 * raster graphic functions.
 *
 */

#ifndef _GPIX_H
#define _GPIX_H

#include <cairo.h>

typedef unsigned char cval; /* color component: from 0 to 255 */

struct gpix {
	int w, h, stride, error;
	cval *data;
	cairo_surface_t *surface;
	cval fg_r, fg_g, fg_b, fg_a;
	cval bg_r, bg_g, bg_b, bg_a;
};

#define gpix_width(ptr)		((ptr)->w)
#define gpix_height(ptr)	((ptr)->h)
#define gpix_data(ptr)		((ptr)->data)
#define gpix_surface(ptr)	((ptr)->surface)
#define gpix_error(ptr)		((ptr)->error)
#define gpix_errstr(ptr)	(GPIX_ERRSTR[((ptr)->error)])

#define GPIX_DEF_FG_R	255
#define GPIX_DEF_FG_G	255
#define GPIX_DEF_FG_B	255
#define GPIX_DEF_BG_R	  0
#define GPIX_DEF_BG_G	  0
#define GPIX_DEF_BG_B	  0

extern const char *GPIX_ERRSTR[];

int gpix_create(struct gpix*);
int gpix_destroy(struct gpix*);
int gpix_create_from_png(struct gpix*, const char*);
int gpix_write_to_png(struct gpix*, const char*);

int gpix_set(struct gpix*, int, int, cval, cval, cval);
int gpix_get(struct gpix*, int, int, cval*, cval*, cval*);

void gpix_define_fg_color(struct gpix*, cval, cval, cval);
void gpix_line(struct gpix*, int, int, int, int);

#endif /* _GPIX_H */
