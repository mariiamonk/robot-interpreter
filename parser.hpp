// A Bison parser, made by GNU Bison 3.8.2.

// Skeleton interface for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2021 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

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
 ** \file parser.hpp
 ** Define the yy::parser class.
 */

// C++ LALR(1) parser skeleton written by Akim Demaille.

// DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
// especially those whose name start with YY_ or yy_.  They are
// private implementation details that can be changed or removed.

#ifndef YY_YY_PARSER_HPP_INCLUDED
# define YY_YY_PARSER_HPP_INCLUDED
// "%code requires" blocks.
#line 8 "robot/robot.y"

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include "ast/ast.h"
#include "ast/bases.h"
#include "robot/robot.h"
#include "graphics/graphics.h"

class Scanner;

#line 62 "parser.hpp"


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
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
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

namespace yy {
#line 197 "parser.hpp"




  /// A Bison parser.
  class parser
  {
  public:
#ifdef YYSTYPE
# ifdef __GNUC__
#  pragma GCC message "bison: do not #define YYSTYPE in C++, use %define api.value.type"
# endif
    typedef YYSTYPE value_type;
#else
  /// A buffer to store and retrieve objects.
  ///
  /// Sort of a variant, but does not keep track of the nature
  /// of the stored data, since that knowledge is available
  /// via the current parser state.
  class value_type
  {
  public:
    /// Type of *this.
    typedef value_type self_type;

    /// Empty construction.
    value_type () YY_NOEXCEPT
      : yyraw_ ()
    {}

    /// Construct and fill.
    template <typename T>
    value_type (YY_RVREF (T) t)
    {
      new (yyas_<T> ()) T (YY_MOVE (t));
    }

#if 201103L <= YY_CPLUSPLUS
    /// Non copyable.
    value_type (const self_type&) = delete;
    /// Non copyable.
    self_type& operator= (const self_type&) = delete;
#endif

    /// Destruction, allowed only if empty.
    ~value_type () YY_NOEXCEPT
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
    value_type (const self_type&);
    /// Non copyable.
    self_type& operator= (const self_type&);
#endif

    /// Accessor to raw memory as \a T.
    template <typename T>
    T*
    yyas_ () YY_NOEXCEPT
    {
      void *yyp = yyraw_;
      return static_cast<T*> (yyp);
     }

    /// Const accessor to raw memory as \a T.
    template <typename T>
    const T*
    yyas_ () const YY_NOEXCEPT
    {
      const void *yyp = yyraw_;
      return static_cast<const T*> (yyp);
     }

    /// An auxiliary type to compute the largest semantic type.
    union union_type
    {
      // program
      // function_decl
      // block
      // statement
      // assignment
      // var_decl
      // array_access
      // size_expr
      // digitize_expr
      // logitize_expr
      // reduce_expr
      // extend_expr
      // for_loop
      // switch_stmt
      // robot_cmd
      // function_call
      // return_stmt
      // print_stmt
      // expr
      char dummy1[sizeof (ASTNode*)];

      // BOOL
      char dummy2[sizeof (BoolValue)];

      // NUMBER
      char dummy3[sizeof (int)];

      // IDENTIFIER
      char dummy4[sizeof (std::string)];

      // function_list
      // statement_list
      // dim_list
      // index_list
      // expr_list
      char dummy5[sizeof (std::vector<ASTNode*>)];

      // param_list
      char dummy6[sizeof (std::vector<std::string>)];
    };

    /// The size of the largest semantic type.
    enum { size = sizeof (union_type) };

    /// A buffer to store semantic values.
    union
    {
      /// Strongest alignment constraints.
      long double yyalign_me_;
      /// A buffer large enough to store any of the semantic values.
      char yyraw_[size];
    };
  };

#endif
    /// Backward compatibility (Bison 3.8).
    typedef value_type semantic_type;


    /// Syntax errors thrown from user actions.
    struct syntax_error : std::runtime_error
    {
      syntax_error (const std::string& m)
        : std::runtime_error (m)
      {}

      syntax_error (const syntax_error& s)
        : std::runtime_error (s.what ())
      {}

      ~syntax_error () YY_NOEXCEPT YY_NOTHROW;
    };

    /// Token kinds.
    struct token
    {
      enum token_kind_type
      {
        YYEMPTY = -2,
    YYEOF = 0,                     // "end of file"
    YYerror = 256,                 // error
    YYUNDEF = 257,                 // "invalid token"
    VAR = 258,                     // VAR
    SIZE = 259,                    // SIZE
    LOGITIZE = 260,                // LOGITIZE
    DIGITIZE = 261,                // DIGITIZE
    REDUCE = 262,                  // REDUCE
    EXTEND = 263,                  // EXTEND
    FOR = 264,                     // FOR
    BOUNDARY = 265,                // BOUNDARY
    STEP = 266,                    // STEP
    SWITCH = 267,                  // SWITCH
    ELSE = 268,                    // ELSE
    MOVE = 269,                    // MOVE
    ROTATE = 270,                  // ROTATE
    LEFT = 271,                    // LEFT
    RIGHT = 272,                   // RIGHT
    GET = 273,                     // GET
    ENVIRONMENT = 274,             // ENVIRONMENT
    AND = 275,                     // AND
    OR = 276,                      // OR
    NOT = 277,                     // NOT
    PRINT = 278,                   // PRINT
    PLEASE = 279,                  // PLEASE
    THANKS = 280,                  // THANKS
    TASK = 281,                    // TASK
    DO = 282,                      // DO
    RESULT = 283,                  // RESULT
    MXTRUE = 284,                  // MXTRUE
    MXFALSE = 285,                 // MXFALSE
    DASSIGN = 286,                 // DASSIGN
    MASSIGN = 287,                 // MASSIGN
    VASSIGN = 288,                 // VASSIGN
    NASSIGN = 289,                 // NASSIGN
    MXEQ = 290,                    // MXEQ
    MXLT = 291,                    // MXLT
    MXGT = 292,                    // MXGT
    MXLTE = 293,                   // MXLTE
    MXGTE = 294,                   // MXGTE
    ELEQ = 295,                    // ELEQ
    ELLT = 296,                    // ELLT
    ELGT = 297,                    // ELGT
    ELLTE = 298,                   // ELLTE
    ELGTE = 299,                   // ELGTE
    ASSIGN = 300,                  // ASSIGN
    SEMICOLON = 301,               // SEMICOLON
    LBRACKET = 302,                // LBRACKET
    RBRACKET = 303,                // RBRACKET
    LPAREN = 304,                  // LPAREN
    RPAREN = 305,                  // RPAREN
    COMMA = 306,                   // COMMA
    PLUS = 307,                    // PLUS
    MINUS = 308,                   // MINUS
    MULT = 309,                    // MULT
    DIV = 310,                     // DIV
    NUMBER = 311,                  // NUMBER
    BOOL = 312,                    // BOOL
    IDENTIFIER = 313,              // IDENTIFIER
    FINDEXIT = 314                 // FINDEXIT
      };
      /// Backward compatibility alias (Bison 3.6).
      typedef token_kind_type yytokentype;
    };

    /// Token kind, as returned by yylex.
    typedef token::token_kind_type token_kind_type;

    /// Backward compatibility alias (Bison 3.6).
    typedef token_kind_type token_type;

    /// Symbol kinds.
    struct symbol_kind
    {
      enum symbol_kind_type
      {
        YYNTOKENS = 62, ///< Number of tokens.
        S_YYEMPTY = -2,
        S_YYEOF = 0,                             // "end of file"
        S_YYerror = 1,                           // error
        S_YYUNDEF = 2,                           // "invalid token"
        S_VAR = 3,                               // VAR
        S_SIZE = 4,                              // SIZE
        S_LOGITIZE = 5,                          // LOGITIZE
        S_DIGITIZE = 6,                          // DIGITIZE
        S_REDUCE = 7,                            // REDUCE
        S_EXTEND = 8,                            // EXTEND
        S_FOR = 9,                               // FOR
        S_BOUNDARY = 10,                         // BOUNDARY
        S_STEP = 11,                             // STEP
        S_SWITCH = 12,                           // SWITCH
        S_ELSE = 13,                             // ELSE
        S_MOVE = 14,                             // MOVE
        S_ROTATE = 15,                           // ROTATE
        S_LEFT = 16,                             // LEFT
        S_RIGHT = 17,                            // RIGHT
        S_GET = 18,                              // GET
        S_ENVIRONMENT = 19,                      // ENVIRONMENT
        S_AND = 20,                              // AND
        S_OR = 21,                               // OR
        S_NOT = 22,                              // NOT
        S_PRINT = 23,                            // PRINT
        S_PLEASE = 24,                           // PLEASE
        S_THANKS = 25,                           // THANKS
        S_TASK = 26,                             // TASK
        S_DO = 27,                               // DO
        S_RESULT = 28,                           // RESULT
        S_MXTRUE = 29,                           // MXTRUE
        S_MXFALSE = 30,                          // MXFALSE
        S_DASSIGN = 31,                          // DASSIGN
        S_MASSIGN = 32,                          // MASSIGN
        S_VASSIGN = 33,                          // VASSIGN
        S_NASSIGN = 34,                          // NASSIGN
        S_MXEQ = 35,                             // MXEQ
        S_MXLT = 36,                             // MXLT
        S_MXGT = 37,                             // MXGT
        S_MXLTE = 38,                            // MXLTE
        S_MXGTE = 39,                            // MXGTE
        S_ELEQ = 40,                             // ELEQ
        S_ELLT = 41,                             // ELLT
        S_ELGT = 42,                             // ELGT
        S_ELLTE = 43,                            // ELLTE
        S_ELGTE = 44,                            // ELGTE
        S_ASSIGN = 45,                           // ASSIGN
        S_SEMICOLON = 46,                        // SEMICOLON
        S_LBRACKET = 47,                         // LBRACKET
        S_RBRACKET = 48,                         // RBRACKET
        S_LPAREN = 49,                           // LPAREN
        S_RPAREN = 50,                           // RPAREN
        S_COMMA = 51,                            // COMMA
        S_PLUS = 52,                             // PLUS
        S_MINUS = 53,                            // MINUS
        S_MULT = 54,                             // MULT
        S_DIV = 55,                              // DIV
        S_NUMBER = 56,                           // NUMBER
        S_BOOL = 57,                             // BOOL
        S_IDENTIFIER = 58,                       // IDENTIFIER
        S_FINDEXIT = 59,                         // FINDEXIT
        S_60_ = 60,                              // '{'
        S_61_ = 61,                              // '}'
        S_YYACCEPT = 62,                         // $accept
        S_program = 63,                          // program
        S_function_list = 64,                    // function_list
        S_function_decl = 65,                    // function_decl
        S_param_list = 66,                       // param_list
        S_block = 67,                            // block
        S_statement_list = 68,                   // statement_list
        S_statement = 69,                        // statement
        S_assignment = 70,                       // assignment
        S_var_decl = 71,                         // var_decl
        S_dim_list = 72,                         // dim_list
        S_array_access = 73,                     // array_access
        S_index_list = 74,                       // index_list
        S_size_expr = 75,                        // size_expr
        S_digitize_expr = 76,                    // digitize_expr
        S_logitize_expr = 77,                    // logitize_expr
        S_reduce_expr = 78,                      // reduce_expr
        S_extend_expr = 79,                      // extend_expr
        S_for_loop = 80,                         // for_loop
        S_switch_stmt = 81,                      // switch_stmt
        S_robot_cmd = 82,                        // robot_cmd
        S_function_call = 83,                    // function_call
        S_return_stmt = 84,                      // return_stmt
        S_print_stmt = 85,                       // print_stmt
        S_expr_list = 86,                        // expr_list
        S_expr = 87                              // expr
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
    /// Provide access to semantic value.
    template <typename Base>
    struct basic_symbol : Base
    {
      /// Alias to Base.
      typedef Base super_type;

      /// Default constructor.
      basic_symbol () YY_NOEXCEPT
        : value ()
      {}

#if 201103L <= YY_CPLUSPLUS
      /// Move constructor.
      basic_symbol (basic_symbol&& that)
        : Base (std::move (that))
        , value ()
      {
        switch (this->kind ())
    {
      case symbol_kind::S_program: // program
      case symbol_kind::S_function_decl: // function_decl
      case symbol_kind::S_block: // block
      case symbol_kind::S_statement: // statement
      case symbol_kind::S_assignment: // assignment
      case symbol_kind::S_var_decl: // var_decl
      case symbol_kind::S_array_access: // array_access
      case symbol_kind::S_size_expr: // size_expr
      case symbol_kind::S_digitize_expr: // digitize_expr
      case symbol_kind::S_logitize_expr: // logitize_expr
      case symbol_kind::S_reduce_expr: // reduce_expr
      case symbol_kind::S_extend_expr: // extend_expr
      case symbol_kind::S_for_loop: // for_loop
      case symbol_kind::S_switch_stmt: // switch_stmt
      case symbol_kind::S_robot_cmd: // robot_cmd
      case symbol_kind::S_function_call: // function_call
      case symbol_kind::S_return_stmt: // return_stmt
      case symbol_kind::S_print_stmt: // print_stmt
      case symbol_kind::S_expr: // expr
        value.move< ASTNode* > (std::move (that.value));
        break;

      case symbol_kind::S_BOOL: // BOOL
        value.move< BoolValue > (std::move (that.value));
        break;

      case symbol_kind::S_NUMBER: // NUMBER
        value.move< int > (std::move (that.value));
        break;

      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
        value.move< std::string > (std::move (that.value));
        break;

      case symbol_kind::S_function_list: // function_list
      case symbol_kind::S_statement_list: // statement_list
      case symbol_kind::S_dim_list: // dim_list
      case symbol_kind::S_index_list: // index_list
      case symbol_kind::S_expr_list: // expr_list
        value.move< std::vector<ASTNode*> > (std::move (that.value));
        break;

      case symbol_kind::S_param_list: // param_list
        value.move< std::vector<std::string> > (std::move (that.value));
        break;

      default:
        break;
    }

      }
#endif

      /// Copy constructor.
      basic_symbol (const basic_symbol& that);

      /// Constructors for typed symbols.
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t)
        : Base (t)
      {}
#else
      basic_symbol (typename Base::kind_type t)
        : Base (t)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, ASTNode*&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const ASTNode*& v)
        : Base (t)
        , value (v)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, BoolValue&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const BoolValue& v)
        : Base (t)
        , value (v)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, int&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const int& v)
        : Base (t)
        , value (v)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::string&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::string& v)
        : Base (t)
        , value (v)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::vector<ASTNode*>&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::vector<ASTNode*>& v)
        : Base (t)
        , value (v)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::vector<std::string>&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::vector<std::string>& v)
        : Base (t)
        , value (v)
      {}
#endif

      /// Destroy the symbol.
      ~basic_symbol ()
      {
        clear ();
      }



      /// Destroy contents, and record that is empty.
      void clear () YY_NOEXCEPT
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
      case symbol_kind::S_program: // program
      case symbol_kind::S_function_decl: // function_decl
      case symbol_kind::S_block: // block
      case symbol_kind::S_statement: // statement
      case symbol_kind::S_assignment: // assignment
      case symbol_kind::S_var_decl: // var_decl
      case symbol_kind::S_array_access: // array_access
      case symbol_kind::S_size_expr: // size_expr
      case symbol_kind::S_digitize_expr: // digitize_expr
      case symbol_kind::S_logitize_expr: // logitize_expr
      case symbol_kind::S_reduce_expr: // reduce_expr
      case symbol_kind::S_extend_expr: // extend_expr
      case symbol_kind::S_for_loop: // for_loop
      case symbol_kind::S_switch_stmt: // switch_stmt
      case symbol_kind::S_robot_cmd: // robot_cmd
      case symbol_kind::S_function_call: // function_call
      case symbol_kind::S_return_stmt: // return_stmt
      case symbol_kind::S_print_stmt: // print_stmt
      case symbol_kind::S_expr: // expr
        value.template destroy< ASTNode* > ();
        break;

      case symbol_kind::S_BOOL: // BOOL
        value.template destroy< BoolValue > ();
        break;

      case symbol_kind::S_NUMBER: // NUMBER
        value.template destroy< int > ();
        break;

      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
        value.template destroy< std::string > ();
        break;

      case symbol_kind::S_function_list: // function_list
      case symbol_kind::S_statement_list: // statement_list
      case symbol_kind::S_dim_list: // dim_list
      case symbol_kind::S_index_list: // index_list
      case symbol_kind::S_expr_list: // expr_list
        value.template destroy< std::vector<ASTNode*> > ();
        break;

      case symbol_kind::S_param_list: // param_list
        value.template destroy< std::vector<std::string> > ();
        break;

      default:
        break;
    }

        Base::clear ();
      }

      /// The user-facing name of this symbol.
      const char *name () const YY_NOEXCEPT
      {
        return parser::symbol_name (this->kind ());
      }

      /// Backward compatibility (Bison 3.6).
      symbol_kind_type type_get () const YY_NOEXCEPT;

      /// Whether empty.
      bool empty () const YY_NOEXCEPT;

      /// Destructive move, \a s is emptied into this.
      void move (basic_symbol& s);

      /// The semantic value.
      value_type value;

    private:
#if YY_CPLUSPLUS < 201103L
      /// Assignment operator.
      basic_symbol& operator= (const basic_symbol& that);
#endif
    };

    /// Type access provider for token (enum) based symbols.
    struct by_kind
    {
      /// The symbol kind as needed by the constructor.
      typedef token_kind_type kind_type;

      /// Default constructor.
      by_kind () YY_NOEXCEPT;

#if 201103L <= YY_CPLUSPLUS
      /// Move constructor.
      by_kind (by_kind&& that) YY_NOEXCEPT;
#endif

      /// Copy constructor.
      by_kind (const by_kind& that) YY_NOEXCEPT;

      /// Constructor from (external) token numbers.
      by_kind (kind_type t) YY_NOEXCEPT;



      /// Record that this symbol is empty.
      void clear () YY_NOEXCEPT;

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
      symbol_type () YY_NOEXCEPT {}

      /// Constructor for valueless symbols, and symbols from each type.
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok)
        : super_type (token_kind_type (tok))
#else
      symbol_type (int tok)
        : super_type (token_kind_type (tok))
#endif
      {}
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, BoolValue v)
        : super_type (token_kind_type (tok), std::move (v))
#else
      symbol_type (int tok, const BoolValue& v)
        : super_type (token_kind_type (tok), v)
#endif
      {}
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, int v)
        : super_type (token_kind_type (tok), std::move (v))
#else
      symbol_type (int tok, const int& v)
        : super_type (token_kind_type (tok), v)
#endif
      {}
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, std::string v)
        : super_type (token_kind_type (tok), std::move (v))
#else
      symbol_type (int tok, const std::string& v)
        : super_type (token_kind_type (tok), v)
#endif
      {}
    };

    /// Build a parser object.
    parser (Scanner &scanner_yyarg);
    virtual ~parser ();

#if 201103L <= YY_CPLUSPLUS
    /// Non copyable.
    parser (const parser&) = delete;
    /// Non copyable.
    parser& operator= (const parser&) = delete;
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
    /// \param msg    a description of the syntax error.
    virtual void error (const std::string& msg);

    /// Report a syntax error.
    void error (const syntax_error& err);

    /// The user-facing name of the symbol whose (internal) number is
    /// YYSYMBOL.  No bounds checking.
    static const char *symbol_name (symbol_kind_type yysymbol);

    // Implementation of make_symbol for each token kind.
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_YYEOF ()
      {
        return symbol_type (token::YYEOF);
      }
#else
      static
      symbol_type
      make_YYEOF ()
      {
        return symbol_type (token::YYEOF);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_YYerror ()
      {
        return symbol_type (token::YYerror);
      }
#else
      static
      symbol_type
      make_YYerror ()
      {
        return symbol_type (token::YYerror);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_YYUNDEF ()
      {
        return symbol_type (token::YYUNDEF);
      }
#else
      static
      symbol_type
      make_YYUNDEF ()
      {
        return symbol_type (token::YYUNDEF);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_VAR ()
      {
        return symbol_type (token::VAR);
      }
#else
      static
      symbol_type
      make_VAR ()
      {
        return symbol_type (token::VAR);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SIZE ()
      {
        return symbol_type (token::SIZE);
      }
#else
      static
      symbol_type
      make_SIZE ()
      {
        return symbol_type (token::SIZE);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LOGITIZE ()
      {
        return symbol_type (token::LOGITIZE);
      }
#else
      static
      symbol_type
      make_LOGITIZE ()
      {
        return symbol_type (token::LOGITIZE);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DIGITIZE ()
      {
        return symbol_type (token::DIGITIZE);
      }
#else
      static
      symbol_type
      make_DIGITIZE ()
      {
        return symbol_type (token::DIGITIZE);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_REDUCE ()
      {
        return symbol_type (token::REDUCE);
      }
#else
      static
      symbol_type
      make_REDUCE ()
      {
        return symbol_type (token::REDUCE);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_EXTEND ()
      {
        return symbol_type (token::EXTEND);
      }
#else
      static
      symbol_type
      make_EXTEND ()
      {
        return symbol_type (token::EXTEND);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_FOR ()
      {
        return symbol_type (token::FOR);
      }
#else
      static
      symbol_type
      make_FOR ()
      {
        return symbol_type (token::FOR);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_BOUNDARY ()
      {
        return symbol_type (token::BOUNDARY);
      }
#else
      static
      symbol_type
      make_BOUNDARY ()
      {
        return symbol_type (token::BOUNDARY);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_STEP ()
      {
        return symbol_type (token::STEP);
      }
#else
      static
      symbol_type
      make_STEP ()
      {
        return symbol_type (token::STEP);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SWITCH ()
      {
        return symbol_type (token::SWITCH);
      }
#else
      static
      symbol_type
      make_SWITCH ()
      {
        return symbol_type (token::SWITCH);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ELSE ()
      {
        return symbol_type (token::ELSE);
      }
#else
      static
      symbol_type
      make_ELSE ()
      {
        return symbol_type (token::ELSE);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_MOVE ()
      {
        return symbol_type (token::MOVE);
      }
#else
      static
      symbol_type
      make_MOVE ()
      {
        return symbol_type (token::MOVE);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ROTATE ()
      {
        return symbol_type (token::ROTATE);
      }
#else
      static
      symbol_type
      make_ROTATE ()
      {
        return symbol_type (token::ROTATE);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LEFT ()
      {
        return symbol_type (token::LEFT);
      }
#else
      static
      symbol_type
      make_LEFT ()
      {
        return symbol_type (token::LEFT);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_RIGHT ()
      {
        return symbol_type (token::RIGHT);
      }
#else
      static
      symbol_type
      make_RIGHT ()
      {
        return symbol_type (token::RIGHT);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_GET ()
      {
        return symbol_type (token::GET);
      }
#else
      static
      symbol_type
      make_GET ()
      {
        return symbol_type (token::GET);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ENVIRONMENT ()
      {
        return symbol_type (token::ENVIRONMENT);
      }
#else
      static
      symbol_type
      make_ENVIRONMENT ()
      {
        return symbol_type (token::ENVIRONMENT);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_AND ()
      {
        return symbol_type (token::AND);
      }
#else
      static
      symbol_type
      make_AND ()
      {
        return symbol_type (token::AND);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_OR ()
      {
        return symbol_type (token::OR);
      }
#else
      static
      symbol_type
      make_OR ()
      {
        return symbol_type (token::OR);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_NOT ()
      {
        return symbol_type (token::NOT);
      }
#else
      static
      symbol_type
      make_NOT ()
      {
        return symbol_type (token::NOT);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_PRINT ()
      {
        return symbol_type (token::PRINT);
      }
#else
      static
      symbol_type
      make_PRINT ()
      {
        return symbol_type (token::PRINT);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_PLEASE ()
      {
        return symbol_type (token::PLEASE);
      }
#else
      static
      symbol_type
      make_PLEASE ()
      {
        return symbol_type (token::PLEASE);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_THANKS ()
      {
        return symbol_type (token::THANKS);
      }
#else
      static
      symbol_type
      make_THANKS ()
      {
        return symbol_type (token::THANKS);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TASK ()
      {
        return symbol_type (token::TASK);
      }
#else
      static
      symbol_type
      make_TASK ()
      {
        return symbol_type (token::TASK);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DO ()
      {
        return symbol_type (token::DO);
      }
#else
      static
      symbol_type
      make_DO ()
      {
        return symbol_type (token::DO);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_RESULT ()
      {
        return symbol_type (token::RESULT);
      }
#else
      static
      symbol_type
      make_RESULT ()
      {
        return symbol_type (token::RESULT);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_MXTRUE ()
      {
        return symbol_type (token::MXTRUE);
      }
#else
      static
      symbol_type
      make_MXTRUE ()
      {
        return symbol_type (token::MXTRUE);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_MXFALSE ()
      {
        return symbol_type (token::MXFALSE);
      }
#else
      static
      symbol_type
      make_MXFALSE ()
      {
        return symbol_type (token::MXFALSE);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DASSIGN ()
      {
        return symbol_type (token::DASSIGN);
      }
#else
      static
      symbol_type
      make_DASSIGN ()
      {
        return symbol_type (token::DASSIGN);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_MASSIGN ()
      {
        return symbol_type (token::MASSIGN);
      }
#else
      static
      symbol_type
      make_MASSIGN ()
      {
        return symbol_type (token::MASSIGN);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_VASSIGN ()
      {
        return symbol_type (token::VASSIGN);
      }
#else
      static
      symbol_type
      make_VASSIGN ()
      {
        return symbol_type (token::VASSIGN);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_NASSIGN ()
      {
        return symbol_type (token::NASSIGN);
      }
#else
      static
      symbol_type
      make_NASSIGN ()
      {
        return symbol_type (token::NASSIGN);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_MXEQ ()
      {
        return symbol_type (token::MXEQ);
      }
#else
      static
      symbol_type
      make_MXEQ ()
      {
        return symbol_type (token::MXEQ);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_MXLT ()
      {
        return symbol_type (token::MXLT);
      }
#else
      static
      symbol_type
      make_MXLT ()
      {
        return symbol_type (token::MXLT);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_MXGT ()
      {
        return symbol_type (token::MXGT);
      }
#else
      static
      symbol_type
      make_MXGT ()
      {
        return symbol_type (token::MXGT);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_MXLTE ()
      {
        return symbol_type (token::MXLTE);
      }
#else
      static
      symbol_type
      make_MXLTE ()
      {
        return symbol_type (token::MXLTE);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_MXGTE ()
      {
        return symbol_type (token::MXGTE);
      }
#else
      static
      symbol_type
      make_MXGTE ()
      {
        return symbol_type (token::MXGTE);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ELEQ ()
      {
        return symbol_type (token::ELEQ);
      }
#else
      static
      symbol_type
      make_ELEQ ()
      {
        return symbol_type (token::ELEQ);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ELLT ()
      {
        return symbol_type (token::ELLT);
      }
#else
      static
      symbol_type
      make_ELLT ()
      {
        return symbol_type (token::ELLT);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ELGT ()
      {
        return symbol_type (token::ELGT);
      }
#else
      static
      symbol_type
      make_ELGT ()
      {
        return symbol_type (token::ELGT);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ELLTE ()
      {
        return symbol_type (token::ELLTE);
      }
#else
      static
      symbol_type
      make_ELLTE ()
      {
        return symbol_type (token::ELLTE);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ELGTE ()
      {
        return symbol_type (token::ELGTE);
      }
#else
      static
      symbol_type
      make_ELGTE ()
      {
        return symbol_type (token::ELGTE);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ASSIGN ()
      {
        return symbol_type (token::ASSIGN);
      }
#else
      static
      symbol_type
      make_ASSIGN ()
      {
        return symbol_type (token::ASSIGN);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SEMICOLON ()
      {
        return symbol_type (token::SEMICOLON);
      }
#else
      static
      symbol_type
      make_SEMICOLON ()
      {
        return symbol_type (token::SEMICOLON);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LBRACKET ()
      {
        return symbol_type (token::LBRACKET);
      }
#else
      static
      symbol_type
      make_LBRACKET ()
      {
        return symbol_type (token::LBRACKET);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_RBRACKET ()
      {
        return symbol_type (token::RBRACKET);
      }
#else
      static
      symbol_type
      make_RBRACKET ()
      {
        return symbol_type (token::RBRACKET);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LPAREN ()
      {
        return symbol_type (token::LPAREN);
      }
#else
      static
      symbol_type
      make_LPAREN ()
      {
        return symbol_type (token::LPAREN);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_RPAREN ()
      {
        return symbol_type (token::RPAREN);
      }
#else
      static
      symbol_type
      make_RPAREN ()
      {
        return symbol_type (token::RPAREN);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_COMMA ()
      {
        return symbol_type (token::COMMA);
      }
#else
      static
      symbol_type
      make_COMMA ()
      {
        return symbol_type (token::COMMA);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_PLUS ()
      {
        return symbol_type (token::PLUS);
      }
#else
      static
      symbol_type
      make_PLUS ()
      {
        return symbol_type (token::PLUS);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_MINUS ()
      {
        return symbol_type (token::MINUS);
      }
#else
      static
      symbol_type
      make_MINUS ()
      {
        return symbol_type (token::MINUS);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_MULT ()
      {
        return symbol_type (token::MULT);
      }
#else
      static
      symbol_type
      make_MULT ()
      {
        return symbol_type (token::MULT);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DIV ()
      {
        return symbol_type (token::DIV);
      }
#else
      static
      symbol_type
      make_DIV ()
      {
        return symbol_type (token::DIV);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_NUMBER (int v)
      {
        return symbol_type (token::NUMBER, std::move (v));
      }
#else
      static
      symbol_type
      make_NUMBER (const int& v)
      {
        return symbol_type (token::NUMBER, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_BOOL (BoolValue v)
      {
        return symbol_type (token::BOOL, std::move (v));
      }
#else
      static
      symbol_type
      make_BOOL (const BoolValue& v)
      {
        return symbol_type (token::BOOL, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_IDENTIFIER (std::string v)
      {
        return symbol_type (token::IDENTIFIER, std::move (v));
      }
#else
      static
      symbol_type
      make_IDENTIFIER (const std::string& v)
      {
        return symbol_type (token::IDENTIFIER, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_FINDEXIT ()
      {
        return symbol_type (token::FINDEXIT);
      }
#else
      static
      symbol_type
      make_FINDEXIT ()
      {
        return symbol_type (token::FINDEXIT);
      }
#endif


    class context
    {
    public:
      context (const parser& yyparser, const symbol_type& yyla);
      const symbol_type& lookahead () const YY_NOEXCEPT { return yyla_; }
      symbol_kind_type token () const YY_NOEXCEPT { return yyla_.kind (); }
      /// Put in YYARG at most YYARGN of the expected tokens, and return the
      /// number of tokens stored in YYARG.  If YYARG is null, return the
      /// number of expected tokens (guaranteed to be less than YYNTOKENS).
      int expected_tokens (symbol_kind_type yyarg[], int yyargn) const;

    private:
      const parser& yyparser_;
      const symbol_type& yyla_;
    };

  private:
#if YY_CPLUSPLUS < 201103L
    /// Non copyable.
    parser (const parser&);
    /// Non copyable.
    parser& operator= (const parser&);
#endif


    /// Stored state numbers (used for stacks).
    typedef unsigned char state_type;

    /// The arguments of the error message.
    int yy_syntax_error_arguments_ (const context& yyctx,
                                    symbol_kind_type yyarg[], int yyargn) const;

    /// Generate an error message.
    /// \param yyctx     the context in which the error occurred.
    virtual std::string yysyntax_error_ (const context& yyctx) const;
    /// Compute post-reduction state.
    /// \param yystate   the current state
    /// \param yysym     the nonterminal to push on the stack
    static state_type yy_lr_goto_state_ (state_type yystate, int yysym);

    /// Whether the given \c yypact_ value indicates a defaulted state.
    /// \param yyvalue   the value to check
    static bool yy_pact_value_is_default_ (int yyvalue) YY_NOEXCEPT;

    /// Whether the given \c yytable_ value indicates a syntax error.
    /// \param yyvalue   the value to check
    static bool yy_table_value_is_error_ (int yyvalue) YY_NOEXCEPT;

    static const signed char yypact_ninf_;
    static const signed char yytable_ninf_;

    /// Convert a scanner token kind \a t to a symbol kind.
    /// In theory \a t should be a token_kind_type, but character literals
    /// are valid, yet not members of the token_kind_type enum.
    static symbol_kind_type yytranslate_ (int t) YY_NOEXCEPT;



    // Tables.
    // YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
    // STATE-NUM.
    static const short yypact_[];

    // YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
    // Performed when YYTABLE does not specify something else to do.  Zero
    // means the default is an error.
    static const signed char yydefact_[];

    // YYPGOTO[NTERM-NUM].
    static const short yypgoto_[];

    // YYDEFGOTO[NTERM-NUM].
    static const signed char yydefgoto_[];

    // YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
    // positive, shift that token.  If negative, reduce the rule whose
    // number is the opposite.  If YYTABLE_NINF, syntax error.
    static const short yytable_[];

    static const short yycheck_[];

    // YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
    // state STATE-NUM.
    static const signed char yystos_[];

    // YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.
    static const signed char yyr1_[];

    // YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.
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

      stack (size_type n = 200) YY_NOEXCEPT
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
        slice (const stack& stack, index_type range) YY_NOEXCEPT
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
    void yypop_ (int n = 1) YY_NOEXCEPT;

    /// Constants.
    enum
    {
      yylast_ = 198,     ///< Last index in yytable_.
      yynnts_ = 26,  ///< Number of nonterminal symbols.
      yyfinal_ = 3 ///< Termination state number.
    };


    // User arguments.
    Scanner &scanner;

  };

  inline
  parser::symbol_kind_type
  parser::yytranslate_ (int t) YY_NOEXCEPT
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
       2,     2,     2,    60,     2,    61,     2,     2,     2,     2,
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
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59
    };
    // Last valid token kind.
    const int code_max = 314;

    if (t <= 0)
      return symbol_kind::S_YYEOF;
    else if (t <= code_max)
      return static_cast <symbol_kind_type> (translate_table[t]);
    else
      return symbol_kind::S_YYUNDEF;
  }

  // basic_symbol.
  template <typename Base>
  parser::basic_symbol<Base>::basic_symbol (const basic_symbol& that)
    : Base (that)
    , value ()
  {
    switch (this->kind ())
    {
      case symbol_kind::S_program: // program
      case symbol_kind::S_function_decl: // function_decl
      case symbol_kind::S_block: // block
      case symbol_kind::S_statement: // statement
      case symbol_kind::S_assignment: // assignment
      case symbol_kind::S_var_decl: // var_decl
      case symbol_kind::S_array_access: // array_access
      case symbol_kind::S_size_expr: // size_expr
      case symbol_kind::S_digitize_expr: // digitize_expr
      case symbol_kind::S_logitize_expr: // logitize_expr
      case symbol_kind::S_reduce_expr: // reduce_expr
      case symbol_kind::S_extend_expr: // extend_expr
      case symbol_kind::S_for_loop: // for_loop
      case symbol_kind::S_switch_stmt: // switch_stmt
      case symbol_kind::S_robot_cmd: // robot_cmd
      case symbol_kind::S_function_call: // function_call
      case symbol_kind::S_return_stmt: // return_stmt
      case symbol_kind::S_print_stmt: // print_stmt
      case symbol_kind::S_expr: // expr
        value.copy< ASTNode* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_BOOL: // BOOL
        value.copy< BoolValue > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_NUMBER: // NUMBER
        value.copy< int > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
        value.copy< std::string > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_function_list: // function_list
      case symbol_kind::S_statement_list: // statement_list
      case symbol_kind::S_dim_list: // dim_list
      case symbol_kind::S_index_list: // index_list
      case symbol_kind::S_expr_list: // expr_list
        value.copy< std::vector<ASTNode*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_param_list: // param_list
        value.copy< std::vector<std::string> > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

  }




  template <typename Base>
  parser::symbol_kind_type
  parser::basic_symbol<Base>::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }


  template <typename Base>
  bool
  parser::basic_symbol<Base>::empty () const YY_NOEXCEPT
  {
    return this->kind () == symbol_kind::S_YYEMPTY;
  }

  template <typename Base>
  void
  parser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move (s);
    switch (this->kind ())
    {
      case symbol_kind::S_program: // program
      case symbol_kind::S_function_decl: // function_decl
      case symbol_kind::S_block: // block
      case symbol_kind::S_statement: // statement
      case symbol_kind::S_assignment: // assignment
      case symbol_kind::S_var_decl: // var_decl
      case symbol_kind::S_array_access: // array_access
      case symbol_kind::S_size_expr: // size_expr
      case symbol_kind::S_digitize_expr: // digitize_expr
      case symbol_kind::S_logitize_expr: // logitize_expr
      case symbol_kind::S_reduce_expr: // reduce_expr
      case symbol_kind::S_extend_expr: // extend_expr
      case symbol_kind::S_for_loop: // for_loop
      case symbol_kind::S_switch_stmt: // switch_stmt
      case symbol_kind::S_robot_cmd: // robot_cmd
      case symbol_kind::S_function_call: // function_call
      case symbol_kind::S_return_stmt: // return_stmt
      case symbol_kind::S_print_stmt: // print_stmt
      case symbol_kind::S_expr: // expr
        value.move< ASTNode* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_BOOL: // BOOL
        value.move< BoolValue > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_NUMBER: // NUMBER
        value.move< int > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
        value.move< std::string > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_function_list: // function_list
      case symbol_kind::S_statement_list: // statement_list
      case symbol_kind::S_dim_list: // dim_list
      case symbol_kind::S_index_list: // index_list
      case symbol_kind::S_expr_list: // expr_list
        value.move< std::vector<ASTNode*> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_param_list: // param_list
        value.move< std::vector<std::string> > (YY_MOVE (s.value));
        break;

      default:
        break;
    }

  }

  // by_kind.
  inline
  parser::by_kind::by_kind () YY_NOEXCEPT
    : kind_ (symbol_kind::S_YYEMPTY)
  {}

#if 201103L <= YY_CPLUSPLUS
  inline
  parser::by_kind::by_kind (by_kind&& that) YY_NOEXCEPT
    : kind_ (that.kind_)
  {
    that.clear ();
  }
#endif

  inline
  parser::by_kind::by_kind (const by_kind& that) YY_NOEXCEPT
    : kind_ (that.kind_)
  {}

  inline
  parser::by_kind::by_kind (token_kind_type t) YY_NOEXCEPT
    : kind_ (yytranslate_ (t))
  {}



  inline
  void
  parser::by_kind::clear () YY_NOEXCEPT
  {
    kind_ = symbol_kind::S_YYEMPTY;
  }

  inline
  void
  parser::by_kind::move (by_kind& that)
  {
    kind_ = that.kind_;
    that.clear ();
  }

  inline
  parser::symbol_kind_type
  parser::by_kind::kind () const YY_NOEXCEPT
  {
    return kind_;
  }


  inline
  parser::symbol_kind_type
  parser::by_kind::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }


} // yy
#line 2529 "parser.hpp"




#endif // !YY_YY_PARSER_HPP_INCLUDED
