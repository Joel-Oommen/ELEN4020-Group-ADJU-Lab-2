#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <math.h>
#include <stdbool.h>
#include <sys/time.h>
struct information
{
	int counter;
	int dimension;
	int* Arr;
};

void* transposeMatrix(void* thread);

int main() 
{
	int numOfThreads = 8;
	int arraySize = 64;
	int dimension = 8;
	int Arr[arraySize];
	int division = arraySize/numOfThreads;
	pthread_t thread[numOfThreads];
	struct information threadArgument[numOfThreads];
	
	for(int i = 0; i < arraySize; i++)
		Arr[i] = i + 1;
	
	
	
	
	for(int i = 0; i < 8; i++)
	{
		for(int j = 0; j < 8; j++)
		{
			printf("%d \t",Arr[i*8 + j]);
		}printf("\n");
	}
	printf("\n");
	printf("\n");
	
	
	for(int i = 0; i < division; i++)
	{
		threadArgument[i].dimension = dimension;
		threadArgument[i].counter = i;
		threadArgument[i].Arr = Arr;
		
	}
	
	for(int i = 0; i < division; i++)
	{
		pthread_create (&thread[i], NULL, &transposeMatrix,&threadArgument[i]);	
	}
	
	for(int i = 0; i < division; i++)
	{
		pthread_join (thread[i], NULL);	
	}
	
	
	for(int i = 0; i < 8; i++)
	{
		for(int j = 0; j < 8; j++)
		{
			printf("%d \t",Arr[i*8 + j]);
		}printf("\n");
	}
	printf("\n");
	printf("\n");
	
	
}

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

void* transposeMatrix(void* thread)
{
	struct information *info;
	info = (struct information *)thread;
	
	int counter = info->counter;
	int dimension = info->dimension;
	int* Arr = info->Arr;
	
	/*
	int j = counter;
	int temp;
	for(int i = 0; i <j; i++)
	{
		temp = Arr[j*dimension + i];
		Arr[j*dimension + i] = Arr[i*dimension + j];
		Arr[i*dimension + j] = temp;
	}
	*/
	
}
