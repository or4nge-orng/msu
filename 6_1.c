#include <stdio.h>
#include <stdlib.h>

int read (FILE *, int **, size_t *);
void pr(int [], size_t);
size_t task(int [], size_t, int);
size_t null_val(int [], size_t);

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
    int *mass = NULL, err = read(in, &mass, &n), nul_val;
    if (err) fclose(in);
    switch(err){
		case 0:	printf("No file\n");break;
		case -1:printf("Bad file\n");break;
		case -2: printf("Empty file\n");break;
        case -3: printf("Memory error\n");break;
		default: 
            nul_val = null_val(mass,n);
            puts("Begin");
            pr(mass,n);
            puts("Answer");
            n = task(mass, n, nul_val);
            pr(mass,n);
    }
    return 0;
}

size_t null_val(int mass[], size_t n){
    int *flags = (int*)calloc(n, sizeof(int)), min_val = mass[0];
    if (flags == NULL) {
        return -1;
    }
    for (size_t i=0;i<n;i++) {
        if (mass[i] < min_val) {
            min_val = mass[i];
        }
    }
    for(size_t i=0;i<n;i++){
        if (mass[i] >= 0 && mass[i] <= (int)n) {
            flags[mass[i]] = 1;
        }
    }
    for (size_t i = 0; i < n; i++) {
        if (flags[i] == 0) {
            return i;
        }
    }
    return n;
}

size_t task(int mass[], size_t n, int null_value){
    int left=0, prev = mass[1], pprev = mass[0];
	for(size_t i=2;i<n;i++) {
        
		if(mass[i]!=(prev + pprev)) {
            prev = mass[i];
			mass[i]=null_value;//пометили элементы, которые надо удалить
        }
        prev = mass[i];
        pprev = mass[i-1];
    }
	for(size_t right=0;right<n;right++) { //левый бегунок - размер уплотненного массива, правый просматривает  элементы исходного
		if(mass[right]!=null_value)//если элемент нужно оставить
			mass[left++]=mass[right];//копируем и увеличиваем левый бегунок, элементы, которые нужно удалить, пропускаем

    }
    return left;//возвращаем новый размер массива
}
