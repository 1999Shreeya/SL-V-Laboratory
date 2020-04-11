/*
	Problem Statement - TSP using DP
	Assignment No. - 10
	Roll No. - 33168
*/

#include<stdio.h>

int cost[10][10],val[10],n;

int find_min(int val[10], int len)
{
	int i,min,tmp;
	min=val[1];
	
	for(i=2;i<=len;i++)
		if(val[i] < min) 
		{
			min = val[i];
			tmp = i;
		}
			
	return min;
}

int gis(int a, int s[10], int m1, int v[10])
{
	int min,i,j,k,p,q,m,r,ind,set[10],visited[10];
	int val[10];
	i=a; m=m1;

	for(k=1;k<=n;k++) 
		visited[k]=v[k];
	
	visited[i]=1;
	
	if(m==1) 
		return(cost[i][s[1]] + cost[s[1]][1]);
	
	for(ind=1;ind<=m;ind++)
	{
		j=s[ind];
		p=1;
		
		for(k=1;k<=n;k++)
		{
			if((k!=j) && (!visited[k]))
			{
				set[p]=k;
				p++;
			}
		}
		
		val[ind] = cost[i][j] + gis(j,set,m-1,visited);
	}
	min=find_min(val,m);

	return min;
}

int main()
{
	int city,v[10],s[10],i,j,k,min,path[10],p,index;
	int dec,done,rcount,total[10],n1;
	
	printf("Enter the number of cities :: ");
	scanf("%d",&n);
	
	printf("\nEnter the cost matrix for cities :: \n");
	for(i=1;i<=n;i++)
		for(j=1;j<=n;j++)
			scanf("%d",&cost[i][j]);
	

	
	for(i=1;i<=n-1;i++)
	{
		s[i]=i+1;
		v[i]=0;
	}
	v[n]=0;
	
	min=gis(1,s,n-1,v);
	
	printf("\n\nMinimum cost of the tour is :: %d\n",min);
	
	return 0;
}
