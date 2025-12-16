#include "funcs.h"
#include <stdlib.h>
#include <time.h>

void generate_array(int **mass, size_t n) {
	srand(time(NULL));
    *mass=(int *)malloc(sizeof(int)*n);
	for(size_t i=0;i<n;i++) 
		(*mass)[i]=rand()%10;
}