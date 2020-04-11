/*
	Problem Statement - Recursive Decent Parser
	Assignment No. - 9
	Roll No. - 33168
*/

#include<iostream>
using namespace std;

string input;

/*
GRAMMAR
declare -> type variable;
type -> int | float | char
variable -> id,variable | id
*/

void parser();
int declare(int index);
int type(int index);
int variable(int index);

//Main Function 
int main()
{
	parser();
	return 0;
}

//Function parser
void parser()
{
	cout<<"Enter input string :: ";
	getline(cin,input);
	
	int check = declare(0);
	
	//check if input string is valid and ends with ;
	if(check!=-1 && input[check] == ';')
		cout<<"\nParsing successfull!! "<<endl;
	else
		cout<<"\nError in parsing!!"<<endl;
}

int declare(int index)
{
	if(index == -1) 
		return -1;
	
	//check for valid type
	index = type(index);
	
	if(index == -1) 
		return -1;
	
	//check for variables
	index = variable(++index);
	
	return index;
}

int type(int index)
{
	if(index == -1)
		return -1;
		
	//check if type is INT
	if(input[index] == 'i')
	{
		if(input[++index] == 'n')
		{
			if(input[++index] == 't') 
				return ++index;
			else 
				return -1;
		}	
		else 
			return -1;
	}	
	//check if type is FLOAT
	if(input[index] == 'f')
	{
		if(input[++index] == 'l')
		{
			if(input[++index] == 'o')
			{
				if(input[++index] == 'a')
				{
					if(input[++index] == 't') 
						return ++index;
					else 
						return -1;
				}	
				else 	
					return -1;
			}	
			else 
				return -1;
		}	
		else 
			return -1;
	}
	//check is type is CHAR
	if(input[index] == 'c')
	{
		if(input[++index] == 'h')
		{
			if(input[++index] == 'a')
			{
				if(input[++index] == 'r')
					return ++index;
				else 
					return -1;
			}	
			else 
				return -1;
		}
		else 
			return -1;
	}
	//If none of above types return -1	
	else 
		return -1;
}


int variable(int index)
{
	if(index == -1)
		return -1;
	
	//check for ID,VAR | ID	
	if(input[index] == 'i')
	{
		if(input[++index] == 'd')
		{
			if(input[++index] == ',') 
				return variable(++index);
			else 
				return index;	
		}	
		else 
			return -1;
	}
	else 
		return -1;
}
