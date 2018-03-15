#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <math.h>
#include <stdbool.h>
#include <sys/time.h>
#include "omp.h"
#include <time.h>
struct information
{
	int lowerBound;
	int upperBound;
	int dimension;
	int* Arr;
};

void* transposeMatrix(void* thread);
int upperBound(int arrSize, int BinNumber, int NumberOfDivisions);
int lowerBound(int arrSize, int BinNumber, int NumberOfDivisions);

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

int main() 
{
	int numOfThreads =128;
	int dimension =8192;
	int arraySize = dimension*dimension;
	int * Arr =malloc(arraySize*sizeof(int));
	int * B =malloc(arraySize*sizeof(int));
	int division = arraySize/numOfThreads;
	pthread_t thread[numOfThreads];
	struct information threadArgument[numOfThreads];
	
	for(int i = 0; i < dimension; i++)
	{
		for (int j = 0; j < dimension; j++)
		{
			B[j*dimension+i] = i*dimension+j;		
			Arr[i*dimension+j] = i*dimension+j;
		}
	}
	
	/*
	for(int i = 0; i < dimension; i++)
	{
		for(int j = 0; j < dimension; j++)
		{
			printf("%d \t ",Arr[i*dimension + j]);
			
		}printf("\n");
	}
	printf("\n");
	
	for(int i = 0; i < dimension; i++)
	{
		for(int j = 0; j < dimension; j++)
		{
			printf("%d \t ",B[i*dimension + j]);
			
		}printf("\n");
	}
	printf("\n");
	*/
	printf("\n");
	
	
	for(int i = 0; i < numOfThreads; i++)
	{
		threadArgument[i].dimension = dimension;
		threadArgument[i].lowerBound = lowerBound(dimension, i, numOfThreads);
		threadArgument[i].upperBound = upperBound(dimension, i, numOfThreads);
		threadArgument[i].Arr = Arr;
		
	}


	double starttime = omp_get_wtime();

	for(int i = 0; i < numOfThreads; i++)
	{
		pthread_create (&thread[i], NULL, &transposeMatrix,&threadArgument[i]);	
	}


	for(int i = 0; i < numOfThreads; i++)
	{
		pthread_join (thread[i], NULL);	
	}
	
	double diff = omp_get_wtime() - starttime;

	printf("Pthread: %f \n", diff);


	bool x;

	//Check transpose took place correctly. 

	x=checkTranspose(Arr,B,dimension);

	printf("Matrix transposed correctly: %s \n", x?"true":"false");
	
	/*
	
	for(int i = 0; i < dimension; i++)
	{
		for(int j = 0; j < dimension; j++)
		{
			printf("%d \t",Arr[i*dimension + j]);
		}printf("\n");
	}
	printf("\n");

	*/
	printf("\n");
	
	
}

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

void* transposeMatrix(void* thread)
{
	struct information *info;
	info = (struct information *)thread;
	
	
	int lowerBound = info->lowerBound;
	int upperBound = info->upperBound;
	int dimension = info->dimension;
	int* Arr = info->Arr;
	/*printf("%d \n", upperBound);*/
	int temp;
	for(int j = lowerBound; j < upperBound+1; j++)
	{
		
		for(int i = 0; i <j; i++)
		{
			temp = Arr[j*dimension + i];
			Arr[j*dimension + i] = Arr[i*dimension + j];
			Arr[i*dimension + j] = temp;		
		}
		
	}
}

int upperBound(int dimension, int BinNumber, int NumberOfDivisions)
{
	/*printf("%s \n", "1");*/
	int BinSize = floor(dimension/NumberOfDivisions);
	int UB = BinSize*(BinNumber + 1) - 1;
	return UB;
}


int lowerBound(int dimension, int BinNumber, int NumberOfDivisions)
{
	int BinSize = floor(dimension/NumberOfDivisions);
	int LB = BinSize*BinNumber;
	return LB;
}





