%option noyywrap nodefault yylineno case-insensitive
%{
	#include "parser.tab.h"
	#include <stdarg.h>
	#include <string.h>
	void yyerror(char *s, ...);
%}

%%

CREATE   { return CREATE; }
SHOW     { return SHOW; }
DROP     { return DROP; }
TABLE    {return  TABLE;}
DATABASE { return DATABASE; }

  /* types */
FLOAT4? { return FLOAT; }
INT4?|INTEGER   { return INTEGER; }

   /* operators */
[-+&~|^/%*(),.;!]   { return yytext[0]; }

  /* numbers */
-?[0-9]+                { yylval.intval = atoi(yytext); return INTNUM; } 

  /* user variables */
@[0-9a-z_.$]+ |
@\"[^"\n]+\" |
@`[^`\n]+` |
@'[^'\n]+' { yylval.strval = strdup(yytext+1); return USERVAR; }

        /* everything else */
[ \t\n]         /* whitespace */
.               { yyerror("mystery character '%c'", *yytext); }
%%
