#include "funcs.h"
#include <time.h>



int main(void) {
    int a[] = {1, 0, 2, 4, 8, 2, 1, 4}, M = 2, N = 0;
    size_t n = sizeof(a) / sizeof(int);
    puts("Begin");
    pr(a, n);
    puts("Answer");
    n = task(a, n, M, N);
    pr(a, n);
    return 0;
}