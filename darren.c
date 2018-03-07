#include <stdlib.h>
#include <stdio.h>
#include "omp.h"
#include <time.h>

void swap_int(int *x, int *y) {int tmp = *x;*x=*y;*y=tmp;}

#define ELEM 14000

int main()
{
	
	struct timeval begin,end;
	

	double elmn=14000;
	int *A = (int *)malloc(elmn*elmn*sizeof(int));
	


	int c=0;
	//printf("\n Original matrix \n");
	for(int i=0;i<ELEM;i++)
	{
		for(int j=0;j<ELEM;j++)
		{
			A[i*ELEM+j]=++c;
			//printf("%d \t", A[i*ELEM+j]);
		}
		//printf("\n");
	}
	
	
	gettimeofday(&begin,NULL);
	for(int n=0;n<ELEM;n++)
	{
		for(int m=n+1;m<ELEM;m++)
		{
			swap_int(&A[n*ELEM+m],&A[m*ELEM+n]);
					
		}
	}
	gettimeofday(&end,NULL);
	double time1 = (end.tv_sec - begin.tv_sec)+((end.tv_usec-begin.tv_usec)/1000000.0);
	printf("%s %f \n","Parallel ",time1);
	

	//printf("\n 1st Transpose matrix \n");
	for(int i=0;i<ELEM;i++)
	{
		for(int j=0;j<ELEM;j++)
		{
			
			//printf("%d \t", A[i*ELEM+j]);
		}
		//printf("\n");
	}

	 

	int h=ELEM-1;
	int i=0;
	int k=0;
	int j=1;

	gettimeofday(&begin,NULL);

	#pragma omp parallel for schedule(dynamic,1) num_threads(512)
	{ 
		for (int n=0;n<45;n++)
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
	
	gettimeofday(&end,NULL);
	double time2 = (end.tv_sec - begin.tv_sec)+((end.tv_usec-begin.tv_usec)/1000000.0);
	printf("%s %f \n","Parallel ",time2);
	


	//printf("\n UNTranspose matrix \n");
	for(int i=0;i<ELEM;i++)
	{
		for(int j=0;j<ELEM;j++)
		{
			
			//printf("%d \t", A[i*ELEM+j]);
		}
		//printf("\n");
	}




	free(A);

	return 0;
}
