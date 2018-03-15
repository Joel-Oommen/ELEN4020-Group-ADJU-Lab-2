#include <stdlib.h>
#include <stdio.h>
#include "omp.h"
#include <time.h>
#include <stdbool.h>

void swap_int(int *x, int *y) {int tmp = *x;*x=*y;*y=tmp;}



void populateArray(int *A, int dimension)
{

	int ELEM = dimension;
	for(int i=0;i<ELEM;i++)
	{
		for(int j=0;j<ELEM;j++)
		{
			A[i*ELEM+j]=i*ELEM+j;
		}
	}
}

bool checkTranspose(int *A,int *B, int dimension)
{
	bool equal = true;
	int ELEM = dimension;
	for(int i=0;i<ELEM;i++)
	{
		for(int j=0;j<ELEM;j++)
		{
			if (A[i*ELEM+j]!=B[i*ELEM+j])
			{
				equal=false;
			}
		}
	}
	return equal;
}

void printArray(int *A, int dimension)
{

	int ELEM = dimension;
	for(int i=0;i<ELEM;i++)
	{
		for(int j=0;j<ELEM;j++)
		{
			printf("%d \t", A[i*ELEM+j]);
		}
		printf("\n");
	}
}

void linearTranspose(int *A, int dimension)
{
	int ELEM = dimension;
	int tmp;
	for(int i=0;i<ELEM;i++)
	{
		
		for(int j=i+1;j<ELEM;j++)
		{
			tmp = A[i*ELEM+j];
               		A[i*ELEM+j] = A[j*ELEM+i];
                	A[j*ELEM+i] = tmp;
					
		}
	}
}

void parallelTranspose(int *A, int dimension,int numThreads)
{
	int ELEM =dimension;
	int i, j,tmp;
    	#pragma omp parallel shared(A) private( i, j,tmp) num_threads(numThreads)
    	{
        	#pragma omp for schedule(dynamic,1)  nowait
        	for (i = 0; i < ELEM - 1; i++) 
		{
            		for (j = i + 1; j < ELEM; j++) 
			{
                		tmp = A[i*ELEM+j];
               		 	A[i*ELEM+j] = A[j*ELEM+i];
                		A[j*ELEM+i] = tmp;
            		}
        	}
    	}




}


#define ELEM 8192
#define numOfThreads 128


int main()
{	

	// CREATE AND PRINT ORIGINAL MATRIX;
	double elmn=ELEM;
	int * A;
    	A = malloc(elmn * elmn*sizeof(int));
	int * B;
    	B = malloc(elmn * elmn*sizeof(int));
	int * C;
    	C = malloc(elmn * elmn*sizeof(int));
	// If you wish to print the matrix to test that the transpose works 
	// you uncomment the print function below.


	populateArray(A,ELEM);
	
	populateArray(B,ELEM);

	populateArray(C,ELEM);
	
	// A, B, and C are equal now 

	linearTranspose(B,ELEM);
	
	// B is now a Test transpose of A used to check if the transposes took place correctly.

	// C is the original A matrix also used for testing if transpose took place correctly.

	
	
	// TO PRINT THE ORIGINAL MATRIX UNCOMMENT THE PRINTF'S BELOW

	//printf("\n Original matrix \n");
	//printArray(A,ELEM);



	//-----------------------------------------------------------------------------------------



	// LINEAR TRANSPOSE
	// THIS IS WHERE THE LINEAR TRANSPOSE TAKES PLACE.

	double starttime = omp_get_wtime();
    	linearTranspose(A,ELEM);
	double diff = omp_get_wtime() - starttime;
	
	bool x;

	//Check transpose took place correctly. 

	x=checkTranspose(A,B,ELEM);
	


	// TO PRINT THE TRANSPOSED MATRIX UNCOMMENT THE PRINTF'S BELOW


	//printf("\n 1st Transposed matrix \n");
	//printArray(A,ELEM);
	
	

	// Display Time of Linear transpose and check of transpose was succesful.

	printf("Linear: %f \n", diff);
	
	printf("Matrix transposed correctly: %s \n", x?"true":"false");



	//-----------------------------------------------------------------------------------------




	// PARALLEL TRANSPOSE
	// THIS IS WHERE THE PARALLEL TRANSPOSE TAKES PLACE.
	printf("\n ");


	// 4  THREADS


	starttime = omp_get_wtime();
	parallelTranspose(A,ELEM,4);
	diff = omp_get_wtime() - starttime;
	
	// A matrix is now transposed back to its original form and 
	//should be equal to transpose tester matrix C

 	x=checkTranspose(A,C,ELEM);
	
	// TO PRINT THE TRANSPOSED MATRIX UNCOMMENT THE PRINTF'S BELOW

	//printf("\n 2nd Transposed matrix \n");
	//printArray(A,ELEM);

	printf("Parallel (%d Threads): %f\n",4, diff);
	
	printf("Matrix transposed correctly: %s \n", x?"true":"false");
	
	
	//-----------------------------------------------------------------------------------------


	// 8  THREADS


	starttime = omp_get_wtime();
	parallelTranspose(A,ELEM,8);
	diff = omp_get_wtime() - starttime;
	
	// A matrix is now transposed and should be equal to transpose tester matrix B

 	x=checkTranspose(A,B,ELEM);
	
	// TO PRINT THE TRANSPOSED MATRIX UNCOMMENT THE PRINTF'S BELOW

	//printf("\n 3rd Transposed matrix \n");
	//printArray(A,ELEM);

	printf("Parallel (%d Threads): %f\n",8, diff);
	
	printf("Matrix transposed correctly: %s \n", x?"true":"false");


	//-----------------------------------------------------------------------------------------


	// 16  THREADS


	starttime = omp_get_wtime();
	parallelTranspose(A,ELEM,16);
	diff = omp_get_wtime() - starttime;
	
	// A matrix is now transposed back to its original form and 
	//should be equal to transpose tester matrix C

 	x=checkTranspose(A,C,ELEM);
	
	// TO PRINT THE TRANSPOSED MATRIX UNCOMMENT THE PRINTF'S BELOW

	//printf("\n 4th Transposed matrix \n");
	//printArray(A,ELEM);

	printf("Parallel (%d Threads): %f\n",16, diff);
	
	printf("Matrix transposed correctly: %s \n", x?"true":"false");
	
	
	//-----------------------------------------------------------------------------------------


	// 64  THREADS


	starttime = omp_get_wtime();
	parallelTranspose(A,ELEM,64);
	diff = omp_get_wtime() - starttime;
	
	// A matrix is now transposed and should be equal to transpose tester matrix B

 	x=checkTranspose(A,B,ELEM);
	
	// TO PRINT THE TRANSPOSED MATRIX UNCOMMENT THE PRINTF'S BELOW

	//printf("\n 5th Transposed matrix \n");
	//printArray(A,ELEM);

	printf("Parallel (%d Threads): %f\n",64, diff);
	
	printf("Matrix transposed correctly: %s \n", x?"true":"false");


	//-----------------------------------------------------------------------------------------


	// 128  THREADS


	starttime = omp_get_wtime();
	parallelTranspose(A,ELEM,128);
	diff = omp_get_wtime() - starttime;
	
	// A matrix is now transposed back to its original form and 
	//should be equal to transpose tester matrix C

 	x=checkTranspose(A,C,ELEM);
	
	// TO PRINT THE TRANSPOSED MATRIX UNCOMMENT THE PRINTF'S BELOW

	//printf("\n 6nd Transposed matrix \n");
	//printArray(A,ELEM);

	printf("Parallel (%d Threads): %f\n",128, diff);
	
	printf("Matrix transposed correctly: %s \n", x?"true":"false");
	
	
	//-----------------------------------------------------------------------------------------




	

	


	free(A);
	free(C);
	free(B);

	return 0;
}
