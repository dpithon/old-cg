#include <stdio.h>
#include <string.h>
#include <math.h>
#include "gpix/gpix.h"

#define L  	 1
#define ALPHA	90
#define W 6400
#define H 6400

static char s1[40000000] = "FX";
static char s2[40000000];
static char *from = s1, *to = s2;

static const char *ruleX = "X+YF";
static const char *ruleY = "FX-Y";

int main()
{
	int n = 21, i, j, vcos, vsin;
	char *tmp;
	int x =	3200, y=3200, xb, yb, alpha = 0;
	struct gpix gp = GPIX_INIT;
	int rulex_sz=strlen(ruleX);
	int ruley_sz=strlen(ruleY);

	while (n-- > 0) {
		i = j = 0;
		to[0] = '\0';

		while (from[i]) {
			switch (from[i]) {
			case 'X':
				strncpy(&(to[j]), ruleX, rulex_sz);
				j += rulex_sz;
				break;
			case 'Y':
				strncpy(&(to[j]), ruleY, ruley_sz);
				j += ruley_sz;
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

	gpix_init(&gp);

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
			gpix_line(&gp, x, y, xb, yb);
			x = xb;
			y = yb;
		}

		to++;
	}
	
        if (gpix_pnm_write_to_file(&gp, "fract.pnm")) {
                return gp.error;
        }

        gpix_cleanup(&gp);
        return 0;
}
