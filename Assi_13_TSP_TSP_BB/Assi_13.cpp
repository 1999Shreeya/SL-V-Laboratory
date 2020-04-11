/*
	Problem Statement - TSP using LCBB
	Assignment No. - 13 
	Roll No. - 33168
*/

#include <bits/stdc++.h>
using namespace std;

#define INF INT_MAX
#define N 5 

//Store nodes in state space tree
struct Node
{
    vector<pair<int, int> > path;  
    int reducedMatrix[N][N];
    int cost;
    int vertex;
    int level;
};

//Operator overloading to set priority
struct comp {
    bool operator()(const Node* lhs, const Node* rhs) const
    {
        return lhs->cost > rhs->cost;
    }
};

//Function to store newNode from city i to j
Node* newNode(int parentMatrix[N][N], vector<pair<int, int> > const &path, int level, int i, int j)
{
    Node* node = new Node;

    node->path = path;

    if (level != 0)
        node->path.push_back(make_pair(i, j));

    memcpy(node->reducedMatrix, parentMatrix,sizeof node->reducedMatrix);

    for (int k = 0; level != 0 && k < N; k++)
    {
        node->reducedMatrix[i][k] = INF;
        node->reducedMatrix[k][j] = INF;
    }

    node->reducedMatrix[j][0] = INF;

    node->level = level;

    node->vertex = j;

    return node;
}

//Function for rowReduction
int rowReduction(int reducedMatrix[N][N], int row[N])
{
    fill_n(row, N, INF);

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (reducedMatrix[i][j] < row[i])
                row[i] = reducedMatrix[i][j];

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (reducedMatrix[i][j] != INF && row[i] != INF)
                reducedMatrix[i][j] -= row[i];
}

//Fucntion for column reduction
int columnReduction(int reducedMatrix[N][N], int col[N])
{
    fill_n(col, N, INF);

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (reducedMatrix[i][j] < col[j])
                col[j] = reducedMatrix[i][j];

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (reducedMatrix[i][j] != INF && col[j] != INF)
                reducedMatrix[i][j] -= col[j];
}

//Function to calculate minimum cost 
int calculateCost(int reducedMatrix[N][N])
{
    int cost = 0;

    int row[N];
    rowReduction(reducedMatrix, row);

    int col[N];
    columnReduction(reducedMatrix, col);

    for (int i = 0; i < N; i++)
        cost += (row[i] != INT_MAX) ? row[i] : 0,
            cost += (col[i] != INT_MAX) ? col[i] : 0;

    return cost;
}

//Function to print final path
void printPath(vector<pair<int, int> > const &list)
{
    for (int i = 0; i < list.size(); i++)
        cout << list[i].first + 1 << " -> ";
    cout<<list[0].first + 1;
}

//Function to solve TSP using LCBB
int solve(int costMatrix[N][N])
{
    priority_queue<Node*, std::vector<Node*>, comp> pq;

    vector<pair<int, int> > v;

    Node* root = newNode(costMatrix, v, 0, -1, 0);

    root->cost = calculateCost(root->reducedMatrix);

    pq.push(root);

    while (!pq.empty())
    {
        Node* min = pq.top();

        pq.pop();

        int i = min->vertex;

        if (min->level == N - 1)
        {
            min->path.push_back(make_pair(i, 0));

            printPath(min->path);

            return min->cost;
        }
        
        for (int j = 0; j < N; j++)
        {
            if (min->reducedMatrix[i][j] != INF)
            {
                Node* child = newNode(min->reducedMatrix, min->path,
                    min->level + 1, i, j);

                child->cost = min->cost + min->reducedMatrix[i][j]
                            + calculateCost(child->reducedMatrix);

                pq.push(child);
            }
        }
        
        delete min;
    }
}

// Main function
int main()
{   
	int n;
    cout<<"\nEnter number of cities :: ";
    cin>>n;
    
    int costMatrix[N][N];
    cout<<"\n\nEnter cost matrix :: \n";
    for(int i=0;i<N;i++)
    	for(int j=0;j<N;j++)
    	{
    		cin>>costMatrix[i][j];
    		if(costMatrix[i][j] == 0)
    			costMatrix[i][j] = INF;
		}
    cout<<"\n\n"<<"TSP Path :: ";
    cout << "\n\nTotal Cost is " << solve(costMatrix);

    return 0;
}
