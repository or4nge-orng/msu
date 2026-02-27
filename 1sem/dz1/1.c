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
    int cur, abs_num, abs_sum = 0, abs_squared = 0, count = 0;
    if (in == NULL) {
        return 0;
    }
    while (fscanf(in, "%d", &cur) == 1) {
        count++;
        abs_num = cur > 0 ? cur : -cur;
        abs_sum += abs_num;
        abs_squared += abs_num * abs_num;
    }
    if (!feof(in)) return 2;
    if(count == 0) return 1;
    *res = (abs_sum * abs_sum - abs_squared) / 2;
    return 3;
}
