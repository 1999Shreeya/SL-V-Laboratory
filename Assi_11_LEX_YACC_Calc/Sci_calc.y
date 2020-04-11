/*
	Problem Statement - Calculator using LEX and YACC
	Assignment No. - 11
	Roll No. - 33168
*/

%{
	#include <stdio.h>
	#include <math.h>
%}

%union	{double p;}	//define symbol type
%token	<p>num
%token	SIN COS TAN LOG SQRT

//define precedence and associativity
%left	'+''-'
%left	'*''/'
%nonassoc uminu
%type	<p>exp

%%

//Store answer
ss :	exp {printf("\nAnswer :: %g\n",$1);}

//Arithmetic operators
exp:	exp'+'exp	{ $$=$1+$3; }
       |exp'-'exp	{ $$=$1-$3; }
       |exp'*'exp	{ $$=$1*$3; }
       |exp'/'exp	{
				if($3==0)
				{
					printf("Divide by Zero");
				}
				else	$$=$1/$3;
			}
       |'-'exp		{ $$=-$2; }
       |SIN'('exp')'    { $$=sin($3); }
       |COS'('exp')'    { $$=cos($3); }
       |TAN'('exp')'    { $$=tan($3); }
       |LOG'('exp')'    { $$=log($3); }
       |SQRT'('exp')'   { $$=sqrt($3);}
       |'('exp')'    	{ $$=$2;      }
       |num;

%%

main()
{
	do
	{
		printf("\n\nEnter expression :: ");
		yyparse();	//parse the input repeatedly
	}while(1);
}

yyerror(char *s;)	//generating error mesaages
{
	printf("\nSyntax ERROR");
}
