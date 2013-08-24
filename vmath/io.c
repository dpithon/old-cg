#include <stdio.h>
#include "core.h"
#include "mstack.h"
#include "io.h"

static int dump_mm(char*, int, int*, const void*, size_t, char);

void printc(const char *fmt, coord_st *c)
{
	static char val[30];

	sprintf(val, "%5.2f %5.2f %5.2f %5.2f", c->x, c->y, c->z, c->w);
	if (fmt) {
		printf(fmt, val);
	} else {
		printf("%s", val);
	}
}


void printm(const char *fmt, matrix_st *m)
{
	int i;
	for (i = 0; i < 4; i++) {
		printc(fmt, (coord_st*) m->cell[i]);
		if (! fmt) {
			printf("\n");
		}
	}
}


void prints(const char *fmt, mstack_st *s)
{
	int i = s->i;
	while (i >= 0) {
		printm(fmt, &(s->m[i--]));
		printf("\n");
	}

	printf("-------------------------------------\n");
}


#ifdef COUNTERS
void print_counters(counter_st *cnt)
{
	unsigned long *ul = (unsigned long*) cnt;

	for (int i = 0; counter_name[i]; i++) {
		printf("%6ld ..... %s\n", ul[i], counter_name[i]);
	}
}
#endif /* COUNTERS */



/**
 * dump_coord: convert coordinates (4 float values) in hex string
 *
 * Values are separated with space.
 *
 * buf: pointer to buffer
 * of : pointer to start offset in buffer
 * sz : buffer size
 * z  : final char to output into buffer
 * c  : coordinates to process
 * 
 * Returns: 
 *   0: ok
 *   1: buffer overflow (of > sz)
 *
 */
int dump_coord(char *buf, int sz, int *of, char z, const coord_st *c)
{
	float *f = (float*) c;

	for (int i = 0; i < 4; i++) {
		if (dump_mm(buf, sz, of, &f[i], sizeof *f, (i == 3)? z: ' ')) {
			return 1;
		}
	}

	return 0;
}


int dump_matrix(char *buf, int sz, int *of, const matrix_st *m)
{
	for (int i = 0; i < 4;  i++) {
		if (dump_coord(buf, sz, of, '\n', (coord_st*) &(m->cell[i]))) {
			return 1;
		}
	}

	return 0;
}


int dump_stack(char *buf, int sz, int *of, const mstack_st *s)
{
	dump_mm(buf, sz, of, &(s->i), sizeof s->i, '\n');
	for (int i = s->i; i >= 0; i--) {
		if (dump_matrix(buf, sz, of, &(s->m[i]))) {
			return 1;
		}
	}

	return 0;
}


#if __BYTE_ORDER__ != __ORDER_LITTLE_ENDIAN__
#error "Unsupported byte order."
#endif

static int dump_mm(char *buf, int bsz, int *of, const void *mm, size_t sz, 
		    char z)
{
	static char hexa[] = { 
		'0', '1', '2', '3',
		'4', '5', '6', '7',
		'8', '9', 'A', 'B',
		'C', 'D', 'E', 'F'
	};
	const unsigned char *uc = (const unsigned char*) mm;
	unsigned char b;

	for (size_t i = 0; i < sz; i++) {
		if (bsz - *of < 3) {
			return 1;
		}

		b = uc[sz - 1 - i];
		buf[(*of)++] = hexa[b >> 4];
		buf[(*of)++] = hexa[b & 0x0F];
	}

	buf[(*of)++] = z;
	return 0;
}
