#include <stdio.h>
#include <stdlib.h>
#include "funcs.h"

int main(void) {
    FILE *file = fopen("1.txt", "r");
    if (!file) {
        perror("Cannot open file");
        return 1;
    }

    int **matrix = NULL;
    int rows = 0, cols = 0;
;
    if (read(file, &matrix, &rows, &cols) != 0) {
        printf("Read failed\n");
        fclose(file);
        return 1;
    }

    if (matrix == NULL) {
        printf("Matrix is NULL\n");
        fclose(file);
        return 1;
    }

    pr(matrix, rows, cols);

    task(matrix, rows, &cols);

    pr(matrix, rows, cols);

    free(matrix);

    fclose(file);
    return 0;
}
