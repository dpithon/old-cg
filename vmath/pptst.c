#include <stdio.h>
#include "vmath.h"
#include "pprint.h"

#define PI 3.141592654F

int main()
{
	matrix_st ri, rj, rk;

	stack_push( rotationx(&ri, - (PI / 2.F)) );
	stack_push( rotationy(&rj, - (PI / 2.F)) );

	printm(NULL, stack_peek());
	
	printf("\n");
	printm(NULL, rotationz(&rk, PI / 2.F));

	return 0;
}


