#include <stdio.h>
#include "core.h"
#include "mstack.h"
#include "mstack_private.h"
#include "io.h"

static int dump_mm(char*, int, int*, const void*, int, char);
static int load_mm(const char*, int, int*, void*, int);

#if __BYTE_ORDER__ != __ORDER_LITTLE_ENDIAN__
#error "Unsupported byte order."
#endif


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
 * sz : buffer size
 * of : pointer to start offset in buffer
 * z  : final char to output into buffer
 * c  : pointer to coordinates
 * 
 * Returns: 
 *   0: ok
 *   1: buffer overflow
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


/**
 * dump_matrix: convert matrix (16 float values) in hex string
 *
 * buf: pointer to buffer
 * sz : buffer size
 * of : pointer to start offset in buffer
 * m  : pointer to matrix
 * 
 * Returns: 
 *   0: ok
 *   1: buffer overflow
 *
 */
int dump_matrix(char *buf, int sz, int *of, const matrix_st *m)
{
	for (int i = 0; i < 4;  i++) {
		if (dump_coord(buf, sz, of, '\n', (coord_st*) &(m->cell[i]))) {
			return 1;
		}
	}

	return 0;
}


/**
 * dump_stack: convert stack in hex string
 *
 * buf: pointer to buffer (0 means main matrix stack)
 * sz : buffer size
 * of : pointer to start offset in buffer
 * s  : pointer to stack
 * 
 * Returns: 
 *   0: ok
 *   1: buffer overflow
 *
 */
int dump_stack(char *buf, int sz, int *of, const mstack_st *s)
{
	if (! s) {
		s = (const mstack_st*) &mstack;
	}

	dump_mm(buf, sz, of, &(s->i), sizeof s->i, '\n');
	for (int i = s->i; i >= 0; i--) {
		if (dump_matrix(buf, sz, of, &(s->m[i]))) {
			return 1;
		}
	}

	return 0;
}


int load_coord(coord_st *c, const char *buf, int sz, int *of)
{
	float *f = (float*) c;

	for (int i = 0; i < 4; i++) {
		if (load_mm(buf, sz, of, &f[i], sizeof *f)) {
			return 1;
		}
		(*of)++;
	}

	return 0;
}


int load_matrix(matrix_st *m, const char *buf, int sz, int *of)
{
	for (int i = 0; i < 4;  i++) {
		if (load_coord((coord_st*) &(m->cell[i]), buf, sz, of)) {
			return 1;
		}
	}

	return 0;
}


int load_stack(mstack_st* s, const char *buf, int sz, int *of)
{
	if (! s) {
		s = (mstack_st*) &mstack;
	}

	load_mm(buf, sz, of, &(s->i), sizeof s->i);
	(*of) ++;
	for (int i = s->i; i >= 0; i--) {
		if (load_matrix(&(s->m[i]), buf, sz, of)) {
			return 1;
		}
	}

	return 0;
}


/**
 * dump_mm: dump memory area to hex codes
 *
 * buf: pointer to buffer
 * bsz: buffer size
 * of : pointer to start offset in buffer
 * mm : pointer to first byte of memory area
 * sz : size of memory area (in bytes)
 * z  : final char to output into buffer
 * 
 * Returns: 
 *   0: ok
 *   1: buffer overflow
 *
 */

int dump_mm(char *buf, int bsz, int *of, const void *mm, int sz, char z)
{
	static char hexa[] = { 
		'0', '1', '2', '3', '4', '5', '6', '7',
		'8', '9', 'A', 'B', 'C', 'D', 'E', 'F'
	};
	const unsigned char *uc = (const unsigned char*) mm;
	unsigned char b;

	for (int i = 0; i < sz; i++) {
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


static unsigned char decode_hex(char c)
{
	if (c >= '0' && c <= '9')
		return c - '0';
	else if (c >= 'A' && c <= 'F')
		return 10 + (c - 'A');
	else
		return 16;
}


/**
 * load_mm: decode hex codes to memory
 *
 * buf: pointer to buffer
 * bsz: buffer size
 * of : pointer to start offset in buffer
 * mm : pointer to first byte of memory area
 * sz : size of memory area to feed (in bytes)
 * 
 * Returns: 
 *   0: ok
 *   1: buffer overflow
 *   2: not an hex character
 *
 */
int load_mm(const char *buf, int bsz, int *of, void *mm, int sz)
{
	unsigned char *uc = (unsigned char*) mm;
	unsigned char hi, lo;

	for (int i = sz - 1; i >= 0; i--) {
		if (bsz - *of < 2) {
			return 1;
		}

		// decode two HEX characters in a byte
		hi = decode_hex(buf[(*of)++]);
		lo = decode_hex(buf[(*of)++]);
		if (hi > 15 || lo > 15)
			return 2;

		uc[i]  = hi << 4;
		uc[i] += lo;
	}

	return 0;
}
