#include "funcs.h"

void pr (int a[], size_t n) {
    for(size_t i = 0; i < n; i++) {
        printf("%d ",a[i]);
    }
    printf("\n");
}

int task (FILE *in, int **res, size_t *L, char *found, int N) {
    int value;
    size_t i = 0;
    (*L) = 0;
    
    if(in==NULL)
		return 0;
    (*res) = (int*)malloc(N*sizeof(int));

    while (fscanf(in, "%d", &value) == 1) {
        i = *L % N;
        
        (*res)[i] = value;
        (*L)++;
        if (*L >= N) {
            if (check_window(*res, N)) {
                *found = 1;
                return 1;
            }
        }
        
    }
    if (*L < N) {
        if (check_window(*res, *L)) {
            *found = 1;
            return 1;
        }
    }
	if(!feof(in)) {
        free(*res);
        *res = NULL;
		return -1;
    }
	if(*L==0) {
        free(*res);
		return -2;
    }
	return 1;
}

char check_window (int mass[], size_t N) {
    int a = mass[0], b = 0, count_a = 0, count_b = 0;
    for (size_t i = 0; i < N; i++) {
        if (mass[i] == a) count_a++;
        else if (count_b == 0){
            b = mass[i];
            count_b++;
        } else if (mass[i] == b) count_b++;
        else return 0;
    }
    if (count_b == 0) return 0;
    return (count_a == 1 || count_b == 1);
}
