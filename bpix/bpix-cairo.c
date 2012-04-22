#include <cairo.h>
#include <assert.h>
#include "bpix-core.h"
#include "bpix-error.h"

int bpix_cairo_create_surface_from_bpix(struct bpix *bp, 
					cairo_surface_t **surf)
{
	assert(bp->init == 0x696E6974);

	*surf = cairo_image_surface_create_for_data(
		bp->data, CAIRO_FORMAT_RGB24, bp->w, bp->h, bp->stride
	);
	
	if (cairo_surface_status(*surf) == CAIRO_STATUS_SUCCESS) 
		return 0;
			
	bp->errno = BPIX_ERR_BPIX_TO_CAIRO_FAILURE;
	return 1;
}


int bpix_cairo_create_bpix_from_surface(struct bpix *bp,
					cairo_surface_t *surf)
{
	assert(bp->init != 0x696E6974);

	if ((bp->data = cairo_image_surface_get_data(surf))) {
		bp->w = cairo_image_surface_get_width(surf);
		bp->h = cairo_image_surface_get_height(surf);
		bp->stride = cairo_image_surface_get_stride(surf);
		bp->sz = bp->stride * bp->h;
		bp->errno = 0;
		bp->init = 0x696E6974;
		
		return 0;
	}

	bp->errno = BPIX_ERR_CAIRO_TO_BPIX_FAILURE;
	return 1;
}
