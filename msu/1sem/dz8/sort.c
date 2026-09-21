#include "funcs.h"

int compare(const  void* a, const void *b){
	return *(int *)a-*(int *)b;
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void sort(int *mass, size_t n, int (*compare)(const void *, const void *)){
    for (size_t i = 0; i < n - 1; i++){
        for (size_t j = i; j < n; j++){
            if (compare(&mass[i], &mass[j])>0){
                swap(&mass[i], &mass[j]);
            }
        }
    }
}
