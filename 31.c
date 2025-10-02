#include <stdio.h>

int task(FILE *, int *);
int main(void) {
    FILE *in = fopen("1.txt", "r");
    int res, err = task(in, &res);
    if (err == 0) {
        printf("File didn't open\n");
        return -1;
    }
    if (err == 1) {
        printf("File is empty\n");
    }
    if (err == 2) {
        printf("File is bad\n");
    }
    if (err == 3) {
        printf("Result = %d\n", res);
    }
    if (in) fclose(in);
    return 0;
}
int task(FILE *in, int *res) {
    int cur, prev_sum = 0, count = 0;
    if (in == NULL) {
        return 0;
    }
    while (fscanf(in, "%d", &cur) == 1) {
        if (count == 0) {
            *res = cur;
        } 
        prev_sum = (cur < prev_sum + cur) ? cur : prev_sum + cur;
        *res = (prev_sum < *res) ? prev_sum : *res;
        count++;
    }
    if (!feof(in)) return 2;
    if(count == 0) return 1;
    return 3;
}
