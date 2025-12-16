#include "funcs.h"

void pr (int a[], size_t n) {
    for(size_t i = 0; i < n; i++) {
        printf("%d ",a[i]);
    }
    printf("\n");
}

size_t task(int a[], size_t n, int M, int N){
    int min_el;
    char first_min = 1;
    size_t group_start,
           group_end, 
           a_id = 0, 
           i_id = 0, 
           I_n = 0, 
           *I = (size_t*)malloc(n*sizeof(size_t));

    if (!I) return n;
    for (size_t i = 0; i < n; i++){
        if (a[i] % M == N) {
            I[I_n++] = i;
            if (first_min) {
                min_el = a[i];
                first_min = 0;
            } else if (a[i] < min_el) {
                min_el = a[i];
            }
        }
    }
    if (I_n == 0) {
        free(I);
        return n;
    }
    for (size_t j = 0; j < n; j++) {
        printf("j=%zu a_id=%zu i_id=%zu, n=%zu\n", j, a_id, i_id, n);
        if (i_id < I_n && j == I[i_id]) {
            if (i_id + 1 < I_n && j + 1 == I[i_id + 1]) {
                a[a_id++] = min_el;
                i_id += 2;
                j++;
            } else {
                a[a_id++] = a[j];
                i_id++;
            }
        } else {
            a[a_id++] = a[j];
        }
    }
    
    free(I);
    return a_id;
}
