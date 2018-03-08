#include <stdlib.h>
#include <stdio.h>
#include "omp.h"
#include <time.h>

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
	for(int n=0;n<ELEM;n++)
	{
		
		for(int m=n+1;m<ELEM;m++)
		{
			//printf("%d \n",m);			
			swap_int(&A[n*ELEM+m],&A[m*ELEM+n]);
					
		}
	}
}

void parallelTranspose(int *A, int dimension,int numThreads)
{
	int ELEM =dimension;
	int h=ELEM-1;
	int i=0;
	int k=0;
	int j=1;
	int looplimit = 0.5*(ELEM*ELEM)-0.5*ELEM;
	
	int n;
	


	#pragma omp parallel for num_threads(numThreads) shared(A) shared(i,j) schedule(dynamic,1)
		for ( n=0;n<looplimit;n++)
		{	
		
			if (k!=0)
			{
				if (k%h==0){i++; h--;k=0;j=i+1;}
			
			} 
			swap_int(&A[i*ELEM+j],&A[j*ELEM+i]);
		
			j++;
			if (k<=h){k++;}
			
		}
}


#define ELEM 10

int main()
{	

	double elmn=ELEM;
	int *A = (int *)malloc(elmn*elmn*sizeof(int));
	

	// CREATE AND PRINT ORIGINAL MATRIX;
	// If you wish to print the matrix to test that the transpose works 
	// you uncomment the print function below.


	populateArray(A,ELEM);

	printf("\n Original matrix \n");
	printArray(A,ELEM);



	// LINEAR TRANSPOSE
	// THIS IS WHERE THE LINEAR TRANSPOSE TAKES PLACE.

	clock_t starttime,stoptime,starttime2,stoptime2;

	starttime =clock();

	linearTranspose(A,ELEM);
	
	stoptime =clock();
	
	double diff = (double)(stoptime-starttime)/1000000;
		


	// TO PRINT THE TRANSPOSED MATRIX UNCOMMENT THE PRINTF'S BELOW


	printf("\n 1st Transposed matrix \n");
	printArray(A,ELEM);

	 


	// PARALLEL TRANSPOSE
	// THIS IS WHERE THE PARALLEL TRANSPOSE TAKES PLACE.


	// 1  THREAD
	
	starttime2 =clock();

	parallelTranspose(A,ELEM,1);

	stoptime2 =clock();	
	double diff2 = (double)(stoptime2-starttime2)/1000000;
	printf("%s %f \n","Linear ",diff);
	printf("%s %f \n","Parallel1 ",diff2);
	
	// TO PRINT THE TRANSPOSED MATRIX UNCOMMENT THE PRINTF'S BELOW

	printf("\n 2nd Transposed matrix \n");
	printArray(A,ELEM);
	

	// 4  THREADS

	starttime2 =clock();

	parallelTranspose(A,ELEM,4);

	stoptime2 =clock();	
	diff2 = (double)(stoptime2-starttime2)/1000000;
	
	printf("%s %f \n","Parallel4 ",diff2);


	// TO PRINT THE TRANSPOSED MATRIX UNCOMMENT THE PRINTF'S BELOW


	printf("\n 3rd Transposed matrix \n");
	printArray(A,ELEM);

	// 128  THREADS

	starttime2 =clock();

	parallelTranspose(A,ELEM,128);
	
	stoptime2 =clock();	
	diff2 = (double)(stoptime2-starttime2)/1000000;
	
	printf("%s %f \n","Parallel128 ",diff2);


	// TO PRINT THE TRANSPOSED MATRIX UNCOMMENT THE PRINTF'S BELOW
	
	printf("\n 4th Transposed matrix \n");
	printArray(A,ELEM);

	// 1024  THREADS



	starttime2 =clock();

	parallelTranspose(A,ELEM,1024);
	
	stoptime2 =clock();	
	diff2 = (double)(stoptime2-starttime2)/1000000;
	
	printf("%s %f \n","Parallel1024 ",diff2);


	// TO PRINT THE TRANSPOSED MATRIX UNCOMMENT THE PRINTF'S BELOW
	
	printf("\n 5th Transposed matrix \n");
	printArray(A,ELEM);




	free(A);

	return 0;
}
