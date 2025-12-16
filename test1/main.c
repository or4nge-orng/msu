#include <stdio.h>
#include <stdlib.h>

int read (FILE *, int **, size_t *, int *, int *);
void write(FILE *, int [], size_t);
void pr(int [], size_t);
void task(int [], size_t, int, int);
void sort(int **, int *, size_t);
int read(FILE *in, int **mass, size_t *n, int *M, int *N) {
    size_t m;
    int cur;
    *mass = NULL;
    if (in == NULL)
        return 0;

    if (fscanf(in, "%d", &(*M)) != 1) {
        return -1;
    }

    if (fscanf(in, "%d", &(*N)) != 1) {
        return -1;
    }

    if (*N == 0) {
        return -1;
    }

    if (fscanf(in, "%zu", &m) != 1) {
        return -1;
    }

    if (m <= 0) {
        return -2;
    }
    *n = m;
    *mass = malloc(m * sizeof(int));
    if (*mass == NULL) {
        return -3;
    }

    for (size_t i = 0; i < m; i++) {
        if (fscanf(in, "%d", &(*mass)[i]) != 1) {
            free(*mass);
            *mass = NULL;
            return -1;
        }
    }
    while (!feof(in)) {
        if (fscanf(in, "%d", &cur) != 1) {
            break;
        } else {
            m++;
        }
    }
    if (!feof(in)) {
        free(*mass);
        *mass = NULL;
        return -1;
    }
    if (m != *n) {
        return -3;
    }
    return 1;
}

void write(FILE *out, int mass[], size_t n) {
    for (size_t i = 0; i < n; i++) {
        fprintf(out, "%d ", mass[i]);
    }
    fclose(out);
    free(mass);
}

void pr (int mass[], size_t n){
    for(size_t i=0;i<n;i++){
        printf("%d ",mass[i]);
    }
    printf("\n");
}
int main(void) {
    FILE *in = fopen("input.txt", "r");
    FILE *out = fopen("output.txt", "w");
    size_t n;
    int *mass = NULL, M, N, err = read(in, &mass, &n, &M, &N);
    if (err) fclose(in);
    switch(err) {
		case 0:	printf("No file\n");return -1;
		case -1: printf("Bad file\n");return -1;
		case -2: printf("Empty file\n");return -1;
        case -3: printf("Bad size\n");return -1;
		default: 
            task(mass, n, M, N);
            write(out, mass, n);
    }
    return 0;
}

void task(int mass[], size_t n, int M, int N){
    int sum = 0, *I = (int*)calloc(n, sizeof(int));
    size_t I_n = 0;
    for (size_t i = 0; i < n; i++) {
        sum+=mass[i];
    }
    for (size_t i = 0; i < n; i++) {
        if ((N * abs(mass[i] * (int)n - sum)) <= M * (int)n) {
            I[I_n++] = i;
        }
    }
    sort(&mass, I, I_n);
}


void sort(int **mass, int *I, size_t I_n) {
    int min, tmp;
    for (size_t i = 0; i < I_n; i++) {
        min = i;
        for (size_t k = i; k < I_n; k++) {
            if ((*mass)[I[k]] < (*mass)[I[min]]) {
                min = k;
            }
        }
        tmp = (*mass)[I[i]];
        (*mass)[I[i]] = (*mass)[I[min]];
        (*mass)[I[min]] = tmp;
    }
}

