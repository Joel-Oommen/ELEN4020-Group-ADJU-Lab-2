#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define NUM_THREADS 4
pthread_mutex_t mutexTranspose;       //Static initialization of mutex

struct Matrix
{
	int Dimensions;
	int *A;
	int rowStart;
	int colStart;
};

//_____________________________Function Definitions_____________________________________
void swapInt(int *x, int *y) {int tmp = *x;*x=*y;*y=tmp;}
//______________________________________________________________________________________
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
//______________________________________________________________________________________
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
//______________________________________________________________________________________
void* transposeMatrix(void* argument)
{
	struct Matrix *arg = (struct Matrix *)argument;
	int Dimensions = arg->Dimensions;
	int *A = arg->A;
	int rowStart = arg->rowStart;
	int colStart = arg->colStart;

  pthread_mutex_lock (&mutexTranspose);
	transposeQuad(Dimensions,(int *)arg->A,rowStart,colStart);
  pthread_mutex_unlock (&mutexTranspose);

	return NULL;
}
//______________________________________________________________________________________


//________________________________________Main__________________________________________
int main(int argc, char** argv)
{
//Struct Initialization
  int Dimensions=4;
	double elmn=Dimensions*Dimensions;
	struct Matrix m;
	m.Dimensions = Dimensions;
	m.A = (int *)malloc(elmn*sizeof(int));
	printf("\n Original matrix \n");

//Matrix Initialization
  for(int i=0;i<Dimensions;i++)
	{
		for(int j=0;j<Dimensions;j++)
		{
			m.A[i*Dimensions+j]=(i*Dimensions + j);
			printf("%d \t", m.A[i*Dimensions+j]);
		}
		printf("\n");
	}


  pthread_t threads[NUM_THREADS];
  pthread_mutex_init(&mutexTranspose, NULL);

  int result_code;
  unsigned index=0;
  //______________________________________________________________________________________
  m.rowStart = 0;
  m.colStart = 0;
  printf("\nIn main: creating thread %d\n", index);
  result_code = pthread_create(&threads[index], NULL, transposeMatrix, (void *) &m);
  assert(!result_code);

 //block until thread 'index' completes
 result_code = pthread_join(threads[0], NULL);
 assert(!result_code);
 printf("\nIn main: thread %d has completed\n", 0);

 printf("Progress \n");
 for(int i=0;i<Dimensions;i++)
 {
   for(int j=0;j<Dimensions;j++)
   {
     printf("%d \t", m.A[i*Dimensions+j]);
   }
   printf("\n");
 }
 //______________________________________________________________________________________
 int Q = Dimensions/2;
 m.rowStart = 0;
 m.colStart = Q;
 ++index;

 printf("\nIn main: creating thread %d\n", index);
 result_code = pthread_create(&threads[index], NULL, transposeMatrix, (void *) &m);
 assert(!result_code);
 //index++;

 // block until thread 'index' completes
 result_code = pthread_join(threads[1], NULL);
 assert(!result_code);
 printf("\nIn main: thread %d has completed\n", 1);

 printf("Progress \n");
 for(int i=0;i<Dimensions;i++)
 {
   for(int j=0;j<Dimensions;j++)
   {
     printf("%d \t", m.A[i*Dimensions+j]);
   }
   printf("\n");
 }
 //______________________________________________________________________________________
 m.rowStart = Q;
 m.colStart = 0;
 ++index;

 printf("\nIn main: creating thread %d\n", index);
 result_code = pthread_create(&threads[index], NULL, transposeMatrix, (void *) &m);
 assert(!result_code);
 //index++;


 //block until thread 'index' completes
 result_code = pthread_join(threads[2], NULL);
 assert(!result_code);
 printf("\nIn main: thread %d has completed\n", 2);

 printf("Progress \n");
 for(int i=0;i<Dimensions;i++)
 {
   for(int j=0;j<Dimensions;j++)
   {
     printf("%d \t", m.A[i*Dimensions+j]);
   }
   printf("\n");
 }
 //______________________________________________________________________________________
 m.rowStart = Q;
 m.colStart = Q;
 ++index;

 printf("\nIn main: creating thread %d\n", index);
 result_code = pthread_create(&threads[index], NULL, transposeMatrix, (void *) &m);
 assert(!result_code);
 //index++;

 //block until thread 'index' completes
 result_code = pthread_join(threads[3], NULL);
 assert(!result_code);
 printf("\nIn main: thread %d has completed\n", 3);

 printf("Progress \n");
 for(int i=0;i<Dimensions;i++)
 {
   for(int j=0;j<Dimensions;j++)
   {
     printf("%d \t", m.A[i*Dimensions+j]);
   }
   printf("\n");
 }
 //______________________________________________________________________________________

 // wait for each thread to complete
 /*for (int newIndex = 0; newIndex < NUM_THREADS; ++newIndex)
 {
   // block until thread 'index' completes
   result_code = pthread_join(threads[newIndex], NULL);
   assert(!result_code);
   printf("\nIn main: thread %d has completed\n", newIndex);

   printf("Progress \n");
   for(int i=0;i<Dimensions;i++)
   {
     for(int j=0;j<Dimensions;j++)
     {
       printf("%d \t", m.A[i*Dimensions+j]);
     }
     printf("\n");
   }
 }
*/
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
 free(m.A);
 pthread_mutex_destroy(&mutexTranspose);
 pthread_exit(NULL);
}
