#include <stdlib.h>
#include <stdio.h>

void swapInt(int *x, int *y) {int tmp = *x;*x=*y;*y=tmp;}

void transposeQuad(int Dimensions,int *A,int rowStart,int colStart)
{
	int quadSize = Dimensions/2;
	for(int n=0;n<quadSize;n++)
	{
		for(int m=n+1;m<quadSize;m++)
		{
			swapInt(&A[(rowStart+n)*Dimensions+(colStart+m)],&A[(rowStart+m)*Dimensions+(colStart+n)]);
		}
	}
}

void swapQuad(int Dimensions, int *A)
{
	int quadSize = Dimensions/2;
	for(int n=0;n<quadSize;n++)
	{
		for(int m=0;m<quadSize;m++)
		{
			swapInt(&A[n*Dimensions+quadSize+m],&A[(quadSize+n)*Dimensions+m]);
		}
	}
}

#define Dimensions 16

int main()
{
	double elmn=16;
	int *A = (int *)malloc(elmn*elmn*sizeof(int));
	int c=0;
	printf("\n Original matrix \n");
	for(int i=0;i<Dimensions;i++)
	{
		for(int j=0;j<Dimensions;j++)
		{
			A[i*Dimensions+j]=++c;
			printf("%d \t", A[i*Dimensions+j]);
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
	transposeQuad(Dimensions,A,0,0);//A
	transposeQuad(Dimensions,A,0,Q);//B
	transposeQuad(Dimensions,A,Q,0);//C
	transposeQuad(Dimensions,A,Q,Q);//D
	swapQuad(Dimensions,A);//swap B and C
	printf("\n Transpose matrix \n");
	for(int i=0;i<Dimensions;i++)
	{
		for(int j=0;j<Dimensions;j++)
		{
			printf("%d \t", A[i*Dimensions+j]);
		}
		printf("\n");
	}
	
	return 0;
}
