#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcs.h"

void print_matrix(int** matrix, int* row_sizes, int rows) {
    printf("Matrix (%d rows):\n", rows);
    for (int i = 0; i < rows; ++i) {
        printf("Row %d [%d]: ", i, row_sizes[i]);
        for (int j = 0; j < row_sizes[i]; ++j) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int comp_cols(int** matrix, int* row_sizes, int rows, int j1, int j2) {
    if (j1 == j2) return 0; // Один и тот же столбец

    int has_positive = 0; // Есть ли разность > 0
    int has_negative = 0; // Есть ли разность < 0

    for (int i = 0; i < rows; ++i) {
        // Пропускаем строки, где один из столбцов отсутствует
        if (j1 >= row_sizes[i] || j2 >= row_sizes[i]) continue;

        int diff = matrix[i][j1] - matrix[i][j2];
        if (diff > 0) has_positive = 1;
        if (diff < 0) has_negative = 1;

        // Если найдены и положительная, и отрицательная разности — столбцы несравнимы
        if (has_positive && has_negative) return 1;
    }

    return (has_positive && has_negative);
}

void delete_column(int** mat, int* row_sizes, int rows, int col) {
    for (int i = 0; i < rows; ++i) {
        if (col < row_sizes[i]) {
            // Сдвигаем элементы влево
            for (int j = col; j < row_sizes[i] - 1; ++j) {
                mat[i][j] = mat[i][j + 1];
            }
            row_sizes[i]--; // Уменьшаем размер строки
        }
    }
}


void task(int*** matrix, int* rows, int** row_sizes) {
    if (*rows == 0) return;
    int r = *rows;
    int* sizes = *row_sizes;
    int** mat = *matrix;

    // Определение текущего количества столбцов (максимальная длина строки)
    int cols = 0;
    for (int i = 0; i < r; ++i)
        if (sizes[i] > cols) cols = sizes[i];
    if (cols == 0) return;

    int j = 0;
    while (j < cols) {
        int found = 0;
        // Поиск столбца k > j, несравнимого с j
        for (int k = j + 1; k < cols; ++k) {
            if (comp_cols(mat, sizes, r, j, k)) {
                // Удаляем оба столбца: сначала j, затем k (после j индекс k уменьшается)
                delete_column(mat, sizes, r, j);
                if (k > j) {
                    delete_column(mat, sizes, r, k - 1);
                } else {
                    delete_column(mat, sizes, r, k);
                }
                // Пересчет максимального количества столбцов
                cols = 0;
                for (int i = 0; i < r; ++i)
                    if (sizes[i] > cols) cols = sizes[i];
                found = 1;
                break;
            }
        }
        if (!found) {
            // Переход к следующему столбцу
            j++;
        }
    }
}