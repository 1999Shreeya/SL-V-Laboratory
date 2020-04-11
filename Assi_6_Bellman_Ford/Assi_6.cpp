//============================================================================
// Name        : Assi_6.cpp
// Author      : Shreeya
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <climits>
#define SIZE 20
#define INIFINITY 9999
using namespace std;

int n,edges;
int node[SIZE],prev[SIZE];
char city[SIZE][SIZE];

typedef struct edges
{
	int from;
	int to;
	int weight;
}Edges;
Edges e[10];

void acceptGraph(int n,int edges)
{
	cout<<"Enter names of cities ::\n";
	for(int i=1;i<=n;i++)
	{
		cout<<"City "<<i<<" :: ";
		cin>>city[i];
	}
	cout<<endl;

	for(int i=0;i<edges;i++)
	{
		cout<<"\nEnter Edge "<<i+1<<":: ";
		cout<<"\n\tSource :: ";
		cin>>e[i].from;
		cout<<"\tDestination :: ";
		cin>>e[i].to;
		cout<<"\tWeight between "<<city[e[i].from]<<" & "<<city[e[i].to]<<" :: ";
		cin>>e[i].weight;
	}
}

void print()
{
	cout<<"\n\nCITIES\t\tMIN DISTANCE FROM "<<city[1]<<"\t\tPATH"<<endl;
	for(int i=1;i<=n;i++)
	{
		cout<<city[i]<<"\t\t"<<node[i]<<"\t\t\t\t";
		int k=i;
		while(prev[k]!=1)
		{
			cout<<prev[k]<<"->";
			k = prev[k];
		}
		cout<<"1"<<endl;
	}

}

void bellManFord()
{

	for(int i=1;i<=n;i++)
			node[i] = INT_MAX;
	node[1] = 0;

	for(int i=1;i<=n-1;i++)
	{
		for(int j=0;j<edges;j++)
		{
			int u = e[j].from;
			int v = e[j].to;
			int weight = e[j].weight;
			if(node[u]!=INT_MAX && node[u]+weight < node[v])
			{
				node[v] = node[u]+weight;
				prev[v] = u;
			}
		}
	}

	for(int j=0;j<edges;j++)
	{
		int u = e[j].from;
		int v = e[j].to;
		int weight = e[j].weight;
		if(node[u]!=INT_MAX && node[u]+weight < node[v])
		{
			cout<<"Graph contains negative weight cycle!!"<<endl;
		}
	}
}

int main()
{
	prev[1] = 1;
	cout<<"\nEnter nodes in graph :: ";
	cin>>n;

	cout<<"\nEnter number of edges of graph :: ";
	cin>>edges;

	acceptGraph(n,edges);

	bellManFord();

	print();

	return 0;
}
