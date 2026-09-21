#include <stdio.h>
#include <stdlib.h>

int read(const char *, int ***, int ***, int *, int *, int *, int *);
int main(void);
void task(int **, int **, int, int, int, int);
void all_zero(int *, int);

int main(void) {
    int **matrix;
    int **matrix2;
    int row, col;
    int N, M;
    FILE *wf; 
	
    switch(read("data.txt", &matrix, &matrix2, &M,&N, &row, &col)) {
        case -1:
            perror("Bad file format");
            return -1;
        case -2:
            perror("Letter in file");
            return -1;
        case -3:
            perror("Found more numbers than expected");
            return -1;
        case -4:
            perror("Found fewer numbers than expected");
            return -1;
    }

    /*printf("bilo:\n");                     dlya proverki
    for (int i=0;i<row;i++){
        for (int j=0;j<col;j++){
            printf("%d ",matrix[i][j]);
        }
        printf("\n");
    }*/ 
    task(matrix, matrix2, M, N, row, col);
    /*printf ("stalo:\n");                dlya proverki
    for (int i=0;i<row;i++){
        for (int j=0;j<col;j++){
            printf("%d ",matrix[i][j]);
        }
        printf("\n");
    }*/

    wf = fopen("res.txt", "w");
    if (wf == NULL)
        return -1;

    fprintf(wf, "%d %d %d %d\n", M, N, row, col);
    for (int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            fprintf(wf, "%d ", matrix[i][j]);
        }
        fprintf(wf, "\n");
    }
    fclose(wf);
    free(matrix); 
    return 0;	
}

void task(int **matrix, int **matrix2, int M, int N, int rows, int cols) {//izmenenie matrizi dlya probnogo avtotesta №112
	int *submat_cols = calloc(cols, sizeof(int)),
        *cols_tochange = calloc(cols, sizeof(int)),
        count = 1;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (matrix2[i][j] % M == N) {
                submat_cols[j] = 1;
            }
        }
    }

    for (int i = 0; i < cols; i++) {
        printf("%d ", submat_cols[i]);
    }
    printf("\n\n");

    for (int i = 0; i < rows; i++) {
        
        for (int left = 0; left < cols - 1; left++) {
            for (int right = left + 1; right < cols; right++) {
                if (submat_cols[left]) {
                    cols_tochange[left] = 1;
                    if (submat_cols[right]) {
                        if (matrix2[i][left] == matrix2[i][right]) {
                            count++;
                            cols_tochange[right] = 1;
                        }
                    }
                }
                if (i == rows - 1) for (int i = 0; i < cols; i++) {
                    printf("%d ", cols_tochange[i]);
                }
                for (int j = 0; j < cols; j++) {
                    if (cols_tochange[j]) {
                        matrix[i][j] = count;
                    }
                }
                count = 0;
                all_zero(cols_tochange, cols);
            }
        }
    }
} 

int read(const char *sf, int ***matrix, int ***matrix2, int *M, int *N, int *row, int *col) //schitivanie iz faila P.S dlia zadachi nushna kopia matrizi
{
 	FILE *f;    
	int k = 0;
 	int *ca;
    int *ca2;
 	f = fopen(sf, "r");
 	if (!f) return -1;

 	if(fscanf(f, "%d %d %d %d", M, N, row, col) != 4 || *M <= 0 || *N <= 0 || *row <= 0 || *col <= 0) {
 	 	fclose(f);
 	 	return -1;
 	}

 	*matrix = (int**)malloc((*row) * sizeof(int*) + (*row) * (*col) * sizeof(int));
 	*matrix2 = (int**)malloc((*row) * sizeof(int*) + (*row) * (*col) * sizeof(int));

    ca = (int*)(*matrix + (*row));
    ca2 = (int*)(*matrix2 + (*row));
    
 	for (int i = 0; i < *row; i++){
        (*matrix)[i] = ca + i * (*col);
        (*matrix2)[i] = ca2 + i * (*col);
    }
 	
    for(int i = 0; i < *row; i++){
 	 	for(int j = 0; j < *col; j++){
 	  		if(fscanf(f, "%d", &(*matrix)[i][j]) == 1){
 	  	 		k += 1;
                (*matrix2)[i][j] = (*matrix)[i][j];
 	  		}
		}
	}

	if(!feof(f)) {
        fclose(f); 
        free(*matrix);
        return -2;
    }
    
	if (k < ((*row) * (*col))) {
        fclose(f); 
        free(*matrix); 
        return -4;
    }

	fclose(f);
 	return 0;
}


void all_zero(int *arr, int n) { //vdrug ponadobitsya swap
	for (int i = 0; i < n; i++) {
        if (arr[i] != 0) {
            arr[i] = 0;
        }
    }
}
/* //sortirovka puzyrkom mb nado
void bubble_sort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                // Обмен элементов
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}
    */
