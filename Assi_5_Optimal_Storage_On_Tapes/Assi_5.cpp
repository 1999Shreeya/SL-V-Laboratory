//============================================================================
// Name        : Assi_5.cpp
// Author      : Shreeya
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>
#define SIZE 3
using namespace std;

void optimalStorage(int p[],int tapes[][SIZE], int t, int n)
{
	if(n > SIZE*t)
	{
		cout<<endl<<"Overflow, number of songs exceed the size of tapes!!"<<endl;
		cout<<"Elements ";
		for(int i=SIZE*t;i<n;i++)
			cout<<p[i]<<" ";
		cout<<"cannot be stored into tapes!!"<<endl<<endl;
	}
	
	int k=0,j=0,level=0;
	for(int i=0;i<n && k<SIZE;i++)
	{
		tapes[j++][k] = p[i];

		if(j == t)
		{
			k++;
			j=0;
		}
	}
	
	float MRT=0;
	for(int i=0;i<t;i++)
	{
		int k=0,sum=0,tmp;
		float mrt=0;
		cout<<"TAPE :: "<<i+1<<" || ";
		while(tapes[i][k]!=0 && k<SIZE)
		{
			cout<<setw(2)<<tapes[i][k]<<" ";
			sum=0;
			for(int j=0;j<k;j++)
			{
				sum+=tapes[i][j];
			}
			mrt+=sum;
			k++;
		}
		if(i==0)
			tmp=k;
		for(int j=k;j<tmp;j++)
			cout<<"   ";
		mrt = mrt/(k-1);
		cout<<"|| MRT :: "<<mrt<<endl<<endl;
		MRT+=mrt;
	}
	
	MRT = MRT/t;

	cout<<"MINIMUM RETREIVAL TIME :: "<<MRT<<endl;

	cout<<endl;
}


int main()
{
	int n,t;
	cout<<"\nOPTIMAL STORAGE ON TAPES\n\n";

	cout<<"Enter number of Tapes :: ";
	cin>>t;

	cout<<"\nEnter number of Songs :: ";
	cin>>n;

	int p[n],tapes[t][SIZE];

	cout<<"\nEnter Song lengths :: \n";
	for(int i=0;i<n;i++)
		cin>>p[i];

	for(int i=0;i<t;i++)
		for(int j=0;j<SIZE;j++)
			tapes[i][j] = 0;

	sort(p,p+n);

	cout<<"ARRANGING SONGS IN ORDER OF INCREASING LENGTH :: "<<endl;
	for(int i=0;i<n;i++)
		cout<<p[i]<<" ";
	cout<<endl<<endl;

	optimalStorage(p,tapes,t,n);

	return 0;
}
