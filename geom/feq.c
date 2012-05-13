#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	float v1 = atof(argv[1]);
	float v2 = atof(argv[2]);

	printf("%3.2f\n%3.2f\n", v1, v2);

	if (v1 == v2)
		printf("values are equal\n");
	else
		printf("values are not equal\n");

	return 0;
}
