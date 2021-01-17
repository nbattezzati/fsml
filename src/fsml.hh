// A Bison parser, made by GNU Bison 3.7.2.

// Skeleton interface for Bison LALR(1) parsers in C++

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


/**
 ** \file fsml.hh
 ** Define the FSML::parser class.
 */

// C++ LALR(1) parser skeleton written by Akim Demaille.

// DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
// especially those whose name start with YY_ or yy_.  They are
// private implementation details that can be changed or removed.

#ifndef YY_FSML_FSML_HH_INCLUDED
# define YY_FSML_FSML_HH_INCLUDED


# include <cstdlib> // std::abort
# include <iostream>
# include <stdexcept>
# include <string>
# include <vector>

#if defined __cplusplus
# define YY_CPLUSPLUS __cplusplus
#else
# define YY_CPLUSPLUS 199711L
#endif

// Support move semantics when possible.
#if 201103L <= YY_CPLUSPLUS
# define YY_MOVE           std::move
# define YY_MOVE_OR_COPY   move
# define YY_MOVE_REF(Type) Type&&
# define YY_RVREF(Type)    Type&&
# define YY_COPY(Type)     Type
#else
# define YY_MOVE
# define YY_MOVE_OR_COPY   copy
# define YY_MOVE_REF(Type) Type&
# define YY_RVREF(Type)    const Type&
# define YY_COPY(Type)     const Type&
#endif

// Support noexcept when possible.
#if 201103L <= YY_CPLUSPLUS
# define YY_NOEXCEPT noexcept
# define YY_NOTHROW
#else
# define YY_NOEXCEPT
# define YY_NOTHROW throw ()
#endif

// Support constexpr when possible.
#if 201703 <= YY_CPLUSPLUS
# define YY_CONSTEXPR constexpr
#else
# define YY_CONSTEXPR
#endif
# include "location.hh"

#ifndef YY_ASSERT
# include <cassert>
# define YY_ASSERT assert
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

namespace FSML {
#line 181 "fsml.hh"




  /// A Bison parser.
  class FSMLParser
  {
  public:
#ifndef YYSTYPE
  /// A buffer to store and retrieve objects.
  ///
  /// Sort of a variant, but does not keep track of the nature
  /// of the stored data, since that knowledge is available
  /// via the current parser state.
  class semantic_type
  {
  public:
    /// Type of *this.
    typedef semantic_type self_type;

    /// Empty construction.
    semantic_type () YY_NOEXCEPT
      : yybuffer_ ()
    {}

    /// Construct and fill.
    template <typename T>
    semantic_type (YY_RVREF (T) t)
    {
      YY_ASSERT (sizeof (T) <= size);
      new (yyas_<T> ()) T (YY_MOVE (t));
    }

#if 201103L <= YY_CPLUSPLUS
    /// Non copyable.
    semantic_type (const self_type&) = delete;
    /// Non copyable.
    self_type& operator= (const self_type&) = delete;
#endif

    /// Destruction, allowed only if empty.
    ~semantic_type () YY_NOEXCEPT
    {}

# if 201103L <= YY_CPLUSPLUS
    /// Instantiate a \a T in here from \a t.
    template <typename T, typename... U>
    T&
    emplace (U&&... u)
    {
      return *new (yyas_<T> ()) T (std::forward <U>(u)...);
    }
# else
    /// Instantiate an empty \a T in here.
    template <typename T>
    T&
    emplace ()
    {
      return *new (yyas_<T> ()) T ();
    }

    /// Instantiate a \a T in here from \a t.
    template <typename T>
    T&
    emplace (const T& t)
    {
      return *new (yyas_<T> ()) T (t);
    }
# endif

    /// Instantiate an empty \a T in here.
    /// Obsolete, use emplace.
    template <typename T>
    T&
    build ()
    {
      return emplace<T> ();
    }

    /// Instantiate a \a T in here from \a t.
    /// Obsolete, use emplace.
    template <typename T>
    T&
    build (const T& t)
    {
      return emplace<T> (t);
    }

    /// Accessor to a built \a T.
    template <typename T>
    T&
    as () YY_NOEXCEPT
    {
      return *yyas_<T> ();
    }

    /// Const accessor to a built \a T (for %printer).
    template <typename T>
    const T&
    as () const YY_NOEXCEPT
    {
      return *yyas_<T> ();
    }

    /// Swap the content with \a that, of same type.
    ///
    /// Both variants must be built beforehand, because swapping the actual
    /// data requires reading it (with as()), and this is not possible on
    /// unconstructed variants: it would require some dynamic testing, which
    /// should not be the variant's responsibility.
    /// Swapping between built and (possibly) non-built is done with
    /// self_type::move ().
    template <typename T>
    void
    swap (self_type& that) YY_NOEXCEPT
    {
      std::swap (as<T> (), that.as<T> ());
    }

    /// Move the content of \a that to this.
    ///
    /// Destroys \a that.
    template <typename T>
    void
    move (self_type& that)
    {
# if 201103L <= YY_CPLUSPLUS
      emplace<T> (std::move (that.as<T> ()));
# else
      emplace<T> ();
      swap<T> (that);
# endif
      that.destroy<T> ();
    }

# if 201103L <= YY_CPLUSPLUS
    /// Move the content of \a that to this.
    template <typename T>
    void
    move (self_type&& that)
    {
      emplace<T> (std::move (that.as<T> ()));
      that.destroy<T> ();
    }
#endif

    /// Copy the content of \a that to this.
    template <typename T>
    void
    copy (const self_type& that)
    {
      emplace<T> (that.as<T> ());
    }

    /// Destroy the stored \a T.
    template <typename T>
    void
    destroy ()
    {
      as<T> ().~T ();
    }

  private:
#if YY_CPLUSPLUS < 201103L
    /// Non copyable.
    semantic_type (const self_type&);
    /// Non copyable.
    self_type& operator= (const self_type&);
#endif

    /// Accessor to raw memory as \a T.
    template <typename T>
    T*
    yyas_ () YY_NOEXCEPT
    {
      void *yyp = yybuffer_.yyraw;
      return static_cast<T*> (yyp);
     }

    /// Const accessor to raw memory as \a T.
    template <typename T>
    const T*
    yyas_ () const YY_NOEXCEPT
    {
      const void *yyp = yybuffer_.yyraw;
      return static_cast<const T*> (yyp);
     }

    /// An auxiliary type to compute the largest semantic type.
    union union_type
    {
      // FLOATING_CONSTANT
      char dummy1[sizeof (float)];

      // INTEGER_CONSTANT
      char dummy2[sizeof (int)];

      // state_type
      char dummy3[sizeof (state_type_t)];

      // C_CODE_BLOCK
      // C_CONDITION_BLOCK
      // IDENTIFIER
      // CHARACTER_CONSTANT
      // type_specifier_list
      // type_specifier
      // struct_or_union_specifier
      // struct_or_union
      // enum_specifier
      // typedef_name
      // constant
      // enumeration_constant
      // timer_initializer
      // state_specifier
      // state_c_code
      // until_condition
      char dummy4[sizeof (std::string)];

      // variable_specifier
      char dummy5[sizeof (var_family_t)];
    };

    /// The size of the largest semantic type.
    enum { size = sizeof (union_type) };

    /// A buffer to store semantic values.
    union
    {
      /// Strongest alignment constraints.
      long double yyalign_me;
      /// A buffer large enough to store any of the semantic values.
      char yyraw[size];
    } yybuffer_;
  };

#else
    typedef YYSTYPE semantic_type;
#endif
    /// Symbol locations.
    typedef location location_type;

    /// Syntax errors thrown from user actions.
    struct syntax_error : std::runtime_error
    {
      syntax_error (const location_type& l, const std::string& m)
        : std::runtime_error (m)
        , location (l)
      {}

      syntax_error (const syntax_error& s)
        : std::runtime_error (s.what ())
        , location (s.location)
      {}

      ~syntax_error () YY_NOEXCEPT YY_NOTHROW;

      location_type location;
    };

    /// Token kinds.
    struct token
    {
      enum token_kind_type
      {
        YYEMPTY = -2,
    END_OF_FILE = 0,               // END_OF_FILE
    YYerror = 256,                 // error
    YYUNDEF = 257,                 // "invalid token"
    DECL_KEY = 258,                // DECL_KEY
    EXPORT_KEY = 259,              // EXPORT_KEY
    TIME_KEY = 260,                // TIME_KEY
    PERIOD_KEY = 261,              // PERIOD_KEY
    FSM_KEY = 262,                 // FSM_KEY
    LCB = 263,                     // LCB
    RCB = 264,                     // RCB
    VAR_KEY = 265,                 // VAR_KEY
    INPUT_KEY = 266,               // INPUT_KEY
    OUTPUT_KEY = 267,              // OUTPUT_KEY
    TIMER_KEY = 268,               // TIMER_KEY
    STATE_KEY = 269,               // STATE_KEY
    ON = 270,                      // ON
    TIMEOUT_KEY = 271,             // TIMEOUT_KEY
    GO = 272,                      // GO
    ERR = 273,                     // ERR
    RETRY = 274,                   // RETRY
    START = 275,                   // START
    VOID = 276,                    // VOID
    CHAR = 277,                    // CHAR
    SHORT = 278,                   // SHORT
    INT = 279,                     // INT
    LONG = 280,                    // LONG
    FLOAT = 281,                   // FLOAT
    DOUBLE = 282,                  // DOUBLE
    SIGNED = 283,                  // SIGNED
    UNSIGNED = 284,                // UNSIGNED
    UNION = 285,                   // UNION
    STRUCT = 286,                  // STRUCT
    ENUM = 287,                    // ENUM
    STAR = 288,                    // STAR
    COMMA = 289,                   // COMMA
    END = 290,                     // END
    RESET = 291,                   // RESET
    LSB = 292,                     // LSB
    RSB = 293,                     // RSB
    OUT = 294,                     // OUT
    UNTIL_KEY = 295,               // UNTIL_KEY
    SC = 296,                      // SC
    EQUAL = 297,                   // EQUAL
    LB = 298,                      // LB
    RB = 299,                      // RB
    C_CODE_BLOCK = 300,            // C_CODE_BLOCK
    C_CONDITION_BLOCK = 301,       // C_CONDITION_BLOCK
    IDENTIFIER = 302,              // IDENTIFIER
    CHARACTER_CONSTANT = 303,      // CHARACTER_CONSTANT
    INTEGER_CONSTANT = 304,        // INTEGER_CONSTANT
    FLOATING_CONSTANT = 305        // FLOATING_CONSTANT
      };
      /// Backward compatibility alias (Bison 3.6).
      typedef token_kind_type yytokentype;
    };

    /// Token kind, as returned by yylex.
    typedef token::yytokentype token_kind_type;

    /// Backward compatibility alias (Bison 3.6).
    typedef token_kind_type token_type;

    /// Symbol kinds.
    struct symbol_kind
    {
      enum symbol_kind_type
      {
        YYNTOKENS = 51, ///< Number of tokens.
        S_YYEMPTY = -2,
        S_YYEOF = 0,                             // END_OF_FILE
        S_YYerror = 1,                           // error
        S_YYUNDEF = 2,                           // "invalid token"
        S_DECL_KEY = 3,                          // DECL_KEY
        S_EXPORT_KEY = 4,                        // EXPORT_KEY
        S_TIME_KEY = 5,                          // TIME_KEY
        S_PERIOD_KEY = 6,                        // PERIOD_KEY
        S_FSM_KEY = 7,                           // FSM_KEY
        S_LCB = 8,                               // LCB
        S_RCB = 9,                               // RCB
        S_VAR_KEY = 10,                          // VAR_KEY
        S_INPUT_KEY = 11,                        // INPUT_KEY
        S_OUTPUT_KEY = 12,                       // OUTPUT_KEY
        S_TIMER_KEY = 13,                        // TIMER_KEY
        S_STATE_KEY = 14,                        // STATE_KEY
        S_ON = 15,                               // ON
        S_TIMEOUT_KEY = 16,                      // TIMEOUT_KEY
        S_GO = 17,                               // GO
        S_ERR = 18,                              // ERR
        S_RETRY = 19,                            // RETRY
        S_START = 20,                            // START
        S_VOID = 21,                             // VOID
        S_CHAR = 22,                             // CHAR
        S_SHORT = 23,                            // SHORT
        S_INT = 24,                              // INT
        S_LONG = 25,                             // LONG
        S_FLOAT = 26,                            // FLOAT
        S_DOUBLE = 27,                           // DOUBLE
        S_SIGNED = 28,                           // SIGNED
        S_UNSIGNED = 29,                         // UNSIGNED
        S_UNION = 30,                            // UNION
        S_STRUCT = 31,                           // STRUCT
        S_ENUM = 32,                             // ENUM
        S_STAR = 33,                             // STAR
        S_COMMA = 34,                            // COMMA
        S_END = 35,                              // END
        S_RESET = 36,                            // RESET
        S_LSB = 37,                              // LSB
        S_RSB = 38,                              // RSB
        S_OUT = 39,                              // OUT
        S_UNTIL_KEY = 40,                        // UNTIL_KEY
        S_SC = 41,                               // SC
        S_EQUAL = 42,                            // EQUAL
        S_LB = 43,                               // LB
        S_RB = 44,                               // RB
        S_C_CODE_BLOCK = 45,                     // C_CODE_BLOCK
        S_C_CONDITION_BLOCK = 46,                // C_CONDITION_BLOCK
        S_IDENTIFIER = 47,                       // IDENTIFIER
        S_CHARACTER_CONSTANT = 48,               // CHARACTER_CONSTANT
        S_INTEGER_CONSTANT = 49,                 // INTEGER_CONSTANT
        S_FLOATING_CONSTANT = 50,                // FLOATING_CONSTANT
        S_YYACCEPT = 51,                         // $accept
        S_fsml = 52,                             // fsml
        S_init_section_list = 53,                // init_section_list
        S_init_section = 54,                     // init_section
        S_declaration = 55,                      // declaration
        S_export = 56,                           // export
        S_time = 57,                             // time
        S_time_specifier = 58,                   // time_specifier
        S_period_specifier = 59,                 // period_specifier
        S_fsm = 60,                              // fsm
        S_fsm_objects_list = 61,                 // fsm_objects_list
        S_fsm_object = 62,                       // fsm_object
        S_variable_declaration = 63,             // variable_declaration
        S_type_specifier_list = 64,              // type_specifier_list
        S_variable_specifier = 65,               // variable_specifier
        S_type_specifier = 66,                   // type_specifier
        S_struct_or_union_specifier = 67,        // struct_or_union_specifier
        S_struct_or_union = 68,                  // struct_or_union
        S_enum_specifier = 69,                   // enum_specifier
        S_typedef_name = 70,                     // typedef_name
        S_init_declarator = 71,                  // init_declarator
        S_initializer = 72,                      // initializer
        S_declarator = 73,                       // declarator
        S_direct_declarator = 74,                // direct_declarator
        S_pointer = 75,                          // pointer
        S_constant = 76,                         // constant
        S_enumeration_constant = 77,             // enumeration_constant
        S_timer_specifier = 78,                  // timer_specifier
        S_timer_initializer = 79,                // timer_initializer
        S_state = 80,                            // state
        S_state_specifier = 81,                  // state_specifier
        S_82_1 = 82,                             // $@1
        S_83_2 = 83,                             // $@2
        S_state_type_specifier = 84,             // state_type_specifier
        S_state_c_code = 85,                     // state_c_code
        S_state_type_list = 86,                  // state_type_list
        S_state_type = 87,                       // state_type
        S_state_decorator_list = 88,             // state_decorator_list
        S_state_decorator = 89,                  // state_decorator
        S_transition_specifier = 90,             // transition_specifier
        S_transition_c_code = 91,                // transition_c_code
        S_transition_condition = 92,             // transition_condition
        S_transition_actuator = 93,              // transition_actuator
        S_timer_actuator = 94,                   // timer_actuator
        S_output_specifier = 95,                 // output_specifier
        S_until_retry = 96,                      // until_retry
        S_97_3 = 97,                             // $@3
        S_98_4 = 98,                             // $@4
        S_until_condition = 99,                  // until_condition
        S_until_object_list = 100,               // until_object_list
        S_until_object = 101                     // until_object
      };
    };

    /// (Internal) symbol kind.
    typedef symbol_kind::symbol_kind_type symbol_kind_type;

    /// The number of tokens.
    static const symbol_kind_type YYNTOKENS = symbol_kind::YYNTOKENS;

    /// A complete symbol.
    ///
    /// Expects its Base type to provide access to the symbol kind
    /// via kind ().
    ///
    /// Provide access to semantic value and location.
    template <typename Base>
    struct basic_symbol : Base
    {
      /// Alias to Base.
      typedef Base super_type;

      /// Default constructor.
      basic_symbol ()
        : value ()
        , location ()
      {}

#if 201103L <= YY_CPLUSPLUS
      /// Move constructor.
      basic_symbol (basic_symbol&& that)
        : Base (std::move (that))
        , value ()
        , location (std::move (that.location))
      {
        switch (this->kind ())
    {
      case symbol_kind::S_FLOATING_CONSTANT: // FLOATING_CONSTANT
        value.move< float > (std::move (that.value));
        break;

      case symbol_kind::S_INTEGER_CONSTANT: // INTEGER_CONSTANT
        value.move< int > (std::move (that.value));
        break;

      case symbol_kind::S_state_type: // state_type
        value.move< state_type_t > (std::move (that.value));
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
        value.move< std::string > (std::move (that.value));
        break;

      case symbol_kind::S_variable_specifier: // variable_specifier
        value.move< var_family_t > (std::move (that.value));
        break;

      default:
        break;
    }

      }
#endif

      /// Copy constructor.
      basic_symbol (const basic_symbol& that);

      /// Constructor for valueless symbols, and symbols from each type.
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, location_type&& l)
        : Base (t)
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const location_type& l)
        : Base (t)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, float&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const float& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, int&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const int& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, state_type_t&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const state_type_t& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::string&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::string& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, var_family_t&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const var_family_t& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

      /// Destroy the symbol.
      ~basic_symbol ()
      {
        clear ();
      }

      /// Destroy contents, and record that is empty.
      void clear ()
      {
        // User destructor.
        symbol_kind_type yykind = this->kind ();
        basic_symbol<Base>& yysym = *this;
        (void) yysym;
        switch (yykind)
        {
       default:
          break;
        }

        // Value type destructor.
switch (yykind)
    {
      case symbol_kind::S_FLOATING_CONSTANT: // FLOATING_CONSTANT
        value.template destroy< float > ();
        break;

      case symbol_kind::S_INTEGER_CONSTANT: // INTEGER_CONSTANT
        value.template destroy< int > ();
        break;

      case symbol_kind::S_state_type: // state_type
        value.template destroy< state_type_t > ();
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
        value.template destroy< std::string > ();
        break;

      case symbol_kind::S_variable_specifier: // variable_specifier
        value.template destroy< var_family_t > ();
        break;

      default:
        break;
    }

        Base::clear ();
      }

#if YYDEBUG || 0
      /// The user-facing name of this symbol.
      const char *name () const YY_NOEXCEPT
      {
        return FSMLParser::symbol_name (this->kind ());
      }
#endif // #if YYDEBUG || 0


      /// Backward compatibility (Bison 3.6).
      symbol_kind_type type_get () const YY_NOEXCEPT;

      /// Whether empty.
      bool empty () const YY_NOEXCEPT;

      /// Destructive move, \a s is emptied into this.
      void move (basic_symbol& s);

      /// The semantic value.
      semantic_type value;

      /// The location.
      location_type location;

    private:
#if YY_CPLUSPLUS < 201103L
      /// Assignment operator.
      basic_symbol& operator= (const basic_symbol& that);
#endif
    };

    /// Type access provider for token (enum) based symbols.
    struct by_kind
    {
      /// Default constructor.
      by_kind ();

#if 201103L <= YY_CPLUSPLUS
      /// Move constructor.
      by_kind (by_kind&& that);
#endif

      /// Copy constructor.
      by_kind (const by_kind& that);

      /// The symbol kind as needed by the constructor.
      typedef token_kind_type kind_type;

      /// Constructor from (external) token numbers.
      by_kind (kind_type t);

      /// Record that this symbol is empty.
      void clear ();

      /// Steal the symbol kind from \a that.
      void move (by_kind& that);

      /// The (internal) type number (corresponding to \a type).
      /// \a empty when empty.
      symbol_kind_type kind () const YY_NOEXCEPT;

      /// Backward compatibility (Bison 3.6).
      symbol_kind_type type_get () const YY_NOEXCEPT;

      /// The symbol kind.
      /// \a S_YYEMPTY when empty.
      symbol_kind_type kind_;
    };

    /// Backward compatibility for a private implementation detail (Bison 3.6).
    typedef by_kind by_type;

    /// "External" symbols: returned by the scanner.
    struct symbol_type : basic_symbol<by_kind>
    {
      /// Superclass.
      typedef basic_symbol<by_kind> super_type;

      /// Empty symbol.
      symbol_type () {}

      /// Constructor for valueless symbols, and symbols from each type.
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, location_type l)
        : super_type(token_type (tok), std::move (l))
      {
        YY_ASSERT (tok == token::END_OF_FILE || tok == token::YYerror || tok == token::YYUNDEF || tok == token::DECL_KEY || tok == token::EXPORT_KEY || tok == token::TIME_KEY || tok == token::PERIOD_KEY || tok == token::FSM_KEY || tok == token::LCB || tok == token::RCB || tok == token::VAR_KEY || tok == token::INPUT_KEY || tok == token::OUTPUT_KEY || tok == token::TIMER_KEY || tok == token::STATE_KEY || tok == token::ON || tok == token::TIMEOUT_KEY || tok == token::GO || tok == token::ERR || tok == token::RETRY || tok == token::START || tok == token::VOID || tok == token::CHAR || tok == token::SHORT || tok == token::INT || tok == token::LONG || tok == token::FLOAT || tok == token::DOUBLE || tok == token::SIGNED || tok == token::UNSIGNED || tok == token::UNION || tok == token::STRUCT || tok == token::ENUM || tok == token::STAR || tok == token::COMMA || tok == token::END || tok == token::RESET || tok == token::LSB || tok == token::RSB || tok == token::OUT || tok == token::UNTIL_KEY || tok == token::SC || tok == token::EQUAL || tok == token::LB || tok == token::RB);
      }
#else
      symbol_type (int tok, const location_type& l)
        : super_type(token_type (tok), l)
      {
        YY_ASSERT (tok == token::END_OF_FILE || tok == token::YYerror || tok == token::YYUNDEF || tok == token::DECL_KEY || tok == token::EXPORT_KEY || tok == token::TIME_KEY || tok == token::PERIOD_KEY || tok == token::FSM_KEY || tok == token::LCB || tok == token::RCB || tok == token::VAR_KEY || tok == token::INPUT_KEY || tok == token::OUTPUT_KEY || tok == token::TIMER_KEY || tok == token::STATE_KEY || tok == token::ON || tok == token::TIMEOUT_KEY || tok == token::GO || tok == token::ERR || tok == token::RETRY || tok == token::START || tok == token::VOID || tok == token::CHAR || tok == token::SHORT || tok == token::INT || tok == token::LONG || tok == token::FLOAT || tok == token::DOUBLE || tok == token::SIGNED || tok == token::UNSIGNED || tok == token::UNION || tok == token::STRUCT || tok == token::ENUM || tok == token::STAR || tok == token::COMMA || tok == token::END || tok == token::RESET || tok == token::LSB || tok == token::RSB || tok == token::OUT || tok == token::UNTIL_KEY || tok == token::SC || tok == token::EQUAL || tok == token::LB || tok == token::RB);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, float v, location_type l)
        : super_type(token_type (tok), std::move (v), std::move (l))
      {
        YY_ASSERT (tok == token::FLOATING_CONSTANT);
      }
#else
      symbol_type (int tok, const float& v, const location_type& l)
        : super_type(token_type (tok), v, l)
      {
        YY_ASSERT (tok == token::FLOATING_CONSTANT);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, int v, location_type l)
        : super_type(token_type (tok), std::move (v), std::move (l))
      {
        YY_ASSERT (tok == token::INTEGER_CONSTANT);
      }
#else
      symbol_type (int tok, const int& v, const location_type& l)
        : super_type(token_type (tok), v, l)
      {
        YY_ASSERT (tok == token::INTEGER_CONSTANT);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, std::string v, location_type l)
        : super_type(token_type (tok), std::move (v), std::move (l))
      {
        YY_ASSERT (tok == token::C_CODE_BLOCK || tok == token::C_CONDITION_BLOCK || tok == token::IDENTIFIER || tok == token::CHARACTER_CONSTANT);
      }
#else
      symbol_type (int tok, const std::string& v, const location_type& l)
        : super_type(token_type (tok), v, l)
      {
        YY_ASSERT (tok == token::C_CODE_BLOCK || tok == token::C_CONDITION_BLOCK || tok == token::IDENTIFIER || tok == token::CHARACTER_CONSTANT);
      }
#endif
    };

    /// Build a parser object.
    FSMLParser (FSMLDriver& driver_yyarg);
    virtual ~FSMLParser ();

#if 201103L <= YY_CPLUSPLUS
    /// Non copyable.
    FSMLParser (const FSMLParser&) = delete;
    /// Non copyable.
    FSMLParser& operator= (const FSMLParser&) = delete;
#endif

    /// Parse.  An alias for parse ().
    /// \returns  0 iff parsing succeeded.
    int operator() ();

    /// Parse.
    /// \returns  0 iff parsing succeeded.
    virtual int parse ();

#if YYDEBUG
    /// The current debugging stream.
    std::ostream& debug_stream () const YY_ATTRIBUTE_PURE;
    /// Set the current debugging stream.
    void set_debug_stream (std::ostream &);

    /// Type for debugging levels.
    typedef int debug_level_type;
    /// The current debugging level.
    debug_level_type debug_level () const YY_ATTRIBUTE_PURE;
    /// Set the current debugging level.
    void set_debug_level (debug_level_type l);
#endif

    /// Report a syntax error.
    /// \param loc    where the syntax error is found.
    /// \param msg    a description of the syntax error.
    virtual void error (const location_type& loc, const std::string& msg);

    /// Report a syntax error.
    void error (const syntax_error& err);

#if YYDEBUG || 0
    /// The user-facing name of the symbol whose (internal) number is
    /// YYSYMBOL.  No bounds checking.
    static const char *symbol_name (symbol_kind_type yysymbol);
#endif // #if YYDEBUG || 0


    // Implementation of make_symbol for each symbol type.
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_END_OF_FILE (location_type l)
      {
        return symbol_type (token::END_OF_FILE, std::move (l));
      }
#else
      static
      symbol_type
      make_END_OF_FILE (const location_type& l)
      {
        return symbol_type (token::END_OF_FILE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_YYerror (location_type l)
      {
        return symbol_type (token::YYerror, std::move (l));
      }
#else
      static
      symbol_type
      make_YYerror (const location_type& l)
      {
        return symbol_type (token::YYerror, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_YYUNDEF (location_type l)
      {
        return symbol_type (token::YYUNDEF, std::move (l));
      }
#else
      static
      symbol_type
      make_YYUNDEF (const location_type& l)
      {
        return symbol_type (token::YYUNDEF, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DECL_KEY (location_type l)
      {
        return symbol_type (token::DECL_KEY, std::move (l));
      }
#else
      static
      symbol_type
      make_DECL_KEY (const location_type& l)
      {
        return symbol_type (token::DECL_KEY, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_EXPORT_KEY (location_type l)
      {
        return symbol_type (token::EXPORT_KEY, std::move (l));
      }
#else
      static
      symbol_type
      make_EXPORT_KEY (const location_type& l)
      {
        return symbol_type (token::EXPORT_KEY, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TIME_KEY (location_type l)
      {
        return symbol_type (token::TIME_KEY, std::move (l));
      }
#else
      static
      symbol_type
      make_TIME_KEY (const location_type& l)
      {
        return symbol_type (token::TIME_KEY, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_PERIOD_KEY (location_type l)
      {
        return symbol_type (token::PERIOD_KEY, std::move (l));
      }
#else
      static
      symbol_type
      make_PERIOD_KEY (const location_type& l)
      {
        return symbol_type (token::PERIOD_KEY, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_FSM_KEY (location_type l)
      {
        return symbol_type (token::FSM_KEY, std::move (l));
      }
#else
      static
      symbol_type
      make_FSM_KEY (const location_type& l)
      {
        return symbol_type (token::FSM_KEY, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LCB (location_type l)
      {
        return symbol_type (token::LCB, std::move (l));
      }
#else
      static
      symbol_type
      make_LCB (const location_type& l)
      {
        return symbol_type (token::LCB, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_RCB (location_type l)
      {
        return symbol_type (token::RCB, std::move (l));
      }
#else
      static
      symbol_type
      make_RCB (const location_type& l)
      {
        return symbol_type (token::RCB, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_VAR_KEY (location_type l)
      {
        return symbol_type (token::VAR_KEY, std::move (l));
      }
#else
      static
      symbol_type
      make_VAR_KEY (const location_type& l)
      {
        return symbol_type (token::VAR_KEY, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_INPUT_KEY (location_type l)
      {
        return symbol_type (token::INPUT_KEY, std::move (l));
      }
#else
      static
      symbol_type
      make_INPUT_KEY (const location_type& l)
      {
        return symbol_type (token::INPUT_KEY, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_OUTPUT_KEY (location_type l)
      {
        return symbol_type (token::OUTPUT_KEY, std::move (l));
      }
#else
      static
      symbol_type
      make_OUTPUT_KEY (const location_type& l)
      {
        return symbol_type (token::OUTPUT_KEY, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TIMER_KEY (location_type l)
      {
        return symbol_type (token::TIMER_KEY, std::move (l));
      }
#else
      static
      symbol_type
      make_TIMER_KEY (const location_type& l)
      {
        return symbol_type (token::TIMER_KEY, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_STATE_KEY (location_type l)
      {
        return symbol_type (token::STATE_KEY, std::move (l));
      }
#else
      static
      symbol_type
      make_STATE_KEY (const location_type& l)
      {
        return symbol_type (token::STATE_KEY, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ON (location_type l)
      {
        return symbol_type (token::ON, std::move (l));
      }
#else
      static
      symbol_type
      make_ON (const location_type& l)
      {
        return symbol_type (token::ON, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TIMEOUT_KEY (location_type l)
      {
        return symbol_type (token::TIMEOUT_KEY, std::move (l));
      }
#else
      static
      symbol_type
      make_TIMEOUT_KEY (const location_type& l)
      {
        return symbol_type (token::TIMEOUT_KEY, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_GO (location_type l)
      {
        return symbol_type (token::GO, std::move (l));
      }
#else
      static
      symbol_type
      make_GO (const location_type& l)
      {
        return symbol_type (token::GO, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ERR (location_type l)
      {
        return symbol_type (token::ERR, std::move (l));
      }
#else
      static
      symbol_type
      make_ERR (const location_type& l)
      {
        return symbol_type (token::ERR, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_RETRY (location_type l)
      {
        return symbol_type (token::RETRY, std::move (l));
      }
#else
      static
      symbol_type
      make_RETRY (const location_type& l)
      {
        return symbol_type (token::RETRY, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_START (location_type l)
      {
        return symbol_type (token::START, std::move (l));
      }
#else
      static
      symbol_type
      make_START (const location_type& l)
      {
        return symbol_type (token::START, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_VOID (location_type l)
      {
        return symbol_type (token::VOID, std::move (l));
      }
#else
      static
      symbol_type
      make_VOID (const location_type& l)
      {
        return symbol_type (token::VOID, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CHAR (location_type l)
      {
        return symbol_type (token::CHAR, std::move (l));
      }
#else
      static
      symbol_type
      make_CHAR (const location_type& l)
      {
        return symbol_type (token::CHAR, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SHORT (location_type l)
      {
        return symbol_type (token::SHORT, std::move (l));
      }
#else
      static
      symbol_type
      make_SHORT (const location_type& l)
      {
        return symbol_type (token::SHORT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_INT (location_type l)
      {
        return symbol_type (token::INT, std::move (l));
      }
#else
      static
      symbol_type
      make_INT (const location_type& l)
      {
        return symbol_type (token::INT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LONG (location_type l)
      {
        return symbol_type (token::LONG, std::move (l));
      }
#else
      static
      symbol_type
      make_LONG (const location_type& l)
      {
        return symbol_type (token::LONG, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_FLOAT (location_type l)
      {
        return symbol_type (token::FLOAT, std::move (l));
      }
#else
      static
      symbol_type
      make_FLOAT (const location_type& l)
      {
        return symbol_type (token::FLOAT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DOUBLE (location_type l)
      {
        return symbol_type (token::DOUBLE, std::move (l));
      }
#else
      static
      symbol_type
      make_DOUBLE (const location_type& l)
      {
        return symbol_type (token::DOUBLE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SIGNED (location_type l)
      {
        return symbol_type (token::SIGNED, std::move (l));
      }
#else
      static
      symbol_type
      make_SIGNED (const location_type& l)
      {
        return symbol_type (token::SIGNED, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UNSIGNED (location_type l)
      {
        return symbol_type (token::UNSIGNED, std::move (l));
      }
#else
      static
      symbol_type
      make_UNSIGNED (const location_type& l)
      {
        return symbol_type (token::UNSIGNED, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UNION (location_type l)
      {
        return symbol_type (token::UNION, std::move (l));
      }
#else
      static
      symbol_type
      make_UNION (const location_type& l)
      {
        return symbol_type (token::UNION, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_STRUCT (location_type l)
      {
        return symbol_type (token::STRUCT, std::move (l));
      }
#else
      static
      symbol_type
      make_STRUCT (const location_type& l)
      {
        return symbol_type (token::STRUCT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ENUM (location_type l)
      {
        return symbol_type (token::ENUM, std::move (l));
      }
#else
      static
      symbol_type
      make_ENUM (const location_type& l)
      {
        return symbol_type (token::ENUM, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_STAR (location_type l)
      {
        return symbol_type (token::STAR, std::move (l));
      }
#else
      static
      symbol_type
      make_STAR (const location_type& l)
      {
        return symbol_type (token::STAR, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_COMMA (location_type l)
      {
        return symbol_type (token::COMMA, std::move (l));
      }
#else
      static
      symbol_type
      make_COMMA (const location_type& l)
      {
        return symbol_type (token::COMMA, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_END (location_type l)
      {
        return symbol_type (token::END, std::move (l));
      }
#else
      static
      symbol_type
      make_END (const location_type& l)
      {
        return symbol_type (token::END, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_RESET (location_type l)
      {
        return symbol_type (token::RESET, std::move (l));
      }
#else
      static
      symbol_type
      make_RESET (const location_type& l)
      {
        return symbol_type (token::RESET, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LSB (location_type l)
      {
        return symbol_type (token::LSB, std::move (l));
      }
#else
      static
      symbol_type
      make_LSB (const location_type& l)
      {
        return symbol_type (token::LSB, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_RSB (location_type l)
      {
        return symbol_type (token::RSB, std::move (l));
      }
#else
      static
      symbol_type
      make_RSB (const location_type& l)
      {
        return symbol_type (token::RSB, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_OUT (location_type l)
      {
        return symbol_type (token::OUT, std::move (l));
      }
#else
      static
      symbol_type
      make_OUT (const location_type& l)
      {
        return symbol_type (token::OUT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UNTIL_KEY (location_type l)
      {
        return symbol_type (token::UNTIL_KEY, std::move (l));
      }
#else
      static
      symbol_type
      make_UNTIL_KEY (const location_type& l)
      {
        return symbol_type (token::UNTIL_KEY, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SC (location_type l)
      {
        return symbol_type (token::SC, std::move (l));
      }
#else
      static
      symbol_type
      make_SC (const location_type& l)
      {
        return symbol_type (token::SC, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_EQUAL (location_type l)
      {
        return symbol_type (token::EQUAL, std::move (l));
      }
#else
      static
      symbol_type
      make_EQUAL (const location_type& l)
      {
        return symbol_type (token::EQUAL, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LB (location_type l)
      {
        return symbol_type (token::LB, std::move (l));
      }
#else
      static
      symbol_type
      make_LB (const location_type& l)
      {
        return symbol_type (token::LB, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_RB (location_type l)
      {
        return symbol_type (token::RB, std::move (l));
      }
#else
      static
      symbol_type
      make_RB (const location_type& l)
      {
        return symbol_type (token::RB, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_C_CODE_BLOCK (std::string v, location_type l)
      {
        return symbol_type (token::C_CODE_BLOCK, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_C_CODE_BLOCK (const std::string& v, const location_type& l)
      {
        return symbol_type (token::C_CODE_BLOCK, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_C_CONDITION_BLOCK (std::string v, location_type l)
      {
        return symbol_type (token::C_CONDITION_BLOCK, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_C_CONDITION_BLOCK (const std::string& v, const location_type& l)
      {
        return symbol_type (token::C_CONDITION_BLOCK, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_IDENTIFIER (std::string v, location_type l)
      {
        return symbol_type (token::IDENTIFIER, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_IDENTIFIER (const std::string& v, const location_type& l)
      {
        return symbol_type (token::IDENTIFIER, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CHARACTER_CONSTANT (std::string v, location_type l)
      {
        return symbol_type (token::CHARACTER_CONSTANT, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_CHARACTER_CONSTANT (const std::string& v, const location_type& l)
      {
        return symbol_type (token::CHARACTER_CONSTANT, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_INTEGER_CONSTANT (int v, location_type l)
      {
        return symbol_type (token::INTEGER_CONSTANT, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_INTEGER_CONSTANT (const int& v, const location_type& l)
      {
        return symbol_type (token::INTEGER_CONSTANT, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_FLOATING_CONSTANT (float v, location_type l)
      {
        return symbol_type (token::FLOATING_CONSTANT, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_FLOATING_CONSTANT (const float& v, const location_type& l)
      {
        return symbol_type (token::FLOATING_CONSTANT, v, l);
      }
#endif


  private:
#if YY_CPLUSPLUS < 201103L
    /// Non copyable.
    FSMLParser (const FSMLParser&);
    /// Non copyable.
    FSMLParser& operator= (const FSMLParser&);
#endif


    /// Stored state numbers (used for stacks).
    typedef unsigned char state_type;

    /// Compute post-reduction state.
    /// \param yystate   the current state
    /// \param yysym     the nonterminal to push on the stack
    static state_type yy_lr_goto_state_ (state_type yystate, int yysym);

    /// Whether the given \c yypact_ value indicates a defaulted state.
    /// \param yyvalue   the value to check
    static bool yy_pact_value_is_default_ (int yyvalue);

    /// Whether the given \c yytable_ value indicates a syntax error.
    /// \param yyvalue   the value to check
    static bool yy_table_value_is_error_ (int yyvalue);

    static const signed char yypact_ninf_;
    static const signed char yytable_ninf_;

    /// Convert a scanner token kind \a t to a symbol kind.
    /// In theory \a t should be a token_kind_type, but character literals
    /// are valid, yet not members of the token_type enum.
    static symbol_kind_type yytranslate_ (int t);

#if YYDEBUG || 0
    /// For a symbol, its name in clear.
    static const char* const yytname_[];
#endif // #if YYDEBUG || 0


    // Tables.
    // YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
    // STATE-NUM.
    static const signed char yypact_[];

    // YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
    // Performed when YYTABLE does not specify something else to do.  Zero
    // means the default is an error.
    static const signed char yydefact_[];

    // YYPGOTO[NTERM-NUM].
    static const signed char yypgoto_[];

    // YYDEFGOTO[NTERM-NUM].
    static const short yydefgoto_[];

    // YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
    // positive, shift that token.  If negative, reduce the rule whose
    // number is the opposite.  If YYTABLE_NINF, syntax error.
    static const short yytable_[];

    static const short yycheck_[];

    // YYSTOS[STATE-NUM] -- The (internal number of the) accessing
    // symbol of state STATE-NUM.
    static const signed char yystos_[];

    // YYR1[YYN] -- Symbol number of symbol that rule YYN derives.
    static const signed char yyr1_[];

    // YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.
    static const signed char yyr2_[];


#if YYDEBUG
    // YYRLINE[YYN] -- Source line where rule number YYN was defined.
    static const short yyrline_[];
    /// Report on the debug stream that the rule \a r is going to be reduced.
    virtual void yy_reduce_print_ (int r) const;
    /// Print the state stack on the debug stream.
    virtual void yy_stack_print_ () const;

    /// Debugging level.
    int yydebug_;
    /// Debug stream.
    std::ostream* yycdebug_;

    /// \brief Display a symbol kind, value and location.
    /// \param yyo    The output stream.
    /// \param yysym  The symbol.
    template <typename Base>
    void yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const;
#endif

    /// \brief Reclaim the memory associated to a symbol.
    /// \param yymsg     Why this token is reclaimed.
    ///                  If null, print nothing.
    /// \param yysym     The symbol.
    template <typename Base>
    void yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const;

  private:
    /// Type access provider for state based symbols.
    struct by_state
    {
      /// Default constructor.
      by_state () YY_NOEXCEPT;

      /// The symbol kind as needed by the constructor.
      typedef state_type kind_type;

      /// Constructor.
      by_state (kind_type s) YY_NOEXCEPT;

      /// Copy constructor.
      by_state (const by_state& that) YY_NOEXCEPT;

      /// Record that this symbol is empty.
      void clear () YY_NOEXCEPT;

      /// Steal the symbol kind from \a that.
      void move (by_state& that);

      /// The symbol kind (corresponding to \a state).
      /// \a symbol_kind::S_YYEMPTY when empty.
      symbol_kind_type kind () const YY_NOEXCEPT;

      /// The state number used to denote an empty symbol.
      /// We use the initial state, as it does not have a value.
      enum { empty_state = 0 };

      /// The state.
      /// \a empty when empty.
      state_type state;
    };

    /// "Internal" symbol: element of the stack.
    struct stack_symbol_type : basic_symbol<by_state>
    {
      /// Superclass.
      typedef basic_symbol<by_state> super_type;
      /// Construct an empty symbol.
      stack_symbol_type ();
      /// Move or copy construction.
      stack_symbol_type (YY_RVREF (stack_symbol_type) that);
      /// Steal the contents from \a sym to build this.
      stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) sym);
#if YY_CPLUSPLUS < 201103L
      /// Assignment, needed by push_back by some old implementations.
      /// Moves the contents of that.
      stack_symbol_type& operator= (stack_symbol_type& that);

      /// Assignment, needed by push_back by other implementations.
      /// Needed by some other old implementations.
      stack_symbol_type& operator= (const stack_symbol_type& that);
#endif
    };

    /// A stack with random access from its top.
    template <typename T, typename S = std::vector<T> >
    class stack
    {
    public:
      // Hide our reversed order.
      typedef typename S::iterator iterator;
      typedef typename S::const_iterator const_iterator;
      typedef typename S::size_type size_type;
      typedef typename std::ptrdiff_t index_type;

      stack (size_type n = 200)
        : seq_ (n)
      {}

#if 201103L <= YY_CPLUSPLUS
      /// Non copyable.
      stack (const stack&) = delete;
      /// Non copyable.
      stack& operator= (const stack&) = delete;
#endif

      /// Random access.
      ///
      /// Index 0 returns the topmost element.
      const T&
      operator[] (index_type i) const
      {
        return seq_[size_type (size () - 1 - i)];
      }

      /// Random access.
      ///
      /// Index 0 returns the topmost element.
      T&
      operator[] (index_type i)
      {
        return seq_[size_type (size () - 1 - i)];
      }

      /// Steal the contents of \a t.
      ///
      /// Close to move-semantics.
      void
      push (YY_MOVE_REF (T) t)
      {
        seq_.push_back (T ());
        operator[] (0).move (t);
      }

      /// Pop elements from the stack.
      void
      pop (std::ptrdiff_t n = 1) YY_NOEXCEPT
      {
        for (; 0 < n; --n)
          seq_.pop_back ();
      }

      /// Pop all elements from the stack.
      void
      clear () YY_NOEXCEPT
      {
        seq_.clear ();
      }

      /// Number of elements on the stack.
      index_type
      size () const YY_NOEXCEPT
      {
        return index_type (seq_.size ());
      }

      /// Iterator on top of the stack (going downwards).
      const_iterator
      begin () const YY_NOEXCEPT
      {
        return seq_.begin ();
      }

      /// Bottom of the stack.
      const_iterator
      end () const YY_NOEXCEPT
      {
        return seq_.end ();
      }

      /// Present a slice of the top of a stack.
      class slice
      {
      public:
        slice (const stack& stack, index_type range)
          : stack_ (stack)
          , range_ (range)
        {}

        const T&
        operator[] (index_type i) const
        {
          return stack_[range_ - i];
        }

      private:
        const stack& stack_;
        index_type range_;
      };

    private:
#if YY_CPLUSPLUS < 201103L
      /// Non copyable.
      stack (const stack&);
      /// Non copyable.
      stack& operator= (const stack&);
#endif
      /// The wrapped container.
      S seq_;
    };


    /// Stack type.
    typedef stack<stack_symbol_type> stack_type;

    /// The stack.
    stack_type yystack_;

    /// Push a new state on the stack.
    /// \param m    a debug message to display
    ///             if null, no trace is output.
    /// \param sym  the symbol
    /// \warning the contents of \a s.value is stolen.
    void yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym);

    /// Push a new look ahead token on the state on the stack.
    /// \param m    a debug message to display
    ///             if null, no trace is output.
    /// \param s    the state
    /// \param sym  the symbol (for its value and location).
    /// \warning the contents of \a sym.value is stolen.
    void yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym);

    /// Pop \a n symbols from the stack.
    void yypop_ (int n = 1);

    /// Constants.
    enum
    {
      yylast_ = 148,     ///< Last index in yytable_.
      yynnts_ = 51,  ///< Number of nonterminal symbols.
      yyfinal_ = 17 ///< Termination state number.
    };


    // User arguments.
    FSMLDriver& driver;

  };


} // FSML
#line 2108 "fsml.hh"




#endif // !YY_FSML_FSML_HH_INCLUDED
