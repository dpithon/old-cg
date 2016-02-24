#include <assert.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include "pixmap.h"


struct bpix {
	int w, h;    /* width and height of pixmap                      */
	int stride;  /* row size in bytes, round to upper multiple of 4 */
	int sz;	     /* size in bytes 				        */
	cval *data;  /* pointer to pixmap buffer		        */
};


int bpix_init(struct bpix *bp, int w, int h)
{
	assert(sizeof(int) == 4);

	if (w < 0 || h < 0 || w > BPIX_MAX_W || h > BPIX_MAX_H) {
		return 1;
	}

	bp->w = w;
	bp->h = h;
	bp->stride = w << 2;
	bp->sz = bp->stride * h;

	bp->data = calloc(bp->sz >> 2, 4);
	if (! bp->data) {
		return 1;
	}

	return 0;
}


/**
 * bpix_cleanup: release memory buffer and reset structure.
 */
int bpix_cleanup(struct bpix *bp)
{
	free(bp->data);
	return 0;
}


int bpix_set(struct bpix *bp, int x, int y, cval r, cval g, cval b)
{
	int offset = bp->stride * y + (x << 2);

	/* data[offset + 3] unused */
	bp->data[offset + 2] = r; 
	bp->data[offset + 1] = g; 
	bp->data[offset]     = b; 
	return 0;
}


int bpix_get(struct bpix *bp, int x, int y, cval *r, cval *g, cval *b)
{
	unsigned int offset = bp->stride * y + (x << 2);

	*r = bp->data[offset + 2]; 
	*g = bp->data[offset + 1]; 
	*b = bp->data[offset]; 
	return 0;
}


int bpix_pnm_write_to_file(struct bpix *bp, const char *fname)
{
	int fd, i, j, err = 0, int_sz;
	size_t sz;
	char header[256]; 
	cval *buffer = 0;

	if ((fd = creat(fname, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH)) < 0) {
		return 1;
	}

	sz = sprintf(header, "P6\n# Created by bpix-pnm\n%d %d\n255\n", 
		bp->w, bp->h);

	if (write(fd, header, sz) < 0) {
		goto on_error_exit;
	}

	sz = bp->w * bp->h * 3;
	if ((buffer = malloc(sz)) == 0) {
		goto on_error_exit;
	}

	int_sz = bp->sz >> 2;
	for (i = j = 0; i < int_sz; i++) {
		buffer[j++] = bp->data[(i << 2) + 2];
		buffer[j++] = bp->data[(i << 2) + 1];
		buffer[j++] = bp->data[(i << 2)];
	}

	i = 0; /* i: buffer[] index */
	while (sz > 0) {
		/* j: amount of data to write */
		j = sz > SIZE_MAX ? SIZE_MAX : sz; 
		if (write(fd, &buffer[i], j) < 0) {
			goto on_error_exit;
		}
		i  += j;
		sz -= j;
	}
	goto no_error_exit;

on_error_exit:
	err = 1;
	unlink(fname);

no_error_exit:
	close(fd);
	if (buffer) {
		free(buffer);
	}

	return err;
}
