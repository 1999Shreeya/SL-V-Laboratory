/*
 ============================================================================
 Name        : Assi_1.c
 Author      : Shreeya
 Roll No.    : 33168
 ============================================================================
 */

//Inclusion of header files
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define SIZE 10

//Global variable declaration
int x[SIZE];
char board[SIZE][SIZE];
int count = 0;
int queen,row,col;

//Function to initialise chessboard
void initialise(int size)
{
	for(int i=1;i<=size;i++)
	{
		for(int j=1;j<=size;j++)
		{
			board[i][j] = '*';
		}
	}
}

//Function to implement NQueens algorithm
void NQueens(int k,int n)
{
	for(int i=1;i<=n;i++)
	{
		if(place(k,i))
		{
			x[k] = i;

			if(k == n)
			{
				initialise(n);
				for(int j=1;j<=n;j++)
				{
					board[j][x[j]] = 'Q';
				}
				count++;
				printf("\n****************************************************\n\n");
				printf("Solution %d :: \n",count);
				printBoard(n);
				printf("\n");
				printf("\n****************************************************\n\n");
				printf("\n****************************************************\n\n");
				initialise(n);
			}
			else
				NQueens(k+1,n);
		}
	}
}

//Function to check queen can be placed in kth row
int place(int k,int i)
{

	queen = k;
	for(int j=1;j<=k-1;j++)
	{
		if((x[j] == i) || (abs(x[j]-i) == abs(j-k)))
		{
			printf("Queen: %d, Row: %d, Column: %d\n",queen,k,i);
			return 0;
		}

	}
	printf("Queen %d placed at %d\n",queen,k);
	return 1;
}

//Function to print chessboard
void printBoard(int size)
{
	for(int i=1;i<=size;i++)
	{
		for(int j=1;j<=size;j++)
		{
			printf("%c\t",board[i][j]);
		}
		printf("\n");
	}
}

int main(void)
{
	int size;

	printf("Enter the size of chessboard :: ");
	scanf("%d",&size);

	printf("\n***************************************************\n\n");
	printf("\n");
	//Function call to NQueens
	NQueens(1,size);
	printf("\nNumber of solutions :: %d\n",count);

	printf("\n***************************************************\n\n");

	return 0;
}
