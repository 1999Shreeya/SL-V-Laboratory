//============================================================================
// Name        : pass-II.cpp
// Author      : Shreeya
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <stdio.h>
#include <string.h>
#include <iostream>
using namespace std;

//Initialise table pointers
int STP=1,LTP=1,PTP=1,RC=0,LC=0;
int PoolTab[15] = {0};

//Structure for Symbol Table
typedef struct Symbol_table
{
	int sr_no;
	char symbol[10];
	int address;
	char val[10];
}SymTab;
SymTab st[10];

//Structure for Literal Table
typedef struct Literal_table
{
	int sr_no;
	char literal[10];
	int address;
}LitTab;
LitTab lt[10];

//Function to search symbol table
int search_symtab(char str[])
{
	for(int i=1;i<=STP;i++)
	{
		if(!strcmp(st[i].symbol,str))
			return i;
	}
	return -1;
}

//Function to print data structure tables
void print_tables()
{
	printf("************************************\n");
	printf("SR. NO.\tSYMBOL\tADDRESS\tSIZE/VALUE\n");
	printf("------------------------------------\n\n");
	for(int i=1;i<STP;i++)
		printf("%d\t%s\t%d\t%s\n",st[i].sr_no,st[i].symbol,st[i].address,st[i].val);
	printf("************************************\n\n");

	printf("*************************\n");
	printf("SR.NO.\tLITERAL\tADDRESS\n");
	printf("-------------------------\n\n");
	for(int i=1;i<LTP;i++)
		printf("%d\t%s\t%d\n",lt[i].sr_no,lt[i].literal,lt[i].address);
	printf("*************************\n\n");
	
	printf("******************\n");
	printf("SR.NO.\tPOOl\n");
	printf("------------------\n");
	for(int i=1;i<=PTP;i++)
		printf("%d\t%d\n",i,PoolTab[i]);
	printf("******************\n\n\n\n");
}

//Function to read data structure tables from file
void read_tables()
{
	FILE *fp4;
	
	fp4 = fopen("DataStructure.txt","r+");
	
	//read STP pointer from file
	fscanf(fp4,"%d",&STP);
	
	//Read Symbol Table contents
	for(int i=1;i<=STP;i++)
		fscanf(fp4,"%d\t%s\t%d\t%s\n",&st[i].sr_no,st[i].symbol,&st[i].address,st[i].val);
		
	//read LTP pointer from file
	fscanf(fp4,"%d",&LTP);
	
	//Read Literal Table contents
	for(int i=1;i<=LTP;i++)
		fscanf(fp4,"%d\t%s\t%d\n",&lt[i].sr_no,lt[i].literal,&lt[i].address);
	
	//read PTP pointer from file
	int temp;
	fscanf(fp4,"%d",&temp);
	
	//Read Pool Table contents
	for(int i=1;i<=temp;i++)
		fscanf(fp4,"%d\n",&PoolTab[i]);
	
	fclose(fp4);
}

//Main function 
int main()
{
	FILE *fp,*fp2;
	char data[100],token[20][20],*temp;
	int index,k,size;

	printf("----------------------------------------------------------------------\n\n");
	printf("*************************ASSEMBLER PASS-II*****************************\n\n");
	printf("----------------------------------------------------------------------\n\n");
	
	printf("INPUT ::\n");
	printf("1.Intermediate code\n");
	printf("2.Data Structure Tables\n");
	printf(" 2.1.Symbol table\n");
	printf(" 2.2.Literal table\n\n");
	
	printf("INTERMEDIATE CODE :: \n\n");
	
	fp = fopen("IntermediateCode.txt","r+");
	
	while(fgets(data, 100, (FILE*) fp)!=NULL)
		printf("%s\n",data);
	fclose(fp);
	
	printf("\n\nDATA STRUCTURES ::\n");
	read_tables();		//read data structures from file
	print_tables();		//display data structures
	
	printf("INTERMEDIATE CODE  ======>  MACHINE CODE\n\n\n");
	
	//Open file to process intermediate code
	fp = fopen("IntermediateCode.txt","r+");

	//Process source file line by line
	while(fgets(data, 100, (FILE*) fp)!=NULL)
	{
		index = 0;
		char *pch = NULL;
		
		//Tokenise the instruction in IC
		pch = strtok (data,"\t");
		while (pch != NULL)
		{
			strcpy(token[index++],pch);
			pch = strtok (NULL, ")(");
		}
		index-=2;

		//Process START statement
		if(!strcmp(token[1],"AD 01"))
		{
			char *pch = NULL;
		
			pch = strtok (token[2]," ");
			pch = strtok (NULL," ");
			
			sscanf(pch,"%d",&LC);
			size = 0;

			fp2 = fopen("MachineCode.txt","w+");
			fprintf(fp2,"\t - \n");
			fclose(fp2);

			LC = LC+size;
			continue;
		}
		
		//Process ORIGIN statement
		if(!strcmp(token[1],"AD 04"))
		{
			fp2 = fopen("MachineCode.txt","a");
			fprintf(fp2,"%d/",LC);
			
			char *pch = NULL;
		
			pch = strtok (token[2]," ");
			if(!strcmp(pch,"C"))
			{
				pch = strtok (NULL," ");
				sscanf(pch,"%d",&LC);
			}
			else if(!strcmp(pch,"S"))
			{
				pch = strtok (NULL," ");
				int loc = search_symtab(pch);
				LC = st[loc].address;
			}
			
			size = 0;

			fprintf(fp2,"%d\n",LC);
			fclose(fp2);

			LC = LC+size;
			continue;
		}

		//Process LTORG statement
		if(!strcmp(token[1],"AD 03"))
		{
			fp2 = fopen("MachineCode.txt","a");
			for(int i=PoolTab[PTP];i<PoolTab[PTP+1];i++)
			{
				fprintf(fp2,"%d\t%s\n",LC,lt[i].literal);
				LC++;
			}
			fclose(fp2);
			PTP++;
			continue;
		}

		//Process IMPERATIVE statement
		if(token[1][0] == 'I')
		{
			char *pch = NULL,*pch1;
		
			pch = strtok (token[1]," ");
			pch = strtok (NULL," ");

			int instr_code;
			sscanf(pch,"%d",&instr_code);
			size = 1;
			
			fp2 = fopen("MachineCode.txt","a");
			fprintf(fp2,"%d\t+%02d\t",LC,instr_code);
			
			if(index+1 == 2 || index+1 == 3)
				fprintf(fp2,"\n");
			else
			{
				pch = strtok (token[2]," ");
				pch = strtok (NULL," ");
				
				int reg_code;
				sscanf(pch,"%d",&reg_code);
				
				fprintf(fp2,"%02d\t",reg_code);
				
				pch = strtok (token[3]," ");
				
				if(!strcmp(pch,"C"))
				{
					int temp;
					pch = strtok (NULL," ");
					sscanf(pch,"%d",&temp);
					fprintf(fp2,"%03d\n",temp);
				}
				else if(!strcmp(pch,"S"))
				{
					int loc;
					pch = strtok (NULL," ");
					sscanf(pch,"%d",&loc);
					int temp = st[loc].address;
					fprintf(fp2,"%03d\n",temp);
				}
				else if(!strcmp(pch,"L"))
				{
					int loc;
					pch = strtok (NULL," ");
					sscanf(pch,"%d",&loc);
					int temp = lt[loc].address;
					fprintf(fp2,"%03d\n",temp);
				}
			}
			
			fclose(fp2);

			LC = LC+size;
			continue;
		}
		
		//Process DC statement
		if(!strcmp(token[1],"DL 01"))
		{
			char *pch = NULL;
		
			pch = strtok (token[2]," ");
			pch = strtok (NULL," ");

			size = 1;

			fp2 = fopen("MachineCode.txt","a");
			fprintf(fp2,"%d\t+01\t%s\n",LC,pch);
			fclose(fp2);

			LC = LC+size;

			continue;
		}

		//Process DS statement
		if(!strcmp(token[1],"DL 02"))
		{
			char *pch = NULL;
		
			pch = strtok (token[2]," ");
			pch = strtok (NULL," ");
			
			int val;
			sscanf(pch,"%d",&val);
			size = val;

			fp2 = fopen("MachineCode.txt","a");
			fprintf(fp2,"%d\t+02\t%d\n",LC,val);
			fclose(fp2);

			LC = LC+size;
			continue;
		}
		
		//Process END statement
		if(!strcmp(token[1],"AD 02"))
		{
			fp2 = fopen("MachineCode.txt","a");
			fprintf(fp2,"%d",LC);
			for(int i=PoolTab[PTP];i<=LTP;i++)
				fprintf(fp2,"\t%s\n",lt[i].literal);
			fclose(fp2);
		}

	}
	fclose(fp);
	
	//Display the Machine code generated
	
	printf("OUTPUT :: \n\n");
	
	printf("\n********************************\n");
	
	printf("\tMachine Code");
	
	fp2 = fopen("MachineCode.txt","r+");
	
	printf("\n********************************\n\n");
	while(fgets(data, 100, (FILE*) fp2)!=NULL)
		printf("%s",data);
	printf("\n\n*********************************\n");
	fclose(fp2);

	return 0;
}
