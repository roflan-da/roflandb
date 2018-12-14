%{ /*** C/C++ Declarations ***/

#include <stdio.h>
#include <string>
#include <vector>

%}

%code requires{
    #include "command.h"
    #include "statements.h"
    #include "../query_conditions/inc/query_conditions.h"
}

/*** yacc/bison Declarations ***/
%require "3.0"

/* add debug output code to generated parser. disable this for release
 * versions. */
/*%debug*/

/* start symbol is named "start" */
%start start

%output "parser.cc"

/* write out a header file containing the token defines */
%defines "parser.h"

/* use newer C++ skeleton file */
%skeleton "lalr1.cc"

/* namespace to enclose parser in */
%define api.prefix roflan_parser

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
%define api.value.type variant

%token			        END	     0	"end of file"
%token			        EOL		    "end of line"
%token <int>            INTEGER		"integer"
%token <std::string>    STRING      "string"

%token CREATE
%token TABLE
%token SHOW
%token SELECT
%token FROM
%token DROP
%token INT_TYPE
%token INSERT
%token VALUES
%token INTO
%token WHERE
%token DELETE
%token UPDATE
%token SET
%token BOOL

%type <std::shared_ptr<std::vector<std::shared_ptr<cmd::SqlStatement>>>>    statement_list
%type <std::shared_ptr<cmd::SqlStatement>>                                  statement

%type <std::shared_ptr<cmd::CreateStatement>>                               create_statement
%type <std::shared_ptr<cmd::ShowStatement>>                                 show_statement
%type <std::shared_ptr<cmd::SelectStatement>>                               select_statement
%type <std::shared_ptr<cmd::InsertStatement>>                               insert_statement
%type <std::shared_ptr<cmd::DropStatement>>                                 drop_statement
%type <std::shared_ptr<cmd::DeleteStatement>>                               delete_statement
%type <std::shared_ptr<cmd::UpdateStatement>>                               update_statement

%type <st_e::Column::Type>                                                  column_type
%type <std::shared_ptr<st_e::Column>>                                       column_def
%type <std::string>                                                         col_value
%type <std::string>                                                         string_val
%type <std::string>                                                         col_name

%type <std::shared_ptr<cond::SimpleCondition>>                              operand binary_expr
%type <std::shared_ptr<cond::SimpleCondition>>                              comp_expr
%type <std::shared_ptr<cond::Condition>>                                    opt_where expr
%type <std::shared_ptr<cond::ComplexCondition>>                             logic_expr
%type <std::string>                                                         atm_operand

%type <std::shared_ptr<std::vector<std::shared_ptr<st_e::Column>>>>         column_def_list
%type <std::shared_ptr<std::vector<std::string>>>                           cols_names_list
%type <std::shared_ptr<std::vector<std::string>>>                           cols_values_list

%type <std::shared_ptr<std::vector<std::pair<std::string, std::string>>>>   updated_cols_list
%type <std::pair<std::string, std::string>>                                 updated_col_def

%left  OR
%left  AND
%left  '(' ')'

%nonassoc EQUALS NOT_EQUALS LESS GREATER LESS_EQUALS GREATER_EQUALS

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
start : statement_list {
            std::shared_ptr<cmd::Command> result = std::make_shared<cmd::Command>($1);
            driver.sql_parser_result = result;
        }
    ;

statement_list : statement {
            $$ = std::make_shared<std::vector<std::shared_ptr<cmd::SqlStatement>>>();
            $$->emplace_back($1);
        }
    |   statement_list statement {
            $1->emplace_back($2);
            $$ = $1;
        }
    ;

statement :
        create_statement ';' { $$ = $1; }
    |   show_statement ';' { $$ = $1; }
    |   select_statement ';' { $$ = $1; }
    |   insert_statement ';' { $$ = $1; }
    |   drop_statement ';' { $$ = $1; }
    |   delete_statement ';' { $$ = $1; }
    |   update_statement ';' { $$ = $1; }
    ;

create_statement :
        CREATE TABLE string_val '(' column_def_list ')' {
            $$ = std::make_shared<cmd::CreateStatement>($3.c_str(), $5);
        }
    ;

show_statement :
        SHOW CREATE TABLE string_val {
            $$ = std::make_shared<cmd::ShowStatement>(cmd::TABLE, $4.c_str());
        }
    ;

select_statement :
        SELECT '*' FROM string_val opt_where{
            $$ = std::make_shared<cmd::SelectStatement>($4.c_str());
            if ($5 != nullptr){
                $$->add_conditions($5);
            }
        }
    |   SELECT cols_names_list FROM string_val opt_where{
            $$ = std::make_shared<cmd::SelectStatement>($4.c_str(), $2, cmd::VARIABLE);
            if ($5 != nullptr){
                $$->add_conditions($5);
            }
        }
    ;

insert_statement :
        INSERT string_val '(' cols_names_list ')' VALUES '(' cols_values_list ')' {
            $$ = std::make_shared<cmd::InsertStatement>($2.c_str(), $4, $8);
        }
    |   INSERT INTO string_val '(' cols_names_list ')' VALUES '(' cols_values_list ')' {
            $$ = std::make_shared<cmd::InsertStatement>($3.c_str(), $5, $9);
        }
    |   INSERT INTO string_val VALUES '(' cols_values_list ')' {
                $$ = std::make_shared<cmd::InsertStatement>($3.c_str(), $6);
        }
    |   INSERT string_val VALUES '(' cols_values_list ')' {
                $$ = std::make_shared<cmd::InsertStatement>($2.c_str(), $5);
        }
    ;

drop_statement :
        DROP TABLE string_val {
            $$ = std::make_shared<cmd::DropStatement>($3.c_str());
        }
    ;

delete_statement :
        DELETE FROM string_val opt_where { $$ = std::make_shared<cmd::DeleteStatement>($3.c_str(), $4); }
    ;

update_statement :
        UPDATE string_val SET updated_cols_list opt_where {
            $$ = std::make_shared<cmd::UpdateStatement>($2.c_str(), $4, $5); }
    ;

updated_cols_list :
        updated_col_def {
            $$ = std::make_shared<std::vector<std::pair<std::string, std::string>>>();
            $$->emplace_back($1);
        }
    |   updated_cols_list ',' updated_col_def {
            $1->emplace_back($3);
            $$ = $1;
        }
    ;

updated_col_def :
        string_val EQUALS col_value { $$ = std::pair<std::string, std::string>($1, $3); }
    ;

opt_where :
        WHERE expr { $$ = $2; }
    |   { $$ = std::shared_ptr<cond::Condition>(new cond::AlwaysTrueCondition()); };
    ;

expr:
        '(' expr ')' { $$ = $2; }
    |   logic_expr { $$ = std::shared_ptr<cond::Condition>(new cond::ComplexCondition($1->type(),
                                                                                      $1->left(),
                                                                                      $1->right()));
        }
    |   operand { $$ = std::shared_ptr<cond::Condition>(new cond::SimpleCondition($1->type(),
                                                                                  $1->column_name(),
                                                                                  $1->value()));
        }
	;

operand :
        binary_expr { $$ = $1; }
    ;

binary_expr :
		comp_expr { $$ = $1; }
	;

comp_expr :
        atm_operand EQUALS atm_operand          { $$ =  std::make_shared<cond::SimpleCondition>(cond::EQUAl, $1, $3); }
    |	atm_operand NOT_EQUALS atm_operand	    { $$ =  std::make_shared<cond::SimpleCondition>(cond::NOT_EQUAL, $1, $3); }
    |	atm_operand LESS_EQUALS atm_operand	    { $$ =  std::make_shared<cond::SimpleCondition>(cond::LESS_EQUAL, $1, $3); }
    |	atm_operand GREATER_EQUALS atm_operand	{ $$ =  std::make_shared<cond::SimpleCondition>(cond::GREATER_EQUALS, $1, $3); }
    |	atm_operand GREATER atm_operand		    { $$ =  std::make_shared<cond::SimpleCondition>(cond::GREATER, $1, $3); }
    |	atm_operand LESS atm_operand	        { $$ =  std::make_shared<cond::SimpleCondition>(cond::LESS, $1, $3); }
    ;

atm_operand :
        col_value { $$ = $1; }
    |   col_name  { $$ = $1; }
    ;

logic_expr :
        expr AND expr	{ $$ = std::make_shared<cond::ComplexCondition>(cond::AND, $1, $3); }
    |	expr OR expr 	{ $$ = std::make_shared<cond::ComplexCondition>(cond::OR, $1, $3); }
    ;

cols_values_list :
        col_value {
            $$ = std::make_shared<std::vector<std::string>>();
            $$->emplace_back($1);
        }
    |   cols_values_list ',' col_value {
            $1->emplace_back($3);
            $$ = $1;
        }
    ;

col_value :
        INTEGER { $$ = std::to_string($1); }
    |   STRING { $$ = $1; }
    |   '"' STRING '"' { $$ = $2; }
    ;

col_name :
        string_val { $$ = $1; }
    ;

cols_names_list :
        string_val {
            $$ = std::make_shared<std::vector<std::string>>();
            $$->emplace_back($1.c_str());
        }
    |   cols_names_list ',' string_val {
            $1->emplace_back($3.c_str());
            $$ = $1;
        }
    ;

column_def_list:
        column_def {
            $$ = std::make_shared<std::vector<std::shared_ptr<st_e::Column>>>();
            $$->emplace_back($1);
        }
    |   column_def_list ',' column_def {
            $1->emplace_back($3);
            $$ = $1;
        }
    ;

column_def:
		string_val column_type {
		    $$ = std::make_shared<st_e::Column>($2, $1.c_str());
		}
	;

string_val :
        STRING {
            $$ = $1;
        }
    |   '`' STRING '`' {
            $$ = $2;
        }

column_type:
        INT_TYPE { $$ = st_e::Column::Type::INT; }
    |   BOOL { $$ = st_e::Column::Type::BOOL; }
    ;

%% /*** Additional Code ***/

void roflan_parser::Parser::error(const Parser::location_type& l,
			    const std::string& m)
{
    driver.error(l, m);
}