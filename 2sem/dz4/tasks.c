#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcs.h"

void print_matrix(int** matrix, int* row_sizes, int rows) {
    int i, j;
    printf("Matrix (%d rows):\n", rows);
    for (i = 0; i < rows; ++i) {
        printf("Row %d [%d]: ", i, row_sizes[i]);
        for (j = 0; j < row_sizes[i]; ++j) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int comp_cols(int** matrix, int* row_sizes, int rows, int j1, int j2) {
    int i;
    int has_positive = 0;
    int has_negative = 0;

    if (j1 == j2) return 0;

    for (i = 0; i < rows; ++i) {
        if (j1 >= row_sizes[i] || j2 >= row_sizes[i]) continue;
        int diff = matrix[i][j1] - matrix[i][j2];
        if (diff > 0) has_positive = 1;
        if (diff < 0) has_negative = 1;
        if (has_positive && has_negative) return 1;
    }

    return (has_positive && has_negative);
}

void delete_column(int** mat, int* row_sizes, int rows, int col) {
    int i, j;
    for (i = 0; i < rows; ++i) {
        if (col < row_sizes[i]) {
            for (j = col; j < row_sizes[i] - 1; ++j) {
                mat[i][j] = mat[i][j + 1];
            }
            row_sizes[i]--;
        }
    }
}

void task(int*** matrix, int* rows, int** row_sizes) {
    int r = *rows;
    int* sizes = *row_sizes;
    int** mat = *matrix;
    int cols = 0;
    int i, j, k;

    if (r == 0) return;

    for (i = 0; i < r; ++i)
        if (sizes[i] > cols) cols = sizes[i];
    if (cols == 0) return;

    j = 0;
    while (j < cols) {
        int found = 0;
        for (k = j + 1; k < cols; ++k) {
            if (comp_cols(mat, sizes, r, j, k)) {
                delete_column(mat, sizes, r, j);
                if (k > j) {
                    delete_column(mat, sizes, r, k - 1);
                } else {
                    delete_column(mat, sizes, r, k);
                }
                cols = 0;
                for (i = 0; i < r; ++i)
                    if (sizes[i] > cols) cols = sizes[i];
                found = 1;
                break;
            }
        }
        if (!found) {
            j++;
        }
    }
}