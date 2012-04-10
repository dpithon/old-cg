#include "gpix-cairo.h"

int gpix_cairo_create_surface_from_gpix(struct gpix *gp, 
					cairo_surface_t **surf)
{

	*surf = cairo_image_surface_create_for_data(
		gp->data, CAIRO_FORMAT_RGB24, gp->w, gp->h, gp->stride
	);
	
	return cairo_surface_status(*surf) == CAIRO_STATUS_SUCCESS ? 0 : 10;
}


int gpix_cairo_create_gpix_from_surface(cairo_surface_t *surf, 
					struct gpix *gp)
{
	if (gp->data) {
		return gp->error = 11;
	}

	if ((gp->data = cairo_image_surface_get_data(surf))) {
		gp->w = cairo_image_surface_get_width(surf);
		gp->h = cairo_image_surface_get_height(surf);
		gp->stride = cairo_image_surface_get_stride(surf);
		gp->sz = gp->stride * gp->h;
		gp->int_sz = gp->sz >> 2;
		
		return 0;
	}

	return 12;
}
