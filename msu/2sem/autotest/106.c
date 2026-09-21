#include<stdio.h>
#include<stdlib.h>

void task(int **matrix, int **matrix2, int M, int N, int rows, int cols);

int main(void)
{
	FILE *fi=fopen("data.txt", "r");
	FILE *fo=fopen("output.txt", "w");

	int **mat=NULL, **newmat=NULL;
	int *cols=NULL;
	int M, N, K, L;

	if(!fi || !fo)
	{
	if(fi) fclose(fi);
	if(fo) fclose(fo);
	printf("ERROR\n");
	return -1;
	}

	if(fscanf(fi, "%d", &M) != 1)
	{
	fclose(fi);
	fclose(fo);
	printf("ERROR\n");
	return -1;
	}

	if(fscanf(fi, "%d", &N) != 1)
	{
	fclose(fi);
	fclose(fo);
	printf("ERROR\n");
	return -1;
	}

	if(fscanf(fi, "%d", &K) != 1)
        {
        fclose(fi);
        fclose(fo);
	printf("ERROR\n");
        return -1;
        }

        if(fscanf(fi, "%d", &L) != 1)
        {
        fclose(fi);
        fclose(fo);
	printf("ERROR\n");
        return -1;
        }

	if(K<=0 || L<=0)
	{
	fclose(fi);
        fclose(fo);
	printf("ERROR\n");
	return -1;
        }

	mat=(int**)malloc(K*sizeof(int*));
	newmat=(int**)malloc(K*sizeof(int*));

	for(int i=0; i<K; i++)
	{
	mat[i]=(int*)malloc(L*sizeof(int));
	newmat[i]=(int*)malloc(L*sizeof(int));
	}

	for(int i=0; i<K; i++)
	{
		for(int j=0; j<L; j++)
		{
			if(fscanf(fi, "%d", &mat[i][j]) != 1)
			{
			fclose(fi);
        		fclose(fo);
			for(int k=0; k<K; k++)
			{
			free(mat[i]);
			free(newmat[i]);
			}
			free(mat);
			free(newmat);
			free(cols);
			printf("ERROR\n");
        		return -1;
			}
		newmat[i][j]=mat[i][j];
		}
	}

	task(mat, newmat, M, N, K, L);

	fprintf(fo, "%d %d %d %d\n", M, N, K, L);
	for(int i=0; i<K; i++)
	{
		for(int j=0; j<L; j++)
		{
			fprintf(fo, "%d ", mat[i][j]);
		}
		fprintf(fo, "\n");
	}

	for(int i=0; i<K; i++)
	{
		free(mat[i]);
		free(newmat[i]);
	}
	free(mat);
	free(newmat);
	free(cols);
	fclose(fi);
	fclose(fo);
	return 0;
}

void task(int **matrix, int **matrix2, int M, int N, int rows, int cols) {
	int count, *cols_arr=(int*)malloc(cols*sizeof(int));
	for(int j=0; j<cols; j++)
	{
		cols_arr[j]=0;
		for(int i=0; i<rows; i++)
		{
			if((matrix[i][j]>=M) && (matrix[i][j]<=N))
                        {
                                cols_arr[j]=1;
                                break;
                        }
                }
        }

	for(int i=0; i<rows; i++)
	{
			for(int j=0; j<cols; j++)
			{
				count=0;
				if(cols_arr[j]==1)
				{
					for(int l=0; l<j; l++)
					{
						if(cols_arr[l]==1)
						{
							if(matrix[i][j]==matrix2[i][l])
							{
							count++;
							}
						}
					}
					matrix[i][j]=count;
				}
			}
	}
}
