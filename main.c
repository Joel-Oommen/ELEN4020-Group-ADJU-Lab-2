#include <stdlib.h>
#include <stdio.h>

void swap_int(int *x, int *y) {int tmp = *x;*x=*y;*y=tmp;}

void transpose(int Dimensions,int A[Dimensions][Dimensions],int rowStart,int colStart,int quadSize)
{
	for(int n=0;n<quadSize;n++)
	{
		for(int m=n+1;m<quadSize;m++)
		{
			swap_int(&A[rowStart+n][colStart+m],&A[rowStart+m][colStart+n]);
		}
	}
}

void swap_quad(int Dimensions, int A[Dimensions][Dimensions])
{
	int quadSize = Dimensions/2;
	for(int n=0;n<quadSize;n++)
	{
		for(int m=0;m<quadSize;m++)
		{
			swap_int(&A[n][quadSize+m],&A[quadSize+n][m]);
		}
	}
}

#define Dimensions 4

int main()
{
	int A[Dimensions][Dimensions];
	int c=0;
	printf("\n Original matrix \n");
	for(int i=0;i<Dimensions;i++)
	{
		for(int j=0;j<Dimensions;j++)
		{
			A[i][j]=++c;
			printf("%d \t", A[i][j]);
		}
		printf("\n");
	}
	/*This diagram only works on tab width 4
	_____________________
	|		  |			|
	|	A	  |	B		|
	|		  |			|
	|_________|_________|
	|		  |			|
	|	C	  |	D		|
	|		  |			|
	|		  |			|
	*********************
	*/
	int Q = Dimensions/2;
	transpose(Dimensions,A,0,0,Q);//A
	transpose(Dimensions,A,0,Q,Q);//B
	transpose(Dimensions,A,Q,0,Q);//C
	transpose(Dimensions,A,Q,Q,Q);//D
	swap_quad(Dimensions,A);//swap B and C
	printf("\n Transpose matrix \n");
	for(int i=0;i<Dimensions;i++)
	{
		for(int j=0;j<Dimensions;j++)
		{
			printf("%d \t", A[i][j]);
		}
		printf("\n");
	}
	
	return 0;
}
