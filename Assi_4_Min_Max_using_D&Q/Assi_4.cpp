//============================================================================
// Name        : Assi_4.cpp

// Author      : Shreeya
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include <stdio.h>
#include <climits>
#include <iostream>
#define SIZE 20
using namespace std;

int array[SIZE] = {0},size;
static int pass = 0;

void print_array(int start,int end)
{
	for(int i=0;i<size;i++)
	{
		if(i>=start && i<=end)
			printf("%d\t",array[i]);
		else
			printf("\t");
	}
}

void minMax(int i,int j,int &max,int &min)
{
	if(i == j)
	{
		max = min = array[i];
		pass++;
		printf("\n*******************************************************************************");
		printf("\n-------------------------------------------------------------------------------");
		printf("\n\nPASS %d :: \n",pass);
		print_array(i,j);
		printf("INDEX_LOW :: %d | INDEX_HIGH :: %d | MAX :: %d | MIN :: %d\n",i+1,j+1,max,min);
		printf("---------------------------------------------------------------------------------");
		printf("\n*******************************************************************************\n");
	}
	else if(i == (j-1))
	{
		if(array[i] < array[j])
		{
			max = array[j];
			min = array[i];
		}
		else
		{
			max = array[i];
			min = array[j];
		}
		pass++;
		printf("\n*******************************************************************************");
		printf("\n-------------------------------------------------------------------------------");
		printf("\n\nPASS %d :: \n",pass);
		print_array(i,j);
		printf("INDEX_LOW :: %d | INDEX_HIGH :: %d | MAX :: %d | MIN :: %d\n",i+1,j+1,max,min);
		printf("---------------------------------------------------------------------------------");
		printf("\n*******************************************************************************\n");
	}
	else
	{
		int mid = (i+j)/2;
		int max1,min1;

		minMax(i,mid,max,min);
		minMax(mid+1,j,max1,min1);

		if(max < max1)
		{
			max = max1;
		}
		if(min > min1)
		{
			min = min1;
		}

		pass++;
		printf("\n*******************************************************************************");
		printf("\n-------------------------------------------------------------------------------");
		printf("\n\nPASS %d :: \n",pass);
		print_array(i,j);
		printf("INDEX_LOW :: %d | INDEX_HIGH :: %d | MAX :: %d | MIN :: %d\n",i+1,j+1,max,min);
		printf("---------------------------------------------------------------------------------");
		printf("\n*******************************************************************************\n");


	}
}

int main()
{
	int max = INT_MAX;
	int min = INT_MIN;

	printf("\n*****************MIN-MAX USING DIVIDE & CONQUER*******************");

	printf("\n\nEnter number of array elements :: ");
	scanf("%d",&size);

	printf("Enter elements :: \n");
	for(int i=0;i<size;i++)
		scanf("%d",&array[i]);

	minMax(0,size-1,max,min);
	printf("\n******************************************************************");
	printf("\n------------------------------------------------------------------");
	printf("\nMAXIMUM NUMBER IS :: %d\n",max);
	printf("MINIMUM NUMBER IS :: %d\n",min);
	printf("------------------------------------------------------------------");
	printf("\n******************************************************************");
	return 0;
}
