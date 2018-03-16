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

#define MAX_ELEM 8192
#define MAX_THREAD 128

int main() 
{
//%%%%%%%%%%%%%%%%%%%%%%%%%%128 ELEMENTS%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	int numOfThreads =4;
	int dimension =128;
	printf("\n %d Elements \n",dimension);
	int arraySize = dimension*dimension;
	int * Arr =malloc(MAX_ELEM*MAX_ELEM*sizeof(int));
	int * B =malloc(MAX_ELEM*MAX_ELEM*sizeof(int));
	int division = arraySize/numOfThreads;
	pthread_t thread[MAX_THREAD];
	struct information threadArgument[MAX_THREAD];
	
	for(int i = 0; i < dimension; i++)
	{
		for (int j = 0; j < dimension; j++)
		{
			B[j*dimension+i] = i*dimension+j;		
			Arr[i*dimension+j] = i*dimension+j;
		}
	}
		
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
	double times[15];
	int i=0;
	times[i++]=diff;
	printf("%d Threads\n",numOfThreads);


	bool x;

	//Check transpose took place correctly. 

	x=checkTranspose(Arr,B,dimension);

	printf("Matrix transposed correctly: %s \n", x?"true":"false");
	
	//8 threads
	numOfThreads =8;
	division = arraySize/numOfThreads;
	
	for(int i = 0; i < dimension; i++)
	{
		for (int j = 0; j < dimension; j++)
		{
			B[j*dimension+i] = i*dimension+j;		
			Arr[i*dimension+j] = i*dimension+j;
		}
	}
		
	for(int i = 0; i < numOfThreads; i++)
	{
		threadArgument[i].dimension = dimension;
		threadArgument[i].lowerBound = lowerBound(dimension, i, numOfThreads);
		threadArgument[i].upperBound = upperBound(dimension, i, numOfThreads);
		threadArgument[i].Arr = Arr;
		
	}


	starttime = omp_get_wtime();

	for(int i = 0; i < numOfThreads; i++)
	{
		pthread_create (&thread[i], NULL, &transposeMatrix,&threadArgument[i]);	
	}


	for(int i = 0; i < numOfThreads; i++)
	{
		pthread_join (thread[i], NULL);	
	}
	
	diff = omp_get_wtime() - starttime;
	times[i++]=diff;
	printf("%d Threads\n",numOfThreads);
	//Check transpose took place correctly. 
	x=checkTranspose(Arr,B,dimension);
	printf("Matrix transposed correctly: %s \n", x?"true":"false");
	//16 threads
	numOfThreads =16;
	division = arraySize/numOfThreads;
	
	for(int i = 0; i < dimension; i++)
	{
		for (int j = 0; j < dimension; j++)
		{
			B[j*dimension+i] = i*dimension+j;		
			Arr[i*dimension+j] = i*dimension+j;
		}
	}
		
	for(int i = 0; i < numOfThreads; i++)
	{
		threadArgument[i].dimension = dimension;
		threadArgument[i].lowerBound = lowerBound(dimension, i, numOfThreads);
		threadArgument[i].upperBound = upperBound(dimension, i, numOfThreads);
		threadArgument[i].Arr = Arr;
		
	}


	starttime = omp_get_wtime();

	for(int i = 0; i < numOfThreads; i++)
	{
		pthread_create (&thread[i], NULL, &transposeMatrix,&threadArgument[i]);	
	}


	for(int i = 0; i < numOfThreads; i++)
	{
		pthread_join (thread[i], NULL);	
	}
	
	diff = omp_get_wtime() - starttime;
	times[i++]=diff;
	printf("%d Threads\n",numOfThreads);
	//Check transpose took place correctly. 
	x=checkTranspose(Arr,B,dimension);
	printf("Matrix transposed correctly: %s \n", x?"true":"false");
	//64 threads
	numOfThreads =64;
	division = arraySize/numOfThreads;
	
	for(int i = 0; i < dimension; i++)
	{
		for (int j = 0; j < dimension; j++)
		{
			B[j*dimension+i] = i*dimension+j;		
			Arr[i*dimension+j] = i*dimension+j;
		}
	}
		
	for(int i = 0; i < numOfThreads; i++)
	{
		threadArgument[i].dimension = dimension;
		threadArgument[i].lowerBound = lowerBound(dimension, i, numOfThreads);
		threadArgument[i].upperBound = upperBound(dimension, i, numOfThreads);
		threadArgument[i].Arr = Arr;
		
	}


	starttime = omp_get_wtime();

	for(int i = 0; i < numOfThreads; i++)
	{
		pthread_create (&thread[i], NULL, &transposeMatrix,&threadArgument[i]);	
	}


	for(int i = 0; i < numOfThreads; i++)
	{
		pthread_join (thread[i], NULL);	
	}
	
	diff = omp_get_wtime() - starttime;
	times[i++]=diff;
	printf("%d Threads\n",numOfThreads);
	//Check transpose took place correctly. 
	x=checkTranspose(Arr,B,dimension);
	printf("Matrix transposed correctly: %s \n", x?"true":"false");
	//128 threads
	numOfThreads =128;
	division = arraySize/numOfThreads;
	
	for(int i = 0; i < dimension; i++)
	{
		for (int j = 0; j < dimension; j++)
		{
			B[j*dimension+i] = i*dimension+j;		
			Arr[i*dimension+j] = i*dimension+j;
		}
	}
		
	for(int i = 0; i < numOfThreads; i++)
	{
		threadArgument[i].dimension = dimension;
		threadArgument[i].lowerBound = lowerBound(dimension, i, numOfThreads);
		threadArgument[i].upperBound = upperBound(dimension, i, numOfThreads);
		threadArgument[i].Arr = Arr;
		
	}


	starttime = omp_get_wtime();

	for(int i = 0; i < numOfThreads; i++)
	{
		pthread_create (&thread[i], NULL, &transposeMatrix,&threadArgument[i]);	
	}


	for(int i = 0; i < numOfThreads; i++)
	{
		pthread_join (thread[i], NULL);	
	}
	
	diff = omp_get_wtime() - starttime;
	times[i++]=diff;
	printf("%d Threads\n",numOfThreads);
	//Check transpose took place correctly. 
	x=checkTranspose(Arr,B,dimension);
	printf("Matrix transposed correctly: %s \n", x?"true":"false");
//%%%%%%%%%%%%%%%%%%%%%%%%%%1024 ELEMENTS%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	numOfThreads =4;
	dimension =1024;
	printf("\n %d Elements \n",dimension);
	arraySize = dimension*dimension;
	division = arraySize/numOfThreads;
	
	for(int i = 0; i < dimension; i++)
	{
		for (int j = 0; j < dimension; j++)
		{
			B[j*dimension+i] = i*dimension+j;		
			Arr[i*dimension+j] = i*dimension+j;
		}
	}
		
	for(int i = 0; i < numOfThreads; i++)
	{
		threadArgument[i].dimension = dimension;
		threadArgument[i].lowerBound = lowerBound(dimension, i, numOfThreads);
		threadArgument[i].upperBound = upperBound(dimension, i, numOfThreads);
		threadArgument[i].Arr = Arr;
		
	}


	starttime = omp_get_wtime();

	for(int i = 0; i < numOfThreads; i++)
	{
		pthread_create (&thread[i], NULL, &transposeMatrix,&threadArgument[i]);	
	}


	for(int i = 0; i < numOfThreads; i++)
	{
		pthread_join (thread[i], NULL);	
	}
	
	diff = omp_get_wtime() - starttime;
	times[i++]=diff;
	printf("%d Threads\n",numOfThreads);

	//Check transpose took place correctly. 

	x=checkTranspose(Arr,B,dimension);

	printf("Matrix transposed correctly: %s \n", x?"true":"false");
	
	//8 threads
	numOfThreads =8;
	division = arraySize/numOfThreads;
	
	for(int i = 0; i < dimension; i++)
	{
		for (int j = 0; j < dimension; j++)
		{
			B[j*dimension+i] = i*dimension+j;		
			Arr[i*dimension+j] = i*dimension+j;
		}
	}
		
	for(int i = 0; i < numOfThreads; i++)
	{
		threadArgument[i].dimension = dimension;
		threadArgument[i].lowerBound = lowerBound(dimension, i, numOfThreads);
		threadArgument[i].upperBound = upperBound(dimension, i, numOfThreads);
		threadArgument[i].Arr = Arr;
		
	}


	starttime = omp_get_wtime();

	for(int i = 0; i < numOfThreads; i++)
	{
		pthread_create (&thread[i], NULL, &transposeMatrix,&threadArgument[i]);	
	}


	for(int i = 0; i < numOfThreads; i++)
	{
		pthread_join (thread[i], NULL);	
	}
	
	diff = omp_get_wtime() - starttime;
	times[i++]=diff;
	printf("%d Threads\n",numOfThreads);
	//Check transpose took place correctly. 
	x=checkTranspose(Arr,B,dimension);
	printf("Matrix transposed correctly: %s \n", x?"true":"false");
	//16 threads
	numOfThreads =16;
	division = arraySize/numOfThreads;
	
	for(int i = 0; i < dimension; i++)
	{
		for (int j = 0; j < dimension; j++)
		{
			B[j*dimension+i] = i*dimension+j;		
			Arr[i*dimension+j] = i*dimension+j;
		}
	}
		
	for(int i = 0; i < numOfThreads; i++)
	{
		threadArgument[i].dimension = dimension;
		threadArgument[i].lowerBound = lowerBound(dimension, i, numOfThreads);
		threadArgument[i].upperBound = upperBound(dimension, i, numOfThreads);
		threadArgument[i].Arr = Arr;
		
	}


	starttime = omp_get_wtime();

	for(int i = 0; i < numOfThreads; i++)
	{
		pthread_create (&thread[i], NULL, &transposeMatrix,&threadArgument[i]);	
	}


	for(int i = 0; i < numOfThreads; i++)
	{
		pthread_join (thread[i], NULL);	
	}
	
	diff = omp_get_wtime() - starttime;
	times[i++]=diff;
	printf("%d Threads\n",numOfThreads);
	//Check transpose took place correctly. 
	x=checkTranspose(Arr,B,dimension);
	printf("Matrix transposed correctly: %s \n", x?"true":"false");
	//64 threads
	numOfThreads =64;
	division = arraySize/numOfThreads;
	
	for(int i = 0; i < dimension; i++)
	{
		for (int j = 0; j < dimension; j++)
		{
			B[j*dimension+i] = i*dimension+j;		
			Arr[i*dimension+j] = i*dimension+j;
		}
	}
		
	for(int i = 0; i < numOfThreads; i++)
	{
		threadArgument[i].dimension = dimension;
		threadArgument[i].lowerBound = lowerBound(dimension, i, numOfThreads);
		threadArgument[i].upperBound = upperBound(dimension, i, numOfThreads);
		threadArgument[i].Arr = Arr;
		
	}


	starttime = omp_get_wtime();

	for(int i = 0; i < numOfThreads; i++)
	{
		pthread_create (&thread[i], NULL, &transposeMatrix,&threadArgument[i]);	
	}


	for(int i = 0; i < numOfThreads; i++)
	{
		pthread_join (thread[i], NULL);	
	}
	
	diff = omp_get_wtime() - starttime;
	times[i++]=diff;
	printf("%d Threads\n",numOfThreads);
	//Check transpose took place correctly. 
	x=checkTranspose(Arr,B,dimension);
	printf("Matrix transposed correctly: %s \n", x?"true":"false");
	//128 threads
	numOfThreads =128;
	division = arraySize/numOfThreads;
	
	for(int i = 0; i < dimension; i++)
	{
		for (int j = 0; j < dimension; j++)
		{
			B[j*dimension+i] = i*dimension+j;		
			Arr[i*dimension+j] = i*dimension+j;
		}
	}
		
	for(int i = 0; i < numOfThreads; i++)
	{
		threadArgument[i].dimension = dimension;
		threadArgument[i].lowerBound = lowerBound(dimension, i, numOfThreads);
		threadArgument[i].upperBound = upperBound(dimension, i, numOfThreads);
		threadArgument[i].Arr = Arr;
		
	}


	starttime = omp_get_wtime();

	for(int i = 0; i < numOfThreads; i++)
	{
		pthread_create (&thread[i], NULL, &transposeMatrix,&threadArgument[i]);	
	}


	for(int i = 0; i < numOfThreads; i++)
	{
		pthread_join (thread[i], NULL);	
	}
	
	diff = omp_get_wtime() - starttime;
	times[i++]=diff;
	printf("%d Threads\n",numOfThreads);
	//Check transpose took place correctly. 
	x=checkTranspose(Arr,B,dimension);
	printf("Matrix transposed correctly: %s \n", x?"true":"false");
//%%%%%%%%%%%%%%%%%%%%%%%%%%8192 ELEMENTS%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	numOfThreads =4;
	dimension =8192;
	printf("\n %d Elements \n",dimension);
	arraySize = dimension*dimension;
	division = arraySize/numOfThreads;
	
	for(int i = 0; i < dimension; i++)
	{
		for (int j = 0; j < dimension; j++)
		{
			B[j*dimension+i] = i*dimension+j;		
			Arr[i*dimension+j] = i*dimension+j;
		}
	}
		
	for(int i = 0; i < numOfThreads; i++)
	{
		threadArgument[i].dimension = dimension;
		threadArgument[i].lowerBound = lowerBound(dimension, i, numOfThreads);
		threadArgument[i].upperBound = upperBound(dimension, i, numOfThreads);
		threadArgument[i].Arr = Arr;
		
	}


	starttime = omp_get_wtime();

	for(int i = 0; i < numOfThreads; i++)
	{
		pthread_create (&thread[i], NULL, &transposeMatrix,&threadArgument[i]);	
	}


	for(int i = 0; i < numOfThreads; i++)
	{
		pthread_join (thread[i], NULL);	
	}
	
	diff = omp_get_wtime() - starttime;
	times[i++]=diff;
	printf("%d Threads\n",numOfThreads);

	//Check transpose took place correctly. 

	x=checkTranspose(Arr,B,dimension);

	printf("Matrix transposed correctly: %s \n", x?"true":"false");
	
	//8 threads
	numOfThreads =8;
	division = arraySize/numOfThreads;
	
	for(int i = 0; i < dimension; i++)
	{
		for (int j = 0; j < dimension; j++)
		{
			B[j*dimension+i] = i*dimension+j;		
			Arr[i*dimension+j] = i*dimension+j;
		}
	}
		
	for(int i = 0; i < numOfThreads; i++)
	{
		threadArgument[i].dimension = dimension;
		threadArgument[i].lowerBound = lowerBound(dimension, i, numOfThreads);
		threadArgument[i].upperBound = upperBound(dimension, i, numOfThreads);
		threadArgument[i].Arr = Arr;
		
	}


	starttime = omp_get_wtime();

	for(int i = 0; i < numOfThreads; i++)
	{
		pthread_create (&thread[i], NULL, &transposeMatrix,&threadArgument[i]);	
	}


	for(int i = 0; i < numOfThreads; i++)
	{
		pthread_join (thread[i], NULL);	
	}
	
	diff = omp_get_wtime() - starttime;
	times[i++]=diff;
	printf("%d Threads\n",numOfThreads);
	//Check transpose took place correctly. 
	x=checkTranspose(Arr,B,dimension);
	printf("Matrix transposed correctly: %s \n", x?"true":"false");
	//16 threads
	numOfThreads =16;
	division = arraySize/numOfThreads;
	
	for(int i = 0; i < dimension; i++)
	{
		for (int j = 0; j < dimension; j++)
		{
			B[j*dimension+i] = i*dimension+j;		
			Arr[i*dimension+j] = i*dimension+j;
		}
	}
		
	for(int i = 0; i < numOfThreads; i++)
	{
		threadArgument[i].dimension = dimension;
		threadArgument[i].lowerBound = lowerBound(dimension, i, numOfThreads);
		threadArgument[i].upperBound = upperBound(dimension, i, numOfThreads);
		threadArgument[i].Arr = Arr;
		
	}


	starttime = omp_get_wtime();

	for(int i = 0; i < numOfThreads; i++)
	{
		pthread_create (&thread[i], NULL, &transposeMatrix,&threadArgument[i]);	
	}


	for(int i = 0; i < numOfThreads; i++)
	{
		pthread_join (thread[i], NULL);	
	}
	
	diff = omp_get_wtime() - starttime;
	times[i++]=diff;
	printf("%d Threads\n",numOfThreads);
	//Check transpose took place correctly. 
	x=checkTranspose(Arr,B,dimension);
	printf("Matrix transposed correctly: %s \n", x?"true":"false");
	//64 threads
	numOfThreads =64;
	division = arraySize/numOfThreads;
	
	for(int i = 0; i < dimension; i++)
	{
		for (int j = 0; j < dimension; j++)
		{
			B[j*dimension+i] = i*dimension+j;		
			Arr[i*dimension+j] = i*dimension+j;
		}
	}
		
	for(int i = 0; i < numOfThreads; i++)
	{
		threadArgument[i].dimension = dimension;
		threadArgument[i].lowerBound = lowerBound(dimension, i, numOfThreads);
		threadArgument[i].upperBound = upperBound(dimension, i, numOfThreads);
		threadArgument[i].Arr = Arr;
		
	}


	starttime = omp_get_wtime();

	for(int i = 0; i < numOfThreads; i++)
	{
		pthread_create (&thread[i], NULL, &transposeMatrix,&threadArgument[i]);	
	}


	for(int i = 0; i < numOfThreads; i++)
	{
		pthread_join (thread[i], NULL);	
	}
	
	diff = omp_get_wtime() - starttime;
	times[i++]=diff;
	printf("%d Threads\n",numOfThreads);
	//Check transpose took place correctly. 
	x=checkTranspose(Arr,B,dimension);
	printf("Matrix transposed correctly: %s \n", x?"true":"false");
	//128 threads
	numOfThreads =128;
	division = arraySize/numOfThreads;
	
	for(int i = 0; i < dimension; i++)
	{
		for (int j = 0; j < dimension; j++)
		{
			B[j*dimension+i] = i*dimension+j;		
			Arr[i*dimension+j] = i*dimension+j;
		}
	}
		
	for(int i = 0; i < numOfThreads; i++)
	{
		threadArgument[i].dimension = dimension;
		threadArgument[i].lowerBound = lowerBound(dimension, i, numOfThreads);
		threadArgument[i].upperBound = upperBound(dimension, i, numOfThreads);
		threadArgument[i].Arr = Arr;
		
	}


	starttime = omp_get_wtime();

	for(int i = 0; i < numOfThreads; i++)
	{
		pthread_create (&thread[i], NULL, &transposeMatrix,&threadArgument[i]);	
	}


	for(int i = 0; i < numOfThreads; i++)
	{
		pthread_join (thread[i], NULL);	
	}
	
	diff = omp_get_wtime() - starttime;
	times[i++]=diff;
	printf("%d Threads\n",numOfThreads);
	//Check transpose took place correctly. 
	x=checkTranspose(Arr,B,dimension);
	printf("Matrix transposed correctly: %s \n", x?"true":"false");
//_________________________________________________________________________________________________________________________________________
	printf("\nTimes\n");
	printf("\t \t 128\t \t 1024\t \t 8192\n");
	printf("4 threads\t %f\t %f\t %f\n",times[0],times[5],times[10]);
	printf("8 threads\t %f\t %f\t %f\n",times[1],times[6],times[11]);
	printf("16 threads\t %f\t %f\t %f\n",times[2],times[7],times[12]);
	printf("64 threads\t %f\t %f\t %f\n",times[3],times[8],times[13]);
	printf("128 threads\t %f\t %f\t %f\n",times[4],times[9],times[14]);
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





