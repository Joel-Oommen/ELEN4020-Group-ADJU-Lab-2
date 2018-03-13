#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
 
#define NUM_THREADS 4

void swapInt(int *x, int *y) {int tmp = *x;*x=*y;*y=tmp;}

void transposeQuad(int Dimensions,int *A,int rowStart,int colStart)
{
	int quadSize = Dimensions/2;
	for(int n=0;n<quadSize;n++)
	{
		for(int m=n+1;m<quadSize;m++)
		{
			swapInt(&A[(rowStart+n)*Dimensions+(colStart+m)],&A[(rowStart+m)*Dimensions+(colStart+n)]);
		}
	}
	
}

void swapQuad(int Dimensions, int *A)
{
	int quadSize = Dimensions/2;
	for(int n=0;n<quadSize;n++)
	{
		for(int m=0;m<quadSize;m++)
		{
			swapInt(&A[n*Dimensions+quadSize+m],&A[(quadSize+n)*Dimensions+m]);
		}
	}
}
struct Matrix
{
	int Dimensions;
	int *A;
	int rowStart;
	int colStart;
};

void* transposeMatrix(void* argument)
{
	struct Matrix *arg = (struct Matrix *)argument;
	int rowStart = arg->rowStart;
	int colStart = arg->colStart;
	transposeQuad(arg->Dimensions,(int *)arg->A,rowStart,colStart);
	return NULL;
}

int main(int argc, char** argv) 
{
	int Dimensions=4;
	double elmn=Dimensions*Dimensions;
	int *A = (int *)malloc(elmn*sizeof(int));
	int c=0;
	printf("\n Original matrix \n");
	for(int i=0;i<Dimensions;i++)
	{
		for(int j=0;j<Dimensions;j++)
		{
			A[i*Dimensions+j]=++c;
			printf("%d \t", A[i*Dimensions+j]);
		}
		printf("\n");
	}
	pthread_t threads[NUM_THREADS];
	int result_code;
	unsigned index=0;
//______________________________________________________________________________________
//Defining arguments	
	int Q = Dimensions/2;
//******************************
	struct Matrix m1;
	m1.Dimensions = Dimensions;
	m1.A = (int *)A;
	m1.rowStart = 0;
	m1.colStart = 0;
//******************************
	struct Matrix m2;
	m2.Dimensions = Dimensions;
	m2.A = (int *)A;	
	m2.rowStart = 0;
	m2.colStart = Q;
//******************************
	struct Matrix m3;
	m3.Dimensions = Dimensions;
	m3.A = (int *)A;
	m3.rowStart = Q;
	m3.colStart = 0;
//******************************
	struct Matrix m4;
	m4.Dimensions = Dimensions;
	m4.A = (int *)A;
	m4.rowStart = Q;
	m4.colStart = Q;
//******************************
//______________________________________________________________________________________
	printf("In main: creating thread %d\n", index);
	result_code = pthread_create(&threads[index], NULL, transposeMatrix, &m1);
	assert(!result_code);
	index++;
//______________________________________________________________________________________
	printf("In main: creating thread %d\n", index);
	result_code = pthread_create(&threads[index], NULL, transposeMatrix, &m2);
	assert(!result_code);
	index++;
//______________________________________________________________________________________
	printf("In main: creating thread %d\n", index);
	result_code = pthread_create(&threads[index], NULL, transposeMatrix, &m3);
	assert(!result_code);
	index++;
//______________________________________________________________________________________
	printf("In main: creating thread %d\n", index);
	result_code = pthread_create(&threads[index], NULL, transposeMatrix, &m4);
	assert(!result_code);
	index++;
//______________________________________________________________________________________
	
	// wait for each thread to complete
	for (int idx = 0; idx < NUM_THREADS ; idx++)
	{
		// block until thread 'index' completes
		result_code = pthread_join(threads[idx], NULL);
		assert(!result_code);
		printf("In main: thread %d has completed\n", idx);
		
		printf("\n Progress \n");
		for(int i=0;i<Dimensions;i++)
		{
			for(int j=0;j<Dimensions;j++)
			{
				printf("%d \t", A[i*Dimensions+j]);
			}
			printf("\n");
		}
	}
	swapQuad(Dimensions,A);//swap B and C
	printf("\n Transpose matrix \n");
	for(int i=0;i<Dimensions;i++)
	{
		for(int j=0;j<Dimensions;j++)
		{
			printf("%d \t",A[i*Dimensions+j]);
		}
		printf("\n");
	}
	free(A);
	exit(EXIT_SUCCESS);
}
