/*
	Problem Statement - ICG using LEX and YACC
	Assignment No. - 12 
	Roll No. - 33168
*/

%{
	#include <stdio.h>
%}

%token	ID NUM WHILE
%right	'='
%left 	'+' '-'
%left 	'*' '/'
%left	MINUS

%%

S : WHILE{L1();} '('E')'{Lcond();} E';'{End();}  //Example while(x=y*z) x=y+z*22;

E :	V'='{push();} E{codegen_assign();}
      | E'+'{push();} E{codegen();}
      | E'-'{push();} E{codegen();}
      | E'*'{push();} E{codegen();}
      | E'/'{push();} E{codegen();}
      | '('E')'
      | '-'{push();} E{codegen_umin();} %prec MINUS
      | V
      | NUM{push();}
      ;

V : ID{push();}
    ;

%%

#include "lex.yy.c"
#include <stdio.h>

char stack[100][10];
int top = 0;
char temp[3] = "t0";;

main()
{
	printf("\n\nEnter the expression :: ");
	yyparse();
}

push()
{
	strcpy(stack[++top],yytext);
}

codegen()
{
	printf("\n%s = %s %s %s",temp,stack[top-2],stack[top-1],stack[top]);
	top -= 2;
	strcpy(stack[top],temp);
	temp[1]++;
}

codegen_umin()
{
	printf("\n%s = -%s",temp,stack[top]);
	top--;
	strcpy(stack[top],temp);
	temp[1]++;
}

codegen_assign()
{
	printf("\n%s = %s",stack[top-2],stack[top]);
	top -= 2;
}

L1()
{
	printf("\n\nL1 : ");
}

Lcond()
{
	printf("\n%s = not %s",temp,stack[top]);
	printf("\nif %s goto End",temp);
	temp[1]++;
}

End()
{
	printf("\ngoto L1");
	printf("\nwhile loop ends\n\n");
}
