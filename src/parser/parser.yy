%{ /*** C/C++ Declarations ***/

#include <stdio.h>
#include <string>
#include <vector>

%}


%code requires{
    #include "command.h"
    #include "statements.h"
}


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
    std::string* 	stringVal;

    ColumnType      column_type_t;
    cmd::CreateStatement* create_stmt;
    cmd::Column*    column_t;
}


%token			END	     0	"end of file"
%token			EOL		    "end of line"
%token <integerVal> INTEGER		"integer"
%token <doubleVal> 	DOUBLE		"double"
%token <stringVal> 	STRING COLUMN_NAME		"string"

%token CREATE
%token TABLE
%token SHOW
%token DROP
%token INT_TYPE

%type <int>	expr create_table
%type <create_stmt> create_statement
%type <column_type_t>       column_type
%type <column_t> column_def

%destructor { delete $$; } STRING
%destructor { } <column_type_t>

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



start	: create_table {}
        | STRING {}
        | create_statement {}

create_statement : CREATE TABLE '(' column_def ')' STRING
                {
                    cmd::CreateStatement stmt($6->c_str());
                    stmt.add_column(std::make_shared<cmd::Column>(*($4->getObj())));
                    driver.create_statement = stmt;

                }

column_type:
		INT_TYPE { $$ = ColumnType::INT; }
	;

column_def:
		STRING column_type {
		    cmd::Column new_col($2, $1->c_str());
		    $$ = &new_col;
		}
	;

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