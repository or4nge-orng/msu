#include <stdio.h>
#include <stdlib.h>

int read (FILE *, int **, size_t *);
void pr(int [], size_t);
size_t task(int [], size_t);
int most_frequent(int [], size_t);

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
            n = task(mass, n);
            pr(mass,n);
            free(mass);
    }
    return 0;
}

int most_frequent(int mass[], size_t n){
    int min_el = mass[0], max_el = mass[0], *count = NULL, res;
    for (size_t i = 0; i < n; i++) {
        if (mass[i] < min_el) {
            min_el = mass[i];
        } else if (mass[i] > max_el) {
            max_el = mass[i];
        }
    }
    count = (int *)calloc(max_el - min_el + 1, sizeof(int));
    for (size_t i = 0; i < n; i++) {
        count[mass[i] - min_el]++;
    }
    res = 0;
    pr(count, max_el - min_el + 1);
    for (int i = 0; i < max_el - min_el + 1; i++) {
        if (count[i] > count[res]) {
            res = i;
        }
    }
    free(count);
    printf("%d %d\n",min_el, res);
    return res + min_el;
}

size_t task(int mass[], size_t n){
    int most_freq = most_frequent(mass, n), left = 0;
    printf("%d\n",most_freq);
    for (size_t i = 0; i < n; i++) {
        if (mass[i]!=most_freq) {
            mass[left++] = mass[i];
        }        
    }
    return left;
}
