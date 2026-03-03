#include "funcs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int read(FILE* file, int*** matrix, int* rows, int* cols) {
    if (file == NULL) {
        return 1;
    }
    if (fscanf(file, "%d %d", rows, cols) != 2) {
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
            int value;
            if (fscanf(file, "%d", &value) != 1) {
                free(*matrix);
                return 5;
            }
            (*matrix)[j][i] = value;
        }
    }
    int extra;
    if (fscanf(file, "%d", &extra) == 1) {
            free(*matrix);
            return 6;
        }
    if (!feof(file)) {
        free(*matrix);
        return 7;
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

int isComparable(const int* col1, const int* col2, int rows) {
    if (col1 == NULL || col2 == NULL) {
    return 0;
}
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
    if (matrix == NULL || cols == NULL || *cols <= 0 || rows <= 0) {
        return;
    }

    int right, left, n = *cols;

    for (int i = 0; i < n; i++) {
        for (right = i+1, left = i+1; right < n; right++) {
            if (!isComparable(matrix[right], matrix[i], rows)) {
                int *tmp = matrix[right];
                matrix[right] = matrix[left];
                matrix[left++] = tmp;
            }  
        }
        n = left;
        for (int j = n; j < *cols; j++) {
            if (isComparable(matrix[i], matrix[j], rows)) {
                matrix[i] = NULL; break;
            }
        }
    }
    for(left = 0, right = 0; right < n; right++) //2 бегунка, удаляем помеченные элементы
		if(matrix[right]) matrix[left++] = matrix[right];
	n = left;
    *cols = n;
}