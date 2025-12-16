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
    int cur, sum = 0, first, count = 0;
    *res = 1;
    if (in == NULL) {
        return 0;
    }
    if (fscanf(in, "%d", &cur) == 1) {
        do {
            count++;
            if (count == 1) {
                sum = cur + count;
                first = cur;
            }
            printf("%d %d %d\n",cur,count,sum);
            if (cur + count != sum) {
                *res = 0;
                return 3;
            }
        } while (fscanf(in, "%d", &cur) == 1);
    } else {
        if (feof(in)) return 1;
        else return 2;
    }
    if (first != count) *res = 0;
    if (!feof(in)) return 2;
    return 3;
}
