// funcs.h — Объявление функций для работы с матрицей
// Назначение: содержит прототипы функций для чтения, печати и обработки разреженной матрицы

#ifndef FUNCS_H
#define FUNCS_H

#include <stdio.h>

/**
 * Читает матрицу из текстового файла
 * @param filename Имя файла
 * @param matrix Указатель на матрицу (выход)
 * @param rows Количество строк (выход)
 * @param row_sizes Массив длин строк (выход)
 * @return Код ошибки (0 — успех)
 */
int read_array(const char *, int ***, int *, int **);

/**
 * Сравнивает два столбца матрицы
 * @param matrix Матрица
 * @param row_sizes Длины строк
 * @param rows Количество строк
 * @param j1 Индекс первого столбца
 * @param j2 Индекс второго столбца
 * @return 1, если столбцы несравнимы; 0 иначе
 */
int comp_cols(int **, int *, int, int, int);

/**
 * Основная задача: удаляет несравнимые пары столбцов
 * @param matrix Указатель на матрицу
 * @param rows Количество строк
 * @param row_sizes Массив длин строк
 */
void task(int ***, int *, int **);

/**
 * Печать матрицы на экран
 * @param matrix Матрица
 * @param row_sizes Длины строк
 * @param rows Количество строк
 */
void print_matrix(int **, int *, int);

/**
 * Удаляет элементы из массива по маске
 * @param src Исходный массив
 * @param len Длина массива
 * @param mask Маска удаления
 * @param new_len Длина результата (выход)
 * @return Указатель на новый массив
 */
int* remove_elements(const int*, int, char *, int *);

/**
 * Удаляет столбец из матрицы
 * @param mat Матрица
 * @param row_sizes Длины строк
 * @param rows Количество строк
 * @param col Индекс столбца
 */
void delete_column(int **, int *, int, int);

#endif // FUNCS_H