#include <stdio.h>
#include <stdlib.h>

void move(int [], size_t n);
int read (FILE *, int **, size_t *);
void pr(int [], size_t);
int find_k_max(int [], size_t, int, int *);
void task(int [], size_t);

int read (FILE *in, int **mass, size_t *n) {
	size_t capacity = 0;
    int value, res;
    (*mass) = NULL;
    (*n) = 0;
    if(in==NULL)
		return 0;
    
    while ((res = fscanf(in, "%d", &value)) == 1) {
        if (*n >= capacity) {
            size_t new_cap = (capacity == 0) ? 2 : capacity * 2;
            int *new_mass = (int*)realloc(*mass, new_cap * sizeof(int));
            if (new_mass == NULL) {
                free(*mass);
                *mass = NULL;
                return -3;
            }
            *mass = new_mass;
            capacity = new_cap;
        }
        (*mass)[*n] = value;
        (*n)++;
    }
	if(!feof(in)) {
        free(*mass);
        *mass = NULL;
		return -1;
    }
	if(*n==0)
		return -2;
    if (capacity > *n) {
        int *optimized_mass = (int*)realloc(*mass, *n * sizeof(int));
        if (optimized_mass != NULL) {
            *mass = optimized_mass;
        }
        // Если realloc вернул NULL, продолжаем использовать существующий массив
    }
	return 1;
}
void pr (int mass[], size_t n){
    for(size_t i=0;i<n;i++){
        printf("%d ",mass[i]);
    }
    printf("\n");
}
int main(void) {
    FILE *in = fopen("1.txt", "r");
    size_t n;
    int *mass = NULL, err = read(in, &mass, &n);
    if (err) fclose(in);
    switch(err){
		case 0:	printf("No file\n");break;
		case -1:printf("Bad file\n");break;
		case -2: printf("Empty file\n");break;
        case -3: printf("Memory error\n");break;
		default: 
            puts("Begin");
            pr(mass,n);
            puts("Answer");
            task(mass,n);
    }
    return 0;
}

int find_k_max(int mass[], size_t n, int k, int *res){
    int cur_max = mass[0];
    for (size_t i = 1; i < n; i++) {
        if (mass[i] > cur_max) {
            cur_max = mass[i];
        }
    }
    if (k == 1) {
        *res = cur_max;
        return 1;
    }
    for (int i = 1; i < k; i++) {
        int candidate = INT32_MIN, found = 0;
        for (size_t j = 0; j < n; j++) {
            if (mass[j] > candidate && mass[j] < cur_max) {
                candidate = mass[j];
                found = 1;
            }
        }
        if (!found) return 0;
        cur_max = candidate;
    }
    *res = cur_max;
    return 1;
}

void task(int mass[], size_t n) {
    int k_max, err, sum1 = 0, sum2 = 0;
    for (size_t k = 1; k <= n; k++) {
        err = find_k_max(mass, n, k, &k_max);
        if (err) {
            for (size_t i = 0; i < n; i++) {
                if (mass[i] <= k_max) sum1 += abs(mass[i]);
                else sum2 += abs(mass[i]);
            }
            if (sum1 == sum2) {
                printf("%zu\n", k);
                return;
            }
            sum1 = sum2 = 0;
        }
    }
}
