#include <stdlib.h>
#include <assert.h>
#include "bpix-core.h"
#include "bpix-error.h"


int bpix_init(struct bpix *gp, int w, int h)
{
	assert(sizeof(int) == 4);

	if (gp->init == 0x696E6974) { /* "init" in hexa */
		gp->error = BPIX_ERR_ALREADY_INIT;
		return 1;
	}

	if (w < 0 || h < 0 || w > BPIX_MAX_W || h > BPIX_MAX_H) {
		gp->error = BPIX_ERR_PIXMAP_SIZE;
		return 1;
	}

	gp->w = w;
	gp->h = h;
	gp->stride = w << 2;
	gp->sz = gp->stride * h;
	gp->int_sz = gp->sz >> 2;

	gp->data = malloc(gp->sz);
	if (! gp->data) {
		gp->error = BPIX_ERR_MALLOC;
		return 1;
	}

	gp->init = 0x696E6974;
	gp->error = 0;

	return 0;
}


/**
 * bpix_cleanup: release memory buffer and reset structure.
 */
int bpix_cleanup(struct bpix *gp)
{
	if (gp->init != 0x696E6974) {
		gp->error = BPIX_ERR_UNINITIALIZED;
		return 1;
	}

	free(gp->data);
	gp->init = 0;

	return 0;
}


int bpix_set(struct bpix *gp, int x, int y, cval r, cval g, cval b)
{
	if (gp->init != 0x696E6974) {
		gp->error = BPIX_ERR_UNINITIALIZED;
		return 1;
	}

	if (x < gp->w && x > -1 && y < gp->h && y > -1) {
		int offset = gp->stride * y + (x << 2);

		/* data[offset + 3] unused */
		gp->data[offset + 2] = r; 
		gp->data[offset + 1] = g; 
		gp->data[offset]     = b; 
		return 0;
	}

	gp->error = BPIX_ERR_OUTSIDE;
	return 1;
}


int bpix_get(struct bpix *gp, int x, int y, cval *r, cval *g, cval *b)
{
	if (gp->init != 0x696E6974) {
		gp->error = BPIX_ERR_UNINITIALIZED;
		return 1;
	}

	if (x < gp->w && x > -1 && y < gp->h && y > -1) {
		unsigned int offset = gp->stride * y + (x << 2);

		*r = gp->data[offset + 2]; 
		*g = gp->data[offset + 1]; 
		*b = gp->data[offset]; 
		return 0;
	}

	gp->error = BPIX_ERR_OUTSIDE;
	return 1;
}
