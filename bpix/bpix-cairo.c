#include <cairo.h>
#include "bpix-core.h"
#include "bpix-error.h"

int bpix_cairo_create_surface_from_bpix(struct bpix *gp, 
					cairo_surface_t **surf)
{

	*surf = cairo_image_surface_create_for_data(
		gp->data, CAIRO_FORMAT_RGB24, gp->w, gp->h, gp->stride
	);
	
	if (cairo_surface_status(*surf) == CAIRO_STATUS_SUCCESS) 
		return 0;
			
	gp->error = BPIX_ERR_BPIX_TO_CAIRO_FAILURE;
	return 1;
}


int bpix_cairo_create_bpix_from_surface(struct bpix *gp,
					cairo_surface_t *surf)
{
	if (gp->data) {
		gp->error = BPIX_ERR_UNINITIALIZED;
		return 1;
	}

	if ((gp->data = cairo_image_surface_get_data(surf))) {
		gp->w = cairo_image_surface_get_width(surf);
		gp->h = cairo_image_surface_get_height(surf);
		gp->stride = cairo_image_surface_get_stride(surf);
		gp->sz = gp->stride * gp->h;
		gp->int_sz = gp->sz >> 2;
		
		return 0;
	}

	gp->error = BPIX_ERR_CAIRO_TO_BPIX_FAILURE;
	return 1;
}
