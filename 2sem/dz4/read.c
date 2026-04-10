// read.c — Функция чтения матрицы из файла
// Назначение: безопасное чтение разреженной матрицы из текстового файла с обработкой ошибок

#include "funcs.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

/**
 * Читает матрицу из текстового файла
 * @param filename Имя файла для чтения
 * @param matrix Указатель на указатель на массив указателей (выходной)
 * @param rows Указатель на количество строк (выходной)
 * @param row_sizes Указатель на массив размеров строк (выходной)
 * @return 0 при успехе, иначе код ошибки:
 *         1 — ошибка выделения памяти
 *         2 — не удалось открыть файл
 *         3 — некорректные данные (не целые числа)
 *         4 — файл пуст или без данных
 */
int read_array(const char* filename, int*** matrix, int* rows, int** row_sizes) {
    FILE* f = fopen(filename, "r");
    if (!f) return 2; // Не удалось открыть файл

    int* data = NULL;         // Временный буфер для всех чисел
    int* sizes = NULL;        // Временный буфер для размеров строк
    int data_cap = 0, data_cnt = 0;  // Емкость и текущее количество чисел
    int sizes_cap = 0, sizes_cnt = 0; // То же для размеров строк
    char* line = NULL;        // Буфер строки
    size_t line_cap = 0;      // Емкость буфера строки
    int empty = 1;            // Признак пустого файла

    // Чтение строк по одной
    while (1) {
        // Динамическое чтение строки произвольной длины
        size_t len = 0;
        int c;
        while ((c = fgetc(f)) != EOF && c != '\n') {
            if (len + 1 >= line_cap) {
                line_cap = line_cap ? line_cap * 2 : 64;
                char* tmp = realloc(line, line_cap);
                if (!tmp) {
                    free(data); free(sizes); free(line); fclose(f);
                    return 1; // Ошибка памяти
                }
                line = tmp;
            }
            line[len++] = c;
        }
        if (c == EOF && len == 0) break; // Конец файла
        line[len] = '\0';
        empty = 0; // Файл не пуст

        // Разбор чисел в строке
        int cnt = 0;
        const char* p = line;
        while (*p) {
            while (isspace(*p)) p++;
            if (!*p) break;
            char* end;
            long val = strtol(p, &end, 10);
            if (p == end) { // Не число
                free(data); free(sizes); free(line); fclose(f);
                return 3; // Ошибка данных
            }
            // Расширение буфера чисел при необходимости
            if (data_cnt >= data_cap) {
                data_cap = data_cap ? data_cap * 2 : 64;
                int* tmp = realloc(data, data_cap * sizeof(int));
                if (!tmp) {
                    free(data); free(sizes); free(line); fclose(f);
                    return 1; // Ошибка памяти
                }
                data = tmp;
            }
            data[data_cnt++] = val;
            cnt++;
            p = end;
            while (isspace(*p)) p++;
        }

        // Сохранение количества чисел в строке
        if (sizes_cnt >= sizes_cap) {
            sizes_cap = sizes_cap ? sizes_cap * 2 : 8;
            int* tmp = realloc(sizes, sizes_cap * sizeof(int));
            if (!tmp) {
                free(data); free(sizes); free(line); fclose(f);
                return 1; // Ошибка памяти
            }
            sizes = tmp;
        }
        sizes[sizes_cnt++] = cnt;
    }
    free(line);
    fclose(f);

    // Проверка на пустой файл
    if (empty || data_cnt == 0) {
        free(data); free(sizes);
        return 4;
    }

    // Выделение единого блока памяти: указатели на строки + данные
    int** mat = malloc(sizes_cnt * sizeof(int*) + data_cnt * sizeof(int));
    if (!mat) {
        free(data); free(sizes);
        return 1; // Ошибка памяти
    }
    int* data_block = (int*)(mat + sizes_cnt); // Блок данных следует сразу за указателями
    memcpy(data_block, data, data_cnt * sizeof(int));
    free(data); // Исходный буфер больше не нужен

    // Настройка указателей на строки
    int* ptr = data_block;
    for (int i = 0; i < sizes_cnt; ++i) {
        mat[i] = ptr;
        ptr += sizes[i];
    }

    // Возврат результатов через указатели
    *matrix = mat;
    *row_sizes = sizes;
    *rows = sizes_cnt;
    return 0; // Успех
}
