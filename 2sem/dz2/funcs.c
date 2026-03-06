#include "funcs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int read(FILE* file, int*** matrix, int* rows, int* cols, int* N) {
    int value, n = 0;
    if (file == NULL) {
        return 1;
    }
    if (fscanf(file, "%d %d %d", N, rows, cols) != 3) {
        return 2;
    }
    if (*rows <= 0 || *cols <= 0) {
        return 3;
    }
    size_t ptr_size = (size_t)(*cols) * sizeof(int*);
    size_t data_size = (size_t)(*rows) * (*cols) * sizeof(int);
    *matrix = (int**)malloc(ptr_size + data_size);
    if (*matrix == NULL) {
        return 4;
    }
    int* data = (int*)((char*)(*matrix) + ptr_size);
    for (int i = 0; i < *cols; ++i) {
        (*matrix)[i] = data + i * (*rows);
    }
    for (int i = 0; i < *rows; ++i) {
        for (int j = 0; j < *cols; ++j) {
            
            if (fscanf(file, "%d", &value) != 1) {
                free(*matrix);
                matrix = NULL;
                return 5;
            }
            (*matrix)[j][i] = value;
            n++;
        }
    }
    while(fscanf(file, "%d", &value) == 1) n++;
    if (!feof(file)) {
        free(*matrix);
        matrix = NULL;
        return 7;
    }
    if (n > (*rows * *cols)) {
        free(*matrix);
        matrix = NULL;
        return 6;
    }
    return 0;
}

void pr(int** matrix, int rows, int cols) {
    if (rows <= 0 || cols <= 0) {
        printf("Empty matrix\n\n");
        return;
    }

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (matrix[j] == NULL) {
                printf("NULL ");
            } else {
                printf("%d ", matrix[j][i]);
            }
        }
        printf("\n");
    }
    printf("\n");
}

int getColSum(const int* col, int rows) {
    int sum = 0;
    for (int i = 0; i < rows; ++i) {
        sum += col[i];
    }
    return sum;
}

void task(int** matrix, int rows, int* cols, int N) {
    int ind[*cols], n_ind = 0, max_sum = getColSum(matrix[0], rows), sum = 0,
    left, right, r, l;
    
    for (int i = 0; i < *cols; i++) {
        sum = getColSum(matrix[i], rows);
        if(sum > max_sum){
            max_sum = sum;
        }
    }
    printf("%d\n", max_sum);
    for (int i = 0; i < *cols; i++) {
        if (getColSum(matrix[i], rows) == max_sum) ind[n_ind++] = i;
    }
    for (int i = 0; i < n_ind; i++) {
        printf("%d ", ind[i]);
    }
    printf("\n\n");
    for(right = 0, left = 0; right < n_ind; right++){
        printf("%d %d\n", ind[right], ind[right+1]);
        if(ind[right] - ind[right+1] == -1) {
            
            continue;
        }
        else {
            printf("here\n");
            if ((right - left + 1) > N) {
                printf("reverse\n");
                for (l = left, r = right; l <= r; l++, r--) {
                    int *tmp = matrix[ind[r]]; matrix[ind[r]] = matrix[ind[l]]; matrix[ind[l]] = tmp;
                }
            }
            left = right + 1;
        }
    }
    
    printf("\n\n");
}