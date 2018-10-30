%option noyywrap nodefault yylineno case-insensitive
%{
#include "parser.tab.h"
#include <stdarg.h>
#include <string.h>
void yyerror(char *s, ...);
int oldstate;
%}
%x COMMENT
%s BTWMODE
%%
CREATE  { return CREATE; }
SHOW    { return SHOW; }
DROP    { return DROP; }

  /* types */
FLOAT4? { return FLOAT; }
INT4?|INTEGER   { return INTEGER; }

   /* operators */
[-+&~|^/%*(),.;!]   { return yytext[0]; }

  /* numbers */
-?[0-9]+                { yylval.intval = atoi(yytext); return INTNUM; } 
-?[0-9]+"."[0-9]* |
-?"."[0-9]+     |
-?[0-9]+E[-+]?[0-9]+    |
-?[0-9]+"."[0-9]*E[-+]?[0-9]+ |
    /* booleans */
TRUE    { yylval.intval = 1; return BOOL; }
UNKNOWN { yylval.intval = -1; return BOOL; }
FALSE   { yylval.intval = 0; return BOOL; }

        /* everything else */
[ \t\n]         /* whitespace */
.               { yyerror("mystery character '%c'", *yytext); }
%%
