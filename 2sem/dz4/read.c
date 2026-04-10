#include "funcs.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int read_array(const char* filename, int*** matrix, int* rows, int** row_sizes) {
    FILE* f = fopen(filename, "r");
    if (!f) return 2;

    int* data = NULL;
    int* sizes = NULL;
    int data_cap = 0, data_cnt = 0;
    int sizes_cap = 0, sizes_cnt = 0;
    char* line = NULL;
    size_t line_cap = 0;
    int empty = 1;
    int c;
    size_t len;

    while (1) {
        len = 0;
        while ((c = fgetc(f)) != EOF && c != '\n') {
            if (len + 1 >= line_cap) {
                line_cap = line_cap ? line_cap * 2 : 64;
                line = (char*) realloc(line, line_cap);
                if (!line) {
                    free(data);
                    free(sizes);
                    fclose(f);
                    return 1;
                }
            }
            line[len++] = c;
        }
        if (c == EOF && len == 0) break;
        line[len] = '\0';
        empty = 0;

        int cnt = 0;
        const char* p = line;
        char* end;
        long val;

        while (*p) {
            while (isspace(*p)) p++;
            if (!*p) break;
            val = strtol(p, &end, 10);
            if (p == end) {
                free(data);
                free(sizes);
                free(line);
                fclose(f);
                return 3;
            }
            if (data_cnt >= data_cap) {
                data_cap = data_cap ? data_cap * 2 : 64;
                data = (int*) realloc(data, data_cap * sizeof(int));
                if (!data) {
                    free(sizes);
                    free(line);
                    fclose(f);
                    return 1;
                }
            }
            data[data_cnt++] = val;
            cnt++;
            p = end;
            while (isspace(*p)) p++;
        }

        if (sizes_cnt >= sizes_cap) {
            sizes_cap = sizes_cap ? sizes_cap * 2 : 8;
            sizes = (int*) realloc(sizes, sizes_cap * sizeof(int));
            if (!sizes) {
                free(data);
                free(line);
                fclose(f);
                return 1;
            }
        }
        sizes[sizes_cnt++] = cnt;
    }

    free(line);
    fclose(f);

    if (empty || data_cnt == 0) {
        free(data);
        free(sizes);
        return 4;
    }

    int** mat = (int**) malloc(sizes_cnt * sizeof(int*) + data_cnt * sizeof(int));
    if (!mat) {
        free(data);
        free(sizes);
        return 1;
    }

    int* data_block = (int*)(mat + sizes_cnt);
    memcpy(data_block, data, data_cnt * sizeof(int));
    free(data);

    int* ptr = data_block;
    int i;
    for (i = 0; i < sizes_cnt; ++i) {
        mat[i] = ptr;
        ptr += sizes[i];
    }

    *matrix = mat;
    *row_sizes = sizes;
    *rows = sizes_cnt;
    return 0;
}