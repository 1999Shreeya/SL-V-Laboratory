/*
 ============================================================================
 Name        : Assi_2.c
 Author      : Shreeya
 ============================================================================
 */

//Inclusion of headers
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
using namespace std;

//Initialising pointers
int LC=0,PTP=1,LTP=1,STP=1,RC=0;
int PoolTab[15] = {0};

//Structure to store registers
typedef struct Registers
{
	char reg_name[20];
	int code;
}Reg;
Reg rg[4];

//Structure for Mnemonic Opcode Table
typedef struct Mnemonic_opcode_table
{
	char Mnemonic_code[10];
	int Machine_code;
	char Class[4];
	int No_of_Operands;
}Optab;
Optab mot[13];

//Structure for storing size or value for symbols
typedef union size_value
{
	int size;
	char value[5];
}SV;

//Structure for Symbol Table
typedef struct Symbol_table
{
	int sr_no;
	char symbol[4];
	int address;
	SV val;
	int flag;
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

//Structure for Psuedo Opcode Table
typedef struct Psuedo_opcode_table
{
	char opcode[20];
	int code;
	char Class[4];
}POT;
POT pot[10];

//Function to Initialise Registers
void initialise_reg()
{
	strcpy(rg[0].reg_name,"AREG");
	strcpy(rg[1].reg_name,"BREG");
	strcpy(rg[2].reg_name,"CREG");
	strcpy(rg[3].reg_name,"DREG");

	for(int i=0;i<4;i++)
		rg[i].code = i+1;
}

//Function to Initialise Psuedo Opcode Table
void initialise_pot()
{
	strcpy(pot[0].opcode,"START");
	strcpy(pot[1].opcode,"END");
	strcpy(pot[2].opcode,"LTORG");
	strcpy(pot[3].opcode,"ORIGIN");
	strcpy(pot[4].opcode,"EQU");

	for(int i=0;i<4;i++)
	{
		pot[i].code = i+1;
		strcpy(pot[i].Class,"AD");
	}
}

//Function to Initialise Mnemonic Opcode Table
void initialise_mot()
{
	strcpy(mot[0].Mnemonic_code,"STOP");
	strcpy(mot[1].Mnemonic_code,"ADD");
	strcpy(mot[2].Mnemonic_code,"SUB");
	strcpy(mot[3].Mnemonic_code,"MULT");
	strcpy(mot[4].Mnemonic_code,"MOVER");
	strcpy(mot[5].Mnemonic_code,"MOVEM");
	strcpy(mot[6].Mnemonic_code,"COMP");
	strcpy(mot[7].Mnemonic_code,"BC");
	strcpy(mot[8].Mnemonic_code,"DIV");
	strcpy(mot[9].Mnemonic_code,"READ");
	strcpy(mot[10].Mnemonic_code,"PRINT");
	strcpy(mot[11].Mnemonic_code,"DC");
	strcpy(mot[12].Mnemonic_code,"DS");

	strcpy(mot[11].Class,"DL");
	strcpy(mot[12].Class,"DL");

	for(int i=0;i<11;i++)
	{
		strcpy(mot[i].Class,"IS");
		mot[i].Machine_code = i;
	}

	mot[11].Machine_code = 1;
	mot[12].Machine_code = 2;

	mot[0].No_of_Operands = 0;

	for(int i=1;i<9;i++)
		mot[i].No_of_Operands = 2;

	mot[7].No_of_Operands = 1;

	for(int i=9;i<13;i++)
		mot[i].No_of_Operands = 1;
}

//Search code in MOT
int search_mot(char str[])
{
	for(int i=0;i<13;i++)
	{
		if(!strcmp(mot[i].Mnemonic_code,str))
			return i;
	}
	return -1;
}

//Search code in POT
int search_pot(char str[])
{
	for(int i=0;i<5;i++)
	{
		if(!strcmp(pot[i].opcode,str))
			return i;
	}
	return -1;
}

//Search code for Register
int search_reg(char str[])
{
	for(int i=0;i<4;i++)
	{
		if(!strcmp(rg[i].reg_name,str))
			return i+1;
	}
	return -1;
}

//Check Symbol Table for new entry
int search_symtab(char str[])
{
	for(int i=1;i<=STP;i++)
	{
		if(!strcmp(st[i].symbol,str))
			return i;
	}
	return -1;
}

//Check Literal Table for new entry
int search_littab(char str[])
{
	for(int i=1;i<=LTP;i++)
	{
		if(!strcmp(lt[i].literal,str))
			return i;
	}
	return -1;
}

//Function to check token is a number
int is_number(char str[])
{
	for(int i=0;i<strlen(str);i++)
	{
		if(!isdigit(str[i]))
			return 0;
	}
	return 1;
}

//Function to print tables
void print_tables()
{
	printf("************************************\n");
	printf("SR. NO.\tSYMBOL\tADDRESS\tSIZE/VALUE\n");
	printf("------------------------------------\n\n");
	for(int i=1;i<STP;i++)
	{
		if(st[i].flag)
			printf("%d\t%s\t%d\t%s\n",st[i].sr_no,st[i].symbol,st[i].address,st[i].val.value);
		else
			printf("%d\t%s\t%d\t%d\n",st[i].sr_no,st[i].symbol,st[i].address,st[i].val.size);
	}
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

//Main function starts here
int main(void)
{
	FILE *fp,*fp2;
	char data[100],token[20][20];
	PoolTab[1] = 1;
	int k=0,index,stmt=1;

	printf("----------------------------------------------------------------------\n\n");
	printf("*************************ASSEMBLER PASS-I*****************************\n\n");
	printf("----------------------------------------------------------------------\n\n");

	//Create MOT,POT & Registers
	initialise_mot();
	initialise_pot();
	initialise_reg();

	//open input source file
	fp = fopen("file.txt","r+");

	//Process source file line by line
	while(fgets(data, 100, (FILE*) fp)!=NULL)
	{
		printf("Statement %d :: \n\n%s\n",stmt,data);
		stmt++;
		index = 0;
		k=0;
		
		//Tokenise String
		for(int i=0;i<=strlen(data);i++)
		{
			if(data[i] == '\t')
			{
				token[index][k] = '\0';
				index++;
				k=0;
			}
			else
			{
				token[index][k] = data[i];
				k++;
			}
		}
		token[index][k] = '\0';
		printf("Number of tokens :: %d\n\n",index+1);

		if(!strcmp("START",token[1]))		//Processing START 
		{
			int val;
			sscanf(token[2],"%d",&val);
			
			fp2 = fopen("file2.txt","w");
			fprintf(fp2,"%3d\t(%s 01)(%s %02d)\n",LC,"AD","C",val);
			fclose(fp2);
			
			sscanf(token[2], "%d", &LC);
			print_tables();
			continue;
		}

		int loc = search_symtab(token[0]);
		if(loc == -1 && strcmp(token[0],"-"))   //Processing Label
		{
			st[STP].sr_no = STP;
			strcpy(st[STP].symbol,token[0]);
			st[STP].address = LC;
			STP++;
		}
		else
		{
			st[loc].address = LC;
		}
		
		if(!strcmp("LTORG",token[1]))       //Processing LTORG
		{
			fp2 = fopen("file2.txt","a");
			fprintf(fp2,"%3d\t(%s 03)\n",LC,"AD");
			fclose(fp2);
			
			for(int i=PoolTab[PTP];i<LTP;i++)
			{
				lt[i].address = LC;
				LC++;
			}
			PTP++;
			PoolTab[PTP] = LTP;
			print_tables();
			continue;
		}

		if(!strcmp("ORIGIN",token[1]))     //Processing ORIGIN
		{
			char temp1[10],temp2[10];
			int flag=0,a=0,b=0,index,val;
			
			fp2 = fopen("file2.txt","a");
			fprintf(fp2,"%3d\t(%s 04)\n",LC,"AD");

			fclose(fp2);	
			if(is_number(token[2]))
			{
				sscanf(token[2],"%d",&val);
				LC = val;
			}
			else
			{	
				for(int i=0;i<strlen(token[2]);i++)
				{
					if(token[2][i] == '+' || token[2][i] == '-')
					{
						flag=1;
						index=i;
						i++;
					}
					if(!flag)
					{
						temp1[a] = token[2][i];
						a++;
					}
					else
					{
						temp2[b] = token[2][i];
						b++;
					}
				}
				temp1[a] = temp2[b] = '\0';
				if(flag && is_number(temp2))
				{
					sscanf(temp2,"%d",&val);
					if(token[2][index] == '+')
						LC = st[search_symtab(temp1)].address + val;
					else if(token[2][index] == '-')
						LC = st[search_symtab(temp1)].address - val;
				}
				else
					LC = st[search_symtab(token[2])].address;
			}
			print_tables();
			continue;
		}
		
		if(!strcmp("EQU",token[1]))    //Processing EQU
		{
			char temp1[10],temp2[10];
			int flag=0,a=0,b=0,index,val;
			
			fp2 = fopen("file2.txt","a");
			fprintf(fp2,"%3d\t(%s 05)\n",LC,"AD");

			fclose(fp2);
			
			if(is_number(token[2]))
			{
				sscanf(token[2],"%d",&val);
				st[search_symtab(token[0])].address = val;
			}
			else
			{
				for(int i=0;i<strlen(token[2]);i++)
				{
					if(token[2][i] == '+' || token[2][i] == '-')
					{
						flag=1;
						index=i;
						i++;
					}
					if(!flag)
					{
						temp1[a] = token[2][i];
						a++;
					}
					else
					{
						temp2[b] = token[2][i];
						b++;
					}
				}
				temp1[a] = temp2[b] = '\0';

				if(flag && is_number(temp2))
				{
					sscanf(temp2,"%d",&val);
					if(token[2][index] == '+')
						st[search_symtab(token[0])].address = st[search_symtab(temp1)].address + val;
					else if(token[2][index] == '-')
						st[search_symtab(token[0])].address = st[search_symtab(temp1)].address - val;
				}
				else
					st[search_symtab(token[0])].address = st[search_symtab(token[2])].address;
			}
			print_tables();
		}

		if(!strcmp("DC",token[1]))     //Processing DC
		{
			int loc = search_symtab(token[0]);
			strcpy(st[loc].val.value,token[2]);
			st[loc].flag = 1;
			
			fp2 = fopen("file2.txt","a");
			fprintf(fp2,"%3d\t(%s 01)(%s %s)\n",LC,"DL","C",token[2]);

			fclose(fp2);
			LC++;
			print_tables();
			continue;
		}

		if(!strcmp("DS",token[1]))		//Processing DS
		{
			int size;
			int loc = search_symtab(token[0]);
			sscanf(token[2], "%d", &size);
			st[loc].val.size = size;
			st[loc].flag = 0;
			
			fp2 = fopen("file2.txt","a");
			fprintf(fp2,"%3d\t(%s 02)(%s %02d)\n",LC,"DL","C",size);

			fclose(fp2);
			LC = LC+size;
			print_tables();
			continue;
		}
		
		if(search_mot(token[1])!=-1)	//Processing Imperative Statements
		{
			token[3][strlen(token[3])-1] = '\0';
			
			fp2 = fopen("file2.txt","a");
			fprintf(fp2,"%3d\t(%s %02d)",LC,"IS",search_mot(token[1]));
			
			if(!strcmp(token[2],"-")) 
				fprintf(fp2,"\n");
			else if(search_reg(token[2])!=-1)
			{
				RC = search_reg(token[2]);
				fprintf(fp2,"(%s %02d)","R",RC);
			}
			else if(is_number(token[2]))
			{
				int val;
				sscanf(token[2],"%d",&val);
				fprintf(fp2,"(%s %02d)\n","C",val);
			}
			else if(search_symtab(token[2]) == -1)
			{
				st[STP].sr_no = STP;
				strcpy(st[STP].symbol,token[2]);
				st[STP].address = LC;
				fprintf(fp2,"(%s %02d)","S",STP);
				STP++;
			}
			else if(search_symtab(token[2]) != -1)
			{
				int loc = search_symtab(token[2]);
				fprintf(fp2,"(%s %02d)\n","S",st[loc].sr_no);
			}
					
			if(!strcmp(token[3],"-")) 
				fprintf(fp2,"\n");
			else if(token[3][0] == '=')
			{
				lt[LTP].sr_no = LTP;
				strcpy(lt[LTP].literal,token[3]);
				fprintf(fp2,"(%s %02d)\n","L",LTP);
				LTP++;
			}
			else if(search_symtab(token[3]) == -1)
			{
				st[STP].sr_no = STP;
				strcpy(st[STP].symbol,token[3]);
				st[STP].address = LC;
				fprintf(fp2,"(%s %02d)\n","S",STP);
				STP++;
			}
			else if(is_number(token[3]))
			{
				int val;
				sscanf(token[3],"%d",&val);
				fprintf(fp2,"(%s %02d)\n","C",val);
			}
			else if(search_symtab(token[3]) != -1)
			{
				int loc = search_symtab(token[3]);
				fprintf(fp2,"(%s %02d)\n","S",st[loc].sr_no);
			}
					
			
			fclose(fp2);
			LC++;
			print_tables();
			continue;
		}

		if(!strcmp("END",token[1]))		//Processing END
		{
			fp2 = fopen("file2.txt","a");
			fprintf(fp2,"%3d\t(%s 02)\n",LC,"AD");
			fclose(fp2);
			
			if(PoolTab[PTP] <= (LTP-1))
			{
				for(int i=PoolTab[PTP];i<LTP;i++)
				{
					lt[i].address = LC;
					LC++;
				}
			}
			print_tables();	
		}
	}
	fclose(fp);
	
	printf("INTERMEDIATE CODE GENERATED :: \n\n");
	fp2 = fopen("file2.txt","r+");
	
	while(fgets(data, 100, (FILE*) fp)!=NULL)
		printf("%s",data);
		
	fclose(fp2);

	return 0;
}
