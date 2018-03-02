#include <stdlib.h>
#include <stdio.h>

void swap_int(int *x, int *y) {int tmp = *x;*x=*y;*y=tmp;}

#define ELEM 4

int main()
{
	int A[ELEM][ELEM];
	int c=0;
	printf("\n Original matrix \n");
	for(int i=0;i<ELEM;i++)
	{
		for(int j=0;j<ELEM;j++)
		{
			A[i][j]=++c;
			printf("%d \t", A[i][j]);
		}
		printf("\n");
	}
	for(int n=0;n<ELEM;n++)
	{
		for(int m=n+1;m<ELEM;m++)
		{
			swap_int(&A[n][m],&A[m][n]);
		}
	}
	printf("\n Transpose matrix \n");
	for(int i=0;i<ELEM;i++)
	{
		for(int j=0;j<ELEM;j++)
		{
			printf("%d \t", A[i][j]);
		}
		printf("\n");
	}
	
	return 0;
}
