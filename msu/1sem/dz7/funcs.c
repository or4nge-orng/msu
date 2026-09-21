#include "funcs.h"

void pr (int mass[], size_t n){
    for(size_t i=0;i<n;i++){
        printf("%d ",mass[i]);
    }
    printf("\n");
}

size_t task(int mass[], size_t n){
    size_t left = 0;
    int min_el = mass[0], max_el = mass[0], range, *count, max_count = 0;
    if (n == 0) return 0;
    
    // Находим min и max для создания массива счетчиков
    
    for (size_t i = 1; i < n; i++) {
        if (mass[i] < min_el) min_el = mass[i];
        if (mass[i] > max_el) max_el = mass[i];
    }
    
    // Создаем массив счетчиков
    range = max_el - min_el + 1;
    count = (int*)calloc(range, sizeof(int));
    
    // Считаем частоты
    for (size_t i = 0; i < n; i++) {
        count[mass[i] - min_el]++;
    }
    
    // Находим максимальную частоту
    for (int i = 0; i < range; i++) {
        if (count[i] > max_count) {
            max_count = count[i];
        }
    }
    
    
    for (size_t i = 0; i < n; i++) {
        if (count[mass[i] - min_el] != max_count) {
            mass[left++] = mass[i];
        }
    }
    
    free(count);
    return left;
}
