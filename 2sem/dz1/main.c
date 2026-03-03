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
    switch (read(file, &matrix, &rows, &cols))
    {
    case 1:
        perror("File error");
        return 0;
    case 2:
        perror("Size reading error");
        return 0;
    case 3:
        fprintf(stderr, "Invalid matrix size: %d x %d\n", rows, cols);
        return 0;
    case 4:
        perror("Memory allocation error");
        return 0;
    case 5:
        perror("Element reading error");
        return 0;
    case 6:
        perror("Extra element");
        return 0;
    case 7:
        perror("File reading error");
        return 0;
    default:
        task(matrix, rows, &cols);
        break;
    }
        

    if (matrix == NULL) {
        printf("Matrix is NULL\n");
        fclose(file);
        return 1;
    }

    pr(matrix, rows, cols);

    free(matrix);

    fclose(file);
    return 0;
}
