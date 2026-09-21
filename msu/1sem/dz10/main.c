#include <stdio.h>
#include <stdlib.h>
#include "funcs.h"

#define N 5


int main(void) {
    FILE *in = fopen("1.txt", "r");
    char found;
    size_t n;
    int *res = NULL, err = task(in, &res, &n, &found, N);
    if (err) fclose(in);
    switch(err){
        case 0:	printf("No file\n");break;
        case -1:printf("Bad file\n");break;
        case -2: printf("Empty file\n");break;
        case -3: printf("Bad size\n");break;
        default:
            puts("Answer");
            if (found) {
                if (n > N) {
                    for (size_t i = 0; i < (size_t)N; i++) {
                        // printf("%zu: ", (n+i)%N);
                        printf("%d ", res[(n+i)%N]);
                    }
                    printf("\n");
                } else {
                    for (size_t i = 0; i < n; i++) {
                        printf("%d ", res[i]);
                    }
                    printf("\n");
                }
            }  else {
                puts("No such segment");
            }
            free(res);
        }
    return 0;
}