// A Bison parser, made by GNU Bison 3.7.2.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2020 Free Software Foundation, Inc.

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

// DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
// especially those whose name start with YY_ or yy_.  They are
// private implementation details that can be changed or removed.


// Take the name prefix into account.
#define yylex   FSMLlex

// First part of user prologue.
#line 10 "fsml.yy"

#include <iostream>
#include <stdio.h>
#include <string>
#include "fsml.h"


#ifdef DEBUG
#define log(...) printf(__VA_ARGS__)
#else
#define log(...)
#endif

class FSMLDriver;

std::string tmp_initializer;
std::string tmp_type;
std::string tmp_ptr_type;
std::string tmp_declarator;
#line 34 "fsml.yy"

#include "FSMLDriver.h"
#include "fsml_inner.h"

FSMState * tmpState = nullptr;
FSMTransition * tmpTrans = nullptr;
FSMUntil * tmpUntil = nullptr;

#line 72 "fsml.cc"


#include "fsml.hh"




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


// Whether we are compiled with exception support.
#ifndef YY_EXCEPTIONS
# if defined __GNUC__ && !defined __EXCEPTIONS
#  define YY_EXCEPTIONS 0
# else
#  define YY_EXCEPTIONS 1
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
    while (false)
# endif


// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << '\n';                       \
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
      yy_stack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

namespace FSML {
#line 169 "fsml.cc"

  /// Build a parser object.
  FSMLParser::FSMLParser (FSMLDriver& driver_yyarg)
#if YYDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr),
#else
    :
#endif
      driver (driver_yyarg)
  {}

  FSMLParser::~FSMLParser ()
  {}

  FSMLParser::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------------.
  | symbol kinds.  |
  `---------------*/

  // basic_symbol.
  template <typename Base>
  FSMLParser::basic_symbol<Base>::basic_symbol (const basic_symbol& that)
    : Base (that)
    , value ()
    , location (that.location)
  {
    switch (this->kind ())
    {
      case symbol_kind::S_FLOATING_CONSTANT: // FLOATING_CONSTANT
        value.copy< float > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_INTEGER_CONSTANT: // INTEGER_CONSTANT
        value.copy< int > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_state_type: // state_type
        value.copy< state_type_t > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_C_CODE_BLOCK: // C_CODE_BLOCK
      case symbol_kind::S_C_CONDITION_BLOCK: // C_CONDITION_BLOCK
      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
      case symbol_kind::S_CHARACTER_CONSTANT: // CHARACTER_CONSTANT
      case symbol_kind::S_type_specifier_list: // type_specifier_list
      case symbol_kind::S_type_specifier: // type_specifier
      case symbol_kind::S_struct_or_union_specifier: // struct_or_union_specifier
      case symbol_kind::S_struct_or_union: // struct_or_union
      case symbol_kind::S_enum_specifier: // enum_specifier
      case symbol_kind::S_typedef_name: // typedef_name
      case symbol_kind::S_constant: // constant
      case symbol_kind::S_enumeration_constant: // enumeration_constant
      case symbol_kind::S_timer_initializer: // timer_initializer
      case symbol_kind::S_state_specifier: // state_specifier
      case symbol_kind::S_state_c_code: // state_c_code
      case symbol_kind::S_until_condition: // until_condition
        value.copy< std::string > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_variable_specifier: // variable_specifier
        value.copy< var_family_t > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

  }



  template <typename Base>
  FSMLParser::symbol_kind_type
  FSMLParser::basic_symbol<Base>::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }

  template <typename Base>
  bool
  FSMLParser::basic_symbol<Base>::empty () const YY_NOEXCEPT
  {
    return this->kind () == symbol_kind::S_YYEMPTY;
  }

  template <typename Base>
  void
  FSMLParser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move (s);
    switch (this->kind ())
    {
      case symbol_kind::S_FLOATING_CONSTANT: // FLOATING_CONSTANT
        value.move< float > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_INTEGER_CONSTANT: // INTEGER_CONSTANT
        value.move< int > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_state_type: // state_type
        value.move< state_type_t > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_C_CODE_BLOCK: // C_CODE_BLOCK
      case symbol_kind::S_C_CONDITION_BLOCK: // C_CONDITION_BLOCK
      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
      case symbol_kind::S_CHARACTER_CONSTANT: // CHARACTER_CONSTANT
      case symbol_kind::S_type_specifier_list: // type_specifier_list
      case symbol_kind::S_type_specifier: // type_specifier
      case symbol_kind::S_struct_or_union_specifier: // struct_or_union_specifier
      case symbol_kind::S_struct_or_union: // struct_or_union
      case symbol_kind::S_enum_specifier: // enum_specifier
      case symbol_kind::S_typedef_name: // typedef_name
      case symbol_kind::S_constant: // constant
      case symbol_kind::S_enumeration_constant: // enumeration_constant
      case symbol_kind::S_timer_initializer: // timer_initializer
      case symbol_kind::S_state_specifier: // state_specifier
      case symbol_kind::S_state_c_code: // state_c_code
      case symbol_kind::S_until_condition: // until_condition
        value.move< std::string > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_variable_specifier: // variable_specifier
        value.move< var_family_t > (YY_MOVE (s.value));
        break;

      default:
        break;
    }

    location = YY_MOVE (s.location);
  }

  // by_kind.
  FSMLParser::by_kind::by_kind ()
    : kind_ (symbol_kind::S_YYEMPTY)
  {}

#if 201103L <= YY_CPLUSPLUS
  FSMLParser::by_kind::by_kind (by_kind&& that)
    : kind_ (that.kind_)
  {
    that.clear ();
  }
#endif

  FSMLParser::by_kind::by_kind (const by_kind& that)
    : kind_ (that.kind_)
  {}

  FSMLParser::by_kind::by_kind (token_kind_type t)
    : kind_ (yytranslate_ (t))
  {}

  void
  FSMLParser::by_kind::clear ()
  {
    kind_ = symbol_kind::S_YYEMPTY;
  }

  void
  FSMLParser::by_kind::move (by_kind& that)
  {
    kind_ = that.kind_;
    that.clear ();
  }

  FSMLParser::symbol_kind_type
  FSMLParser::by_kind::kind () const YY_NOEXCEPT
  {
    return kind_;
  }

  FSMLParser::symbol_kind_type
  FSMLParser::by_kind::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }


  // by_state.
  FSMLParser::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

  FSMLParser::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
  FSMLParser::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
  FSMLParser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  FSMLParser::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

  FSMLParser::symbol_kind_type
  FSMLParser::by_state::kind () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return symbol_kind::S_YYEMPTY;
    else
      return YY_CAST (symbol_kind_type, yystos_[+state]);
  }

  FSMLParser::stack_symbol_type::stack_symbol_type ()
  {}

  FSMLParser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state), YY_MOVE (that.location))
  {
    switch (that.kind ())
    {
      case symbol_kind::S_FLOATING_CONSTANT: // FLOATING_CONSTANT
        value.YY_MOVE_OR_COPY< float > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_INTEGER_CONSTANT: // INTEGER_CONSTANT
        value.YY_MOVE_OR_COPY< int > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_state_type: // state_type
        value.YY_MOVE_OR_COPY< state_type_t > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_C_CODE_BLOCK: // C_CODE_BLOCK
      case symbol_kind::S_C_CONDITION_BLOCK: // C_CONDITION_BLOCK
      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
      case symbol_kind::S_CHARACTER_CONSTANT: // CHARACTER_CONSTANT
      case symbol_kind::S_type_specifier_list: // type_specifier_list
      case symbol_kind::S_type_specifier: // type_specifier
      case symbol_kind::S_struct_or_union_specifier: // struct_or_union_specifier
      case symbol_kind::S_struct_or_union: // struct_or_union
      case symbol_kind::S_enum_specifier: // enum_specifier
      case symbol_kind::S_typedef_name: // typedef_name
      case symbol_kind::S_constant: // constant
      case symbol_kind::S_enumeration_constant: // enumeration_constant
      case symbol_kind::S_timer_initializer: // timer_initializer
      case symbol_kind::S_state_specifier: // state_specifier
      case symbol_kind::S_state_c_code: // state_c_code
      case symbol_kind::S_until_condition: // until_condition
        value.YY_MOVE_OR_COPY< std::string > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_variable_specifier: // variable_specifier
        value.YY_MOVE_OR_COPY< var_family_t > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

#if 201103L <= YY_CPLUSPLUS
    // that is emptied.
    that.state = empty_state;
#endif
  }

  FSMLParser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s, YY_MOVE (that.location))
  {
    switch (that.kind ())
    {
      case symbol_kind::S_FLOATING_CONSTANT: // FLOATING_CONSTANT
        value.move< float > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_INTEGER_CONSTANT: // INTEGER_CONSTANT
        value.move< int > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_state_type: // state_type
        value.move< state_type_t > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_C_CODE_BLOCK: // C_CODE_BLOCK
      case symbol_kind::S_C_CONDITION_BLOCK: // C_CONDITION_BLOCK
      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
      case symbol_kind::S_CHARACTER_CONSTANT: // CHARACTER_CONSTANT
      case symbol_kind::S_type_specifier_list: // type_specifier_list
      case symbol_kind::S_type_specifier: // type_specifier
      case symbol_kind::S_struct_or_union_specifier: // struct_or_union_specifier
      case symbol_kind::S_struct_or_union: // struct_or_union
      case symbol_kind::S_enum_specifier: // enum_specifier
      case symbol_kind::S_typedef_name: // typedef_name
      case symbol_kind::S_constant: // constant
      case symbol_kind::S_enumeration_constant: // enumeration_constant
      case symbol_kind::S_timer_initializer: // timer_initializer
      case symbol_kind::S_state_specifier: // state_specifier
      case symbol_kind::S_state_c_code: // state_c_code
      case symbol_kind::S_until_condition: // until_condition
        value.move< std::string > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_variable_specifier: // variable_specifier
        value.move< var_family_t > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

    // that is emptied.
    that.kind_ = symbol_kind::S_YYEMPTY;
  }

#if YY_CPLUSPLUS < 201103L
  FSMLParser::stack_symbol_type&
  FSMLParser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_FLOATING_CONSTANT: // FLOATING_CONSTANT
        value.copy< float > (that.value);
        break;

      case symbol_kind::S_INTEGER_CONSTANT: // INTEGER_CONSTANT
        value.copy< int > (that.value);
        break;

      case symbol_kind::S_state_type: // state_type
        value.copy< state_type_t > (that.value);
        break;

      case symbol_kind::S_C_CODE_BLOCK: // C_CODE_BLOCK
      case symbol_kind::S_C_CONDITION_BLOCK: // C_CONDITION_BLOCK
      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
      case symbol_kind::S_CHARACTER_CONSTANT: // CHARACTER_CONSTANT
      case symbol_kind::S_type_specifier_list: // type_specifier_list
      case symbol_kind::S_type_specifier: // type_specifier
      case symbol_kind::S_struct_or_union_specifier: // struct_or_union_specifier
      case symbol_kind::S_struct_or_union: // struct_or_union
      case symbol_kind::S_enum_specifier: // enum_specifier
      case symbol_kind::S_typedef_name: // typedef_name
      case symbol_kind::S_constant: // constant
      case symbol_kind::S_enumeration_constant: // enumeration_constant
      case symbol_kind::S_timer_initializer: // timer_initializer
      case symbol_kind::S_state_specifier: // state_specifier
      case symbol_kind::S_state_c_code: // state_c_code
      case symbol_kind::S_until_condition: // until_condition
        value.copy< std::string > (that.value);
        break;

      case symbol_kind::S_variable_specifier: // variable_specifier
        value.copy< var_family_t > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    return *this;
  }

  FSMLParser::stack_symbol_type&
  FSMLParser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_FLOATING_CONSTANT: // FLOATING_CONSTANT
        value.move< float > (that.value);
        break;

      case symbol_kind::S_INTEGER_CONSTANT: // INTEGER_CONSTANT
        value.move< int > (that.value);
        break;

      case symbol_kind::S_state_type: // state_type
        value.move< state_type_t > (that.value);
        break;

      case symbol_kind::S_C_CODE_BLOCK: // C_CODE_BLOCK
      case symbol_kind::S_C_CONDITION_BLOCK: // C_CONDITION_BLOCK
      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
      case symbol_kind::S_CHARACTER_CONSTANT: // CHARACTER_CONSTANT
      case symbol_kind::S_type_specifier_list: // type_specifier_list
      case symbol_kind::S_type_specifier: // type_specifier
      case symbol_kind::S_struct_or_union_specifier: // struct_or_union_specifier
      case symbol_kind::S_struct_or_union: // struct_or_union
      case symbol_kind::S_enum_specifier: // enum_specifier
      case symbol_kind::S_typedef_name: // typedef_name
      case symbol_kind::S_constant: // constant
      case symbol_kind::S_enumeration_constant: // enumeration_constant
      case symbol_kind::S_timer_initializer: // timer_initializer
      case symbol_kind::S_state_specifier: // state_specifier
      case symbol_kind::S_state_c_code: // state_c_code
      case symbol_kind::S_until_condition: // until_condition
        value.move< std::string > (that.value);
        break;

      case symbol_kind::S_variable_specifier: // variable_specifier
        value.move< var_family_t > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    // that is emptied.
    that.state = empty_state;
    return *this;
  }
#endif

  template <typename Base>
  void
  FSMLParser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if YYDEBUG
  template <typename Base>
  void
  FSMLParser::yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YYUSE (yyoutput);
    if (yysym.empty ())
      yyo << "empty symbol";
    else
      {
        symbol_kind_type yykind = yysym.kind ();
        yyo << (yykind < YYNTOKENS ? "token" : "nterm")
            << ' ' << yysym.name () << " ("
            << yysym.location << ": ";
        YYUSE (yykind);
        yyo << ')';
      }
  }
#endif

  void
  FSMLParser::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
  FSMLParser::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
  FSMLParser::yypop_ (int n)
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  FSMLParser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  FSMLParser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  FSMLParser::debug_level_type
  FSMLParser::debug_level () const
  {
    return yydebug_;
  }

  void
  FSMLParser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  FSMLParser::state_type
  FSMLParser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - YYNTOKENS] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - YYNTOKENS];
  }

  bool
  FSMLParser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  FSMLParser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  FSMLParser::operator() ()
  {
    return parse ();
  }

  int
  FSMLParser::parse ()
  {
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

#if YY_EXCEPTIONS
    try
#endif // YY_EXCEPTIONS
      {
    YYCDEBUG << "Starting parse\n";


    // User initialization code.
#line 44 "fsml.yy"
{
  // Initialize the initial location.
  yyla.location.begin.filename = yyla.location.end.filename = driver.FilenamePtr();
}

#line 735 "fsml.cc"


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, YY_MOVE (yyla));

  /*-----------------------------------------------.
  | yynewstate -- push a new symbol on the stack.  |
  `-----------------------------------------------*/
  yynewstate:
    YYCDEBUG << "Entering state " << int (yystack_[0].state) << '\n';
    YY_STACK_PRINT ();

    // Accept?
    if (yystack_[0].state == yyfinal_)
      YYACCEPT;

    goto yybackup;


  /*-----------.
  | yybackup.  |
  `-----------*/
  yybackup:
    // Try to take a decision without lookahead.
    yyn = yypact_[+yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token\n";
#if YY_EXCEPTIONS
        try
#endif // YY_EXCEPTIONS
          {
            yyla.kind_ = yytranslate_ (yylex (&yyla.value, &yyla.location, driver));
          }
#if YY_EXCEPTIONS
        catch (const syntax_error& yyexc)
          {
            YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
            error (yyexc);
            goto yyerrlab1;
          }
#endif // YY_EXCEPTIONS
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    if (yyla.kind () == symbol_kind::S_YYerror)
    {
      // The scanner already issued an error message, process directly
      // to error recovery.  But do not keep the error token as
      // lookahead, it is too special and may lead us to an endless
      // loop in error recovery. */
      yyla.kind_ = symbol_kind::S_YYUNDEF;
      goto yyerrlab1;
    }

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.kind ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.kind ())
      {
        goto yydefault;
      }

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
    yypush_ ("Shifting", state_type (yyn), YY_MOVE (yyla));
    goto yynewstate;


  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[+yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;


  /*-----------------------------.
  | yyreduce -- do a reduction.  |
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
      case symbol_kind::S_FLOATING_CONSTANT: // FLOATING_CONSTANT
        yylhs.value.emplace< float > ();
        break;

      case symbol_kind::S_INTEGER_CONSTANT: // INTEGER_CONSTANT
        yylhs.value.emplace< int > ();
        break;

      case symbol_kind::S_state_type: // state_type
        yylhs.value.emplace< state_type_t > ();
        break;

      case symbol_kind::S_C_CODE_BLOCK: // C_CODE_BLOCK
      case symbol_kind::S_C_CONDITION_BLOCK: // C_CONDITION_BLOCK
      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
      case symbol_kind::S_CHARACTER_CONSTANT: // CHARACTER_CONSTANT
      case symbol_kind::S_type_specifier_list: // type_specifier_list
      case symbol_kind::S_type_specifier: // type_specifier
      case symbol_kind::S_struct_or_union_specifier: // struct_or_union_specifier
      case symbol_kind::S_struct_or_union: // struct_or_union
      case symbol_kind::S_enum_specifier: // enum_specifier
      case symbol_kind::S_typedef_name: // typedef_name
      case symbol_kind::S_constant: // constant
      case symbol_kind::S_enumeration_constant: // enumeration_constant
      case symbol_kind::S_timer_initializer: // timer_initializer
      case symbol_kind::S_state_specifier: // state_specifier
      case symbol_kind::S_state_c_code: // state_c_code
      case symbol_kind::S_until_condition: // until_condition
        yylhs.value.emplace< std::string > ();
        break;

      case symbol_kind::S_variable_specifier: // variable_specifier
        yylhs.value.emplace< var_family_t > ();
        break;

      default:
        break;
    }


      // Default location.
      {
        stack_type::slice range (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, range, yylen);
        yyerror_range[1].location = yylhs.location;
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
#if YY_EXCEPTIONS
      try
#endif // YY_EXCEPTIONS
        {
          switch (yyn)
            {
  case 9: // declaration: DECL_KEY C_CODE_BLOCK
#line 84 "fsml.yy"
                                    { 
		if (driver.Decl(YY_MOVE (yystack_[0].value.as < std::string > ())) == false) {
			driver.error(yylhs.location, driver.GetLastError()); 
			YYERROR; 
		}
	}
#line 912 "fsml.cc"
    break;

  case 10: // export: EXPORT_KEY C_CODE_BLOCK
#line 91 "fsml.yy"
                                 {
		if (driver.Export(YY_MOVE (yystack_[0].value.as < std::string > ())) == false) {
			driver.error(yylhs.location, driver.GetLastError()); 
			YYERROR; 
		}
	}
#line 923 "fsml.cc"
    break;

  case 13: // time_specifier: TIME_KEY C_CODE_BLOCK
#line 102 "fsml.yy"
                                       { 
		if (driver.TimeSpec(YY_MOVE (yystack_[0].value.as < std::string > ())) == false) { 
			driver.error(yylhs.location, driver.GetLastError()); 
			YYERROR; 
		}; 
	}
#line 934 "fsml.cc"
    break;

  case 14: // period_specifier: PERIOD_KEY C_CODE_BLOCK
#line 109 "fsml.yy"
                                           {
		if (driver.PeriodSpec(YY_MOVE (yystack_[0].value.as < std::string > ())) == false) { 
			driver.error(yylhs.location, driver.GetLastError()); 
			YYERROR; 
		}; 
	}
#line 945 "fsml.cc"
    break;

  case 15: // fsm: FSM_KEY IDENTIFIER LCB fsm_objects_list RCB
#line 116 "fsml.yy"
                                                  { driver.FsmName(YY_MOVE (yystack_[3].value.as < std::string > ())); }
#line 951 "fsml.cc"
    break;

  case 21: // variable_declaration: variable_specifier type_specifier_list init_declarator SC
#line 129 "fsml.yy"
                                                {
							bool result = driver.AddVariable(
													YY_MOVE (yystack_[3].value.as < var_family_t > ()), 
													tmp_type + (tmp_ptr_type.size() ? " " : "") + tmp_ptr_type, 
													tmp_declarator, 
													tmp_initializer);
							tmp_initializer.clear();
							tmp_ptr_type.clear();
							if (result == false) {
								driver.error(yylhs.location, driver.GetLastError()); 
								YYERROR; 
							}
						}
#line 969 "fsml.cc"
    break;

  case 23: // type_specifier_list: type_specifier
#line 145 "fsml.yy"
                                                                                { tmp_type = YY_MOVE (yystack_[0].value.as < std::string > ()); }
#line 975 "fsml.cc"
    break;

  case 24: // type_specifier_list: type_specifier_list type_specifier
#line 146 "fsml.yy"
                                                                                { tmp_type.append(" " + YY_MOVE (yystack_[0].value.as < std::string > ())); }
#line 981 "fsml.cc"
    break;

  case 25: // variable_specifier: VAR_KEY
#line 149 "fsml.yy"
                                        { yylhs.value.as < var_family_t > () = VariableFamily_VAR; }
#line 987 "fsml.cc"
    break;

  case 26: // variable_specifier: INPUT_KEY
#line 150 "fsml.yy"
                                                        { yylhs.value.as < var_family_t > () = VariableFamily_INPUT; }
#line 993 "fsml.cc"
    break;

  case 27: // variable_specifier: OUTPUT_KEY
#line 151 "fsml.yy"
                                                        { yylhs.value.as < var_family_t > () = VariableFamily_OUTPUT; }
#line 999 "fsml.cc"
    break;

  case 28: // type_specifier: VOID
#line 154 "fsml.yy"
                                                { yylhs.value.as < std::string > () = std::string("void"); }
#line 1005 "fsml.cc"
    break;

  case 29: // type_specifier: CHAR
#line 155 "fsml.yy"
                                                                { yylhs.value.as < std::string > () = std::string("char"); }
#line 1011 "fsml.cc"
    break;

  case 30: // type_specifier: SHORT
#line 156 "fsml.yy"
                                                                { yylhs.value.as < std::string > () = std::string("short"); }
#line 1017 "fsml.cc"
    break;

  case 31: // type_specifier: INT
#line 157 "fsml.yy"
                                                                { yylhs.value.as < std::string > () = std::string("int"); }
#line 1023 "fsml.cc"
    break;

  case 32: // type_specifier: LONG
#line 158 "fsml.yy"
                                                                { yylhs.value.as < std::string > () = std::string("long"); }
#line 1029 "fsml.cc"
    break;

  case 33: // type_specifier: FLOAT
#line 159 "fsml.yy"
                                                                { yylhs.value.as < std::string > () = std::string("float"); }
#line 1035 "fsml.cc"
    break;

  case 34: // type_specifier: DOUBLE
#line 160 "fsml.yy"
                                                                { yylhs.value.as < std::string > () = std::string("double"); }
#line 1041 "fsml.cc"
    break;

  case 35: // type_specifier: SIGNED
#line 161 "fsml.yy"
                                                                { yylhs.value.as < std::string > () = std::string("signed"); }
#line 1047 "fsml.cc"
    break;

  case 36: // type_specifier: UNSIGNED
#line 162 "fsml.yy"
                                                        { yylhs.value.as < std::string > () = std::string("unsigned"); }
#line 1053 "fsml.cc"
    break;

  case 37: // type_specifier: struct_or_union_specifier
#line 163 "fsml.yy"
                                                        { yylhs.value.as < std::string > () = YY_MOVE (yystack_[0].value.as < std::string > ()); }
#line 1059 "fsml.cc"
    break;

  case 38: // type_specifier: enum_specifier
#line 164 "fsml.yy"
                                                        { yylhs.value.as < std::string > () = YY_MOVE (yystack_[0].value.as < std::string > ()); }
#line 1065 "fsml.cc"
    break;

  case 39: // type_specifier: typedef_name
#line 165 "fsml.yy"
                                                        { yylhs.value.as < std::string > () = YY_MOVE (yystack_[0].value.as < std::string > ()); }
#line 1071 "fsml.cc"
    break;

  case 40: // struct_or_union_specifier: struct_or_union IDENTIFIER
#line 168 "fsml.yy"
                                                       { yylhs.value.as < std::string > () = YY_MOVE (yystack_[1].value.as < std::string > ()) + " " + YY_MOVE (yystack_[0].value.as < std::string > ()); }
#line 1077 "fsml.cc"
    break;

  case 41: // struct_or_union: STRUCT
#line 170 "fsml.yy"
                                                { yylhs.value.as < std::string > () = std::string("struct"); }
#line 1083 "fsml.cc"
    break;

  case 42: // struct_or_union: UNION
#line 171 "fsml.yy"
                                                                { yylhs.value.as < std::string > () = std::string("union"); }
#line 1089 "fsml.cc"
    break;

  case 43: // enum_specifier: ENUM IDENTIFIER
#line 174 "fsml.yy"
                                        { yylhs.value.as < std::string > () = std::string("enum " + YY_MOVE (yystack_[0].value.as < std::string > ())); }
#line 1095 "fsml.cc"
    break;

  case 44: // typedef_name: IDENTIFIER
#line 177 "fsml.yy"
                                                { yylhs.value.as < std::string > () = YY_MOVE (yystack_[0].value.as < std::string > ()); }
#line 1101 "fsml.cc"
    break;

  case 46: // initializer: constant
#line 182 "fsml.yy"
                                        { tmp_initializer = YY_MOVE (yystack_[0].value.as < std::string > ()); }
#line 1107 "fsml.cc"
    break;

  case 47: // initializer: LCB constant RCB
#line 183 "fsml.yy"
                                                { tmp_initializer = std::string("{" + YY_MOVE (yystack_[1].value.as < std::string > ()) + "}"); }
#line 1113 "fsml.cc"
    break;

  case 50: // direct_declarator: IDENTIFIER
#line 190 "fsml.yy"
                                                { tmp_declarator = YY_MOVE (yystack_[0].value.as < std::string > ()); }
#line 1119 "fsml.cc"
    break;

  case 51: // pointer: STAR
#line 193 "fsml.yy"
                                                                { tmp_ptr_type.append("*"); }
#line 1125 "fsml.cc"
    break;

  case 52: // pointer: STAR pointer
#line 194 "fsml.yy"
                                                                { tmp_ptr_type.append("*"); }
#line 1131 "fsml.cc"
    break;

  case 53: // constant: INTEGER_CONSTANT
#line 197 "fsml.yy"
                                                        { yylhs.value.as < std::string > () = std::to_string(YY_MOVE (yystack_[0].value.as < int > ())); }
#line 1137 "fsml.cc"
    break;

  case 54: // constant: CHARACTER_CONSTANT
#line 198 "fsml.yy"
                                                        { yylhs.value.as < std::string > () = YY_MOVE (yystack_[0].value.as < std::string > ()); }
#line 1143 "fsml.cc"
    break;

  case 55: // constant: FLOATING_CONSTANT
#line 199 "fsml.yy"
                                                        { yylhs.value.as < std::string > () = std::to_string(YY_MOVE (yystack_[0].value.as < float > ())); }
#line 1149 "fsml.cc"
    break;

  case 56: // constant: enumeration_constant
#line 200 "fsml.yy"
                                                        { yylhs.value.as < std::string > () = YY_MOVE (yystack_[0].value.as < std::string > ()); }
#line 1155 "fsml.cc"
    break;

  case 57: // enumeration_constant: IDENTIFIER
#line 203 "fsml.yy"
                                                { yylhs.value.as < std::string > () = YY_MOVE (yystack_[0].value.as < std::string > ()); }
#line 1161 "fsml.cc"
    break;

  case 58: // timer_specifier: TIMER_KEY IDENTIFIER LB timer_initializer RB
#line 207 "fsml.yy"
                                        {
						if (driver.AddTimer(YY_MOVE (yystack_[3].value.as < std::string > ()), YY_MOVE (yystack_[1].value.as < std::string > ())) == false) {
							driver.error(yylhs.location, driver.GetLastError()); 
							YYERROR; 
						};
					}
#line 1172 "fsml.cc"
    break;

  case 59: // timer_initializer: INTEGER_CONSTANT
#line 215 "fsml.yy"
                                        { yylhs.value.as < std::string > () = std::to_string(YY_MOVE (yystack_[0].value.as < int > ())); }
#line 1178 "fsml.cc"
    break;

  case 60: // timer_initializer: IDENTIFIER
#line 216 "fsml.yy"
                                                                { yylhs.value.as < std::string > () = YY_MOVE (yystack_[0].value.as < std::string > ()); }
#line 1184 "fsml.cc"
    break;

  case 61: // state: state_specifier state_decorator_list SC
#line 220 "fsml.yy"
                { 
			if (driver.AddState(tmpState) == false) {
				driver.error(yylhs.location, driver.GetLastError()); 
				YYERROR; 
			} 
		}
#line 1195 "fsml.cc"
    break;

  case 62: // $@1: %empty
#line 227 "fsml.yy"
                            { tmpState = new FSMState(driver); }
#line 1201 "fsml.cc"
    break;

  case 63: // $@2: %empty
#line 229 "fsml.yy"
                                             { tmpState->Name(YY_MOVE (yystack_[0].value.as < std::string > ())); }
#line 1207 "fsml.cc"
    break;

  case 64: // state_specifier: STATE_KEY $@1 state_type_specifier IDENTIFIER $@2 state_c_code
#line 230 "fsml.yy"
                                               { tmpState->Code(YY_MOVE (yystack_[0].value.as < std::string > ())); }
#line 1213 "fsml.cc"
    break;

  case 67: // state_c_code: C_CODE_BLOCK
#line 237 "fsml.yy"
                                        { yylhs.value.as < std::string > () = YY_MOVE (yystack_[0].value.as < std::string > ()); }
#line 1219 "fsml.cc"
    break;

  case 68: // state_c_code: %empty
#line 238 "fsml.yy"
                                                { yylhs.value.as < std::string > () = std::string(); }
#line 1225 "fsml.cc"
    break;

  case 69: // state_type_list: state_type
#line 241 "fsml.yy"
                                                                                { tmpState->AddType(YY_MOVE (yystack_[0].value.as < state_type_t > ())); }
#line 1231 "fsml.cc"
    break;

  case 70: // state_type_list: state_type_list COMMA state_type
#line 242 "fsml.yy"
                                                                                { tmpState->AddType(YY_MOVE (yystack_[0].value.as < state_type_t > ())); }
#line 1237 "fsml.cc"
    break;

  case 71: // state_type: RESET
#line 245 "fsml.yy"
                                { yylhs.value.as < state_type_t > () = kStateTypeReset; }
#line 1243 "fsml.cc"
    break;

  case 72: // state_type: END
#line 246 "fsml.yy"
                                        { yylhs.value.as < state_type_t > () = kStateTypeEnd; }
#line 1249 "fsml.cc"
    break;

  case 73: // state_type: ERR
#line 247 "fsml.yy"
                                        { yylhs.value.as < state_type_t > () = kStateTypeErr; }
#line 1255 "fsml.cc"
    break;

  case 77: // state_decorator: transition_specifier
#line 256 "fsml.yy"
                                        { tmpState->AddTransition(tmpTrans); }
#line 1261 "fsml.cc"
    break;

  case 80: // transition_c_code: C_CODE_BLOCK
#line 263 "fsml.yy"
                                        { tmpTrans->Code(YY_MOVE (yystack_[0].value.as < std::string > ())); }
#line 1267 "fsml.cc"
    break;

  case 82: // transition_condition: C_CONDITION_BLOCK
#line 267 "fsml.yy"
                                                                        { tmpTrans = new FSMTransition(driver, TransType_Normal, YY_MOVE (yystack_[0].value.as < std::string > ())); }
#line 1273 "fsml.cc"
    break;

  case 83: // transition_condition: TIMEOUT_KEY LB IDENTIFIER RB
#line 268 "fsml.yy"
                                                                        { 
						 std::string timer = YY_MOVE (yystack_[1].value.as < std::string > ());
						 if (driver.TimerExists(timer)) {
						 	tmpTrans = new FSMTransition(driver, TransType_Timeout, timer);
						 }
						 else {
							 driver.error(yylhs.location, std::string("timer <" + timer + "> is not defined"));
							 YYERROR;
						 }
					 }
#line 1288 "fsml.cc"
    break;

  case 84: // transition_actuator: GO IDENTIFIER
#line 280 "fsml.yy"
                                                { tmpTrans->Actuator(TransActuator_GO); tmpTrans->EndState(YY_MOVE (yystack_[0].value.as < std::string > ())); }
#line 1294 "fsml.cc"
    break;

  case 85: // transition_actuator: ERR IDENTIFIER
#line 281 "fsml.yy"
                                                                { tmpTrans->Actuator(TransActuator_ERR); tmpTrans->ErrorCode(YY_MOVE (yystack_[0].value.as < std::string > ())); }
#line 1300 "fsml.cc"
    break;

  case 86: // transition_actuator: RETRY
#line 282 "fsml.yy"
                                                                        { tmpTrans->Actuator(TransActuator_RETRY); }
#line 1306 "fsml.cc"
    break;

  case 87: // timer_actuator: START IDENTIFIER
#line 285 "fsml.yy"
                                  { 
					if(tmpTrans->SetTimer(YY_MOVE (yystack_[0].value.as < std::string > ())) == false) {
						driver.error(yylhs.location, driver.GetLastError());
						YYERROR;
					}
				}
#line 1317 "fsml.cc"
    break;

  case 89: // output_specifier: OUT IDENTIFIER EQUAL C_CODE_BLOCK
#line 294 "fsml.yy"
                                                     { 
						if (tmpState->AddOutput(YY_MOVE (yystack_[2].value.as < std::string > ()), YY_MOVE (yystack_[0].value.as < std::string > ())) == false) {
							driver.error(yylhs.location, driver.GetLastError()); 
							YYERROR;
						} 
				 }
#line 1328 "fsml.cc"
    break;

  case 90: // $@3: %empty
#line 302 "fsml.yy"
                                { 
					tmpUntil = new FSMUntil(); 
					driver.PushUntil(tmpUntil); 
			  	}
#line 1337 "fsml.cc"
    break;

  case 91: // $@4: %empty
#line 307 "fsml.yy"
                                { 
					tmpTrans = new FSMTransition(driver, TransType_ExitUntil, YY_MOVE (yystack_[4].value.as < std::string > ())); 
					driver.CurUntil()->ExitTransition(tmpTrans);
				}
#line 1346 "fsml.cc"
    break;

  case 92: // until_retry: UNTIL_KEY until_condition $@3 LCB until_object_list RCB $@4 transition_actuator SC
#line 312 "fsml.yy"
                                { 
					parse_result_t res = driver.PopUntil();
					if (res == ParseResult_WARN) {
						driver.warning(yystack_[8].location, driver.GetLastError());
					}
				}
#line 1357 "fsml.cc"
    break;

  case 93: // until_condition: LB INTEGER_CONSTANT RB
#line 319 "fsml.yy"
                                                        { yylhs.value.as < std::string > () = std::to_string(YY_MOVE (yystack_[1].value.as < int > ())); }
#line 1363 "fsml.cc"
    break;

  case 94: // until_condition: LB enumeration_constant RB
#line 320 "fsml.yy"
                                                                { yylhs.value.as < std::string > () = YY_MOVE (yystack_[1].value.as < std::string > ()); }
#line 1369 "fsml.cc"
    break;

  case 97: // until_object: state
#line 327 "fsml.yy"
                     { driver.CurUntil()->AddState(tmpState); }
#line 1375 "fsml.cc"
    break;


#line 1379 "fsml.cc"

            default:
              break;
            }
        }
#if YY_EXCEPTIONS
      catch (const syntax_error& yyexc)
        {
          YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
          error (yyexc);
          YYERROR;
        }
#endif // YY_EXCEPTIONS
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, YY_MOVE (yylhs));
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
        std::string msg = YY_("syntax error");
        error (yyla.location, YY_MOVE (msg));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.kind () == symbol_kind::S_YYEOF)
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
    /* Pacify compilers when the user code never invokes YYERROR and
       the label yyerrorlab therefore never appears in user code.  */
    if (false)
      YYERROR;

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    YY_STACK_PRINT ();
    goto yyerrlab1;


  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    // Pop stack until we find a state that shifts the error token.
    for (;;)
      {
        yyn = yypact_[+yystack_[0].state];
        if (!yy_pact_value_is_default_ (yyn))
          {
            yyn += symbol_kind::S_YYerror;
            if (0 <= yyn && yyn <= yylast_
                && yycheck_[yyn] == symbol_kind::S_YYerror)
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
    {
      stack_symbol_type error_token;

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

      // Shift the error token.
      error_token.state = state_type (yyn);
      yypush_ ("Shifting", YY_MOVE (error_token));
    }
    goto yynewstate;


  /*-------------------------------------.
  | yyacceptlab -- YYACCEPT comes here.  |
  `-------------------------------------*/
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;


  /*-----------------------------------.
  | yyabortlab -- YYABORT comes here.  |
  `-----------------------------------*/
  yyabortlab:
    yyresult = 1;
    goto yyreturn;


  /*-----------------------------------------------------.
  | yyreturn -- parsing is finished, return the result.  |
  `-----------------------------------------------------*/
  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    YY_STACK_PRINT ();
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
#if YY_EXCEPTIONS
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack\n";
        // Do not try to display the values of the reclaimed symbols,
        // as their printers might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
#endif // YY_EXCEPTIONS
  }

  void
  FSMLParser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what ());
  }

#if YYDEBUG || 0
  const char *
  FSMLParser::symbol_name (symbol_kind_type yysymbol)
  {
    return yytname_[yysymbol];
  }
#endif // #if YYDEBUG || 0





  const signed char FSMLParser::yypact_ninf_ = -90;

  const signed char FSMLParser::yytable_ninf_ = -51;

  const signed char
  FSMLParser::yypact_[] =
  {
      78,   -36,   -30,   -21,     2,    35,    73,   -90,   -90,   -90,
     -90,   -90,   -90,   -90,   -90,   -90,   -90,   -90,    39,   -90,
     -90,    66,     8,   -90,   -90,   -90,    46,   -90,    51,    -7,
     -90,   -90,    41,    54,   -90,    -1,   -90,    53,    60,   -19,
     -90,   -90,   -90,   -90,   -90,   -90,   -90,   -90,   -90,   -90,
     -90,   -90,   -90,   -90,    52,   -90,    28,   -90,   -90,    55,
     -90,   -90,   -90,   -15,    56,    -5,   -90,   -90,   -90,    38,
     -10,    57,   -90,    61,    62,    90,   -90,    67,    59,   -90,
      68,    65,   -90,    63,   -90,    69,   -90,    70,    71,   -90,
     -90,   -90,   -90,    64,   -90,   -90,   -90,   -11,   -90,   -90,
     -90,   -90,    -3,   -90,   -90,    -8,   -90,   -90,    72,   -90,
      27,    75,   -90,   -10,   -90,    76,   -90,   -90,     3,   -90,
      42,   -90,   -90,   -90,   -90,   -90,   -90,    74,    77,    79,
     -90,    91,   -90,   -90,   -90,   -90,   -90,   -90,   105,   -90,
     -90,   -90,    80,   -90,    27,   -90,   -90,    81,   -90
  };

  const signed char
  FSMLParser::yydefact_[] =
  {
       5,     0,     0,     0,     0,     0,     0,     3,     6,     7,
       8,    11,    12,     9,    10,    13,    14,     1,     0,     4,
       2,     0,     0,    25,    26,    27,     0,    62,     0,     0,
      16,    18,     0,     0,    19,    76,    20,     0,    66,     0,
      90,    15,    17,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    42,    41,     0,    44,     0,    23,    37,     0,
      38,    39,    22,     0,     0,     0,    74,    77,    78,     0,
       0,     0,    57,     0,     0,     0,    43,    51,    44,    24,
       0,     0,    49,     0,    40,     0,    82,    81,     0,    61,
      75,    60,    59,     0,    73,    72,    71,     0,    69,    63,
      93,    94,     0,    52,    21,     0,    50,    48,     0,    80,
       0,     0,    58,     0,    65,    68,    97,    98,     0,    95,
       0,    54,    53,    55,    45,    46,    56,     0,     0,     0,
      86,    88,    89,    70,    67,    64,    91,    96,     0,    83,
      84,    85,     0,    79,     0,    47,    87,     0,    92
  };

  const signed char
  FSMLParser::yypgoto_[] =
  {
     -90,   -90,   -90,   110,   -90,   -90,   -90,   -90,   -90,   -90,
     -90,    88,   -90,   -90,   -90,    82,   -90,   -90,   -90,   -90,
     -90,   -90,   -90,    40,    48,     9,    89,   -90,   -90,   -89,
     -90,   -90,   -90,   -90,   -90,   -90,    17,   -90,    83,   -90,
     -90,   -90,   -13,   -90,   -90,   -86,   -90,   -90,   -90,   -90,
      14
  };

  const short
  FSMLParser::yydefgoto_[] =
  {
      -1,     5,     6,     7,     8,     9,    10,    11,    12,    20,
      29,    30,    31,    56,    32,    57,    58,    59,    60,    61,
      80,   124,    81,    82,    83,   125,   126,    33,    93,    34,
      35,    38,   115,    71,   135,    97,    98,    65,    66,    67,
     110,    87,   131,   143,    68,    36,    75,   144,    40,   118,
     119
  };

  const short
  FSMLParser::yytable_[] =
  {
     120,    85,    41,    23,    24,    25,    26,    27,    94,    13,
      63,    27,   136,   116,    63,    14,   117,    27,    23,    24,
      25,    26,    27,   113,    15,    95,    96,   114,    72,   116,
      73,    86,   117,    28,    64,    17,    89,    28,    64,    72,
     121,   122,   123,    28,   128,   129,   130,    16,    28,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    77,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    22,    78,     1,     2,     3,     4,
      18,     1,     2,     3,     4,    91,    21,    92,    55,    72,
     121,   122,   123,    37,    39,    62,    69,    70,   102,    76,
      77,   -50,    84,    88,    99,   100,   101,   105,   112,   104,
     106,   142,   108,   111,   145,   109,    19,    42,   139,   127,
     132,   134,   148,   107,   140,   103,   141,   146,    74,   138,
     133,   147,   137,     0,     0,     0,     0,     0,    79,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    90
  };

  const short
  FSMLParser::yycheck_[] =
  {
       8,    16,     9,    10,    11,    12,    13,    14,    18,    45,
      15,    14,     9,   102,    15,    45,   102,    14,    10,    11,
      12,    13,    14,    34,    45,    35,    36,    38,    47,   118,
      49,    46,   118,    40,    39,     0,    41,    40,    39,    47,
      48,    49,    50,    40,    17,    18,    19,    45,    40,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,     8,    47,     3,     4,     5,     6,
       7,     3,     4,     5,     6,    47,    47,    49,    47,    47,
      48,    49,    50,    47,    43,    41,    43,    37,     8,    47,
      33,    42,    47,    47,    47,    44,    44,    42,    44,    41,
      47,    20,    43,    42,     9,    45,     6,    29,    44,    47,
      45,    45,    41,    83,    47,    77,    47,    47,    39,   120,
     113,   144,   118,    -1,    -1,    -1,    -1,    -1,    56,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    65
  };

  const signed char
  FSMLParser::yystos_[] =
  {
       0,     3,     4,     5,     6,    52,    53,    54,    55,    56,
      57,    58,    59,    45,    45,    45,    45,     0,     7,    54,
      60,    47,     8,    10,    11,    12,    13,    14,    40,    61,
      62,    63,    65,    78,    80,    81,    96,    47,    82,    43,
      99,     9,    62,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    47,    64,    66,    67,    68,
      69,    70,    41,    15,    39,    88,    89,    90,    95,    43,
      37,    84,    47,    49,    77,    97,    47,    33,    47,    66,
      71,    73,    74,    75,    47,    16,    46,    92,    47,    41,
      89,    47,    49,    79,    18,    35,    36,    86,    87,    47,
      44,    44,     8,    75,    41,    42,    47,    74,    43,    45,
      91,    42,    44,    34,    38,    83,    80,    96,   100,   101,
       8,    48,    49,    50,    72,    76,    77,    47,    17,    18,
      19,    93,    45,    87,    45,    85,     9,   101,    76,    44,
      47,    47,    20,    94,    98,     9,    47,    93,    41
  };

  const signed char
  FSMLParser::yyr1_[] =
  {
       0,    51,    52,    53,    53,    53,    54,    54,    54,    55,
      56,    57,    57,    58,    59,    60,    61,    61,    62,    62,
      62,    63,    63,    64,    64,    65,    65,    65,    66,    66,
      66,    66,    66,    66,    66,    66,    66,    66,    66,    66,
      67,    68,    68,    69,    70,    71,    72,    72,    73,    73,
      74,    75,    75,    76,    76,    76,    76,    77,    78,    79,
      79,    80,    82,    83,    81,    84,    84,    85,    85,    86,
      86,    87,    87,    87,    88,    88,    88,    89,    89,    90,
      91,    91,    92,    92,    93,    93,    93,    94,    94,    95,
      97,    98,    96,    99,    99,   100,   100,   101,   101
  };

  const signed char
  FSMLParser::yyr2_[] =
  {
       0,     2,     2,     1,     2,     0,     1,     1,     1,     2,
       2,     1,     1,     2,     2,     5,     1,     2,     1,     1,
       1,     4,     2,     1,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       2,     1,     1,     2,     1,     3,     1,     3,     2,     1,
       1,     1,     2,     1,     1,     1,     1,     1,     5,     1,
       1,     3,     0,     0,     6,     3,     0,     1,     0,     1,
       3,     1,     1,     1,     1,     2,     0,     1,     1,     5,
       1,     0,     1,     4,     2,     2,     1,     2,     0,     4,
       0,     0,     9,     3,     3,     1,     2,     1,     1
  };


#if YYDEBUG
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a YYNTOKENS, nonterminals.
  const char*
  const FSMLParser::yytname_[] =
  {
  "END_OF_FILE", "error", "\"invalid token\"", "DECL_KEY", "EXPORT_KEY",
  "TIME_KEY", "PERIOD_KEY", "FSM_KEY", "LCB", "RCB", "VAR_KEY",
  "INPUT_KEY", "OUTPUT_KEY", "TIMER_KEY", "STATE_KEY", "ON", "TIMEOUT_KEY",
  "GO", "ERR", "RETRY", "START", "VOID", "CHAR", "SHORT", "INT", "LONG",
  "FLOAT", "DOUBLE", "SIGNED", "UNSIGNED", "UNION", "STRUCT", "ENUM",
  "STAR", "COMMA", "END", "RESET", "LSB", "RSB", "OUT", "UNTIL_KEY", "SC",
  "EQUAL", "LB", "RB", "C_CODE_BLOCK", "C_CONDITION_BLOCK", "IDENTIFIER",
  "CHARACTER_CONSTANT", "INTEGER_CONSTANT", "FLOATING_CONSTANT", "$accept",
  "fsml", "init_section_list", "init_section", "declaration", "export",
  "time", "time_specifier", "period_specifier", "fsm", "fsm_objects_list",
  "fsm_object", "variable_declaration", "type_specifier_list",
  "variable_specifier", "type_specifier", "struct_or_union_specifier",
  "struct_or_union", "enum_specifier", "typedef_name", "init_declarator",
  "initializer", "declarator", "direct_declarator", "pointer", "constant",
  "enumeration_constant", "timer_specifier", "timer_initializer", "state",
  "state_specifier", "$@1", "$@2", "state_type_specifier", "state_c_code",
  "state_type_list", "state_type", "state_decorator_list",
  "state_decorator", "transition_specifier", "transition_c_code",
  "transition_condition", "transition_actuator", "timer_actuator",
  "output_specifier", "until_retry", "$@3", "$@4", "until_condition",
  "until_object_list", "until_object", YY_NULLPTR
  };
#endif


#if YYDEBUG
  const short
  FSMLParser::yyrline_[] =
  {
       0,    72,    72,    74,    75,    76,    79,    80,    81,    84,
      91,    98,    99,   102,   109,   116,   119,   120,   123,   124,
     125,   128,   142,   145,   146,   149,   150,   151,   154,   155,
     156,   157,   158,   159,   160,   161,   162,   163,   164,   165,
     168,   170,   171,   174,   177,   180,   182,   183,   186,   187,
     190,   193,   194,   197,   198,   199,   200,   203,   206,   215,
     216,   219,   227,   229,   227,   233,   234,   237,   238,   241,
     242,   245,   246,   247,   250,   251,   252,   256,   257,   261,
     263,   264,   267,   268,   280,   281,   282,   285,   291,   294,
     302,   307,   301,   319,   320,   323,   324,   327,   328
  };

  void
  FSMLParser::yy_stack_print_ () const
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << int (i->state);
    *yycdebug_ << '\n';
  }

  void
  FSMLParser::yy_reduce_print_ (int yyrule) const
  {
    int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):\n";
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG

  FSMLParser::symbol_kind_type
  FSMLParser::yytranslate_ (int t)
  {
    // YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to
    // TOKEN-NUM as returned by yylex.
    static
    const signed char
    translate_table[] =
    {
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50
    };
    // Last valid token kind.
    const int code_max = 305;

    if (t <= 0)
      return symbol_kind::S_YYEOF;
    else if (t <= code_max)
      return YY_CAST (symbol_kind_type, translate_table[t]);
    else
      return symbol_kind::S_YYUNDEF;
  }

} // FSML
#line 1852 "fsml.cc"

#line 333 "fsml.yy"


void FSML::FSMLParser::error(const FSML::FSMLParser::location_type& l, const std::string& m)
{
	driver.error(l, m);
}
