#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int read (FILE *, int **, size_t *, int *);
void write(FILE *, int [], size_t);
void pr(int [], size_t);
void task(int [], size_t, int);
int count_bits(int);
int read(FILE *in, int **mass, size_t *n, int *M) {
    size_t m;
    int cur;
    *mass = NULL;
    if (in == NULL) return 0;

    if (fscanf(in, "%d", &(*M)) != 1) return -1;
    if (*M < 0 || *M > 30) return -1; //(M>=0
    if (fscanf(in, "%zu", &m) != 1) return -1;
    if (m <= 0) return -2;
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
    int *mass = NULL, M, err = read(in, &mass, &n, &M);
    if (err) fclose(in);
    switch(err) {
		case 0:	printf("No file\n");return -1;
		case -1: printf("Bad file\n");return -1;
		case -2: printf("Empty file\n");return -1;
        case -3: printf("Bad size\n");return -1;
		default: 
            puts("Begin");
            pr(mass,n);
            puts("Answer");
            task(mass, n, M);
            write(out, mass, n);
    }
    return 0;
}

void task(int mass[], size_t n, int M) { 
    
    int *I = (int*)calloc(n, sizeof(int)), start, end, sum = mass[n], c = 0;
    size_t I_n = 0;



    for (size_t i = 0; i < n-1; i++) {
        sum+=mass[i];
        if (count_bits(mass[i])%2 == M%2 && 2*mass[i]>mass[i+1]) I[I_n++] = i;
    }
    for (size_t i = 0; i < n; i++) {
        if (abs(mass[i] * (int)n - sum)<=M * (int)n) c++;
    }
    start = I[0];
    end = I[0];
    for (size_t i = 0; i < I_n - 1; i++) {
        if (I[i + 1] - I[i] == 1) {
            end = I[i + 1];
        } else {
            start = end = I[i + 1];
        }
        
        if (end - start > 0) {
            for (size_t j = start; j <= (size_t)end; j++) mass[j] = c;
        }
    }
    pr(I,n);
    pr(mass,n);
}

int count_bits(int n) {
    int c = 0;
    while (n) {
        c += (n & 1) ? 1 : 0; n >>= 1;
    }
    return c;
}
