#include "funcs.h" 
#include <string.h>
#include <stdio.h> 
#include <stdlib.h>

int main(void) {
    // Указатели на матрицу и размеры строк
    int** matrix = NULL;
    int* row_sizes = NULL;
    int rows = 0; // Количество строк

    // Имя входного файла
    char* filename = "1.txt";

    // Чтение матрицы из файла
    int read_res = read_array(filename, &matrix, &rows, &row_sizes);

    // Обработка ошибок чтения
    switch (read_res) {
        case 0:
            break;
        case 1:
            fprintf(stderr, "Error: Memory allocation failed.\n");
            return EXIT_FAILURE;
        case 2:
            fprintf(stderr, "Error: Cannot open file '%s'.\n", filename);
            return EXIT_FAILURE;
        case 3:
            fprintf(stderr, "Error: Invalid data in file '%s' — non-integer value found.\n", filename);
            return EXIT_FAILURE;
        case 4:
            fprintf(stderr, "Error: File '%s' is empty or contains no data.\n", filename);
            return EXIT_FAILURE;
        default:
            fprintf(stderr, "Error: Unknown error occurred (code %d).\n", read_res);
            return EXIT_FAILURE;
    }

    print_matrix(matrix, row_sizes, rows);
    task(&matrix, &rows, &row_sizes);
    print_matrix(matrix, row_sizes, rows);


    free(matrix); 
    free(row_sizes);

    return EXIT_SUCCESS;
}