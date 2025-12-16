#include "funcs.h"

int read (FILE *in, int **mass, size_t *n) {
	size_t capacity = 0;
    int value, res;
    (*mass) = NULL;
    (*n) = 0;
    if(in==NULL)
		return 0;
    
    while ((res = fscanf(in, "%d", &value)) == 1) {
        if (*n >= capacity) {
            size_t new_cap = (capacity == 0) ? 2 : capacity * 2;
            int *new_mass = (int*)realloc(*mass, new_cap * sizeof(int));
            if (new_mass == NULL) {
                free(*mass);
                *mass = NULL;
                return -3;
            }
            *mass = new_mass;
            capacity = new_cap;
        }
        (*mass)[*n] = value;
        (*n)++;
    }
	if(!feof(in)) {
        free(*mass);
        *mass = NULL;
		return -1;
    }
	if(*n==0)
		return -2;
    if (capacity > *n) {
        int *optimized_mass = (int*)realloc(*mass, *n * sizeof(int));
        if (optimized_mass != NULL) {
            *mass = optimized_mass;
        }
        // Если realloc вернул NULL, продолжаем использовать существующий массив
    }
	return 1;
}