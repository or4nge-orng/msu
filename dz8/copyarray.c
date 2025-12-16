#include "funcs.h"

void copy_array(int *mass1, int **mass2, size_t n){
    *mass2 = (int *)malloc(n * sizeof(int));
    for (size_t i = 0; i < n; i++){
        (*mass2)[i] = mass1[i];
    }
}