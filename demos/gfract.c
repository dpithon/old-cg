#include <stdio.h>
#include <string.h>
#include <math.h>
#include "bpix/bpix.h"

#define L  	 1
#define ALPHA	90
#define W 800
#define H 800

static char s1[2000000] = "F";
static char s2[2000000];
static char *from = s1, *to = s2;

static const char *rule = "F+F-F-F+F";

int main()
{
	int n = 8, i, j, vcos, vsin;
	char *tmp;
	int x = 10, y=10, xb, yb, alpha = 0;
	struct bpix gp = BPIX_INIT;
	int rule_sz=strlen(rule);

	while (n-- > 0) {
		i = j = 0;
		to[0] = '\0';

		while (from[i]) {
			switch (from[i]) {
			case 'F':
				strncpy(&(to[j]), rule, rule_sz);
				j += rule_sz;
				break;
			default:
				to[j++] = from[i];
			}

			++ i;
		}

		to[j] = 0;

		tmp = to;
		to = from;
		from = tmp;
	}

	to = from;

	gp.w = W;
	gp.h = H;

	bpix_init(&gp);

	while (*to) {
		switch (*to) {
		case '-': 
			alpha -= ALPHA; 
			break;

		case '+': 
			alpha += ALPHA; 
			break;

		case 'F':
			switch (alpha % 360) {
				case -270:
				case 90:  vcos=0;  vsin=1; break;
				case -180:
				case 180: vcos=-1; vsin=0; break;
				case -90:
				case 270: vcos=0;  vsin=-1; break;
				case 0:   vcos=1;  vsin=0; break;
			}
			xb = x + L * vcos;
			yb = y + L * vsin;
			bpix_line(&gp, x, y, xb, yb);
			x = xb;
			y = yb;
		}

		to++;
	}
	
        if (bpix_pnm_write_to_file(&gp, "fract.pnm")) {
                return gp.error;
        }

        bpix_cleanup(&gp);
        return 0;
}
