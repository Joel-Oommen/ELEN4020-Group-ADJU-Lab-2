#include <stdlib.h>
#include <stdio.h>
#include "omp.h"
#include <time.h>

void swap_int(int *x, int *y) {int tmp = *x;*x=*y;*y=tmp;}



void populateArray(int **A, int dimension)
{

	int ELEM = dimension;
	for(int i=0;i<ELEM;i++)
	{
		for(int j=0;j<ELEM;j++)
		{
			A[i][j]=i*ELEM+j;
		}
	}
}


void printArray(int **A, int dimension)
{

	int ELEM = dimension;
	for(int i=0;i<ELEM;i++)
	{
		for(int j=0;j<ELEM;j++)
		{
			printf("%d \t", A[i][j]);
		}
		printf("\n");
	}
}

void linearTranspose(int **A, int dimension)
{
	int ELEM = dimension;
	int tmp;
	for(int i=0;i<ELEM;i++)
	{
		
		for(int j=i+1;j<ELEM;j++)
		{
			tmp = A[i][j];
               		A[i][j] = A[j][i];
                	A[j][i] = tmp;
					
		}
	}
}

void parallelTranspose(int **A, int dimension,int numThreads)
{
	int ELEM =dimension;
	int i, j,tmp;
    	#pragma omp parallel shared(A) private( i, j) num_threads(numThreads)
    	{
        	#pragma omp for schedule(dynamic,1)  nowait
        	for (i = 0; i < ELEM - 1; i++) 
		{
            		for (j = i + 1; j < ELEM; j++) 
			{
                		tmp = A[i][j];
               		 	A[i][j] = A[j][i];
                		A[j][i] = tmp;
            		}
        	}
    	}




}


#define ELEM 20000


int main()
{	

	// CREATE AND PRINT ORIGINAL MATRIX;
	double elmn=ELEM;
	int ** A;
    	A = malloc(elmn * sizeof(int *));
	for(int i = 0; i < ELEM; i++)
	{
        	A[i] = (int *)malloc(ELEM * sizeof(int));
	}	
	
	// If you wish to print the matrix to test that the transpose works 
	// you uncomment the print function below.


	populateArray(A,ELEM);

	//printf("\n Original matrix \n");
	//printArray(A,ELEM);



	// LINEAR TRANSPOSE
	// THIS IS WHERE THE LINEAR TRANSPOSE TAKES PLACE.

	double starttime = omp_get_wtime();
    	linearTranspose(A,ELEM);
	double diff = omp_get_wtime() - starttime;
	printf("Linear %c %c: %f\n", ' ',' ', diff);
		


	// TO PRINT THE TRANSPOSED MATRIX UNCOMMENT THE PRINTF'S BELOW


	//printf("\n 1st Transposed matrix \n");
	//printArray(A,ELEM);
	

	// PARALLEL TRANSPOSE
	// THIS IS WHERE THE PARALLEL TRANSPOSE TAKES PLACE.


	// 4  THREADS

	starttime = omp_get_wtime();
	parallelTranspose(A,ELEM,4);
	diff = omp_get_wtime() - starttime;
	printf("Parallel (4 Threads): %c %c: %f\n", ' ',' ', diff);
		
	
	// TO PRINT THE TRANSPOSED MATRIX UNCOMMENT THE PRINTF'S BELOW

	//printf("\n 2nd Transposed matrix \n");
	//printArray(A,ELEM);


	// 8  THREADS


	starttime = omp_get_wtime();
	parallelTranspose(A,ELEM,8);
	diff = omp_get_wtime() - starttime;
	printf("Parallel (8 Threads): %c %c: %f\n", ' ',' ', diff);

	// TO PRINT THE TRANSPOSED MATRIX UNCOMMENT THE PRINTF'S BELOW


	//printf("\n 3rd Transposed matrix \n");
	//printArray(A,ELEM);


	// 16  THREADS

	
	starttime = omp_get_wtime();
	parallelTranspose(A,ELEM,16);
	diff = omp_get_wtime() - starttime;
	printf("Parallel (16 Threads): %c %c: %f\n", ' ',' ', diff);

	// TO PRINT THE TRANSPOSED MATRIX UNCOMMENT THE PRINTF'S BELOW
	
	//printf("\n 4th Transposed matrix \n");
	//printArray(A,ELEM);




	// 64  THREADS
	
	
	starttime = omp_get_wtime();
	parallelTranspose(A,ELEM,64);
	diff = omp_get_wtime() - starttime;
	printf("Parallel (64 Threads): %c %c: %f\n", ' ',' ', diff);

	
	// TO PRINT THE TRANSPOSED MATRIX UNCOMMENT THE PRINTF'S BELOW
	
	//printf("\n 5th Transposed matrix \n");
	//printArray(A,ELEM);


	// 128  THREADS
	
	
	starttime = omp_get_wtime();
	parallelTranspose(A,ELEM,128);
	diff = omp_get_wtime() - starttime;
	printf("Parallel (128 Threads): %c %c: %f\n", ' ',' ', diff);

	
	// TO PRINT THE TRANSPOSED MATRIX UNCOMMENT THE PRINTF'S BELOW
	
	//printf("\n 6th Transposed matrix \n");
	//printArray(A,ELEM);

	// 8192  THREADS
	
	
	starttime = omp_get_wtime();
	parallelTranspose(A,ELEM,10000);
	diff = omp_get_wtime() - starttime;
	printf("Parallel (128 Threads): %c %c: %f\n", ' ',' ', diff);

	
	// TO PRINT THE TRANSPOSED MATRIX UNCOMMENT THE PRINTF'S BELOW
	
	//printf("\n 6th Transposed matrix \n");
	//printArray(A,ELEM);

	free(A);

	return 0;
}
