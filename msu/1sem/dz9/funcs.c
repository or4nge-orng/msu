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
    size_t j = 0, 
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

    while (a_id < n) {
        if (i_id < I_n && a_id == I[i_id]) {
            if (i_id + 1 < I_n && a_id + 1 == I[i_id + 1]) {
                a[j++] = min_el;
                a_id += 2;
                i_id += 2;
            } else {
                a[j++] = a[a_id++];
                i_id++;
            }
        } else {
            a[j++] = a[a_id++];
        }
    }
    
    free(I);
    return j;
}
