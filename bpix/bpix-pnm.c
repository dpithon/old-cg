#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

#include "bpix-pnm.h"
#include "bpix-error.h"

int bpix_pnm_write_to_file(struct bpix *bp, const char *fname)
{
	int fd, i, j, err = 0, int_sz;
	size_t sz;
	char header[256]; 
	cval *buffer = 0;

	assert(bp->init == 0x696E6974);

	if ((fd = creat(fname, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH)) < 0) {
		bp->errno = BPIX_ERR_IO;
		return 1;
	}

	sz = sprintf(header, "P6\n# Created by bpix-pnm\n%d %d\n255\n", 
		bp->w, bp->h);

	if (write(fd, header, sz) < 0) {
		bp->errno = BPIX_ERR_IO;
		goto on_error_exit;
	}

	sz = bp->w * bp->h * 3;
	if ((buffer = malloc(sz)) == 0) {
		bp->errno = BPIX_ERR_MALLOC;
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
			bp->errno = BPIX_ERR_IO;
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
