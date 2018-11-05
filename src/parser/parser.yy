%{ /*** C/C++ Declarations ***/

#include <stdio.h>
#include <string>
#include <vector>

%}

/*** yacc/bison Declarations ***/
%require "3.0"

/* add debug output code to generated parser. disable this for release
 * versions. */
%debug

/* start symbol is named "start" */
%start start

%output "parser.cc"

/* write out a header file containing the token defines */
%defines "parser.h"

/* use newer C++ skeleton file */
%skeleton "lalr1.cc"

/* namespace to enclose parser in */
%define api.prefix RoflanParser

/* set the parser's class identifier */
%define "parser_class_name" "Parser"


/* keep track of the current position within the input */
%locations
%initial-action
{
    // initialize the initial location object
    @$.begin.filename = @$.end.filename = &driver.streamname;
};


/* The driver is passed by reference to the parser and to the scanner. This
 * provides a simple but effective pure interface, not relying on global
 * variables. */
%parse-param { class Driver& driver }

/* verbose error messages */
%error-verbose

 /*** TOKENS ***/

%union {
    int  			integerVal;
    double 			doubleVal;
    std::string*	stringVal;
}


%token			END	     0	"end of file"
%token			EOL		    "end of line"
%token <integerVal> INTEGER		"integer"
%token <doubleVal> 	DOUBLE		"double"
%token <stringVal> 	STRING		"string"

%token CREATE
%token TABLE
%token SHOW
%token DROP

%type <int>	expr create_table

%destructor { delete $$; } STRING

 /*** END TOKENS ***/

%{

#include "driver.h"
#include "scanner.h"

/* this "connects" the bison parser in the driver to the flex scanner class
 * object. it defines the yylex() function call to pull the next token from the
 * current lexer object of the driver context. */
#undef yylex
#define yylex driver.lexer->lex

%}

%% /*** Grammar Rules ***/


start	: create_table
        | STRING
        {}

create_table : CREATE TABLE STRING';'
            {
                driver.result = "really wanna crate table " + *$3 + "?";
            }


%% /*** Additional Code ***/

void RoflanParser::Parser::error(const Parser::location_type& l,
			    const std::string& m)
{
    driver.error(l, m);
}