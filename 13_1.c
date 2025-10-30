#include <stdio.h>
#include <stdlib.h>
#define N 1000

void move(int [], size_t n);
int read (FILE *, int [], size_t *);
void pr(int [], size_t);
void inverse(int [], int, int);
int find_next_area(int [], size_t, int);
int find_area_end(int [], size_t, int);
int read (FILE *in, int mass[], size_t *n){
	*n=0;
	if(in==NULL)
		return 0;
	while(fscanf(in, "%d",&mass[*n])==1)
		(*n)++;
	if(!feof(in))
		return -1;
	if(*n==0)
		return -2;
	return 1;
}
void pr (int mass[], size_t n){
    for(size_t i=0;i<n;i++){
        printf("%d ",mass[i]);
    }
    printf("\n");
}
void inverse(int mass[], int start, int end){
    while (start < end) {
        // Меняем местами элементы
        int temp = mass[start];
        mass[start] = mass[end];
        mass[end] = temp;
        
        // Двигаем указатели к центру
        start++;
        end--;
    }

}
int main(void) {
    FILE *in = fopen("1.txt", "r");
    size_t n;
    int mass[N], err = read(in, mass, &n);
    if (err) fclose(in);
    switch(err){
		case 0:	printf("No file\n");break;
		case -1:printf("Bad file\n");break;
		case -2: printf("Empty file\n");break;
		default: 
            puts("Begin");
            pr(mass,n);
            move(mass,n);
            pr(mass,n);
    }
    return 0;
}
int find_next_area(int a[], size_t n, int start) {
    for (int i = start; i < (int)n - 1; i++) {
        if (a[i] == a[i + 1]) {
            return i; // Нашли начало участка
        }
    }
    return -1; // Участков больше нет
}

// Находит конец участка, начинающегося с позиции start
int find_area_end(int a[], size_t n, int start) {
    int end = start;
    while (end < (int)n - 1 && a[end] == a[end + 1]) {
        end++;
    }
    return end;
}
void move(int a[], size_t n) {
    int start_ind1 = find_next_area(a, n, 0), end_ind1 = -1,
    start_ind2 = -1, end_ind2 = -1, l1, l2;
    if (start_ind1 == -1) return;
    end_ind1 = find_area_end(a, n, start_ind1);
    while (1) {
        start_ind2 = find_next_area(a, n, end_ind1 + 1);
        if (start_ind2 == -1) break;
        end_ind2 = find_area_end(a, n, start_ind2);
        inverse(a, start_ind1, end_ind2);
        l1 = end_ind1 - start_ind1;
        l2 = end_ind2 - start_ind2;
        start_ind2 = start_ind1;
        end_ind1 = end_ind2;
        start_ind1 = end_ind1 - l1;
        end_ind2 = start_ind2 + l2;
        inverse(a, end_ind2 + 1, start_ind1 - 1);
    }
}
