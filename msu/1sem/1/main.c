#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int read (FILE *, int **, size_t *);
void write(FILE *, int [], size_t);
void pr(int [], size_t);
int read(FILE *in, int **mass, size_t *n) {
    size_t N, min = 0;
    int cur;
    *mass = NULL;
    if (in == NULL) return 0;

    if (fscanf(in, "%zu", &N) != 3) return -1;
    
    if (N <= 0) return -2;

    *mass = malloc(N * sizeof(int));

    if (*mass == NULL) {
        return -3;
    }

    if (fscanf(in, "%d", &cur) != 1) {
        return -1;
    }
    *mass[(*n)++] = cur;
    do {
        *mass[(*n)++] = cur;
    } while (fscanf(in, "%d", &cur) == 1);
    if (*n < N) {
        for (size_t i = (*n); i < N; i++) {
            *mass[i] = -1;
        }
    }
    if (fscanf(in, "%d", &(*mass[(*n)++])) != 1) 
        return -1;
    do {
        for (size_t i = 0; i < *n; i++) {
            if (*mass[i] < *mass[min]) min = i;
        }
        if (*mass[min] < cur) continue;
        else *mass[min] = cur;

    } while (fscanf(in, "%d", &cur) == 1);
    
    if (!feof(in)) {
        free(*mass);
        *mass = NULL;
        return -1;
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
    int *mass = NULL, err = read(in, &mass, &n);
    if (err) fclose(in);
    switch(err) {
		case 0:	printf("No file\n");return -1;
		case -1: printf("Bad file\n");return -1;
		case -2: printf("Empty file\n");return -1;
        case -3: printf("Bad size\n");return -1;
		default: 
            //sort(&mass, n);
            pr(mass, n);
            write(out, mass, n);
    }
}

