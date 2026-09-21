#include <stdio.h>
#include <stdlib.h>

int read(const char *, int ***, int ***, int *, int *, int *, int *);
int main(void);
int task(int **, int **, int, int, int, int);
int swap(int **, int, int, int);

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

int task(int **matrix, int **matrix2, int M, int N, int rows, int cols) {//izmenenie matrizi dlya probnogo avtotesta №112
	int *submat_rows = calloc(rows, sizeof(int)),
        *submat_cols = calloc(cols, sizeof(int)),
        down;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (matrix2[i][j] % M == N) {
                submat_rows[i] = 1;
                submat_cols[j] = 1;
            }
        }
    }
    for (int j = 0; j < cols; j++) {
        if (submat_cols[j]) {
            for (int up = 0; up < rows - 1; up++) {
                if (submat_rows[up]) {
                    for (down = up + 1; down < rows; down++) {
                        if (matrix2[up][j] == matrix2[down][j]) {
                            matrix[up][j] = matrix[down][j] = 1;
                            break;
                        }
                    }
                    if (down == rows) {
                        matrix[up][j] = 0;
                    }
                }
            }
        }
    }
    return 0;
} 

int read(const char *sf, int ***matrix, int ***matrix2, int *M, int *N, int *row, int *col) //schitivanie iz faila P.S dlia zadachi nushna kopia matrizi
{
 	FILE *f;    
	int k = 0, q;
 	int *ca;
    int *ca2;
 	f = fopen(sf, "r");
 	if (!f) return -1;

 	if(fscanf(f, "%d %d %d %d", M, N, row, col) != 4 || *M <= 0 || *N <= 0 || *row <= 0 || *col <= 0) {
 	 	fclose(f);
 	 	return -1;
 	}

 	*matrix = (int**)malloc((*row + 1) * sizeof(int*) + (*row) * (*col) * sizeof(int) + (*col) * sizeof(int));
 	*matrix2 = (int**)malloc((*row + 1) * sizeof(int*) + (*row) * (*col) * sizeof(int) + (*col) * sizeof(int));

    ca = (int*)(*matrix + (*row + 1));
    ca2 = (int*)(*matrix2 + (*row + 1));
    
 	for (int i = 0; i < *row + 1; i++){
        (*matrix)[i]=ca+i*(*col);
        (*matrix2)[i]=ca2+i*(*col);
    }
 	
    for(int i = 0; i < *row; i++){
 	 	for(int j = 0; j < *col; j++){
 	  		if(fscanf(f, "%d", &(*matrix)[i][j]) == 1){
 	  	 		k += 1;
                (*matrix2)[i][j] = (*matrix)[i][j];
 	  		}
		}
	}
    

	if (fscanf(f, "%d", &q) == 1) {
        while (fscanf(f, "%d", &q) == 1) {

        } 
        q = 1;
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
	if (q == 1) {
        fclose(f);
        free(*matrix);
        return -3;
    }
	fclose(f);
 	return 0;
}


int swap(int **matrix, int left, int right, int str){ //vdrug ponadobitsya swap
	int k;
	for (int i=0; i < str; i++){
		k =  matrix[i][right];
		matrix[i][right] = matrix[i][left];
		matrix[i][left] = k;
	}
	return 0; 
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
