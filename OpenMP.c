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


#define MAX_ELEM 8192

int main()
{	
//%%%%%%%%%%%%%%%%%%%%%%%%%%128 ELEMENTS%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	int ELEM = 128;
	printf("\n %d Elements \n",ELEM);
	// CREATE AND PRINT ORIGINAL MATRIX;
	double elmn=MAX_ELEM;
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
	double times[18];
	int i;
	bool x;

	//Check transpose took place correctly. 

	x=checkTranspose(A,B,ELEM);
	


	// TO PRINT THE TRANSPOSED MATRIX UNCOMMENT THE PRINTF'S BELOW


	//printf("\n 1st Transposed matrix \n");
	//printArray(A,ELEM);
	
	

	// Display Time of Linear transpose and check of transpose was succesful.

	printf("Linear\n");
	
	printf("Matrix transposed correctly: %s \n", x?"true":"false");
	times[i++]=diff;

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

	printf("Parallel (%d Threads)\n",4);
	
	printf("Matrix transposed correctly: %s \n", x?"true":"false");
	times[i++]=diff;
	
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

	printf("Parallel (%d Threads)\n",8);
	
	printf("Matrix transposed correctly: %s \n", x?"true":"false");
	times[i++]=diff;

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

	printf("Parallel (%d Threads)\n",16);
	
	printf("Matrix transposed correctly: %s \n", x?"true":"false");
	times[i++]=diff;
	
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

	printf("Parallel (%d Threads)\n",64);
	
	printf("Matrix transposed correctly: %s \n", x?"true":"false");
	times[i++]=diff;

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

	printf("Parallel (%d Threads)\n",128);
	
	printf("Matrix transposed correctly: %s \n", x?"true":"false");	
	times[i++]=diff;
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%1024 ELEMENTS%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	ELEM = 1024;
	printf("\n %d Elements \n",ELEM);
	
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

	starttime = omp_get_wtime();
    	linearTranspose(A,ELEM);
	diff = omp_get_wtime() - starttime;
	
	//Check transpose took place correctly. 

	x=checkTranspose(A,B,ELEM);
	


	// TO PRINT THE TRANSPOSED MATRIX UNCOMMENT THE PRINTF'S BELOW


	//printf("\n 1st Transposed matrix \n");
	//printArray(A,ELEM);
	
	

	// Display Time of Linear transpose and check of transpose was succesful.

	printf("Linear\n");
	
	printf("Matrix transposed correctly: %s \n", x?"true":"false");
	times[i++]=diff;


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

	printf("Parallel (%d Threads)\n",4);
	
	printf("Matrix transposed correctly: %s \n", x?"true":"false");
	times[i++]=diff;
	
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

	printf("Parallel (%d Threads)\n",8);
	
	printf("Matrix transposed correctly: %s \n", x?"true":"false");
	times[i++]=diff;

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

	printf("Parallel (%d Threads)\n",16);
	
	printf("Matrix transposed correctly: %s \n", x?"true":"false");
	times[i++]=diff;
	
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

	printf("Parallel (%d Threads)\n",64);
	
	printf("Matrix transposed correctly: %s \n", x?"true":"false");
	times[i++]=diff;

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

	printf("Parallel (%d Threads)\n",128);
	
	printf("Matrix transposed correctly: %s \n", x?"true":"false");
	times[i++]=diff;
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%8192 ELEMENTS%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	ELEM = 8192;
	printf("\n %d Elements \n",ELEM);
	
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

	starttime = omp_get_wtime();
    	linearTranspose(A,ELEM);
	diff = omp_get_wtime() - starttime;
	
	//Check transpose took place correctly. 

	x=checkTranspose(A,B,ELEM);
	


	// TO PRINT THE TRANSPOSED MATRIX UNCOMMENT THE PRINTF'S BELOW


	//printf("\n 1st Transposed matrix \n");
	//printArray(A,ELEM);
	
	

	// Display Time of Linear transpose and check of transpose was succesful.

	printf("Linear\n");
	
	printf("Matrix transposed correctly: %s \n", x?"true":"false");
	times[i++]=diff;


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

	printf("Parallel (%d Threads)\n",4);
	
	printf("Matrix transposed correctly: %s \n", x?"true":"false");
	times[i++]=diff;
	
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

	printf("Parallel (%d Threads)\n",8);
	
	printf("Matrix transposed correctly: %s \n", x?"true":"false");
	times[i++]=diff;

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

	printf("Parallel (%d Threads)\n",16);
	
	printf("Matrix transposed correctly: %s \n", x?"true":"false");
	times[i++]=diff;
	
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

	printf("Parallel (%d Threads)\n",64);
	
	printf("Matrix transposed correctly: %s \n", x?"true":"false");
	times[i++]=diff;

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

	printf("Parallel (%d Threads)\n",128);
	
	printf("Matrix transposed correctly: %s \n", x?"true":"false");
	times[i++]=diff;
//_________________________________________________________________________________________________________________________________________
	printf("\nTimes\n");
	printf("\t \t 128\t \t 1024\t \t 8192\n");
	printf("1 thread\t %f\t %f\t %f\n",times[0],times[6],times[12]);
	printf("4 threads\t %f\t %f\t %f\n",times[1],times[7],times[13]);
	printf("8 threads\t %f\t %f\t %f\n",times[2],times[8],times[14]);
	printf("16 threads\t %f\t %f\t %f\n",times[3],times[9],times[15]);
	printf("64 threads\t %f\t %f\t %f\n",times[4],times[10],times[16]);
	printf("128 threads\t %f\t %f\t %f\n",times[5],times[11],times[17]);
	free(A);
	free(C);
	free(B);
	return 0;
}
