#include <stdio.h>
#include <stdlib.h>
#include "funcs.h"

int main (void) {
    FILE *file = fopen("1.txt", "r");
    int **matrix = NULL, rows = 0, cols = 0;
    if (read(file, &matrix, &rows, &cols) != 0) {
        fclose(file);
        return 1;
    }

    task(matrix, rows, &cols);

    pr(matrix, rows, cols);

    free(matrix); 

    fclose(file);
    return 0;
}
