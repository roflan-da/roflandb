// A Bison parser, made by GNU Bison 3.0.5.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.

// Take the name prefix into account.
#define yylex   roflan_parserlex

// First part of user declarations.
#line 1 "parser.yy" // lalr1.cc:406
 /*** C/C++ Declarations ***/

#include <stdio.h>
#include <string>
#include <vector>

#line 116 "parser.yy" // lalr1.cc:406


#include "driver.h"
#include "scanner.h"

/* this "connects" the bison parser in the driver to the flex scanner class
 * object. it defines the yylex() function call to pull the next token from the
 * current lexer object of the driver context. */
#undef yylex
#define yylex driver.lexer->lex


#line 58 "parser.cc" // lalr1.cc:406

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

#include "parser.h"

// User implementation prologue.

#line 72 "parser.cc" // lalr1.cc:414


#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K].location)
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (/*CONSTCOND*/ false)
# endif


// Suppress unused-variable warnings by "using" E.
#define YYUSE(E) ((void) (E))

// Enable debugging if requested.
#if ROFLAN_PARSERDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << std::endl;                  \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yystack_print_ ();                \
  } while (false)

#else // !ROFLAN_PARSERDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !ROFLAN_PARSERDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)


namespace roflan_parser {
#line 158 "parser.cc" // lalr1.cc:481

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  Parser::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr = "";
        char const *yyp = yystr;

        for (;;)
          switch (*++yyp)
            {
            case '\'':
            case ',':
              goto do_not_strip_quotes;

            case '\\':
              if (*++yyp != '\\')
                goto do_not_strip_quotes;
              // Fall through.
            default:
              yyr += *yyp;
              break;

            case '"':
              return yyr;
            }
      do_not_strip_quotes: ;
      }

    return yystr;
  }


  /// Build a parser object.
  Parser::Parser (class Driver& driver_yyarg)
    :
#if ROFLAN_PARSERDEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      driver (driver_yyarg)
  {}

  Parser::~Parser ()
  {}


  /*---------------.
  | Symbol types.  |
  `---------------*/

  Parser::syntax_error::syntax_error (const location_type& l, const std::string& m)
    : std::runtime_error (m)
    , location (l)
  {}

  // basic_symbol.
  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol ()
    : value ()
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (const basic_symbol& other)
    : Base (other)
    , value ()
    , location (other.location)
  {
    switch (other.type_get ())
    {
      case 4: // "integer"
        value.copy< int > (other.value);
        break;

      case 61: // column_type
        value.copy< st_e::Column::Type > (other.value);
        break;

      case 47: // updated_col_def
        value.copy< std::pair<std::string, std::string> > (other.value);
        break;

      case 39: // create_statement
        value.copy< std::shared_ptr<cmd::CreateStatement> > (other.value);
        break;

      case 44: // delete_statement
        value.copy< std::shared_ptr<cmd::DeleteStatement> > (other.value);
        break;

      case 43: // drop_statement
        value.copy< std::shared_ptr<cmd::DropStatement> > (other.value);
        break;

      case 42: // insert_statement
        value.copy< std::shared_ptr<cmd::InsertStatement> > (other.value);
        break;

      case 41: // select_statement
        value.copy< std::shared_ptr<cmd::SelectStatement> > (other.value);
        break;

      case 40: // show_statement
        value.copy< std::shared_ptr<cmd::ShowStatement> > (other.value);
        break;

      case 38: // statement
        value.copy< std::shared_ptr<cmd::SqlStatement> > (other.value);
        break;

      case 45: // update_statement
        value.copy< std::shared_ptr<cmd::UpdateStatement> > (other.value);
        break;

      case 54: // logic_expr
        value.copy< std::shared_ptr<cond::ComplexCondition> > (other.value);
        break;

      case 48: // opt_where
      case 49: // expr
        value.copy< std::shared_ptr<cond::Condition> > (other.value);
        break;

      case 50: // operand
      case 51: // binary_expr
      case 52: // comp_expr
        value.copy< std::shared_ptr<cond::SimpleCondition> > (other.value);
        break;

      case 59: // column_def
        value.copy< std::shared_ptr<st_e::Column> > (other.value);
        break;

      case 46: // updated_cols_list
        value.copy< std::shared_ptr<std::vector<std::pair<std::string, std::string>>> > (other.value);
        break;

      case 37: // statement_list
        value.copy< std::shared_ptr<std::vector<std::shared_ptr<cmd::SqlStatement>>> > (other.value);
        break;

      case 58: // column_def_list
        value.copy< std::shared_ptr<std::vector<std::shared_ptr<st_e::Column>>> > (other.value);
        break;

      case 55: // cols_values_list
      case 57: // cols_names_list
        value.copy< std::shared_ptr<std::vector<std::string>> > (other.value);
        break;

      case 5: // "string"
      case 53: // atm_operand
      case 56: // col_value
      case 60: // string_val
        value.copy< std::string > (other.value);
        break;

      default:
        break;
    }

  }

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const semantic_type& v, const location_type& l)
    : Base (t)
    , value ()
    , location (l)
  {
    (void) v;
    switch (this->type_get ())
    {
      case 4: // "integer"
        value.copy< int > (v);
        break;

      case 61: // column_type
        value.copy< st_e::Column::Type > (v);
        break;

      case 47: // updated_col_def
        value.copy< std::pair<std::string, std::string> > (v);
        break;

      case 39: // create_statement
        value.copy< std::shared_ptr<cmd::CreateStatement> > (v);
        break;

      case 44: // delete_statement
        value.copy< std::shared_ptr<cmd::DeleteStatement> > (v);
        break;

      case 43: // drop_statement
        value.copy< std::shared_ptr<cmd::DropStatement> > (v);
        break;

      case 42: // insert_statement
        value.copy< std::shared_ptr<cmd::InsertStatement> > (v);
        break;

      case 41: // select_statement
        value.copy< std::shared_ptr<cmd::SelectStatement> > (v);
        break;

      case 40: // show_statement
        value.copy< std::shared_ptr<cmd::ShowStatement> > (v);
        break;

      case 38: // statement
        value.copy< std::shared_ptr<cmd::SqlStatement> > (v);
        break;

      case 45: // update_statement
        value.copy< std::shared_ptr<cmd::UpdateStatement> > (v);
        break;

      case 54: // logic_expr
        value.copy< std::shared_ptr<cond::ComplexCondition> > (v);
        break;

      case 48: // opt_where
      case 49: // expr
        value.copy< std::shared_ptr<cond::Condition> > (v);
        break;

      case 50: // operand
      case 51: // binary_expr
      case 52: // comp_expr
        value.copy< std::shared_ptr<cond::SimpleCondition> > (v);
        break;

      case 59: // column_def
        value.copy< std::shared_ptr<st_e::Column> > (v);
        break;

      case 46: // updated_cols_list
        value.copy< std::shared_ptr<std::vector<std::pair<std::string, std::string>>> > (v);
        break;

      case 37: // statement_list
        value.copy< std::shared_ptr<std::vector<std::shared_ptr<cmd::SqlStatement>>> > (v);
        break;

      case 58: // column_def_list
        value.copy< std::shared_ptr<std::vector<std::shared_ptr<st_e::Column>>> > (v);
        break;

      case 55: // cols_values_list
      case 57: // cols_names_list
        value.copy< std::shared_ptr<std::vector<std::string>> > (v);
        break;

      case 5: // "string"
      case 53: // atm_operand
      case 56: // col_value
      case 60: // string_val
        value.copy< std::string > (v);
        break;

      default:
        break;
    }
}


  // Implementation of basic_symbol constructor for each type.

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const location_type& l)
    : Base (t)
    , value ()
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const int v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const st_e::Column::Type v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const std::pair<std::string, std::string> v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const std::shared_ptr<cmd::CreateStatement> v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const std::shared_ptr<cmd::DeleteStatement> v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const std::shared_ptr<cmd::DropStatement> v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const std::shared_ptr<cmd::InsertStatement> v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const std::shared_ptr<cmd::SelectStatement> v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const std::shared_ptr<cmd::ShowStatement> v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const std::shared_ptr<cmd::SqlStatement> v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const std::shared_ptr<cmd::UpdateStatement> v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const std::shared_ptr<cond::ComplexCondition> v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const std::shared_ptr<cond::Condition> v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const std::shared_ptr<cond::SimpleCondition> v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const std::shared_ptr<st_e::Column> v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const std::shared_ptr<std::vector<std::pair<std::string, std::string>>> v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const std::shared_ptr<std::vector<std::shared_ptr<cmd::SqlStatement>>> v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const std::shared_ptr<std::vector<std::shared_ptr<st_e::Column>>> v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const std::shared_ptr<std::vector<std::string>> v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const std::string v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}


  template <typename Base>
  Parser::basic_symbol<Base>::~basic_symbol ()
  {
    clear ();
  }

  template <typename Base>
  void
  Parser::basic_symbol<Base>::clear ()
  {
    // User destructor.
    symbol_number_type yytype = this->type_get ();
    basic_symbol<Base>& yysym = *this;
    (void) yysym;
    switch (yytype)
    {
   default:
      break;
    }

    // Type destructor.
  switch (yytype)
    {
      case 4: // "integer"
        value.template destroy< int > ();
        break;

      case 61: // column_type
        value.template destroy< st_e::Column::Type > ();
        break;

      case 47: // updated_col_def
        value.template destroy< std::pair<std::string, std::string> > ();
        break;

      case 39: // create_statement
        value.template destroy< std::shared_ptr<cmd::CreateStatement> > ();
        break;

      case 44: // delete_statement
        value.template destroy< std::shared_ptr<cmd::DeleteStatement> > ();
        break;

      case 43: // drop_statement
        value.template destroy< std::shared_ptr<cmd::DropStatement> > ();
        break;

      case 42: // insert_statement
        value.template destroy< std::shared_ptr<cmd::InsertStatement> > ();
        break;

      case 41: // select_statement
        value.template destroy< std::shared_ptr<cmd::SelectStatement> > ();
        break;

      case 40: // show_statement
        value.template destroy< std::shared_ptr<cmd::ShowStatement> > ();
        break;

      case 38: // statement
        value.template destroy< std::shared_ptr<cmd::SqlStatement> > ();
        break;

      case 45: // update_statement
        value.template destroy< std::shared_ptr<cmd::UpdateStatement> > ();
        break;

      case 54: // logic_expr
        value.template destroy< std::shared_ptr<cond::ComplexCondition> > ();
        break;

      case 48: // opt_where
      case 49: // expr
        value.template destroy< std::shared_ptr<cond::Condition> > ();
        break;

      case 50: // operand
      case 51: // binary_expr
      case 52: // comp_expr
        value.template destroy< std::shared_ptr<cond::SimpleCondition> > ();
        break;

      case 59: // column_def
        value.template destroy< std::shared_ptr<st_e::Column> > ();
        break;

      case 46: // updated_cols_list
        value.template destroy< std::shared_ptr<std::vector<std::pair<std::string, std::string>>> > ();
        break;

      case 37: // statement_list
        value.template destroy< std::shared_ptr<std::vector<std::shared_ptr<cmd::SqlStatement>>> > ();
        break;

      case 58: // column_def_list
        value.template destroy< std::shared_ptr<std::vector<std::shared_ptr<st_e::Column>>> > ();
        break;

      case 55: // cols_values_list
      case 57: // cols_names_list
        value.template destroy< std::shared_ptr<std::vector<std::string>> > ();
        break;

      case 5: // "string"
      case 53: // atm_operand
      case 56: // col_value
      case 60: // string_val
        value.template destroy< std::string > ();
        break;

      default:
        break;
    }

    Base::clear ();
  }

  template <typename Base>
  bool
  Parser::basic_symbol<Base>::empty () const
  {
    return Base::type_get () == empty_symbol;
  }

  template <typename Base>
  void
  Parser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move (s);
    switch (this->type_get ())
    {
      case 4: // "integer"
        value.move< int > (s.value);
        break;

      case 61: // column_type
        value.move< st_e::Column::Type > (s.value);
        break;

      case 47: // updated_col_def
        value.move< std::pair<std::string, std::string> > (s.value);
        break;

      case 39: // create_statement
        value.move< std::shared_ptr<cmd::CreateStatement> > (s.value);
        break;

      case 44: // delete_statement
        value.move< std::shared_ptr<cmd::DeleteStatement> > (s.value);
        break;

      case 43: // drop_statement
        value.move< std::shared_ptr<cmd::DropStatement> > (s.value);
        break;

      case 42: // insert_statement
        value.move< std::shared_ptr<cmd::InsertStatement> > (s.value);
        break;

      case 41: // select_statement
        value.move< std::shared_ptr<cmd::SelectStatement> > (s.value);
        break;

      case 40: // show_statement
        value.move< std::shared_ptr<cmd::ShowStatement> > (s.value);
        break;

      case 38: // statement
        value.move< std::shared_ptr<cmd::SqlStatement> > (s.value);
        break;

      case 45: // update_statement
        value.move< std::shared_ptr<cmd::UpdateStatement> > (s.value);
        break;

      case 54: // logic_expr
        value.move< std::shared_ptr<cond::ComplexCondition> > (s.value);
        break;

      case 48: // opt_where
      case 49: // expr
        value.move< std::shared_ptr<cond::Condition> > (s.value);
        break;

      case 50: // operand
      case 51: // binary_expr
      case 52: // comp_expr
        value.move< std::shared_ptr<cond::SimpleCondition> > (s.value);
        break;

      case 59: // column_def
        value.move< std::shared_ptr<st_e::Column> > (s.value);
        break;

      case 46: // updated_cols_list
        value.move< std::shared_ptr<std::vector<std::pair<std::string, std::string>>> > (s.value);
        break;

      case 37: // statement_list
        value.move< std::shared_ptr<std::vector<std::shared_ptr<cmd::SqlStatement>>> > (s.value);
        break;

      case 58: // column_def_list
        value.move< std::shared_ptr<std::vector<std::shared_ptr<st_e::Column>>> > (s.value);
        break;

      case 55: // cols_values_list
      case 57: // cols_names_list
        value.move< std::shared_ptr<std::vector<std::string>> > (s.value);
        break;

      case 5: // "string"
      case 53: // atm_operand
      case 56: // col_value
      case 60: // string_val
        value.move< std::string > (s.value);
        break;

      default:
        break;
    }

    location = s.location;
  }

  // by_type.
  Parser::by_type::by_type ()
    : type (empty_symbol)
  {}

  Parser::by_type::by_type (const by_type& other)
    : type (other.type)
  {}

  Parser::by_type::by_type (token_type t)
    : type (yytranslate_ (t))
  {}

  void
  Parser::by_type::clear ()
  {
    type = empty_symbol;
  }

  void
  Parser::by_type::move (by_type& that)
  {
    type = that.type;
    that.clear ();
  }

  int
  Parser::by_type::type_get () const
  {
    return type;
  }
  // Implementation of make_symbol for each symbol type.
  Parser::symbol_type
  Parser::make_END (const location_type& l)
  {
    return symbol_type (token::END, l);
  }

  Parser::symbol_type
  Parser::make_EOL (const location_type& l)
  {
    return symbol_type (token::EOL, l);
  }

  Parser::symbol_type
  Parser::make_INTEGER (const int& v, const location_type& l)
  {
    return symbol_type (token::INTEGER, v, l);
  }

  Parser::symbol_type
  Parser::make_STRING (const std::string& v, const location_type& l)
  {
    return symbol_type (token::STRING, v, l);
  }

  Parser::symbol_type
  Parser::make_CREATE (const location_type& l)
  {
    return symbol_type (token::CREATE, l);
  }

  Parser::symbol_type
  Parser::make_TABLE (const location_type& l)
  {
    return symbol_type (token::TABLE, l);
  }

  Parser::symbol_type
  Parser::make_SHOW (const location_type& l)
  {
    return symbol_type (token::SHOW, l);
  }

  Parser::symbol_type
  Parser::make_SELECT (const location_type& l)
  {
    return symbol_type (token::SELECT, l);
  }

  Parser::symbol_type
  Parser::make_FROM (const location_type& l)
  {
    return symbol_type (token::FROM, l);
  }

  Parser::symbol_type
  Parser::make_DROP (const location_type& l)
  {
    return symbol_type (token::DROP, l);
  }

  Parser::symbol_type
  Parser::make_INT_TYPE (const location_type& l)
  {
    return symbol_type (token::INT_TYPE, l);
  }

  Parser::symbol_type
  Parser::make_INSERT (const location_type& l)
  {
    return symbol_type (token::INSERT, l);
  }

  Parser::symbol_type
  Parser::make_VALUES (const location_type& l)
  {
    return symbol_type (token::VALUES, l);
  }

  Parser::symbol_type
  Parser::make_INTO (const location_type& l)
  {
    return symbol_type (token::INTO, l);
  }

  Parser::symbol_type
  Parser::make_WHERE (const location_type& l)
  {
    return symbol_type (token::WHERE, l);
  }

  Parser::symbol_type
  Parser::make_DELETE (const location_type& l)
  {
    return symbol_type (token::DELETE, l);
  }

  Parser::symbol_type
  Parser::make_UPDATE (const location_type& l)
  {
    return symbol_type (token::UPDATE, l);
  }

  Parser::symbol_type
  Parser::make_SET (const location_type& l)
  {
    return symbol_type (token::SET, l);
  }

  Parser::symbol_type
  Parser::make_BOOL (const location_type& l)
  {
    return symbol_type (token::BOOL, l);
  }

  Parser::symbol_type
  Parser::make_OR (const location_type& l)
  {
    return symbol_type (token::OR, l);
  }

  Parser::symbol_type
  Parser::make_AND (const location_type& l)
  {
    return symbol_type (token::AND, l);
  }

  Parser::symbol_type
  Parser::make_EQUALS (const location_type& l)
  {
    return symbol_type (token::EQUALS, l);
  }

  Parser::symbol_type
  Parser::make_NOT_EQUALS (const location_type& l)
  {
    return symbol_type (token::NOT_EQUALS, l);
  }

  Parser::symbol_type
  Parser::make_LESS (const location_type& l)
  {
    return symbol_type (token::LESS, l);
  }

  Parser::symbol_type
  Parser::make_GREATER (const location_type& l)
  {
    return symbol_type (token::GREATER, l);
  }

  Parser::symbol_type
  Parser::make_LESS_EQUALS (const location_type& l)
  {
    return symbol_type (token::LESS_EQUALS, l);
  }

  Parser::symbol_type
  Parser::make_GREATER_EQUALS (const location_type& l)
  {
    return symbol_type (token::GREATER_EQUALS, l);
  }



  // by_state.
  Parser::by_state::by_state ()
    : state (empty_state)
  {}

  Parser::by_state::by_state (const by_state& other)
    : state (other.state)
  {}

  void
  Parser::by_state::clear ()
  {
    state = empty_state;
  }

  void
  Parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  Parser::by_state::by_state (state_type s)
    : state (s)
  {}

  Parser::symbol_number_type
  Parser::by_state::type_get () const
  {
    if (state == empty_state)
      return empty_symbol;
    else
      return yystos_[state];
  }

  Parser::stack_symbol_type::stack_symbol_type ()
  {}

  Parser::stack_symbol_type::stack_symbol_type (const stack_symbol_type& that)
    : super_type (that.state, that.location)
  {
    switch (that.type_get ())
    {
      case 4: // "integer"
        value.copy< int > (that.value);
        break;

      case 61: // column_type
        value.copy< st_e::Column::Type > (that.value);
        break;

      case 47: // updated_col_def
        value.copy< std::pair<std::string, std::string> > (that.value);
        break;

      case 39: // create_statement
        value.copy< std::shared_ptr<cmd::CreateStatement> > (that.value);
        break;

      case 44: // delete_statement
        value.copy< std::shared_ptr<cmd::DeleteStatement> > (that.value);
        break;

      case 43: // drop_statement
        value.copy< std::shared_ptr<cmd::DropStatement> > (that.value);
        break;

      case 42: // insert_statement
        value.copy< std::shared_ptr<cmd::InsertStatement> > (that.value);
        break;

      case 41: // select_statement
        value.copy< std::shared_ptr<cmd::SelectStatement> > (that.value);
        break;

      case 40: // show_statement
        value.copy< std::shared_ptr<cmd::ShowStatement> > (that.value);
        break;

      case 38: // statement
        value.copy< std::shared_ptr<cmd::SqlStatement> > (that.value);
        break;

      case 45: // update_statement
        value.copy< std::shared_ptr<cmd::UpdateStatement> > (that.value);
        break;

      case 54: // logic_expr
        value.copy< std::shared_ptr<cond::ComplexCondition> > (that.value);
        break;

      case 48: // opt_where
      case 49: // expr
        value.copy< std::shared_ptr<cond::Condition> > (that.value);
        break;

      case 50: // operand
      case 51: // binary_expr
      case 52: // comp_expr
        value.copy< std::shared_ptr<cond::SimpleCondition> > (that.value);
        break;

      case 59: // column_def
        value.copy< std::shared_ptr<st_e::Column> > (that.value);
        break;

      case 46: // updated_cols_list
        value.copy< std::shared_ptr<std::vector<std::pair<std::string, std::string>>> > (that.value);
        break;

      case 37: // statement_list
        value.copy< std::shared_ptr<std::vector<std::shared_ptr<cmd::SqlStatement>>> > (that.value);
        break;

      case 58: // column_def_list
        value.copy< std::shared_ptr<std::vector<std::shared_ptr<st_e::Column>>> > (that.value);
        break;

      case 55: // cols_values_list
      case 57: // cols_names_list
        value.copy< std::shared_ptr<std::vector<std::string>> > (that.value);
        break;

      case 5: // "string"
      case 53: // atm_operand
      case 56: // col_value
      case 60: // string_val
        value.copy< std::string > (that.value);
        break;

      default:
        break;
    }

  }

  Parser::stack_symbol_type::stack_symbol_type (state_type s, symbol_type& that)
    : super_type (s, that.location)
  {
    switch (that.type_get ())
    {
      case 4: // "integer"
        value.move< int > (that.value);
        break;

      case 61: // column_type
        value.move< st_e::Column::Type > (that.value);
        break;

      case 47: // updated_col_def
        value.move< std::pair<std::string, std::string> > (that.value);
        break;

      case 39: // create_statement
        value.move< std::shared_ptr<cmd::CreateStatement> > (that.value);
        break;

      case 44: // delete_statement
        value.move< std::shared_ptr<cmd::DeleteStatement> > (that.value);
        break;

      case 43: // drop_statement
        value.move< std::shared_ptr<cmd::DropStatement> > (that.value);
        break;

      case 42: // insert_statement
        value.move< std::shared_ptr<cmd::InsertStatement> > (that.value);
        break;

      case 41: // select_statement
        value.move< std::shared_ptr<cmd::SelectStatement> > (that.value);
        break;

      case 40: // show_statement
        value.move< std::shared_ptr<cmd::ShowStatement> > (that.value);
        break;

      case 38: // statement
        value.move< std::shared_ptr<cmd::SqlStatement> > (that.value);
        break;

      case 45: // update_statement
        value.move< std::shared_ptr<cmd::UpdateStatement> > (that.value);
        break;

      case 54: // logic_expr
        value.move< std::shared_ptr<cond::ComplexCondition> > (that.value);
        break;

      case 48: // opt_where
      case 49: // expr
        value.move< std::shared_ptr<cond::Condition> > (that.value);
        break;

      case 50: // operand
      case 51: // binary_expr
      case 52: // comp_expr
        value.move< std::shared_ptr<cond::SimpleCondition> > (that.value);
        break;

      case 59: // column_def
        value.move< std::shared_ptr<st_e::Column> > (that.value);
        break;

      case 46: // updated_cols_list
        value.move< std::shared_ptr<std::vector<std::pair<std::string, std::string>>> > (that.value);
        break;

      case 37: // statement_list
        value.move< std::shared_ptr<std::vector<std::shared_ptr<cmd::SqlStatement>>> > (that.value);
        break;

      case 58: // column_def_list
        value.move< std::shared_ptr<std::vector<std::shared_ptr<st_e::Column>>> > (that.value);
        break;

      case 55: // cols_values_list
      case 57: // cols_names_list
        value.move< std::shared_ptr<std::vector<std::string>> > (that.value);
        break;

      case 5: // "string"
      case 53: // atm_operand
      case 56: // col_value
      case 60: // string_val
        value.move< std::string > (that.value);
        break;

      default:
        break;
    }

    // that is emptied.
    that.type = empty_symbol;
  }

  Parser::stack_symbol_type&
  Parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    switch (that.type_get ())
    {
      case 4: // "integer"
        value.copy< int > (that.value);
        break;

      case 61: // column_type
        value.copy< st_e::Column::Type > (that.value);
        break;

      case 47: // updated_col_def
        value.copy< std::pair<std::string, std::string> > (that.value);
        break;

      case 39: // create_statement
        value.copy< std::shared_ptr<cmd::CreateStatement> > (that.value);
        break;

      case 44: // delete_statement
        value.copy< std::shared_ptr<cmd::DeleteStatement> > (that.value);
        break;

      case 43: // drop_statement
        value.copy< std::shared_ptr<cmd::DropStatement> > (that.value);
        break;

      case 42: // insert_statement
        value.copy< std::shared_ptr<cmd::InsertStatement> > (that.value);
        break;

      case 41: // select_statement
        value.copy< std::shared_ptr<cmd::SelectStatement> > (that.value);
        break;

      case 40: // show_statement
        value.copy< std::shared_ptr<cmd::ShowStatement> > (that.value);
        break;

      case 38: // statement
        value.copy< std::shared_ptr<cmd::SqlStatement> > (that.value);
        break;

      case 45: // update_statement
        value.copy< std::shared_ptr<cmd::UpdateStatement> > (that.value);
        break;

      case 54: // logic_expr
        value.copy< std::shared_ptr<cond::ComplexCondition> > (that.value);
        break;

      case 48: // opt_where
      case 49: // expr
        value.copy< std::shared_ptr<cond::Condition> > (that.value);
        break;

      case 50: // operand
      case 51: // binary_expr
      case 52: // comp_expr
        value.copy< std::shared_ptr<cond::SimpleCondition> > (that.value);
        break;

      case 59: // column_def
        value.copy< std::shared_ptr<st_e::Column> > (that.value);
        break;

      case 46: // updated_cols_list
        value.copy< std::shared_ptr<std::vector<std::pair<std::string, std::string>>> > (that.value);
        break;

      case 37: // statement_list
        value.copy< std::shared_ptr<std::vector<std::shared_ptr<cmd::SqlStatement>>> > (that.value);
        break;

      case 58: // column_def_list
        value.copy< std::shared_ptr<std::vector<std::shared_ptr<st_e::Column>>> > (that.value);
        break;

      case 55: // cols_values_list
      case 57: // cols_names_list
        value.copy< std::shared_ptr<std::vector<std::string>> > (that.value);
        break;

      case 5: // "string"
      case 53: // atm_operand
      case 56: // col_value
      case 60: // string_val
        value.copy< std::string > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    return *this;
  }


  template <typename Base>
  void
  Parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if ROFLAN_PARSERDEBUG
  template <typename Base>
  void
  Parser::yy_print_ (std::ostream& yyo,
                                     const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YYUSE (yyoutput);
    symbol_number_type yytype = yysym.type_get ();
    // Avoid a (spurious) G++ 4.8 warning about "array subscript is
    // below array bounds".
    if (yysym.empty ())
      std::abort ();
    yyo << (yytype < yyntokens_ ? "token" : "nterm")
        << ' ' << yytname_[yytype] << " ("
        << yysym.location << ": ";
    YYUSE (yytype);
    yyo << ')';
  }
#endif

  void
  Parser::yypush_ (const char* m, state_type s, symbol_type& sym)
  {
    stack_symbol_type t (s, sym);
    yypush_ (m, t);
  }

  void
  Parser::yypush_ (const char* m, stack_symbol_type& s)
  {
    if (m)
      YY_SYMBOL_PRINT (m, s);
    yystack_.push (s);
  }

  void
  Parser::yypop_ (unsigned n)
  {
    yystack_.pop (n);
  }

#if ROFLAN_PARSERDEBUG
  std::ostream&
  Parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  Parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  Parser::debug_level_type
  Parser::debug_level () const
  {
    return yydebug_;
  }

  void
  Parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // ROFLAN_PARSERDEBUG

  Parser::state_type
  Parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  bool
  Parser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  Parser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  Parser::parse ()
  {
    // State.
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The locations where the error started and ended.
    stack_symbol_type yyerror_range[3];

    /// The return value of parse ().
    int yyresult;

    // FIXME: This shoud be completely indented.  It is not yet to
    // avoid gratuitous conflicts when merging into the master branch.
    try
      {
    YYCDEBUG << "Starting parse" << std::endl;


    // User initialization code.
    #line 42 "parser.yy" // lalr1.cc:737
{
    // initialize the initial location object
    yyla.location.begin.filename = yyla.location.end.filename = &driver.streamname;
}

#line 1473 "parser.cc" // lalr1.cc:737

    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, yyla);

    // A new symbol was pushed on the stack.
  yynewstate:
    YYCDEBUG << "Entering state " << yystack_[0].state << std::endl;

    // Accept?
    if (yystack_[0].state == yyfinal_)
      goto yyacceptlab;

    goto yybackup;

    // Backup.
  yybackup:

    // Try to take a decision without lookahead.
    yyn = yypact_[yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token: ";
        try
          {
            yyla.type = yytranslate_ (yylex (&yyla.value, &yyla.location));
          }
        catch (const syntax_error& yyexc)
          {
            error (yyexc);
            goto yyerrlab1;
          }
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.type_get ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.type_get ())
      goto yydefault;

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", yyn, yyla);
    goto yynewstate;

  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;

  /*-----------------------------.
  | yyreduce -- Do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_ (yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
      switch (yyr1_[yyn])
    {
      case 4: // "integer"
        yylhs.value.build< int > ();
        break;

      case 61: // column_type
        yylhs.value.build< st_e::Column::Type > ();
        break;

      case 47: // updated_col_def
        yylhs.value.build< std::pair<std::string, std::string> > ();
        break;

      case 39: // create_statement
        yylhs.value.build< std::shared_ptr<cmd::CreateStatement> > ();
        break;

      case 44: // delete_statement
        yylhs.value.build< std::shared_ptr<cmd::DeleteStatement> > ();
        break;

      case 43: // drop_statement
        yylhs.value.build< std::shared_ptr<cmd::DropStatement> > ();
        break;

      case 42: // insert_statement
        yylhs.value.build< std::shared_ptr<cmd::InsertStatement> > ();
        break;

      case 41: // select_statement
        yylhs.value.build< std::shared_ptr<cmd::SelectStatement> > ();
        break;

      case 40: // show_statement
        yylhs.value.build< std::shared_ptr<cmd::ShowStatement> > ();
        break;

      case 38: // statement
        yylhs.value.build< std::shared_ptr<cmd::SqlStatement> > ();
        break;

      case 45: // update_statement
        yylhs.value.build< std::shared_ptr<cmd::UpdateStatement> > ();
        break;

      case 54: // logic_expr
        yylhs.value.build< std::shared_ptr<cond::ComplexCondition> > ();
        break;

      case 48: // opt_where
      case 49: // expr
        yylhs.value.build< std::shared_ptr<cond::Condition> > ();
        break;

      case 50: // operand
      case 51: // binary_expr
      case 52: // comp_expr
        yylhs.value.build< std::shared_ptr<cond::SimpleCondition> > ();
        break;

      case 59: // column_def
        yylhs.value.build< std::shared_ptr<st_e::Column> > ();
        break;

      case 46: // updated_cols_list
        yylhs.value.build< std::shared_ptr<std::vector<std::pair<std::string, std::string>>> > ();
        break;

      case 37: // statement_list
        yylhs.value.build< std::shared_ptr<std::vector<std::shared_ptr<cmd::SqlStatement>>> > ();
        break;

      case 58: // column_def_list
        yylhs.value.build< std::shared_ptr<std::vector<std::shared_ptr<st_e::Column>>> > ();
        break;

      case 55: // cols_values_list
      case 57: // cols_names_list
        yylhs.value.build< std::shared_ptr<std::vector<std::string>> > ();
        break;

      case 5: // "string"
      case 53: // atm_operand
      case 56: // col_value
      case 60: // string_val
        yylhs.value.build< std::string > ();
        break;

      default:
        break;
    }


      // Default location.
      {
        slice<stack_symbol_type, stack_type> slice (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, slice, yylen);
        yyerror_range[1].location = yylhs.location;
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
      try
        {
          switch (yyn)
            {
  case 2:
#line 130 "parser.yy" // lalr1.cc:856
    {
            std::shared_ptr<cmd::Command> result = std::make_shared<cmd::Command>(yystack_[0].value.as< std::shared_ptr<std::vector<std::shared_ptr<cmd::SqlStatement>>> > ());
            driver.sql_parser_result = result;
        }
#line 1673 "parser.cc" // lalr1.cc:856
    break;

  case 3:
#line 136 "parser.yy" // lalr1.cc:856
    {
            yylhs.value.as< std::shared_ptr<std::vector<std::shared_ptr<cmd::SqlStatement>>> > () = std::make_shared<std::vector<std::shared_ptr<cmd::SqlStatement>>>();
            yylhs.value.as< std::shared_ptr<std::vector<std::shared_ptr<cmd::SqlStatement>>> > ()->emplace_back(yystack_[0].value.as< std::shared_ptr<cmd::SqlStatement> > ());
        }
#line 1682 "parser.cc" // lalr1.cc:856
    break;

  case 4:
#line 140 "parser.yy" // lalr1.cc:856
    {
            yystack_[1].value.as< std::shared_ptr<std::vector<std::shared_ptr<cmd::SqlStatement>>> > ()->emplace_back(yystack_[0].value.as< std::shared_ptr<cmd::SqlStatement> > ());
            yylhs.value.as< std::shared_ptr<std::vector<std::shared_ptr<cmd::SqlStatement>>> > () = yystack_[1].value.as< std::shared_ptr<std::vector<std::shared_ptr<cmd::SqlStatement>>> > ();
        }
#line 1691 "parser.cc" // lalr1.cc:856
    break;

  case 5:
#line 147 "parser.yy" // lalr1.cc:856
    { yylhs.value.as< std::shared_ptr<cmd::SqlStatement> > () = yystack_[1].value.as< std::shared_ptr<cmd::CreateStatement> > (); }
#line 1697 "parser.cc" // lalr1.cc:856
    break;

  case 6:
#line 148 "parser.yy" // lalr1.cc:856
    { yylhs.value.as< std::shared_ptr<cmd::SqlStatement> > () = yystack_[1].value.as< std::shared_ptr<cmd::ShowStatement> > (); }
#line 1703 "parser.cc" // lalr1.cc:856
    break;

  case 7:
#line 149 "parser.yy" // lalr1.cc:856
    { yylhs.value.as< std::shared_ptr<cmd::SqlStatement> > () = yystack_[1].value.as< std::shared_ptr<cmd::SelectStatement> > (); }
#line 1709 "parser.cc" // lalr1.cc:856
    break;

  case 8:
#line 150 "parser.yy" // lalr1.cc:856
    { yylhs.value.as< std::shared_ptr<cmd::SqlStatement> > () = yystack_[1].value.as< std::shared_ptr<cmd::InsertStatement> > (); }
#line 1715 "parser.cc" // lalr1.cc:856
    break;

  case 9:
#line 151 "parser.yy" // lalr1.cc:856
    { yylhs.value.as< std::shared_ptr<cmd::SqlStatement> > () = yystack_[1].value.as< std::shared_ptr<cmd::DropStatement> > (); }
#line 1721 "parser.cc" // lalr1.cc:856
    break;

  case 10:
#line 152 "parser.yy" // lalr1.cc:856
    { yylhs.value.as< std::shared_ptr<cmd::SqlStatement> > () = yystack_[1].value.as< std::shared_ptr<cmd::DeleteStatement> > (); }
#line 1727 "parser.cc" // lalr1.cc:856
    break;

  case 11:
#line 153 "parser.yy" // lalr1.cc:856
    { yylhs.value.as< std::shared_ptr<cmd::SqlStatement> > () = yystack_[1].value.as< std::shared_ptr<cmd::UpdateStatement> > (); }
#line 1733 "parser.cc" // lalr1.cc:856
    break;

  case 12:
#line 157 "parser.yy" // lalr1.cc:856
    {
            yylhs.value.as< std::shared_ptr<cmd::CreateStatement> > () = std::make_shared<cmd::CreateStatement>(yystack_[3].value.as< std::string > ().c_str(), yystack_[1].value.as< std::shared_ptr<std::vector<std::shared_ptr<st_e::Column>>> > ());
        }
#line 1741 "parser.cc" // lalr1.cc:856
    break;

  case 13:
#line 163 "parser.yy" // lalr1.cc:856
    {
            yylhs.value.as< std::shared_ptr<cmd::ShowStatement> > () = std::make_shared<cmd::ShowStatement>(cmd::TABLE, yystack_[0].value.as< std::string > ().c_str());
        }
#line 1749 "parser.cc" // lalr1.cc:856
    break;

  case 14:
#line 169 "parser.yy" // lalr1.cc:856
    {
            yylhs.value.as< std::shared_ptr<cmd::SelectStatement> > () = std::make_shared<cmd::SelectStatement>(yystack_[1].value.as< std::string > ().c_str());
            if (yystack_[0].value.as< std::shared_ptr<cond::Condition> > () != nullptr){
                yylhs.value.as< std::shared_ptr<cmd::SelectStatement> > ()->add_conditions(yystack_[0].value.as< std::shared_ptr<cond::Condition> > ());
            }
        }
#line 1760 "parser.cc" // lalr1.cc:856
    break;

  case 15:
#line 175 "parser.yy" // lalr1.cc:856
    {
            yylhs.value.as< std::shared_ptr<cmd::SelectStatement> > () = std::make_shared<cmd::SelectStatement>(yystack_[1].value.as< std::string > ().c_str(), yystack_[3].value.as< std::shared_ptr<std::vector<std::string>> > (), cmd::VARIABLE);
        }
#line 1768 "parser.cc" // lalr1.cc:856
    break;

  case 16:
#line 181 "parser.yy" // lalr1.cc:856
    {
            yylhs.value.as< std::shared_ptr<cmd::InsertStatement> > () = std::make_shared<cmd::InsertStatement>(yystack_[7].value.as< std::string > ().c_str(), yystack_[5].value.as< std::shared_ptr<std::vector<std::string>> > (), yystack_[1].value.as< std::shared_ptr<std::vector<std::string>> > ());
        }
#line 1776 "parser.cc" // lalr1.cc:856
    break;

  case 17:
#line 184 "parser.yy" // lalr1.cc:856
    {
            yylhs.value.as< std::shared_ptr<cmd::InsertStatement> > () = std::make_shared<cmd::InsertStatement>(yystack_[7].value.as< std::string > ().c_str(), yystack_[5].value.as< std::shared_ptr<std::vector<std::string>> > (), yystack_[1].value.as< std::shared_ptr<std::vector<std::string>> > ());
        }
#line 1784 "parser.cc" // lalr1.cc:856
    break;

  case 18:
#line 187 "parser.yy" // lalr1.cc:856
    {
                yylhs.value.as< std::shared_ptr<cmd::InsertStatement> > () = std::make_shared<cmd::InsertStatement>(yystack_[4].value.as< std::string > ().c_str(), yystack_[1].value.as< std::shared_ptr<std::vector<std::string>> > ());
        }
#line 1792 "parser.cc" // lalr1.cc:856
    break;

  case 19:
#line 190 "parser.yy" // lalr1.cc:856
    {
                yylhs.value.as< std::shared_ptr<cmd::InsertStatement> > () = std::make_shared<cmd::InsertStatement>(yystack_[4].value.as< std::string > ().c_str(), yystack_[1].value.as< std::shared_ptr<std::vector<std::string>> > ());
        }
#line 1800 "parser.cc" // lalr1.cc:856
    break;

  case 20:
#line 196 "parser.yy" // lalr1.cc:856
    {
            yylhs.value.as< std::shared_ptr<cmd::DropStatement> > () = std::make_shared<cmd::DropStatement>(yystack_[0].value.as< std::string > ().c_str());
        }
#line 1808 "parser.cc" // lalr1.cc:856
    break;

  case 21:
#line 202 "parser.yy" // lalr1.cc:856
    { yylhs.value.as< std::shared_ptr<cmd::DeleteStatement> > () = std::make_shared<cmd::DeleteStatement>(yystack_[1].value.as< std::string > ().c_str(), yystack_[0].value.as< std::shared_ptr<cond::Condition> > ()); }
#line 1814 "parser.cc" // lalr1.cc:856
    break;

  case 22:
#line 206 "parser.yy" // lalr1.cc:856
    {
            yylhs.value.as< std::shared_ptr<cmd::UpdateStatement> > () = std::make_shared<cmd::UpdateStatement>(yystack_[3].value.as< std::string > ().c_str(), yystack_[1].value.as< std::shared_ptr<std::vector<std::pair<std::string, std::string>>> > (), yystack_[0].value.as< std::shared_ptr<cond::Condition> > ()); }
#line 1821 "parser.cc" // lalr1.cc:856
    break;

  case 23:
#line 211 "parser.yy" // lalr1.cc:856
    {
            yylhs.value.as< std::shared_ptr<std::vector<std::pair<std::string, std::string>>> > () = std::make_shared<std::vector<std::pair<std::string, std::string>>>();
            yylhs.value.as< std::shared_ptr<std::vector<std::pair<std::string, std::string>>> > ()->emplace_back(yystack_[0].value.as< std::pair<std::string, std::string> > ());
        }
#line 1830 "parser.cc" // lalr1.cc:856
    break;

  case 24:
#line 215 "parser.yy" // lalr1.cc:856
    {
            yystack_[2].value.as< std::shared_ptr<std::vector<std::pair<std::string, std::string>>> > ()->emplace_back(yystack_[0].value.as< std::pair<std::string, std::string> > ());
            yylhs.value.as< std::shared_ptr<std::vector<std::pair<std::string, std::string>>> > () = yystack_[2].value.as< std::shared_ptr<std::vector<std::pair<std::string, std::string>>> > ();
        }
#line 1839 "parser.cc" // lalr1.cc:856
    break;

  case 25:
#line 222 "parser.yy" // lalr1.cc:856
    { yylhs.value.as< std::pair<std::string, std::string> > () = std::pair<std::string, std::string>(yystack_[2].value.as< std::string > (), yystack_[0].value.as< std::string > ()); }
#line 1845 "parser.cc" // lalr1.cc:856
    break;

  case 26:
#line 226 "parser.yy" // lalr1.cc:856
    { yylhs.value.as< std::shared_ptr<cond::Condition> > () = yystack_[0].value.as< std::shared_ptr<cond::Condition> > (); }
#line 1851 "parser.cc" // lalr1.cc:856
    break;

  case 27:
#line 227 "parser.yy" // lalr1.cc:856
    { yylhs.value.as< std::shared_ptr<cond::Condition> > () = std::shared_ptr<cond::Condition>(new cond::AlwaysTrueCondition()); }
#line 1857 "parser.cc" // lalr1.cc:856
    break;

  case 28:
#line 231 "parser.yy" // lalr1.cc:856
    { yylhs.value.as< std::shared_ptr<cond::Condition> > () = yystack_[1].value.as< std::shared_ptr<cond::Condition> > (); }
#line 1863 "parser.cc" // lalr1.cc:856
    break;

  case 29:
#line 232 "parser.yy" // lalr1.cc:856
    { yylhs.value.as< std::shared_ptr<cond::Condition> > () = std::shared_ptr<cond::Condition>(new cond::ComplexCondition(yystack_[0].value.as< std::shared_ptr<cond::ComplexCondition> > ()->type(),
                                                                                      yystack_[0].value.as< std::shared_ptr<cond::ComplexCondition> > ()->left(),
                                                                                      yystack_[0].value.as< std::shared_ptr<cond::ComplexCondition> > ()->right()));
        }
#line 1872 "parser.cc" // lalr1.cc:856
    break;

  case 30:
#line 236 "parser.yy" // lalr1.cc:856
    { yylhs.value.as< std::shared_ptr<cond::Condition> > () = std::shared_ptr<cond::Condition>(new cond::SimpleCondition(yystack_[0].value.as< std::shared_ptr<cond::SimpleCondition> > ()->type(),
                                                                                  yystack_[0].value.as< std::shared_ptr<cond::SimpleCondition> > ()->column_name(),
                                                                                  yystack_[0].value.as< std::shared_ptr<cond::SimpleCondition> > ()->value()));
        }
#line 1881 "parser.cc" // lalr1.cc:856
    break;

  case 31:
#line 243 "parser.yy" // lalr1.cc:856
    { yylhs.value.as< std::shared_ptr<cond::SimpleCondition> > () = yystack_[0].value.as< std::shared_ptr<cond::SimpleCondition> > (); }
#line 1887 "parser.cc" // lalr1.cc:856
    break;

  case 32:
#line 247 "parser.yy" // lalr1.cc:856
    { yylhs.value.as< std::shared_ptr<cond::SimpleCondition> > () = yystack_[0].value.as< std::shared_ptr<cond::SimpleCondition> > (); }
#line 1893 "parser.cc" // lalr1.cc:856
    break;

  case 33:
#line 251 "parser.yy" // lalr1.cc:856
    { yylhs.value.as< std::shared_ptr<cond::SimpleCondition> > () =  std::make_shared<cond::SimpleCondition>(cond::EQUAl, yystack_[2].value.as< std::string > (), yystack_[0].value.as< std::string > ()); }
#line 1899 "parser.cc" // lalr1.cc:856
    break;

  case 34:
#line 252 "parser.yy" // lalr1.cc:856
    { yylhs.value.as< std::shared_ptr<cond::SimpleCondition> > () =  std::make_shared<cond::SimpleCondition>(cond::NOT_EQUAL, yystack_[2].value.as< std::string > (), yystack_[0].value.as< std::string > ()); }
#line 1905 "parser.cc" // lalr1.cc:856
    break;

  case 35:
#line 253 "parser.yy" // lalr1.cc:856
    { yylhs.value.as< std::shared_ptr<cond::SimpleCondition> > () =  std::make_shared<cond::SimpleCondition>(cond::LESS_EQUAL, yystack_[2].value.as< std::string > (), yystack_[0].value.as< std::string > ()); }
#line 1911 "parser.cc" // lalr1.cc:856
    break;

  case 36:
#line 254 "parser.yy" // lalr1.cc:856
    { yylhs.value.as< std::shared_ptr<cond::SimpleCondition> > () =  std::make_shared<cond::SimpleCondition>(cond::GREATER_EQUALS, yystack_[2].value.as< std::string > (), yystack_[0].value.as< std::string > ()); }
#line 1917 "parser.cc" // lalr1.cc:856
    break;

  case 37:
#line 255 "parser.yy" // lalr1.cc:856
    { yylhs.value.as< std::shared_ptr<cond::SimpleCondition> > () =  std::make_shared<cond::SimpleCondition>(cond::GREATER, yystack_[2].value.as< std::string > (), yystack_[0].value.as< std::string > ()); }
#line 1923 "parser.cc" // lalr1.cc:856
    break;

  case 38:
#line 256 "parser.yy" // lalr1.cc:856
    { yylhs.value.as< std::shared_ptr<cond::SimpleCondition> > () =  std::make_shared<cond::SimpleCondition>(cond::LESS, yystack_[2].value.as< std::string > (), yystack_[0].value.as< std::string > ()); }
#line 1929 "parser.cc" // lalr1.cc:856
    break;

  case 39:
#line 260 "parser.yy" // lalr1.cc:856
    { yylhs.value.as< std::string > () = yystack_[0].value.as< std::string > (); }
#line 1935 "parser.cc" // lalr1.cc:856
    break;

  case 40:
#line 264 "parser.yy" // lalr1.cc:856
    { yylhs.value.as< std::shared_ptr<cond::ComplexCondition> > () = std::make_shared<cond::ComplexCondition>(cond::AND, yystack_[2].value.as< std::shared_ptr<cond::Condition> > (), yystack_[0].value.as< std::shared_ptr<cond::Condition> > ()); }
#line 1941 "parser.cc" // lalr1.cc:856
    break;

  case 41:
#line 265 "parser.yy" // lalr1.cc:856
    { yylhs.value.as< std::shared_ptr<cond::ComplexCondition> > () = std::make_shared<cond::ComplexCondition>(cond::OR, yystack_[2].value.as< std::shared_ptr<cond::Condition> > (), yystack_[0].value.as< std::shared_ptr<cond::Condition> > ()); }
#line 1947 "parser.cc" // lalr1.cc:856
    break;

  case 42:
#line 269 "parser.yy" // lalr1.cc:856
    {
            yylhs.value.as< std::shared_ptr<std::vector<std::string>> > () = std::make_shared<std::vector<std::string>>();
            yylhs.value.as< std::shared_ptr<std::vector<std::string>> > ()->emplace_back(yystack_[0].value.as< std::string > ());
        }
#line 1956 "parser.cc" // lalr1.cc:856
    break;

  case 43:
#line 273 "parser.yy" // lalr1.cc:856
    {
            yystack_[2].value.as< std::shared_ptr<std::vector<std::string>> > ()->emplace_back(yystack_[0].value.as< std::string > ());
            yylhs.value.as< std::shared_ptr<std::vector<std::string>> > () = yystack_[2].value.as< std::shared_ptr<std::vector<std::string>> > ();
        }
#line 1965 "parser.cc" // lalr1.cc:856
    break;

  case 44:
#line 280 "parser.yy" // lalr1.cc:856
    {
            yylhs.value.as< std::string > () = std::to_string(yystack_[0].value.as< int > ());
        }
#line 1973 "parser.cc" // lalr1.cc:856
    break;

  case 45:
#line 283 "parser.yy" // lalr1.cc:856
    {
            yylhs.value.as< std::string > () = yystack_[0].value.as< std::string > ();
        }
#line 1981 "parser.cc" // lalr1.cc:856
    break;

  case 46:
#line 286 "parser.yy" // lalr1.cc:856
    {
            yylhs.value.as< std::string > () = std::to_string(yystack_[1].value.as< int > ());
        }
#line 1989 "parser.cc" // lalr1.cc:856
    break;

  case 47:
#line 292 "parser.yy" // lalr1.cc:856
    {
            yylhs.value.as< std::shared_ptr<std::vector<std::string>> > () = std::make_shared<std::vector<std::string>>();
            yylhs.value.as< std::shared_ptr<std::vector<std::string>> > ()->emplace_back(yystack_[0].value.as< std::string > ().c_str());
        }
#line 1998 "parser.cc" // lalr1.cc:856
    break;

  case 48:
#line 296 "parser.yy" // lalr1.cc:856
    {
            yystack_[2].value.as< std::shared_ptr<std::vector<std::string>> > ()->emplace_back(yystack_[0].value.as< std::string > ().c_str());
            yylhs.value.as< std::shared_ptr<std::vector<std::string>> > () = yystack_[2].value.as< std::shared_ptr<std::vector<std::string>> > ();
        }
#line 2007 "parser.cc" // lalr1.cc:856
    break;

  case 49:
#line 303 "parser.yy" // lalr1.cc:856
    {
            yylhs.value.as< std::shared_ptr<std::vector<std::shared_ptr<st_e::Column>>> > () = std::make_shared<std::vector<std::shared_ptr<st_e::Column>>>();
            yylhs.value.as< std::shared_ptr<std::vector<std::shared_ptr<st_e::Column>>> > ()->emplace_back(yystack_[0].value.as< std::shared_ptr<st_e::Column> > ());
        }
#line 2016 "parser.cc" // lalr1.cc:856
    break;

  case 50:
#line 307 "parser.yy" // lalr1.cc:856
    {
            yystack_[2].value.as< std::shared_ptr<std::vector<std::shared_ptr<st_e::Column>>> > ()->emplace_back(yystack_[0].value.as< std::shared_ptr<st_e::Column> > ());
            yylhs.value.as< std::shared_ptr<std::vector<std::shared_ptr<st_e::Column>>> > () = yystack_[2].value.as< std::shared_ptr<std::vector<std::shared_ptr<st_e::Column>>> > ();
        }
#line 2025 "parser.cc" // lalr1.cc:856
    break;

  case 51:
#line 314 "parser.yy" // lalr1.cc:856
    {
		    yylhs.value.as< std::shared_ptr<st_e::Column> > () = std::make_shared<st_e::Column>(yystack_[0].value.as< st_e::Column::Type > (), yystack_[1].value.as< std::string > ().c_str());
		}
#line 2033 "parser.cc" // lalr1.cc:856
    break;

  case 52:
#line 320 "parser.yy" // lalr1.cc:856
    {
            yylhs.value.as< std::string > () = yystack_[0].value.as< std::string > ();
        }
#line 2041 "parser.cc" // lalr1.cc:856
    break;

  case 53:
#line 323 "parser.yy" // lalr1.cc:856
    {
            yylhs.value.as< std::string > () = yystack_[1].value.as< std::string > ();
        }
#line 2049 "parser.cc" // lalr1.cc:856
    break;

  case 54:
#line 328 "parser.yy" // lalr1.cc:856
    { yylhs.value.as< st_e::Column::Type > () = st_e::Column::Type::INT; }
#line 2055 "parser.cc" // lalr1.cc:856
    break;

  case 55:
#line 329 "parser.yy" // lalr1.cc:856
    { yylhs.value.as< st_e::Column::Type > () = st_e::Column::Type::BOOL; }
#line 2061 "parser.cc" // lalr1.cc:856
    break;


#line 2065 "parser.cc" // lalr1.cc:856
            default:
              break;
            }
        }
      catch (const syntax_error& yyexc)
        {
          error (yyexc);
          YYERROR;
        }
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;
      YY_STACK_PRINT ();

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, yylhs);
    }
    goto yynewstate;

  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        error (yyla.location, yysyntax_error_ (yystack_[0].state, yyla));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.type_get () == yyeof_)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:

    /* Pacify compilers like GCC when the user code never invokes
       YYERROR and the label yyerrorlab therefore never appears in user
       code.  */
    if (false)
      goto yyerrorlab;
    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    goto yyerrlab1;

  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    {
      stack_symbol_type error_token;
      for (;;)
        {
          yyn = yypact_[yystack_[0].state];
          if (!yy_pact_value_is_default_ (yyn))
            {
              yyn += yyterror_;
              if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == yyterror_)
                {
                  yyn = yytable_[yyn];
                  if (0 < yyn)
                    break;
                }
            }

          // Pop the current state because it cannot handle the error token.
          if (yystack_.size () == 1)
            YYABORT;

          yyerror_range[1].location = yystack_[0].location;
          yy_destroy_ ("Error: popping", yystack_[0]);
          yypop_ ();
          YY_STACK_PRINT ();
        }

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

      // Shift the error token.
      error_token.state = yyn;
      yypush_ ("Shifting", error_token);
    }
    goto yynewstate;

    // Accept.
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;

    // Abort.
  yyabortlab:
    yyresult = 1;
    goto yyreturn;

  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack"
                 << std::endl;
        // Do not try to display the values of the reclaimed symbols,
        // as their printer might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
  }

  void
  Parser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what ());
  }

  // Generate an error message.
  std::string
  Parser::yysyntax_error_ (state_type yystate, const symbol_type& yyla) const
  {
    // Number of reported tokens (one for the "unexpected", one per
    // "expected").
    size_t yycount = 0;
    // Its maximum.
    enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
    // Arguments of yyformat.
    char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];

    /* There are many possibilities here to consider:
       - If this state is a consistent state with a default action, then
         the only way this function was invoked is if the default action
         is an error action.  In that case, don't check for expected
         tokens because there are none.
       - The only way there can be no lookahead present (in yyla) is
         if this state is a consistent state with a default action.
         Thus, detecting the absence of a lookahead is sufficient to
         determine that there is no unexpected or expected token to
         report.  In that case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is
         a consistent state with a default action.  There might have
         been a previous inconsistent state, consistent state with a
         non-default action, or user semantic action that manipulated
         yyla.  (However, yyla is currently not documented for users.)
       - Of course, the expected token list depends on states to have
         correct lookahead information, and it depends on the parser not
         to perform extra reductions after fetching a lookahead from the
         scanner and before detecting a syntax error.  Thus, state
         merging (from LALR or IELR) and default reductions corrupt the
         expected token list.  However, the list is correct for
         canonical LR with one exception: it will still contain any
         token that will not be accepted due to an error action in a
         later state.
    */
    if (!yyla.empty ())
      {
        int yytoken = yyla.type_get ();
        yyarg[yycount++] = yytname_[yytoken];
        int yyn = yypact_[yystate];
        if (!yy_pact_value_is_default_ (yyn))
          {
            /* Start YYX at -YYN if negative to avoid negative indexes in
               YYCHECK.  In other words, skip the first -YYN actions for
               this state because they are default actions.  */
            int yyxbegin = yyn < 0 ? -yyn : 0;
            // Stay within bounds of both yycheck and yytname.
            int yychecklim = yylast_ - yyn + 1;
            int yyxend = yychecklim < yyntokens_ ? yychecklim : yyntokens_;
            for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
              if (yycheck_[yyx + yyn] == yyx && yyx != yyterror_
                  && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
                {
                  if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                    {
                      yycount = 1;
                      break;
                    }
                  else
                    yyarg[yycount++] = yytname_[yyx];
                }
          }
      }

    char const* yyformat = YY_NULLPTR;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
      default: // Avoid compiler warnings.
        YYCASE_ (0, YY_("syntax error"));
        YYCASE_ (1, YY_("syntax error, unexpected %s"));
        YYCASE_ (2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_ (3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_ (4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_ (5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    std::string yyres;
    // Argument number.
    size_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += yytnamerr_ (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const signed char Parser::yypact_ninf_ = -69;

  const signed char Parser::yytable_ninf_ = -1;

  const signed char
  Parser::yypact_[] =
  {
      52,    10,    14,     0,    26,    -4,    42,     9,    56,    52,
     -69,    23,    55,    73,    79,    80,    82,    83,     9,    72,
     -69,    75,    90,    -2,   -69,     9,     9,    21,     9,    93,
     -69,   -69,   -69,   -69,   -69,   -69,   -69,   -69,   -69,    92,
       9,     9,    84,     9,     9,   -69,    39,    94,     9,   100,
       9,     9,   -69,   100,   -69,   100,   -69,    96,     9,     8,
      33,     5,   -69,    -9,   -69,    95,    43,   -69,    63,   -69,
     -69,     8,    44,   -69,   102,    47,   -69,   -69,   107,     5,
      87,   -69,   -69,   -69,    64,   -69,   -69,     9,   -69,     8,
     -69,     9,   -69,   -69,   -69,    48,   108,    89,   -69,     8,
     101,    81,     5,     5,     8,     8,     8,     8,     8,     8,
     -69,   -69,   -69,   -69,   103,   -69,   -69,     8,   -69,   105,
     -69,   -69,   -69,   -69,   -69,   -69,   -69,     8,    49,    54,
     -69,   -69
  };

  const unsigned char
  Parser::yydefact_[] =
  {
       0,     0,     0,     0,     0,     0,     0,     0,     0,     2,
       3,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      52,     0,     0,     0,    47,     0,     0,     0,     0,     0,
       1,     4,     5,     6,     7,     8,     9,    10,    11,     0,
       0,     0,     0,     0,     0,    20,     0,     0,     0,    27,
       0,     0,    13,    27,    53,    27,    48,     0,     0,     0,
       0,     0,    21,    27,    23,     0,     0,    49,     0,    14,
      15,     0,     0,    44,     0,     0,    42,    45,     0,     0,
      26,    30,    31,    32,     0,    29,    39,     0,    22,     0,
      12,     0,    54,    55,    51,     0,     0,     0,    19,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      24,    25,    50,    18,     0,    46,    43,     0,    28,    41,
      40,    33,    34,    38,    37,    35,    36,     0,     0,     0,
      16,    17
  };

  const signed char
  Parser::yypgoto_[] =
  {
     -69,   -69,   -69,   116,   -69,   -69,   -69,   -69,   -69,   -69,
     -69,   -69,    41,   -34,   -52,   -69,   -69,   -69,    -8,   -69,
     -68,   -53,   -32,   -69,    38,    -3,   -69
  };

  const signed char
  Parser::yydefgoto_[] =
  {
      -1,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    63,    64,    62,    80,    81,    82,    83,    84,    85,
      75,    86,    23,    66,    67,    77,    94
  };

  const unsigned char
  Parser::yytable_[] =
  {
      24,    20,    27,    95,    29,    20,    76,    61,    43,    73,
      20,    26,    73,    20,    20,    39,    60,    18,    76,    69,
      19,    70,    45,    46,    87,    49,    72,   101,    79,    88,
      22,    44,    21,    25,    22,    47,   111,    52,    53,    74,
      55,    56,    74,    22,    48,    24,   116,    65,    68,   128,
     119,   120,    28,    57,    32,    24,    30,    78,     1,   129,
       2,     3,    58,     4,    76,     5,    44,    90,    96,     6,
       7,    98,   113,   130,    76,    92,    91,    44,   131,    40,
      99,    99,    99,    93,    65,    41,    33,    99,    68,   104,
     105,   106,   107,   108,   109,    42,   121,   122,   123,   124,
     125,   126,   102,   103,    34,   118,    97,    42,   102,   103,
      35,    36,    50,    37,    38,    51,    61,    59,    54,    71,
      89,   100,   114,   115,   117,    31,   127,   103,   110,   112
  };

  const unsigned char
  Parser::yycheck_[] =
  {
       3,     5,     5,    71,     7,     5,    59,    16,    10,     4,
       5,    15,     4,     5,     5,    18,    48,     7,    71,    53,
       6,    55,    25,    26,    33,    28,    58,    79,    23,    63,
      34,    33,    32,     7,    34,    14,    89,    40,    41,    34,
      43,    44,    34,    34,    23,    48,    99,    50,    51,   117,
     102,   103,    10,    14,    31,    58,     0,    24,     6,   127,
       8,     9,    23,    11,   117,    13,    33,    24,    24,    17,
      18,    24,    24,    24,   127,    12,    33,    33,    24,     7,
      33,    33,    33,    20,    87,    10,    31,    33,    91,    25,
      26,    27,    28,    29,    30,     5,   104,   105,   106,   107,
     108,   109,    21,    22,    31,    24,     4,     5,    21,    22,
      31,    31,    19,    31,    31,    23,    16,    23,    34,    23,
      25,    14,    14,    34,    23,     9,    23,    22,    87,    91
  };

  const unsigned char
  Parser::yystos_[] =
  {
       0,     6,     8,     9,    11,    13,    17,    18,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,     7,     6,
       5,    32,    34,    57,    60,     7,    15,    60,    10,    60,
       0,    38,    31,    31,    31,    31,    31,    31,    31,    60,
       7,    10,     5,    10,    33,    60,    60,    14,    23,    60,
      19,    23,    60,    60,    34,    60,    60,    14,    23,    23,
      57,    16,    48,    46,    47,    60,    58,    59,    60,    48,
      48,    23,    57,     4,    34,    55,    56,    60,    24,    23,
      49,    50,    51,    52,    53,    54,    56,    33,    48,    25,
      24,    33,    12,    20,    61,    55,    24,     4,    24,    33,
      14,    49,    21,    22,    25,    26,    27,    28,    29,    30,
      47,    56,    59,    24,    14,    34,    56,    23,    24,    49,
      49,    53,    53,    53,    53,    53,    53,    23,    55,    55,
      24,    24
  };

  const unsigned char
  Parser::yyr1_[] =
  {
       0,    35,    36,    37,    37,    38,    38,    38,    38,    38,
      38,    38,    39,    40,    41,    41,    42,    42,    42,    42,
      43,    44,    45,    46,    46,    47,    48,    48,    49,    49,
      49,    50,    51,    52,    52,    52,    52,    52,    52,    53,
      54,    54,    55,    55,    56,    56,    56,    57,    57,    58,
      58,    59,    60,    60,    61,    61
  };

  const unsigned char
  Parser::yyr2_[] =
  {
       0,     2,     1,     1,     2,     2,     2,     2,     2,     2,
       2,     2,     6,     4,     5,     5,     9,    10,     7,     6,
       3,     4,     5,     1,     3,     3,     2,     0,     3,     1,
       1,     1,     1,     3,     3,     3,     3,     3,     3,     1,
       3,     3,     1,     3,     1,     1,     3,     1,     3,     1,
       3,     2,     1,     3,     1,     1
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const Parser::yytname_[] =
  {
  "\"end of file\"", "error", "$undefined", "\"end of line\"",
  "\"integer\"", "\"string\"", "CREATE", "TABLE", "SHOW", "SELECT", "FROM",
  "DROP", "INT_TYPE", "INSERT", "VALUES", "INTO", "WHERE", "DELETE",
  "UPDATE", "SET", "BOOL", "OR", "AND", "'('", "')'", "EQUALS",
  "NOT_EQUALS", "LESS", "GREATER", "LESS_EQUALS", "GREATER_EQUALS", "';'",
  "'*'", "','", "'`'", "$accept", "start", "statement_list", "statement",
  "create_statement", "show_statement", "select_statement",
  "insert_statement", "drop_statement", "delete_statement",
  "update_statement", "updated_cols_list", "updated_col_def", "opt_where",
  "expr", "operand", "binary_expr", "comp_expr", "atm_operand",
  "logic_expr", "cols_values_list", "col_value", "cols_names_list",
  "column_def_list", "column_def", "string_val", "column_type", YY_NULLPTR
  };

#if ROFLAN_PARSERDEBUG
  const unsigned short int
  Parser::yyrline_[] =
  {
       0,   130,   130,   136,   140,   147,   148,   149,   150,   151,
     152,   153,   157,   163,   169,   175,   181,   184,   187,   190,
     196,   202,   206,   211,   215,   222,   226,   227,   231,   232,
     236,   243,   247,   251,   252,   253,   254,   255,   256,   260,
     264,   265,   269,   273,   280,   283,   286,   292,   296,   303,
     307,   314,   320,   323,   328,   329
  };

  // Print the state stack on the debug stream.
  void
  Parser::yystack_print_ ()
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << i->state;
    *yycdebug_ << std::endl;
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  Parser::yy_reduce_print_ (int yyrule)
  {
    unsigned yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):" << std::endl;
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // ROFLAN_PARSERDEBUG

  // Symbol number corresponding to token number t.
  Parser::token_number_type
  Parser::yytranslate_ (int t)
  {
    static
    const token_number_type
    translate_table[] =
    {
     0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      23,    24,    32,     2,    33,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    31,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,    34,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    25,    26,
      27,    28,    29,    30
    };
    const unsigned user_token_number_max_ = 283;
    const token_number_type undef_token_ = 2;

    if (static_cast<int> (t) <= yyeof_)
      return yyeof_;
    else if (static_cast<unsigned> (t) <= user_token_number_max_)
      return translate_table[t];
    else
      return undef_token_;
  }


} // roflan_parser
#line 2568 "parser.cc" // lalr1.cc:1164
#line 332 "parser.yy" // lalr1.cc:1165
 /*** Additional Code ***/

void roflan_parser::Parser::error(const Parser::location_type& l,
			    const std::string& m)
{
    driver.error(l, m);
}