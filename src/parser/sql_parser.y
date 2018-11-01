%{
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

 void yyerror (char const *s) {
   fprintf (stderr, "%s\n", s);
 }
void emit(char *s, ...);
%}

%union {
	int intval;
	double floatval;
	char *strval;
}

%token <strval> NAME
%token <strval> STRING
%token <intval> INTNUM
%token <strval> USERVAR
%token CREATE
%token SHOW
%token DROP
%token TABLE
%token DATABASE
%token FLOAT
%token INTEGER

%%

commands: /* empty */
        | commands command
        ;

command:
        create_table
        |
        drop_table
        ;

create_table:
        CREATE TABLE NAME '(' NAME INTEGER ')'{
		printf("\tCreate table statement\n");
	} 
	;
drop_table:
	DROP TABLE NAME{
		printf("\tDrop table statement\n");
	}
	;

%%
main(){
        yyparse();
} 