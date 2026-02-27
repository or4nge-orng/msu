#include "funcs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int read(FILE* file, int*** matrix, int* rows, int* cols) {
    if (file == NULL) {
        perror("File error");
        return 1;
    }
    if (fscanf(file, "%d %d", rows, cols) != 2) {
        perror("Size reading error");
        return 1;
    }
    if (*rows <= 0 || *cols <= 0) {
        fprintf(stderr, "Invalid matrix size: %d x %d\n", *rows, *cols);
        return 1;
    }
    size_t ptr_size = (size_t)(*cols) * sizeof(int*);
    size_t data_size = (size_t)(*rows) * (*cols) * sizeof(int);
    *matrix = (int**)malloc(ptr_size + data_size);
    if (*matrix == NULL) {
        perror("Memory allocation error");
        return 1;
    }
    int* data = (int*)((char*)(*matrix) + ptr_size);
    for (int i = 0; i < *cols; ++i) {
        (*matrix)[i] = data + i * (*rows);
    }
    for (int i = 0; i < *rows; ++i) {
        for (int j = 0; j < *cols; ++j) {
            int value;
            if (fscanf(file, "%d", &value) != 1) {
                fprintf(stderr, "Element [%d][%d] reading error\n", i, j);
                free(*matrix);
                return 1;
            }
            (*matrix)[j][i] = value;
        }
    }
    return 0;
}

void pr(int** matrix, int rows, int cols) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            printf("%d ", matrix[j][i]); 
        }
        printf("\n");
    }
    printf("\n");
}

int isComparable(const int* col1, const int* col2, int rows) {
    int pos = 0, neg = 0, diff;
    for (int i = 0; i < rows; ++i) {
        diff = col1[i] - col2[i];
        if (diff < 0) {
            neg++;
        } else if (diff > 0) {
            pos++;
        }
    }
    return pos && neg;
}

void task(int** matrix, int rows, int* cols) {
    for (int i = 0; i < *cols; ++i) {
        for (int j = i + 1; j < *cols; ++j) {
            if (isComparable(matrix[i], matrix[j], rows)) {
                for (int k = j; k < *cols - 1; ++k) {
                    matrix[k] = matrix[k + 1];
                }
                (*cols)--;
                j--;
            }
        }
    }
}
