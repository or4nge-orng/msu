#include "funcs.h"
#include <time.h>



int main(void) {
    size_t n = 6;
    int *mass1 = NULL, *mass2 = NULL;
    clock_t t1, t2;
    generate_array(&mass1, n);
    copy_array(mass1, &mass2, n);
    puts("Begin");
    pr(mass1, n);
    puts("Answer");
    t1 = clock();
    sort(mass1, n, compare);
    t2 = clock();
    pr(mass1, n);
    printf("My sort time: %f\n", (double)(t2 - t1));
    t1 = clock();
    qsort(mass2, n, sizeof(int), compare);
    t2 = clock();
    pr(mass2, n);
    printf("Qsort time: %f\n", (double)(t2 - t1));
    free(mass1); free(mass2);
    return 0;
}