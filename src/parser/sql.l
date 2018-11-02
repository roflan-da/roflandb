%option noyywrap nodefault yylineno case-insensitive
%option c++
%{
	#include "sql_parser.tab.hpp"
	#include <stdarg.h>
	#include <string>
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

  /* names */
[A-Za-z][A-Za-z0-9_]*	{ yylval.strval = strdup(yytext);
                          return NAME; }
`[^`/\\.\n]+`           { yylval.strval = strdup(yytext+1);
                          yylval.strval[yyleng-2] = 0;
                          return NAME; }

  /* user variables */
@[0-9a-z_.$]+ |
@\"[^"\n]+\" |
@`[^`\n]+` |
@'[^'\n]+' { yylval.strval = strdup(yytext+1); return USERVAR; }

        /* everything else */
[ \t\n]         /* whitespace */
.               { yyerror(("mystery character %c", yytext)); }
%%
