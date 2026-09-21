// 103.c — Перестановка активных столбцов по возрастанию суммы
#include <stdio.h>
#include <stdlib.h>

int read(const char *, int ***, int ***, int *, int *, int *, int *);
int main(void);
void task(int **, int **, int, int, int, int);
void all_zero(int *, int);

int main(void) {
    int **matrix;
    int **matrix2;
    int row, col;
    int N, M;
    FILE *wf;

    switch (read("data.txt", &matrix, &matrix2, &M, &N, &row, &col)) {
        case -1:
            perror("Bad file format");
            return -1;
        case -2:
            perror("Letter in file");
            return -1;
        case -3:
            perror("Found more numbers than expected");
            return -1;
        case -4:
            perror("Found fewer numbers than expected");
            return -1;
    }

    task(matrix, matrix2, M, N, row, col);

    wf = fopen("res.txt", "w");
    if (wf == NULL)
        return -1;

    fprintf(wf, "%d %d %d %d\n", M, N, row, col);
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            fprintf(wf, "%d ", matrix[i][j]);
        }
        fprintf(wf, "\n");
    }
    fclose(wf);
    free(matrix);
    return 0;
}

void task(int **matrix, int **matrix2, int M, int N, int rows, int cols) {
    int **kol = (int**)malloc(2 * sizeof(int*));
    for (int i = 0; i < 2; i++) {
        kol[i] = (int*)calloc(cols, sizeof(int));
    }

    int count = 0;

    // Шаг 1: Найти столбцы, содержащие элемент из [M, N]
    for (int j = 0; j < cols; j++) {
        for (int i = 0; i < rows; i++) {
            if (matrix2[i][j] >= M && matrix2[i][j] <= N) {
                kol[0][count] = j;
                // Считаем сумму столбца
                int sum = 0;
                for (int k = 0; k < rows; k++) {
                    sum += matrix2[k][j];
                }
                kol[1][count] = sum;
                count++;
                break;
            }
        }
    }

    // Шаг 2: Сортировка активных столбцов по сумме (пузырьком)
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - 1; j++) {
            if (kol[1][j] > kol[1][j + 1]) {
                // Обмен сумм
                int temp_sum = kol[1][j];
                kol[1][j] = kol[1][j + 1];
                kol[1][j + 1] = temp_sum;
                // Обмен индексов
                int temp_idx = kol[0][j];
                kol[0][j] = kol[0][j + 1];
                kol[0][j + 1] = temp_idx;
            }
        }
    }

    // Шаг 3: Создаём временный буфер для результата
    int **result = (int**)malloc(rows * sizeof(int*));
    int *data = (int*)malloc(rows * cols * sizeof(int));
    for (int i = 0; i < rows; i++) {
        result[i] = data + i * cols;
    }

    // Копируем исходную матрицу
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result[i][j] = matrix[i][j];
        }
    }

    // Шаг 4: Заменяем активные столбцы в нужном порядке
    int ptr = 0;
    for (int j = 0; j < cols; j++) {
        int is_active = 0;
        for (int c = 0; c < count; c++) {
            if (kol[0][c] == j) {
                is_active = 1;
                break;
            }
        }
        if (is_active) {
            // Берём столбец из отсортированного списка
            int new_col_idx = kol[0][ptr++];
            for (int i = 0; i < rows; i++) {
                matrix[i][j] = result[i][new_col_idx];
            }
        }
    }

    // Очистка
    for (int i = 0; i < 2; i++) {
        free(kol[i]);
    }
    free(kol);
    free(data);
    free(result);
}

int read(const char *sf, int ***matrix, int ***matrix2, int *M, int *N, int *row, int *col) {
    FILE *f;
    int k = 0;
    int *ca, *ca2;

    f = fopen(sf, "r");
    if (!f) return -1;

    if (fscanf(f, "%d %d %d %d", M, N, row, col) != 4 || *M <= 0 || *N < 0 || *row <= 0 || *col <= 0) {
        fclose(f);
        return -1;
    }

    *matrix = (int**)malloc(*row * sizeof(int*) + *row * *col * sizeof(int));
    *matrix2 = (int**)malloc(*row * sizeof(int*) + *row * *col * sizeof(int));

    if (!*matrix || !*matrix2) {
        free(*matrix);
        free(*matrix2);
        fclose(f);
        return -1;
    }

    ca = (int*)(*matrix + *row);
    ca2 = (int*)(*matrix2 + *row);

    for (int i = 0; i < *row; i++) {
        (*matrix)[i] = ca + i * *col;
        (*matrix2)[i] = ca2 + i * *col;
    }

    for (int i = 0; i < *row; i++) {
        for (int j = 0; j < *col; j++) {
            if (fscanf(f, "%d", &(*matrix)[i][j]) == 1) {
                k++;
                (*matrix2)[i][j] = (*matrix)[i][j];
            } else {
                fclose(f);
                free(*matrix);
                free(*matrix2);
                return -2;
            }
        }
    }

    // Проверка на лишние данные
    int extra;
    if (fscanf(f, "%d", &extra) == 1) {
        fclose(f);
        free(*matrix);
        free(*matrix2);
        return -3;
    }

    if (!feof(f)) {
        fclose(f);
        free(*matrix);
        free(*matrix2);
        return -2;
    }

    if (k < *row * *col) {
        fclose(f);
        free(*matrix);
        free(*matrix2);
        return -4;
    }

    fclose(f);
    return 0;
}

void all_zero(int *arr, int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = 0;
    }
}