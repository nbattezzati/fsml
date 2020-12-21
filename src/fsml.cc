// A Bison parser, made by GNU Bison 3.6.4.

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
      case 49: // FLOATING_CONSTANT
        value.copy< float > (YY_MOVE (that.value));
        break;

      case 48: // INTEGER_CONSTANT
        value.copy< int > (YY_MOVE (that.value));
        break;

      case 85: // state_type
        value.copy< state_type_t > (YY_MOVE (that.value));
        break;

      case 44: // C_CODE_BLOCK
      case 45: // C_CONDITION_BLOCK
      case 46: // IDENTIFIER
      case 47: // CHARACTER_CONSTANT
      case 62: // type_specifier_list
      case 64: // type_specifier
      case 65: // struct_or_union_specifier
      case 66: // struct_or_union
      case 67: // enum_specifier
      case 68: // typedef_name
      case 74: // constant
      case 75: // enumeration_constant
      case 77: // timer_initializer
      case 79: // state_specifier
      case 83: // state_c_code
      case 97: // until_condition
        value.copy< std::string > (YY_MOVE (that.value));
        break;

      case 63: // variable_specifier
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
      case 49: // FLOATING_CONSTANT
        value.move< float > (YY_MOVE (s.value));
        break;

      case 48: // INTEGER_CONSTANT
        value.move< int > (YY_MOVE (s.value));
        break;

      case 85: // state_type
        value.move< state_type_t > (YY_MOVE (s.value));
        break;

      case 44: // C_CODE_BLOCK
      case 45: // C_CONDITION_BLOCK
      case 46: // IDENTIFIER
      case 47: // CHARACTER_CONSTANT
      case 62: // type_specifier_list
      case 64: // type_specifier
      case 65: // struct_or_union_specifier
      case 66: // struct_or_union
      case 67: // enum_specifier
      case 68: // typedef_name
      case 74: // constant
      case 75: // enumeration_constant
      case 77: // timer_initializer
      case 79: // state_specifier
      case 83: // state_c_code
      case 97: // until_condition
        value.move< std::string > (YY_MOVE (s.value));
        break;

      case 63: // variable_specifier
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
      case 49: // FLOATING_CONSTANT
        value.YY_MOVE_OR_COPY< float > (YY_MOVE (that.value));
        break;

      case 48: // INTEGER_CONSTANT
        value.YY_MOVE_OR_COPY< int > (YY_MOVE (that.value));
        break;

      case 85: // state_type
        value.YY_MOVE_OR_COPY< state_type_t > (YY_MOVE (that.value));
        break;

      case 44: // C_CODE_BLOCK
      case 45: // C_CONDITION_BLOCK
      case 46: // IDENTIFIER
      case 47: // CHARACTER_CONSTANT
      case 62: // type_specifier_list
      case 64: // type_specifier
      case 65: // struct_or_union_specifier
      case 66: // struct_or_union
      case 67: // enum_specifier
      case 68: // typedef_name
      case 74: // constant
      case 75: // enumeration_constant
      case 77: // timer_initializer
      case 79: // state_specifier
      case 83: // state_c_code
      case 97: // until_condition
        value.YY_MOVE_OR_COPY< std::string > (YY_MOVE (that.value));
        break;

      case 63: // variable_specifier
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
      case 49: // FLOATING_CONSTANT
        value.move< float > (YY_MOVE (that.value));
        break;

      case 48: // INTEGER_CONSTANT
        value.move< int > (YY_MOVE (that.value));
        break;

      case 85: // state_type
        value.move< state_type_t > (YY_MOVE (that.value));
        break;

      case 44: // C_CODE_BLOCK
      case 45: // C_CONDITION_BLOCK
      case 46: // IDENTIFIER
      case 47: // CHARACTER_CONSTANT
      case 62: // type_specifier_list
      case 64: // type_specifier
      case 65: // struct_or_union_specifier
      case 66: // struct_or_union
      case 67: // enum_specifier
      case 68: // typedef_name
      case 74: // constant
      case 75: // enumeration_constant
      case 77: // timer_initializer
      case 79: // state_specifier
      case 83: // state_c_code
      case 97: // until_condition
        value.move< std::string > (YY_MOVE (that.value));
        break;

      case 63: // variable_specifier
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
      case 49: // FLOATING_CONSTANT
        value.copy< float > (that.value);
        break;

      case 48: // INTEGER_CONSTANT
        value.copy< int > (that.value);
        break;

      case 85: // state_type
        value.copy< state_type_t > (that.value);
        break;

      case 44: // C_CODE_BLOCK
      case 45: // C_CONDITION_BLOCK
      case 46: // IDENTIFIER
      case 47: // CHARACTER_CONSTANT
      case 62: // type_specifier_list
      case 64: // type_specifier
      case 65: // struct_or_union_specifier
      case 66: // struct_or_union
      case 67: // enum_specifier
      case 68: // typedef_name
      case 74: // constant
      case 75: // enumeration_constant
      case 77: // timer_initializer
      case 79: // state_specifier
      case 83: // state_c_code
      case 97: // until_condition
        value.copy< std::string > (that.value);
        break;

      case 63: // variable_specifier
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
      case 49: // FLOATING_CONSTANT
        value.move< float > (that.value);
        break;

      case 48: // INTEGER_CONSTANT
        value.move< int > (that.value);
        break;

      case 85: // state_type
        value.move< state_type_t > (that.value);
        break;

      case 44: // C_CODE_BLOCK
      case 45: // C_CONDITION_BLOCK
      case 46: // IDENTIFIER
      case 47: // CHARACTER_CONSTANT
      case 62: // type_specifier_list
      case 64: // type_specifier
      case 65: // struct_or_union_specifier
      case 66: // struct_or_union
      case 67: // enum_specifier
      case 68: // typedef_name
      case 74: // constant
      case 75: // enumeration_constant
      case 77: // timer_initializer
      case 79: // state_specifier
      case 83: // state_c_code
      case 97: // until_condition
        value.move< std::string > (that.value);
        break;

      case 63: // variable_specifier
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
      case 49: // FLOATING_CONSTANT
        yylhs.value.emplace< float > ();
        break;

      case 48: // INTEGER_CONSTANT
        yylhs.value.emplace< int > ();
        break;

      case 85: // state_type
        yylhs.value.emplace< state_type_t > ();
        break;

      case 44: // C_CODE_BLOCK
      case 45: // C_CONDITION_BLOCK
      case 46: // IDENTIFIER
      case 47: // CHARACTER_CONSTANT
      case 62: // type_specifier_list
      case 64: // type_specifier
      case 65: // struct_or_union_specifier
      case 66: // struct_or_union
      case 67: // enum_specifier
      case 68: // typedef_name
      case 74: // constant
      case 75: // enumeration_constant
      case 77: // timer_initializer
      case 79: // state_specifier
      case 83: // state_c_code
      case 97: // until_condition
        yylhs.value.emplace< std::string > ();
        break;

      case 63: // variable_specifier
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
  case 8:
#line 79 "fsml.yy"
                                    { driver.Decl(YY_MOVE (yystack_[0].value.as < std::string > ())); }
#line 897 "fsml.cc"
    break;

  case 11:
#line 85 "fsml.yy"
                                       { 
		if (driver.TimeSpec(YY_MOVE (yystack_[0].value.as < std::string > ())) == false) { 
			driver.error(yylhs.location, driver.GetLastError()); 
			YYERROR; 
		}; 
	}
#line 908 "fsml.cc"
    break;

  case 12:
#line 92 "fsml.yy"
                                           {
		if (driver.PeriodSpec(YY_MOVE (yystack_[0].value.as < std::string > ())) == false) { 
			driver.error(yylhs.location, driver.GetLastError()); 
			YYERROR; 
		}; 
	}
#line 919 "fsml.cc"
    break;

  case 13:
#line 99 "fsml.yy"
                                                  { driver.FsmName(YY_MOVE (yystack_[3].value.as < std::string > ())); }
#line 925 "fsml.cc"
    break;

  case 19:
#line 112 "fsml.yy"
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
#line 943 "fsml.cc"
    break;

  case 21:
#line 128 "fsml.yy"
                                                                                { tmp_type = YY_MOVE (yystack_[0].value.as < std::string > ()); }
#line 949 "fsml.cc"
    break;

  case 22:
#line 129 "fsml.yy"
                                                                                { tmp_type.append(" " + YY_MOVE (yystack_[0].value.as < std::string > ())); }
#line 955 "fsml.cc"
    break;

  case 23:
#line 132 "fsml.yy"
                                        { yylhs.value.as < var_family_t > () = VariableFamily_VAR; }
#line 961 "fsml.cc"
    break;

  case 24:
#line 133 "fsml.yy"
                                                        { yylhs.value.as < var_family_t > () = VariableFamily_INPUT; }
#line 967 "fsml.cc"
    break;

  case 25:
#line 134 "fsml.yy"
                                                        { yylhs.value.as < var_family_t > () = VariableFamily_OUTPUT; }
#line 973 "fsml.cc"
    break;

  case 26:
#line 137 "fsml.yy"
                                                { yylhs.value.as < std::string > () = std::string("void"); }
#line 979 "fsml.cc"
    break;

  case 27:
#line 138 "fsml.yy"
                                                                { yylhs.value.as < std::string > () = std::string("char"); }
#line 985 "fsml.cc"
    break;

  case 28:
#line 139 "fsml.yy"
                                                                { yylhs.value.as < std::string > () = std::string("short"); }
#line 991 "fsml.cc"
    break;

  case 29:
#line 140 "fsml.yy"
                                                                { yylhs.value.as < std::string > () = std::string("int"); }
#line 997 "fsml.cc"
    break;

  case 30:
#line 141 "fsml.yy"
                                                                { yylhs.value.as < std::string > () = std::string("long"); }
#line 1003 "fsml.cc"
    break;

  case 31:
#line 142 "fsml.yy"
                                                                { yylhs.value.as < std::string > () = std::string("float"); }
#line 1009 "fsml.cc"
    break;

  case 32:
#line 143 "fsml.yy"
                                                                { yylhs.value.as < std::string > () = std::string("double"); }
#line 1015 "fsml.cc"
    break;

  case 33:
#line 144 "fsml.yy"
                                                                { yylhs.value.as < std::string > () = std::string("signed"); }
#line 1021 "fsml.cc"
    break;

  case 34:
#line 145 "fsml.yy"
                                                        { yylhs.value.as < std::string > () = std::string("unsigned"); }
#line 1027 "fsml.cc"
    break;

  case 35:
#line 146 "fsml.yy"
                                                        { yylhs.value.as < std::string > () = YY_MOVE (yystack_[0].value.as < std::string > ()); }
#line 1033 "fsml.cc"
    break;

  case 36:
#line 147 "fsml.yy"
                                                        { yylhs.value.as < std::string > () = YY_MOVE (yystack_[0].value.as < std::string > ()); }
#line 1039 "fsml.cc"
    break;

  case 37:
#line 148 "fsml.yy"
                                                        { yylhs.value.as < std::string > () = YY_MOVE (yystack_[0].value.as < std::string > ()); }
#line 1045 "fsml.cc"
    break;

  case 38:
#line 151 "fsml.yy"
                                                       { yylhs.value.as < std::string > () = YY_MOVE (yystack_[1].value.as < std::string > ()) + " " + YY_MOVE (yystack_[0].value.as < std::string > ()); }
#line 1051 "fsml.cc"
    break;

  case 39:
#line 153 "fsml.yy"
                                                { yylhs.value.as < std::string > () = std::string("struct"); }
#line 1057 "fsml.cc"
    break;

  case 40:
#line 154 "fsml.yy"
                                                                { yylhs.value.as < std::string > () = std::string("union"); }
#line 1063 "fsml.cc"
    break;

  case 41:
#line 157 "fsml.yy"
                                        { yylhs.value.as < std::string > () = std::string("enum " + YY_MOVE (yystack_[0].value.as < std::string > ())); }
#line 1069 "fsml.cc"
    break;

  case 42:
#line 160 "fsml.yy"
                                                { yylhs.value.as < std::string > () = YY_MOVE (yystack_[0].value.as < std::string > ()); }
#line 1075 "fsml.cc"
    break;

  case 44:
#line 165 "fsml.yy"
                                        { tmp_initializer = YY_MOVE (yystack_[0].value.as < std::string > ()); }
#line 1081 "fsml.cc"
    break;

  case 45:
#line 166 "fsml.yy"
                                                { tmp_initializer = std::string("{" + YY_MOVE (yystack_[1].value.as < std::string > ()) + "}"); }
#line 1087 "fsml.cc"
    break;

  case 48:
#line 173 "fsml.yy"
                                                { tmp_declarator = YY_MOVE (yystack_[0].value.as < std::string > ()); }
#line 1093 "fsml.cc"
    break;

  case 49:
#line 176 "fsml.yy"
                                                                { tmp_ptr_type.append("*"); }
#line 1099 "fsml.cc"
    break;

  case 50:
#line 177 "fsml.yy"
                                                                { tmp_ptr_type.append("*"); }
#line 1105 "fsml.cc"
    break;

  case 51:
#line 180 "fsml.yy"
                                                        { yylhs.value.as < std::string > () = std::to_string(YY_MOVE (yystack_[0].value.as < int > ())); }
#line 1111 "fsml.cc"
    break;

  case 52:
#line 181 "fsml.yy"
                                                        { yylhs.value.as < std::string > () = YY_MOVE (yystack_[0].value.as < std::string > ()); }
#line 1117 "fsml.cc"
    break;

  case 53:
#line 182 "fsml.yy"
                                                        { yylhs.value.as < std::string > () = std::to_string(YY_MOVE (yystack_[0].value.as < float > ())); }
#line 1123 "fsml.cc"
    break;

  case 54:
#line 183 "fsml.yy"
                                                        { yylhs.value.as < std::string > () = YY_MOVE (yystack_[0].value.as < std::string > ()); }
#line 1129 "fsml.cc"
    break;

  case 55:
#line 186 "fsml.yy"
                                                { yylhs.value.as < std::string > () = YY_MOVE (yystack_[0].value.as < std::string > ()); }
#line 1135 "fsml.cc"
    break;

  case 56:
#line 190 "fsml.yy"
                                        {
						if (driver.AddTimer(YY_MOVE (yystack_[3].value.as < std::string > ()), YY_MOVE (yystack_[1].value.as < std::string > ())) == false) {
							driver.error(yylhs.location, driver.GetLastError()); 
							YYERROR; 
						};
					}
#line 1146 "fsml.cc"
    break;

  case 57:
#line 198 "fsml.yy"
                                        { yylhs.value.as < std::string > () = std::to_string(YY_MOVE (yystack_[0].value.as < int > ())); }
#line 1152 "fsml.cc"
    break;

  case 58:
#line 199 "fsml.yy"
                                                                { yylhs.value.as < std::string > () = YY_MOVE (yystack_[0].value.as < std::string > ()); }
#line 1158 "fsml.cc"
    break;

  case 59:
#line 203 "fsml.yy"
                { 
			if (driver.AddState(tmpState) == false) {
				driver.error(yylhs.location, driver.GetLastError()); 
				YYERROR; 
			} 
		}
#line 1169 "fsml.cc"
    break;

  case 60:
#line 210 "fsml.yy"
                            { tmpState = new FSMState(driver); }
#line 1175 "fsml.cc"
    break;

  case 61:
#line 212 "fsml.yy"
                                             { tmpState->Name(YY_MOVE (yystack_[0].value.as < std::string > ())); }
#line 1181 "fsml.cc"
    break;

  case 62:
#line 213 "fsml.yy"
                                               { tmpState->Code(YY_MOVE (yystack_[0].value.as < std::string > ())); }
#line 1187 "fsml.cc"
    break;

  case 65:
#line 220 "fsml.yy"
                                        { yylhs.value.as < std::string > () = YY_MOVE (yystack_[0].value.as < std::string > ()); }
#line 1193 "fsml.cc"
    break;

  case 66:
#line 221 "fsml.yy"
                                                { yylhs.value.as < std::string > () = std::string(); }
#line 1199 "fsml.cc"
    break;

  case 67:
#line 224 "fsml.yy"
                                                                                { tmpState->AddType(YY_MOVE (yystack_[0].value.as < state_type_t > ())); }
#line 1205 "fsml.cc"
    break;

  case 68:
#line 225 "fsml.yy"
                                                                                { tmpState->AddType(YY_MOVE (yystack_[0].value.as < state_type_t > ())); }
#line 1211 "fsml.cc"
    break;

  case 69:
#line 228 "fsml.yy"
                                { yylhs.value.as < state_type_t > () = kStateTypeReset; }
#line 1217 "fsml.cc"
    break;

  case 70:
#line 229 "fsml.yy"
                                        { yylhs.value.as < state_type_t > () = kStateTypeEnd; }
#line 1223 "fsml.cc"
    break;

  case 71:
#line 230 "fsml.yy"
                                        { yylhs.value.as < state_type_t > () = kStateTypeErr; }
#line 1229 "fsml.cc"
    break;

  case 75:
#line 239 "fsml.yy"
                                        { tmpState->AddTransition(tmpTrans); }
#line 1235 "fsml.cc"
    break;

  case 78:
#line 246 "fsml.yy"
                                        { tmpTrans->Code(YY_MOVE (yystack_[0].value.as < std::string > ())); }
#line 1241 "fsml.cc"
    break;

  case 80:
#line 250 "fsml.yy"
                                                                        { tmpTrans = new FSMTransition(driver, TransType_Normal, YY_MOVE (yystack_[0].value.as < std::string > ())); }
#line 1247 "fsml.cc"
    break;

  case 81:
#line 251 "fsml.yy"
                                                                                { tmpTrans = new FSMTransition(driver, TransType_Timeout, YY_MOVE (yystack_[1].value.as < std::string > ())); }
#line 1253 "fsml.cc"
    break;

  case 82:
#line 254 "fsml.yy"
                                                { tmpTrans->Actuator(TransActuator_GO); tmpTrans->EndState(YY_MOVE (yystack_[0].value.as < std::string > ())); }
#line 1259 "fsml.cc"
    break;

  case 83:
#line 255 "fsml.yy"
                                                                { tmpTrans->Actuator(TransActuator_ERR); tmpTrans->ErrorCode(YY_MOVE (yystack_[0].value.as < std::string > ())); }
#line 1265 "fsml.cc"
    break;

  case 84:
#line 256 "fsml.yy"
                                                                        { tmpTrans->Actuator(TransActuator_RETRY); }
#line 1271 "fsml.cc"
    break;

  case 85:
#line 259 "fsml.yy"
                                        { tmpTrans->Timer(YY_MOVE (yystack_[0].value.as < std::string > ())); }
#line 1277 "fsml.cc"
    break;

  case 87:
#line 263 "fsml.yy"
                                                     { 
						if (tmpState->AddOutput(YY_MOVE (yystack_[2].value.as < std::string > ()), YY_MOVE (yystack_[0].value.as < std::string > ())) == false) {
							driver.error(yylhs.location, driver.GetLastError()); 
							YYERROR;
						} 
				 }
#line 1288 "fsml.cc"
    break;

  case 88:
#line 271 "fsml.yy"
                                { 
					tmpUntil = new FSMUntil(); 
					driver.PushUntil(tmpUntil); 
			  	}
#line 1297 "fsml.cc"
    break;

  case 89:
#line 276 "fsml.yy"
                                { 
					tmpTrans = new FSMTransition(driver, TransType_ExitUntil, YY_MOVE (yystack_[4].value.as < std::string > ())); 
					driver.CurUntil()->ExitTransition(tmpTrans);
				}
#line 1306 "fsml.cc"
    break;

  case 90:
#line 281 "fsml.yy"
                                { 
					driver.PopUntil();
				}
#line 1314 "fsml.cc"
    break;

  case 91:
#line 285 "fsml.yy"
                                                        { yylhs.value.as < std::string > () = std::to_string(YY_MOVE (yystack_[1].value.as < int > ())); }
#line 1320 "fsml.cc"
    break;

  case 92:
#line 286 "fsml.yy"
                                                                { yylhs.value.as < std::string > () = YY_MOVE (yystack_[1].value.as < std::string > ()); }
#line 1326 "fsml.cc"
    break;

  case 95:
#line 293 "fsml.yy"
                     { driver.CurUntil()->AddState(tmpState); }
#line 1332 "fsml.cc"
    break;


#line 1336 "fsml.cc"

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





  const signed char FSMLParser::yypact_ninf_ = -87;

  const signed char FSMLParser::yytable_ninf_ = -49;

  const signed char
  FSMLParser::yypact_[] =
  {
      77,   -35,   -29,   -20,    35,    41,   -87,   -87,   -87,   -87,
     -87,   -87,   -87,   -87,   -87,    28,   -87,   -87,    79,     9,
     -87,   -87,   -87,    44,   -87,    45,    -6,   -87,   -87,    42,
      52,   -87,     0,   -87,    51,    58,   -18,   -87,   -87,   -87,
     -87,   -87,   -87,   -87,   -87,   -87,   -87,   -87,   -87,   -87,
     -87,    49,   -87,    29,   -87,   -87,    50,   -87,   -87,   -87,
     -14,    53,    -4,   -87,   -87,   -87,    43,    -9,    54,   -87,
      55,    59,    90,   -87,    69,    62,   -87,    64,    65,   -87,
      61,   -87,    63,   -87,    66,    68,   -87,   -87,   -87,   -87,
      70,   -87,   -87,   -87,   -10,   -87,   -87,   -87,   -87,    -2,
     -87,   -87,    -7,   -87,   -87,    71,   -87,    67,    72,   -87,
      -9,   -87,    74,   -87,   -87,     4,   -87,    30,   -87,   -87,
     -87,   -87,   -87,   -87,    76,    75,    78,   -87,    89,   -87,
     -87,   -87,   -87,   -87,   -87,   103,   -87,   -87,   -87,    80,
     -87,    67,   -87,   -87,    82,   -87
  };

  const signed char
  FSMLParser::yydefact_[] =
  {
       5,     0,     0,     0,     0,     0,     3,     6,     7,     9,
      10,     8,    11,    12,     1,     0,     4,     2,     0,     0,
      23,    24,    25,     0,    60,     0,     0,    14,    16,     0,
       0,    17,    74,    18,     0,    64,     0,    88,    13,    15,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    40,
      39,     0,    42,     0,    21,    35,     0,    36,    37,    20,
       0,     0,     0,    72,    75,    76,     0,     0,     0,    55,
       0,     0,     0,    41,    49,    42,    22,     0,     0,    47,
       0,    38,     0,    80,    79,     0,    59,    73,    58,    57,
       0,    71,    70,    69,     0,    67,    61,    91,    92,     0,
      50,    19,     0,    48,    46,     0,    78,     0,     0,    56,
       0,    63,    66,    95,    96,     0,    93,     0,    52,    51,
      53,    43,    44,    54,     0,     0,     0,    84,    86,    87,
      68,    65,    62,    89,    94,     0,    81,    82,    83,     0,
      77,     0,    45,    85,     0,    90
  };

  const signed char
  FSMLParser::yypgoto_[] =
  {
     -87,   -87,   -87,   107,   -87,   -87,   -87,   -87,   -87,   -87,
      88,   -87,   -87,   -87,    81,   -87,   -87,   -87,   -87,   -87,
     -87,   -87,    40,    56,     6,    91,   -87,   -87,   -86,   -87,
     -87,   -87,   -87,   -87,   -87,     5,   -87,    73,   -87,   -87,
     -87,   -16,   -87,   -87,   -83,   -87,   -87,   -87,   -87,    13
  };

  const short
  FSMLParser::yydefgoto_[] =
  {
      -1,     4,     5,     6,     7,     8,     9,    10,    17,    26,
      27,    28,    53,    29,    54,    55,    56,    57,    58,    77,
     121,    78,    79,    80,   122,   123,    30,    90,    31,    32,
      35,   112,    68,   132,    94,    95,    62,    63,    64,   107,
      84,   128,   140,    65,    33,    72,   141,    37,   115,   116
  };

  const short
  FSMLParser::yytable_[] =
  {
     117,    82,    38,    20,    21,    22,    23,    24,    91,    11,
      60,    24,   133,   113,    60,    12,   114,    24,    20,    21,
      22,    23,    24,   110,    13,    92,    93,   111,    69,   113,
      70,    83,   114,    25,    61,    14,    86,    25,    61,    69,
     118,   119,   120,    25,     1,     2,     3,    15,    25,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    74,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    18,    75,    69,   118,   119,   120,
       1,     2,     3,   125,   126,   127,    19,    36,    52,    88,
      34,    89,    59,    66,    67,    73,    81,    99,    97,    85,
      96,    74,    98,   -48,   101,   105,   102,   103,   139,   108,
     106,   142,    16,   109,    39,   130,   129,   124,   131,   136,
     104,   137,   145,   135,   138,   144,   143,    71,   134,     0,
     100,     0,     0,     0,    76,    87
  };

  const short
  FSMLParser::yycheck_[] =
  {
       7,    15,     8,     9,    10,    11,    12,    13,    17,    44,
      14,    13,     8,    99,    14,    44,    99,    13,     9,    10,
      11,    12,    13,    33,    44,    34,    35,    37,    46,   115,
      48,    45,   115,    39,    38,     0,    40,    39,    38,    46,
      47,    48,    49,    39,     3,     4,     5,     6,    39,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    46,    46,    46,    47,    48,    49,
       3,     4,     5,    16,    17,    18,     7,    42,    46,    46,
      46,    48,    40,    42,    36,    46,    46,     7,    43,    46,
      46,    32,    43,    41,    40,    42,    41,    46,    19,    41,
      44,     8,     5,    43,    26,   110,    44,    46,    44,    43,
      80,    46,    40,   117,    46,   141,    46,    36,   115,    -1,
      74,    -1,    -1,    -1,    53,    62
  };

  const signed char
  FSMLParser::yystos_[] =
  {
       0,     3,     4,     5,    51,    52,    53,    54,    55,    56,
      57,    44,    44,    44,     0,     6,    53,    58,    46,     7,
       9,    10,    11,    12,    13,    39,    59,    60,    61,    63,
      76,    78,    79,    94,    46,    80,    42,    97,     8,    60,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    46,    62,    64,    65,    66,    67,    68,    40,
      14,    38,    86,    87,    88,    93,    42,    36,    82,    46,
      48,    75,    95,    46,    32,    46,    64,    69,    71,    72,
      73,    46,    15,    45,    90,    46,    40,    87,    46,    48,
      77,    17,    34,    35,    84,    85,    46,    43,    43,     7,
      73,    40,    41,    46,    72,    42,    44,    89,    41,    43,
      33,    37,    81,    78,    94,    98,    99,     7,    47,    48,
      49,    70,    74,    75,    46,    16,    17,    18,    91,    44,
      85,    44,    83,     8,    99,    74,    43,    46,    46,    19,
      92,    96,     8,    46,    91,    40
  };

  const signed char
  FSMLParser::yyr1_[] =
  {
       0,    50,    51,    52,    52,    52,    53,    53,    54,    55,
      55,    56,    57,    58,    59,    59,    60,    60,    60,    61,
      61,    62,    62,    63,    63,    63,    64,    64,    64,    64,
      64,    64,    64,    64,    64,    64,    64,    64,    65,    66,
      66,    67,    68,    69,    70,    70,    71,    71,    72,    73,
      73,    74,    74,    74,    74,    75,    76,    77,    77,    78,
      80,    81,    79,    82,    82,    83,    83,    84,    84,    85,
      85,    85,    86,    86,    86,    87,    87,    88,    89,    89,
      90,    90,    91,    91,    91,    92,    92,    93,    95,    96,
      94,    97,    97,    98,    98,    99,    99
  };

  const signed char
  FSMLParser::yyr2_[] =
  {
       0,     2,     2,     1,     2,     0,     1,     1,     2,     1,
       1,     2,     2,     5,     1,     2,     1,     1,     1,     4,
       2,     1,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     2,     1,
       1,     2,     1,     3,     1,     3,     2,     1,     1,     1,
       2,     1,     1,     1,     1,     1,     5,     1,     1,     3,
       0,     0,     6,     3,     0,     1,     0,     1,     3,     1,
       1,     1,     1,     2,     0,     1,     1,     5,     1,     0,
       1,     4,     2,     2,     1,     2,     0,     4,     0,     0,
       9,     3,     3,     1,     2,     1,     1
  };


#if YYDEBUG
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a YYNTOKENS, nonterminals.
  const char*
  const FSMLParser::yytname_[] =
  {
  "END_OF_FILE", "error", "\"invalid token\"", "DECL_KEY", "TIME_KEY",
  "PERIOD_KEY", "FSM_KEY", "LCB", "RCB", "VAR_KEY", "INPUT_KEY",
  "OUTPUT_KEY", "TIMER_KEY", "STATE_KEY", "ON", "TIMEOUT_KEY", "GO", "ERR",
  "RETRY", "START", "VOID", "CHAR", "SHORT", "INT", "LONG", "FLOAT",
  "DOUBLE", "SIGNED", "UNSIGNED", "UNION", "STRUCT", "ENUM", "STAR",
  "COMMA", "END", "RESET", "LSB", "RSB", "OUT", "UNTIL_KEY", "SC", "EQUAL",
  "LB", "RB", "C_CODE_BLOCK", "C_CONDITION_BLOCK", "IDENTIFIER",
  "CHARACTER_CONSTANT", "INTEGER_CONSTANT", "FLOATING_CONSTANT", "$accept",
  "fsml", "init_section_list", "init_section", "declaration", "time",
  "time_specifier", "period_specifier", "fsm", "fsm_objects_list",
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
       0,    68,    68,    70,    71,    72,    75,    76,    79,    81,
      82,    85,    92,    99,   102,   103,   106,   107,   108,   111,
     125,   128,   129,   132,   133,   134,   137,   138,   139,   140,
     141,   142,   143,   144,   145,   146,   147,   148,   151,   153,
     154,   157,   160,   163,   165,   166,   169,   170,   173,   176,
     177,   180,   181,   182,   183,   186,   189,   198,   199,   202,
     210,   212,   210,   216,   217,   220,   221,   224,   225,   228,
     229,   230,   233,   234,   235,   239,   240,   244,   246,   247,
     250,   251,   254,   255,   256,   259,   260,   263,   271,   276,
     270,   285,   286,   289,   290,   293,   294
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
      45,    46,    47,    48,    49
    };
    const int user_token_number_max_ = 304;

    if (t <= 0)
      return symbol_kind::S_YYEOF;
    else if (t <= user_token_number_max_)
      return YY_CAST (symbol_kind_type, translate_table[t]);
    else
      return symbol_kind::S_YYUNDEF;
  }

} // FSML
#line 1804 "fsml.cc"

#line 299 "fsml.yy"


void FSML::FSMLParser::error(const FSML::FSMLParser::location_type& l, const std::string& m)
{
	driver.error(l, m);
}
