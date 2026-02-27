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
    int cur, max = 0, count = 0;
    *res = 0;
    if (in == NULL) {
        return 0;
    }
    while (fscanf(in, "%d", &cur) == 1) {
        count = count + 1;
        (*res) += cur;
        if (cur > max) {
            max = cur;
        }
        if (cur != max) {
            (*res) -= max;
            return 3;
        }
    }
    if (!feof(in)) return 2;
    if(count == 0) return 1;
    return 3;
}
