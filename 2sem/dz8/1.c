#include <string.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
void pr(int **matrix,int *rows,int M);
void swap(int **matrix,int*rows,int left,int right);

int main(void){
    int *mass = NULL;
    int min_str=0,max,right;
    int M; // M - количество строк в матрице
    int **matrix=NULL; //построим криволинейный двумерный массив со случайными размерами строк и заполним случайными числами
	int *rows,s=0;//нам нужен массив длин строк(rows) 
    //и s - в дальнейшем будем говорить что это количество элементов в матрице
	srand(time(NULL));
    M = rand()%11; // P.S 11 можно заменить на любое другое число как и в дальнейшем
    // просто для удобства мы берем ограничение в 11 строк и элементы не больше 11
    rows = (int*) malloc(M*sizeof(*rows));
	for(int i=0;i<M;i++){rows[i]=rand()%11; s+=rows[i];}//заполняем его и подсчитываем количество чисел в матрице
	matrix=(int **)malloc(M*sizeof(*matrix)+s*sizeof(**matrix)); //отводим место для матрицы единым куском
	matrix[0]=(int *)(matrix+M); //разметка памяти
	for(int i=1;i<M;i++)
		matrix[i]=matrix[i-1]+rows[i-1];//разметка памяти 
	for(int i=0;i<s;i++)
		matrix [0][i]=rand()%10; //заполнение массива (попутно видим, что  строки расположены одна за другой)

    pr(matrix,rows,M);
    printf("_____________________________\n");
    // пишите код который меняет матрицу
    
    
    mass = (int*) malloc( M*sizeof(int));// массив индексов выделяем память (в условии написано не больше чем количество строк)

    // решение задачи 9
    for (int i=0;i < M; i++){ // нахождение максималоного веса в матрице 
        if (rows[i] == 0 ) min_str = 0;// начало нахождения веса строки i
        else{
            for (int j=0;j<rows[i];j++){
                if (j == 0) min_str = matrix[i][j];
                if (matrix [i][j] < min_str) min_str = matrix[i][j];
            }
        } // конец нахождения веса строки i
        if(i == 0) max = min_str; 
        if (min_str > max) max = min_str;
    }

    for (int i=0; i<M;i++){
        if (rows[i] == 0 ) min_str = 0;
        else{
            for (int j=0;j<rows[i];j++){
                if (j == 0) min_str = matrix[i][j];
                if (matrix [i][j] < min_str) min_str = matrix[i][j];
            }
        }
        if (min_str == max) mass[i] = 1; // заполняем массив индексов 1- надо удалить 0 - не надо
        else mass[i]=0;
    }

    for (int i=0;i<M;i++){
        if (mass[i] == 1 && i %2 == 0) matrix[i] = NULL;
    }
    for (int i=0;i<M;i++) printf("%d ",mass[i]); // для проверки себя печать массива индесов
    printf("\n");
    printf("\n");

    right = M-1;
    for (int left = 0;left<M;left++){
        if (matrix[left] == NULL){
            swap(matrix,rows,left,right);
            right--;
            M--;
        }
    }// конец решения 9 задачи
    pr(matrix,rows,M);
    free(mass);
    free(rows);
    free(matrix);
    return 0;
}

void pr(int **matrix,int *rows,int M){ //печать матрицы. внутри () 1) матрица 2) массив длин строк 3) количество строк
    for(int i=0;i<M;i++){
		for(int j=0;j<rows[i];j++)
			printf("%d ",matrix[i][j]);  
		puts("");       
	}
}

void swap(int **matrix,int*rows,int left,int right){
    int *t;
    int k;
    t = matrix[left];
    matrix[left] = matrix[right];
    matrix[right] = t;
    k = rows[left];
    rows[left] = rows[right];
    rows[right] = k;
}