#include <stdio.h>
#include <stdlib.h>

int read (FILE *, int **, size_t *);
void pr(int [], size_t);
size_t task(int [], size_t);
int most_frequent(int [], size_t);
int read(FILE *in, int **mass, size_t *n) {
    size_t m;
    int cur;
    *mass = NULL;
    if (in == NULL)
        return 0;
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
        case -3: printf("Bad size\n");break;
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
    for (int i = 0; i < max_el - min_el; i++) {
        if (count[i] > count[res]) {
            res = i;
        }
    }
    free(count);
    return res + min_el;
}

size_t task(int mass[], size_t n){
    int most_freq = most_frequent(mass, n), left = 0;
    for (size_t i = 0; i < n; i++) {
        if (mass[i]!=most_freq) {
            mass[left++] = mass[i];
        }        
    }
    return left;
}
