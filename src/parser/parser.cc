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
#define yylex   RoflanParserlex

// First part of user declarations.
#line 1 "parser.yy" // lalr1.cc:406
 /*** C/C++ Declarations ***/

#include <stdio.h>
#include <string>
#include <vector>

#line 79 "parser.yy" // lalr1.cc:406


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
#if ROFLANPARSERDEBUG

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

#else // !ROFLANPARSERDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !ROFLANPARSERDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)


namespace RoflanParser {
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
#if ROFLANPARSERDEBUG
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
      case 22: // column_type
        value.copy< ColumnType > (other.value);
        break;

      case 4: // "integer"
        value.copy< int > (other.value);
        break;

      case 21: // column_def
        value.copy< std::shared_ptr<cmd::Column> > (other.value);
        break;

      case 19: // create_statement
        value.copy< std::shared_ptr<cmd::CreateStatement> > (other.value);
        break;

      case 18: // statement
        value.copy< std::shared_ptr<cmd::SQLStatement> > (other.value);
        break;

      case 20: // column_def_list
        value.copy< std::shared_ptr<std::vector<std::shared_ptr<cmd::Column>>> > (other.value);
        break;

      case 17: // statement_list
        value.copy< std::shared_ptr<std::vector<std::shared_ptr<cmd::SQLStatement>>> > (other.value);
        break;

      case 5: // "string"
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
      case 22: // column_type
        value.copy< ColumnType > (v);
        break;

      case 4: // "integer"
        value.copy< int > (v);
        break;

      case 21: // column_def
        value.copy< std::shared_ptr<cmd::Column> > (v);
        break;

      case 19: // create_statement
        value.copy< std::shared_ptr<cmd::CreateStatement> > (v);
        break;

      case 18: // statement
        value.copy< std::shared_ptr<cmd::SQLStatement> > (v);
        break;

      case 20: // column_def_list
        value.copy< std::shared_ptr<std::vector<std::shared_ptr<cmd::Column>>> > (v);
        break;

      case 17: // statement_list
        value.copy< std::shared_ptr<std::vector<std::shared_ptr<cmd::SQLStatement>>> > (v);
        break;

      case 5: // "string"
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
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const ColumnType v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const int v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const std::shared_ptr<cmd::Column> v, const location_type& l)
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
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const std::shared_ptr<cmd::SQLStatement> v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const std::shared_ptr<std::vector<std::shared_ptr<cmd::Column>>> v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const std::shared_ptr<std::vector<std::shared_ptr<cmd::SQLStatement>>> v, const location_type& l)
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
      case 22: // column_type
        value.template destroy< ColumnType > ();
        break;

      case 4: // "integer"
        value.template destroy< int > ();
        break;

      case 21: // column_def
        value.template destroy< std::shared_ptr<cmd::Column> > ();
        break;

      case 19: // create_statement
        value.template destroy< std::shared_ptr<cmd::CreateStatement> > ();
        break;

      case 18: // statement
        value.template destroy< std::shared_ptr<cmd::SQLStatement> > ();
        break;

      case 20: // column_def_list
        value.template destroy< std::shared_ptr<std::vector<std::shared_ptr<cmd::Column>>> > ();
        break;

      case 17: // statement_list
        value.template destroy< std::shared_ptr<std::vector<std::shared_ptr<cmd::SQLStatement>>> > ();
        break;

      case 5: // "string"
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
      case 22: // column_type
        value.move< ColumnType > (s.value);
        break;

      case 4: // "integer"
        value.move< int > (s.value);
        break;

      case 21: // column_def
        value.move< std::shared_ptr<cmd::Column> > (s.value);
        break;

      case 19: // create_statement
        value.move< std::shared_ptr<cmd::CreateStatement> > (s.value);
        break;

      case 18: // statement
        value.move< std::shared_ptr<cmd::SQLStatement> > (s.value);
        break;

      case 20: // column_def_list
        value.move< std::shared_ptr<std::vector<std::shared_ptr<cmd::Column>>> > (s.value);
        break;

      case 17: // statement_list
        value.move< std::shared_ptr<std::vector<std::shared_ptr<cmd::SQLStatement>>> > (s.value);
        break;

      case 5: // "string"
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
  Parser::make_DROP (const location_type& l)
  {
    return symbol_type (token::DROP, l);
  }

  Parser::symbol_type
  Parser::make_INT_TYPE (const location_type& l)
  {
    return symbol_type (token::INT_TYPE, l);
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
      case 22: // column_type
        value.copy< ColumnType > (that.value);
        break;

      case 4: // "integer"
        value.copy< int > (that.value);
        break;

      case 21: // column_def
        value.copy< std::shared_ptr<cmd::Column> > (that.value);
        break;

      case 19: // create_statement
        value.copy< std::shared_ptr<cmd::CreateStatement> > (that.value);
        break;

      case 18: // statement
        value.copy< std::shared_ptr<cmd::SQLStatement> > (that.value);
        break;

      case 20: // column_def_list
        value.copy< std::shared_ptr<std::vector<std::shared_ptr<cmd::Column>>> > (that.value);
        break;

      case 17: // statement_list
        value.copy< std::shared_ptr<std::vector<std::shared_ptr<cmd::SQLStatement>>> > (that.value);
        break;

      case 5: // "string"
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
      case 22: // column_type
        value.move< ColumnType > (that.value);
        break;

      case 4: // "integer"
        value.move< int > (that.value);
        break;

      case 21: // column_def
        value.move< std::shared_ptr<cmd::Column> > (that.value);
        break;

      case 19: // create_statement
        value.move< std::shared_ptr<cmd::CreateStatement> > (that.value);
        break;

      case 18: // statement
        value.move< std::shared_ptr<cmd::SQLStatement> > (that.value);
        break;

      case 20: // column_def_list
        value.move< std::shared_ptr<std::vector<std::shared_ptr<cmd::Column>>> > (that.value);
        break;

      case 17: // statement_list
        value.move< std::shared_ptr<std::vector<std::shared_ptr<cmd::SQLStatement>>> > (that.value);
        break;

      case 5: // "string"
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
      case 22: // column_type
        value.copy< ColumnType > (that.value);
        break;

      case 4: // "integer"
        value.copy< int > (that.value);
        break;

      case 21: // column_def
        value.copy< std::shared_ptr<cmd::Column> > (that.value);
        break;

      case 19: // create_statement
        value.copy< std::shared_ptr<cmd::CreateStatement> > (that.value);
        break;

      case 18: // statement
        value.copy< std::shared_ptr<cmd::SQLStatement> > (that.value);
        break;

      case 20: // column_def_list
        value.copy< std::shared_ptr<std::vector<std::shared_ptr<cmd::Column>>> > (that.value);
        break;

      case 17: // statement_list
        value.copy< std::shared_ptr<std::vector<std::shared_ptr<cmd::SQLStatement>>> > (that.value);
        break;

      case 5: // "string"
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

#if ROFLANPARSERDEBUG
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

#if ROFLANPARSERDEBUG
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
#endif // ROFLANPARSERDEBUG

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
    #line 41 "parser.yy" // lalr1.cc:737
{
    // initialize the initial location object
    yyla.location.begin.filename = yyla.location.end.filename = &driver.streamname;
}

#line 896 "parser.cc" // lalr1.cc:737

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
      case 22: // column_type
        yylhs.value.build< ColumnType > ();
        break;

      case 4: // "integer"
        yylhs.value.build< int > ();
        break;

      case 21: // column_def
        yylhs.value.build< std::shared_ptr<cmd::Column> > ();
        break;

      case 19: // create_statement
        yylhs.value.build< std::shared_ptr<cmd::CreateStatement> > ();
        break;

      case 18: // statement
        yylhs.value.build< std::shared_ptr<cmd::SQLStatement> > ();
        break;

      case 20: // column_def_list
        yylhs.value.build< std::shared_ptr<std::vector<std::shared_ptr<cmd::Column>>> > ();
        break;

      case 17: // statement_list
        yylhs.value.build< std::shared_ptr<std::vector<std::shared_ptr<cmd::SQLStatement>>> > ();
        break;

      case 5: // "string"
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
#line 93 "parser.yy" // lalr1.cc:856
    {
            std::shared_ptr<cmd::Command> result = std::make_shared<cmd::Command>(yystack_[0].value.as< std::shared_ptr<std::vector<std::shared_ptr<cmd::SQLStatement>>> > ());
            driver.SQLParseResult = result;
            driver.SQLParseResult.get()->isValid(true);
        }
#line 1042 "parser.cc" // lalr1.cc:856
    break;

  case 3:
#line 99 "parser.yy" // lalr1.cc:856
    {
            yylhs.value.as< std::shared_ptr<std::vector<std::shared_ptr<cmd::SQLStatement>>> > () = std::make_shared<std::vector<std::shared_ptr<cmd::SQLStatement>>>();
            yylhs.value.as< std::shared_ptr<std::vector<std::shared_ptr<cmd::SQLStatement>>> > ().get()->emplace_back(yystack_[0].value.as< std::shared_ptr<cmd::SQLStatement> > ());
        }
#line 1051 "parser.cc" // lalr1.cc:856
    break;

  case 4:
#line 104 "parser.yy" // lalr1.cc:856
    {
            yylhs.value.as< std::shared_ptr<cmd::SQLStatement> > () = yystack_[0].value.as< std::shared_ptr<cmd::CreateStatement> > ();
        }
#line 1059 "parser.cc" // lalr1.cc:856
    break;

  case 5:
#line 109 "parser.yy" // lalr1.cc:856
    {
            yylhs.value.as< std::shared_ptr<cmd::CreateStatement> > () = std::make_shared<cmd::CreateStatement>(yystack_[4].value.as< std::string > ().c_str());
            yylhs.value.as< std::shared_ptr<cmd::CreateStatement> > ().get()->set_columns(yystack_[2].value.as< std::shared_ptr<std::vector<std::shared_ptr<cmd::Column>>> > ());
        }
#line 1068 "parser.cc" // lalr1.cc:856
    break;

  case 6:
#line 115 "parser.yy" // lalr1.cc:856
    {
            yylhs.value.as< std::shared_ptr<std::vector<std::shared_ptr<cmd::Column>>> > () = std::make_shared<std::vector<std::shared_ptr<cmd::Column>>>();
            yylhs.value.as< std::shared_ptr<std::vector<std::shared_ptr<cmd::Column>>> > ().get()->emplace_back(yystack_[0].value.as< std::shared_ptr<cmd::Column> > ());
        }
#line 1077 "parser.cc" // lalr1.cc:856
    break;

  case 7:
#line 119 "parser.yy" // lalr1.cc:856
    {
            yystack_[2].value.as< std::shared_ptr<std::vector<std::shared_ptr<cmd::Column>>> > ()->emplace_back(yystack_[0].value.as< std::shared_ptr<cmd::Column> > ());
            yylhs.value.as< std::shared_ptr<std::vector<std::shared_ptr<cmd::Column>>> > () = yystack_[2].value.as< std::shared_ptr<std::vector<std::shared_ptr<cmd::Column>>> > ();
        }
#line 1086 "parser.cc" // lalr1.cc:856
    break;

  case 8:
#line 125 "parser.yy" // lalr1.cc:856
    {
		    yylhs.value.as< std::shared_ptr<cmd::Column> > () = std::make_shared<cmd::Column>(yystack_[0].value.as< ColumnType > (), yystack_[1].value.as< std::string > ().c_str());
		}
#line 1094 "parser.cc" // lalr1.cc:856
    break;

  case 9:
#line 131 "parser.yy" // lalr1.cc:856
    { yylhs.value.as< ColumnType > () = ColumnType::INT; }
#line 1100 "parser.cc" // lalr1.cc:856
    break;


#line 1104 "parser.cc" // lalr1.cc:856
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


  const signed char Parser::yypact_ninf_ = -13;

  const signed char Parser::yytable_ninf_ = -1;

  const signed char
  Parser::yypact_[] =
  {
      -5,    -4,     4,   -13,   -13,   -13,     0,   -13,    -3,     1,
      -1,   -12,   -13,   -13,   -13,    -6,     1,   -13,   -13
  };

  const unsigned char
  Parser::yydefact_[] =
  {
       0,     0,     0,     2,     3,     4,     0,     1,     0,     0,
       0,     0,     6,     9,     8,     0,     0,     5,     7
  };

  const signed char
  Parser::yypgoto_[] =
  {
     -13,   -13,   -13,   -13,   -13,   -13,    -2,   -13
  };

  const signed char
  Parser::yydefgoto_[] =
  {
      -1,     2,     3,     4,     5,    11,    12,    14
  };

  const unsigned char
  Parser::yytable_[] =
  {
      15,     1,    16,     6,     7,     8,    10,    17,     9,    13,
       0,     0,     0,     0,    18
  };

  const signed char
  Parser::yycheck_[] =
  {
      12,     6,    14,     7,     0,     5,     5,    13,    11,    10,
      -1,    -1,    -1,    -1,    16
  };

  const unsigned char
  Parser::yystos_[] =
  {
       0,     6,    16,    17,    18,    19,     7,     0,     5,    11,
       5,    20,    21,    10,    22,    12,    14,    13,    21
  };

  const unsigned char
  Parser::yyr1_[] =
  {
       0,    15,    16,    17,    18,    19,    20,    20,    21,    22
  };

  const unsigned char
  Parser::yyr2_[] =
  {
       0,     2,     1,     1,     1,     7,     1,     3,     2,     1
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const Parser::yytname_[] =
  {
  "\"end of file\"", "error", "$undefined", "\"end of line\"",
  "\"integer\"", "\"string\"", "CREATE", "TABLE", "SHOW", "DROP",
  "INT_TYPE", "'('", "')'", "';'", "','", "$accept", "start",
  "statement_list", "statement", "create_statement", "column_def_list",
  "column_def", "column_type", YY_NULLPTR
  };

#if ROFLANPARSERDEBUG
  const unsigned char
  Parser::yyrline_[] =
  {
       0,    93,    93,    99,   104,   109,   115,   119,   125,   131
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
#endif // ROFLANPARSERDEBUG

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
      11,    12,     2,     2,    14,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    13,
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
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10
    };
    const unsigned user_token_number_max_ = 265;
    const token_number_type undef_token_ = 2;

    if (static_cast<int> (t) <= yyeof_)
      return yyeof_;
    else if (static_cast<unsigned> (t) <= user_token_number_max_)
      return translate_table[t];
    else
      return undef_token_;
  }


} // RoflanParser
#line 1521 "parser.cc" // lalr1.cc:1164
#line 134 "parser.yy" // lalr1.cc:1165
 /*** Additional Code ***/

void RoflanParser::Parser::error(const Parser::location_type& l,
			    const std::string& m)
{
    driver.error(l, m);
}
