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
	int* A;
	int rowStart;
	int colStart;
};

void* transposeMatrix(void* argument) 
{
	struct Matrix *arg = (struct Matrix *)argument;
	int Dimensions = arg->Dimensions;
	int *A = arg->A;
	int rowStart = arg->rowStart;
	int colStart = arg->colStart;
	transposeQuad(Dimensions,A,rowStart,colStart);
	return NULL;
}

void* perform_work(void* argument) 
{
	int passed_in_value;

	passed_in_value = *((int*) argument);
	printf("Hello World! It's me, thread with argument %d!\n", passed_in_value);

	return NULL;
}
 
int main(int argc, char** argv) 
{
	int Dimensions=4;
	double elmn=Dimensions*Dimensions;
	struct Matrix m;
	m.Dimensions = Dimensions;
	m.A = (int *)malloc(elmn*sizeof(int));
	int c=0;
	printf("\n Original matrix \n");
	for(int i=0;i<Dimensions;i++)
	{
		for(int j=0;j<Dimensions;j++)
		{
			m.A[i*Dimensions+j]=++c;
			printf("%d \t", m.A[i*Dimensions+j]);
		}
		printf("\n");
	}
	pthread_t threads[NUM_THREADS];
	int result_code;
	unsigned index=0;
//______________________________________________________________________________________
	m.rowStart = 0;
	m.colStart = 0;	
	printf("In main: creating thread %d\n", index);
	result_code = pthread_create(&threads[index], NULL, transposeMatrix, &m);
	assert(!result_code);
	index++;
//______________________________________________________________________________________	
	int Q = Dimensions/2;
	m.rowStart = 0;
	m.colStart = Q;
	
	printf("In main: creating thread %d\n", index);
	result_code = pthread_create(&threads[index], NULL, transposeMatrix, &m);
	assert(!result_code);
	index++;
//______________________________________________________________________________________	
	m.rowStart = Q;
	m.colStart = 0;
	
	printf("In main: creating thread %d\n", index);
	result_code = pthread_create(&threads[index], NULL, transposeMatrix, &m);
	assert(!result_code);
	index++;
//______________________________________________________________________________________
	m.rowStart = Q;
	m.colStart = Q;
	
	printf("In main: creating thread %d\n", index);
	result_code = pthread_create(&threads[index], NULL, transposeMatrix, &m);
	assert(!result_code);
	index++;
//______________________________________________________________________________________	
	
	// wait for each thread to complete
	for (index = 0; index < NUM_THREADS; ++index)
	{
		// block until thread 'index' completes
		result_code = pthread_join(threads[index], NULL);
		assert(!result_code);
		printf("In main: thread %d has completed\n", index);
	}
	swapQuad(Dimensions,m.A);//swap B and C
	printf("\n Transpose matrix \n");
	for(int i=0;i<Dimensions;i++)
	{
		for(int j=0;j<Dimensions;j++)
		{
			printf("%d \t", m.A[i*Dimensions+j]);
		}
		printf("\n");
	}
	exit(EXIT_SUCCESS);
}
