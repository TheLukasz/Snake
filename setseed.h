#include <stdio.h>
#include <stdlib.h>

void setseed(){
	u_int32_t seed = 0;
	FILE *devrnd = fopen("/dev/random","r");
	fread(&seed, 4, 1, devrnd);
	fclose(devrnd);
	srand(seed);
}
