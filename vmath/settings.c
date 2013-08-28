#include "settings.h"

float vmset_eps   = 0.001F;
int   vmset_width = 5;
int   vmset_prec  = 2;
char  vmset_start_char = 0;

#define CAST_INT long

int vmath_set(int set, void *val)
{
        switch (set) {
        case VMSET_EPSILON:
                vmset_eps = (float) ((CAST_INT) val);
                break;

        case VMSET_IO_WIDTH:
                vmset_width = (CAST_INT) val;
                break;

        case VMSET_IO_PREC:
                vmset_prec = (CAST_INT) val;
                break;

        case VMSET_IO_START_CHAR:
                vmset_start_char = (CAST_INT) val;
                break;

        default:
                return 1;
        }
                
        return 0;
}


int vmath_get(int set, void *val)
{
        switch (set) {
        case VMSET_EPSILON:
                *((float*) val) = vmset_eps;
                break;

        case VMSET_IO_WIDTH:
                *((int*) val) = vmset_width;
                break;

        case VMSET_IO_PREC:
                *((int*) val) = vmset_prec;
                break;

        case VMSET_IO_START_CHAR:
                *((char*) val) = vmset_start_char;
                break;

        default:
                return 1;
        }
                
        return 0;
}
