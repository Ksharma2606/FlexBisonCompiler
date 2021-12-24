/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "parser.y"

// check version
//Made By: Karan Sharma
//Refrence: Help from Adam Harris
//Date: 22/12/2021
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <regex.h>
#include <time.h>

#include "stack.h"
#include "symbolTable.h"
#include "AST.h"
#include "IRcode.h"
#include "MIPS.h"

extern int yylex();
extern int yyparse();
extern FILE* yyin;

// get the line and character number from the lexer file to show them in error messages 
extern int lines;
extern int chars;

void yyerror(const char* s);
int semanticCheckPassed = 1;
/* stack to keep track of the current scope */
struct stack_t* theStack = NULL;
struct stack_t* ifwhilestack = NULL;
struct stack_t* userout = NULL;
int if_counter = 1;
int while_counter = 1;
int useroutnumber = 0;

#line 107 "parser.tab.c"

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

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_PARSER_TAB_H_INCLUDED
# define YY_YY_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    ID = 258,
    BINOP = 259,
    RETURN = 260,
    READ = 261,
    WRITELN = 262,
    BREAK = 263,
    IFELSE = 264,
    IF = 265,
    ELSE = 266,
    WHILE = 267,
    VOID = 268,
    TYPE = 269,
    UNARYOP = 270,
    SEMICOLON = 271,
    STRING = 272,
    CHACHA = 273,
    COMMA = 274,
    EQ = 275,
    LCURL = 276,
    RCURL = 277,
    LBRACK = 278,
    RBRACK = 279,
    LPAREN = 280,
    RPAREN = 281,
    NUMBER = 282,
    WRITE = 283,
    INPUT = 284
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 38 "parser.y"

	int number;
	char character;
	char* string;
	struct AST* ast;

#line 196 "parser.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */



#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))

/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
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


#define YY_ASSERT(E) ((void) (0 && (E)))

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  53
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   274

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  34
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  31
/* YYNRULES -- Number of rules.  */
#define YYNRULES  81
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  136

#define YYUNDEFTOK  2
#define YYMAXUTOK   284


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,    32,    30,     2,    31,     2,    33,     2,     2,
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
      25,    26,    27,    28,    29
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    70,    70,    80,    86,    92,    93,    94,    98,   102,
     124,   176,   183,   185,   207,   206,   303,   304,   314,   335,
     371,   376,   385,   391,   397,   398,   403,   404,   413,   415,
     421,   449,   458,   465,   472,   477,   476,   751,   899,   900,
     913,   917,   921,   925,   929,  1037,  1287,  1589,  1865,  2161,
    2444,  2606,  2890,  2894,  2902,  2906,  2907,  2911,  3033,  3054,
    3058,  3150,  3154,  3163,  3257,  3261,  3271,  3276,  3285,  3289,
    3293,  3299,  3305,  3275,  3393,  3393,  3393,  3393,  3477,  3487,
    3476,  3583
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "ID", "BINOP", "RETURN", "READ",
  "WRITELN", "BREAK", "IFELSE", "IF", "ELSE", "WHILE", "VOID", "TYPE",
  "UNARYOP", "SEMICOLON", "STRING", "CHACHA", "COMMA", "EQ", "LCURL",
  "RCURL", "LBRACK", "RBRACK", "LPAREN", "RPAREN", "NUMBER", "WRITE",
  "INPUT", "'+'", "'-'", "'*'", "'/'", "$accept", "Program", "DeclList",
  "Decl", "VarDeclId", "VarDecl", "ParamDeclList", "FunDecl", "$@1",
  "ParamDeclListTail", "ParamDecl", "Block", "InnerBlockList",
  "InnerBlock", "ExprListTail", "ExprList", "Primary", "$@2", "Expr",
  "Stmt", "$@3", "$@4", "$@5", "$@6", "$@7", "$@8", "$@9", "$@10", "$@11",
  "$@12", "$@13", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
      43,    45,    42,    47
};
# endif

#define YYPACT_NINF (-18)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     144,   -11,   213,    -1,   230,    -5,   -18,   -10,   -18,    15,
     247,   -18,   -18,   -18,    17,   118,   247,   -18,   247,    16,
     -18,   144,   -18,   -18,   -18,   -18,     6,   -18,   247,   247,
     -18,    13,     1,     0,    27,   -18,    24,   -18,     8,   247,
      22,   -17,    32,    80,   -18,    47,   -18,   -18,    42,   170,
     -18,    45,    37,   -18,   -18,   247,   -18,   247,   247,   247,
     247,    80,    55,   -18,    49,   -12,    57,    56,   -18,   247,
      80,   247,    63,   -18,   -18,    58,    66,   -18,   -18,   -18,
     -18,    80,    19,    19,    87,    87,    77,   -18,   -18,    88,
     -18,   -18,    80,    70,    76,    79,   100,   247,   247,   -18,
      89,   -18,   -18,   -18,   113,    91,   -18,   101,   -18,    93,
      62,    80,   -18,   196,   196,   106,   110,   100,   -18,   247,
     196,   -18,   -18,   111,   -18,   -18,   -18,   -18,   -18,   117,
     131,   -18,   -18,   196,   -18,   -18
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       4,    30,     0,     0,     0,    66,    67,     0,    78,     0,
       0,    54,    33,    32,     0,     0,     0,    31,     0,     0,
       2,     4,     5,     6,    81,    38,    56,     7,    52,     0,
      58,    59,     0,     0,     0,    62,    64,    65,     0,     0,
       0,     8,    11,    44,    35,     0,    21,    24,     0,    23,
      25,     0,    61,     1,     3,     0,    55,     0,     0,     0,
       0,    50,     0,    57,     0,     0,     0,     0,    63,     0,
      74,     0,     0,    14,    10,     0,     8,    20,    22,    34,
      60,    45,    46,    47,    48,    49,    37,    42,    41,     0,
      40,    43,    68,     0,     0,     0,    13,    29,    53,    39,
       0,    75,    79,     9,     0,     0,    12,    16,    28,     0,
      26,    51,    69,     0,     0,    18,     0,     0,    36,     0,
       0,    76,    80,     0,    15,    17,    27,    70,    77,     0,
       0,    19,    71,     0,    72,    73
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -18,   -18,   123,   -18,   -18,   -14,   -18,   -18,   -18,    31,
     -18,    39,   108,   -18,    48,   -18,   -18,   -18,     3,   -15,
     -18,   -18,   -18,   -18,   -18,   -18,   -18,   -18,   -18,   -18,
     -18
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    19,    20,    21,    42,    22,   105,    23,    96,   106,
     107,    24,    48,    49,   108,   109,    25,    75,    26,    27,
      38,   100,   120,   130,   133,   135,    93,   113,   128,    40,
     114
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      50,    47,    32,    65,    88,    31,    72,    36,    73,    28,
      55,    37,    29,    43,    89,    39,    53,    55,    41,    51,
      44,    52,    56,    55,    33,    34,    66,    64,    55,    63,
      67,    61,    62,    69,    50,    47,    57,    58,    59,    60,
      68,    55,    70,    57,    58,    59,    60,    71,    74,    55,
      76,    59,    60,    80,    57,    58,    59,    60,    81,    55,
      82,    83,    84,    85,    77,    87,    55,    57,    58,    59,
      60,    79,    92,    90,    94,    57,    58,    59,    60,    86,
      55,   119,    91,    97,    55,    57,    58,    59,    60,    72,
      95,    55,    57,    58,    59,    60,   101,    98,   121,   122,
     110,   111,   102,   103,    99,   127,    57,    58,    59,    60,
      57,    58,    59,    60,   104,   112,   115,   116,   134,   118,
     117,     1,   110,     2,     3,     4,     5,     6,     7,   123,
       8,    15,    45,    10,    11,    12,    13,    14,   129,    15,
      46,   131,   132,    16,    54,    17,    18,     1,   125,     2,
       3,     4,     5,     6,     7,   124,     8,    78,     9,    10,
      11,    12,    13,    14,     0,    15,     0,   126,     0,    16,
       0,    17,    18,     1,     0,     2,     3,     4,     5,     6,
       7,     0,     8,     0,    45,    10,    11,    12,    13,    14,
       0,    15,     0,     0,     0,    16,     0,    17,    18,     1,
       0,     2,     3,     4,     5,     6,     7,     0,     8,     0,
       0,    10,    11,    12,    13,    14,     1,    15,     0,     3,
       0,    16,     0,    17,    18,     0,     0,     0,    10,    30,
      12,    13,    14,     1,     0,     0,     3,     0,    16,     0,
      17,     0,     0,     0,     0,    10,    35,    12,    13,    14,
       1,     0,     0,     3,     0,    16,     0,    17,     0,     0,
       0,     0,    10,     0,    12,    13,    14,     0,     0,     0,
       0,     0,    16,     0,    17
};

static const yytype_int16 yycheck[] =
{
      15,    15,     3,     3,    16,     2,    23,     4,    25,    20,
       4,    16,    23,    10,    26,    25,     0,     4,     3,    16,
       3,    18,    16,     4,    25,    26,    26,    26,     4,    16,
       3,    28,    29,    25,    49,    49,    30,    31,    32,    33,
      16,     4,    39,    30,    31,    32,    33,    25,    16,     4,
       3,    32,    33,    16,    30,    31,    32,    33,    55,     4,
      57,    58,    59,    60,    22,    16,     4,    30,    31,    32,
      33,    26,    69,    16,    71,    30,    31,    32,    33,    24,
       4,    19,    26,    25,     4,    30,    31,    32,    33,    23,
      27,     4,    30,    31,    32,    33,    26,    20,   113,   114,
      97,    98,    26,    24,    16,   120,    30,    31,    32,    33,
      30,    31,    32,    33,    14,    26,     3,    26,   133,    26,
      19,     3,   119,     5,     6,     7,     8,     9,    10,    23,
      12,    21,    14,    15,    16,    17,    18,    19,    27,    21,
      22,    24,    11,    25,    21,    27,    28,     3,   117,     5,
       6,     7,     8,     9,    10,   116,    12,    49,    14,    15,
      16,    17,    18,    19,    -1,    21,    -1,   119,    -1,    25,
      -1,    27,    28,     3,    -1,     5,     6,     7,     8,     9,
      10,    -1,    12,    -1,    14,    15,    16,    17,    18,    19,
      -1,    21,    -1,    -1,    -1,    25,    -1,    27,    28,     3,
      -1,     5,     6,     7,     8,     9,    10,    -1,    12,    -1,
      -1,    15,    16,    17,    18,    19,     3,    21,    -1,     6,
      -1,    25,    -1,    27,    28,    -1,    -1,    -1,    15,    16,
      17,    18,    19,     3,    -1,    -1,     6,    -1,    25,    -1,
      27,    -1,    -1,    -1,    -1,    15,    16,    17,    18,    19,
       3,    -1,    -1,     6,    -1,    25,    -1,    27,    -1,    -1,
      -1,    -1,    15,    -1,    17,    18,    19,    -1,    -1,    -1,
      -1,    -1,    25,    -1,    27
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     5,     6,     7,     8,     9,    10,    12,    14,
      15,    16,    17,    18,    19,    21,    25,    27,    28,    35,
      36,    37,    39,    41,    45,    50,    52,    53,    20,    23,
      16,    52,     3,    25,    26,    16,    52,    16,    54,    25,
      63,     3,    38,    52,     3,    14,    22,    39,    46,    47,
      53,    52,    52,     0,    36,     4,    16,    30,    31,    32,
      33,    52,    52,    16,    26,     3,    26,     3,    16,    25,
      52,    25,    23,    25,    16,    51,     3,    22,    46,    26,
      16,    52,    52,    52,    52,    52,    24,    16,    16,    26,
      16,    26,    52,    60,    52,    27,    42,    25,    20,    16,
      55,    26,    26,    24,    14,    40,    43,    44,    48,    49,
      52,    52,    26,    61,    64,     3,    26,    19,    26,    19,
      56,    53,    53,    23,    45,    43,    48,    53,    62,    27,
      57,    24,    11,    58,    53,    59
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    34,    35,    36,    36,    37,    37,    37,    38,    38,
      39,    39,    40,    40,    42,    41,    43,    43,    44,    44,
      45,    45,    46,    46,    47,    47,    48,    48,    49,    49,
      50,    50,    50,    50,    50,    51,    50,    50,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    53,    53,    53,    53,    53,    53,
      53,    53,    53,    53,    53,    53,    53,    54,    55,    56,
      57,    58,    59,    53,    60,    61,    62,    53,    63,    64,
      53,    53
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     0,     1,     1,     1,     1,     4,
       3,     2,     1,     0,     0,     7,     1,     3,     2,     5,
       3,     2,     2,     0,     1,     1,     1,     3,     1,     0,
       1,     1,     1,     1,     3,     0,     6,     4,     1,     5,
       4,     4,     4,     4,     2,     3,     3,     3,     3,     3,
       3,     6,     2,     5,     1,     2,     1,     3,     2,     2,
       3,     2,     2,     3,     2,     2,     1,     0,     0,     0,
       0,     0,     0,    13,     0,     0,     0,     8,     0,     0,
       7,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  switch (yytype)
    {
    case 3: /* ID  */
#line 52 "parser.y"
         { fprintf(yyoutput, "%s", ((*yyvaluep).string)); }
#line 889 "parser.tab.c"
        break;

    case 27: /* NUMBER  */
#line 53 "parser.y"
         { fprintf(yyoutput, "%d", ((*yyvaluep).number)); }
#line 895 "parser.tab.c"
        break;

      default:
        break;
    }
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
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
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYPTRDIFF_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
# undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2:
#line 71 "parser.y"
                                        { 
						/* start the AST */
						printf("\n--- Abstract Syntax Tree ---\n\n");
						makeAST((yyvsp[0].ast), 0);
						printAST();
					}
#line 1516 "parser.tab.c"
    break;

  case 3:
#line 81 "parser.y"
                                        {
						(yyval.ast) = (yyvsp[-1].ast);
						(yyval.ast)->mid = (yyvsp[0].ast);
					}
#line 1525 "parser.tab.c"
    break;

  case 4:
#line 86 "parser.y"
                                        {
						(yyval.ast) = AST_node("");
					}
#line 1533 "parser.tab.c"
    break;

  case 8:
#line 99 "parser.y"
                                                {
							printf("RECOGNIZED RULE: Variable declaration || %s || Line: %d || Char: %d\n", (yyvsp[0].string), lines, chars);
						}
#line 1541 "parser.tab.c"
    break;

  case 9:
#line 103 "parser.y"
                                                {
							printf("RECOGNIZED RULE: Array declaration || %s || Line: %d || Char: %d\n", (yyvsp[-3].string), lines, chars);
							/* create ast node for array declaration */
							char str[1000];
							sprintf(str, "%d", (yyvsp[-1].number));
							(yyval.ast) = AST_node("ARR");
							(yyval.ast)->left = AST_node((yyvsp[-3].string));
							(yyval.ast)->right = AST_node(str);
							/* check if array is declared with length of 0 */
							if ((yyvsp[-1].number) < 1){
								printf("SEMANTIC ERROR: %s array has length that is smaller than one || Line: %d || Char: %d\n", (yyvsp[-3].string) , lines, chars);
							}
						}
#line 1559 "parser.tab.c"
    break;

  case 10:
#line 125 "parser.y"
                                        {
						/* create node for variable declaration*/
						(yyval.ast) = AST_node("TYPE");
						(yyval.ast)->left = AST_node((yyvsp[-2].string));
						(yyval.ast)->right = (yyvsp[-1].ast);

						// Symbol Table
						symTabAccess();
						/* check if variable is already declared in the same scope */
						int inSymTab;

						if (strcmp((yyvsp[-1].ast)->nodeType, "ARR") == 0)
						{
							inSymTab = found((yyvsp[-1].ast)->left->nodeType, top(theStack));
						}
						else{
							inSymTab = found((yyvsp[-1].ast)->nodeType, top(theStack));
						}

						if (strcmp((yyvsp[-1].ast)->nodeType, "ARR") == 0)
						{
							printf("looking for %s in symtab - found: %d \n", (yyvsp[-1].ast)->left->nodeType, inSymTab);
						}
						else{
							printf("looking for %s in symtab - found: %d \n", (yyvsp[-1].ast)->nodeType, inSymTab);
						}
						/* if variable has been declared, add them to the symbol table now */
						if (inSymTab == 0) 
						{
							if (strcmp((yyvsp[-1].ast)->nodeType, "ARR") == 0){

								addItem((yyvsp[-1].ast)->left->nodeType, "Var", (yyvsp[-2].string), (yyvsp[-1].ast)->right->nodeType, top(theStack), "", "");
							}
							else {
								addItem((yyvsp[-1].ast)->nodeType, "Var", (yyvsp[-2].string), "", top(theStack), "", "");
							}
						}
						/* if the vairiable has been declared, print SEMANTIC ERROR */
						else
						{
							if (strcmp((yyvsp[-1].ast)->nodeType, "ARR") == 0)
							{
								printf("SEMANTIC ERROR: Var %s is already in the symbol table || Line: %d || Char: %d\n", (yyvsp[-1].ast)->left->nodeType, lines, chars);
							}
							else{					
								printf("SEMANTIC ERROR: Var %s is already in the symbol table || Line: %d || Char: %d\n", (yyvsp[-1].ast)->nodeType, lines, chars);
							}
						}
						/* show symbol table */
						showSymTable();
					}
#line 1615 "parser.tab.c"
    break;

  case 11:
#line 177 "parser.y"
                                        {
						printf("SYNTAX ERROR: Missing SEMICOLON || Line: %d || Char: %d\n", lines, chars);
					}
#line 1623 "parser.tab.c"
    break;

  case 13:
#line 185 "parser.y"
                                                                {
									(yyval.ast) = AST_node("EMPTY PARAM");
								}
#line 1631 "parser.tab.c"
    break;

  case 14:
#line 207 "parser.y"
                                        {						
						// Symbol Table
						symTabAccess();
						/* check if function has been declared before */
						int inSymTab = found((yyvsp[-1].string), top(theStack));
						printf("looking for %s in symtab - found: %d \n", (yyvsp[-1].string), inSymTab);
						/* if function has not been declared */
						if (inSymTab == 0) 
						{
							/* add to symbol table */
							addItem((yyvsp[-1].string), "Func", (yyvsp[-2].string), "",top(theStack), "", "");
						}
						/* if function has been declared */
						else{
							/* print error message */
							printf("SEMANTIC ERROR: Var %s is already in the symbol table || Line: %d || Char: %d\n", (yyvsp[-1].string), lines, chars);
						}
						/* print symbol table */
						showSymTable();
						/* change the current scope */
						push(theStack, (yyvsp[-1].string));

						// IR code
						// Sum:
						char* line;
						char line1[500] = "";
						strcat(line1, (yyvsp[-1].string));
						strcat(line1, ":");
						line = line1;
						writeIR(line1);

						// MIPS code
						fprintf(MIPS, "%s", (yyvsp[-1].string));
						fprintf(MIPS, ":\n");
						if (strcmp((yyvsp[-1].string), "main") != 0)
						{
							fprintf(MIPS, "addi $sp, $sp, -4\n");
							fprintf(MIPS, "sw $ra, 0($sp)\n");
						} else{
							emitStartTimer();
						}
					}
#line 1678 "parser.tab.c"
    break;

  case 15:
#line 250 "parser.y"
                                        {
						/* after the program finished parsing the function, we go back global scope*/
						printf("RECOGNIZED RULE: Function declaration || %s || Line: %d || Char: %d\n", (yyvsp[-5].string), lines, chars);
						/* create ast node for function */
						(yyval.ast) = AST_node("FUNC");
						(yyval.ast)->left = AST_node((yyvsp[-6].string));
						(yyval.ast)->right = AST_node((yyvsp[-5].string));
						(yyval.ast)->right->left = AST_node("PARAM");
						(yyval.ast)->right->left->left = (yyvsp[-2].ast);
						(yyval.ast)->right->right = AST_node("BLOCK");
						(yyval.ast)->right->right->left = (yyvsp[0].ast);

						// IR code
						// jr $ra
						// .end Sum
						char* line;
						char line1[500] = "";
						strcat(line1, "jr $ra");
						line = line1;
						writeIR(line1);
						char line2[500] = "";
						strcat(line2, ".end ");
						strcat(line2, (yyvsp[-5].string));
						line = line2;
						writeIR(line2);
						
						// MIPS code
						if (strcmp(top(theStack), "main") != 0){
							fprintf(MIPS, ".end %s\n", top(theStack));
						}
						pop(theStack);
						if_counter = 0;
						while_counter = 0;
					}
#line 1717 "parser.tab.c"
    break;

  case 17:
#line 305 "parser.y"
                                                                                {
											/* create node for parameters */
											(yyval.ast) = AST_node("COMMA");
											(yyval.ast)->left = (yyvsp[-2].ast);
											(yyval.ast)->right = (yyvsp[0].ast);
										}
#line 1728 "parser.tab.c"
    break;

  case 18:
#line 315 "parser.y"
                                                {
							printf("RECOGNIZED RULE: Parameter declaration || %s || Line: %d || Char: %d\n", (yyvsp[0].string), lines, chars);
							(yyval.ast) = AST_node("TYPE");
							(yyval.ast)->left = AST_node((yyvsp[-1].string));
							(yyval.ast)->right = AST_node((yyvsp[0].string));
							// Symbol Table
							symTabAccess();
							/* check if varible has been declared */
							int inSymTab = found((yyvsp[0].string), top(theStack));
							printf("looking for %s in symtab - found: %d \n", (yyvsp[0].string), inSymTab);
							/* if variable hasn't been declared, add them to symbol table */
							if (inSymTab == 0) 
							{
								addItem((yyvsp[0].string), "Var", (yyvsp[-1].string), "", top(theStack), top(theStack),"");
							}
							/* if variable has been declared, print error message*/
							else
								printf("SEMANTIC ERROR: Var %s is already in the symbol table || Line: %d || Char: %d", (yyvsp[0].string), lines, chars);
							showSymTable();
						}
#line 1753 "parser.tab.c"
    break;

  case 19:
#line 336 "parser.y"
                                                {
							/* ast node to array parameter varibles*/
							printf("RECOGNIZED RULE: Parameter array declaration || %s || Line: %d || Char: %d\n", (yyvsp[-3].string), lines, chars);
							(yyval.ast) = AST_node("TYPE");
							(yyval.ast)->left = AST_node((yyvsp[-4].string));
							(yyval.ast)->right = AST_node("ARR");
							(yyval.ast)->right->left = AST_node((yyvsp[-3].string));

							
							// Symbol Table
							symTabAccess();
							/* check if varible has been declared */
							int inSymTab = found((yyvsp[-3].string), top(theStack));
							printf("looking for %s in symtab - found: %d \n", (yyvsp[-3].string), inSymTab);
							/* if variable hasn't been declared, add them to symbol table */
							if (inSymTab == 0) 
							{
								char str[1000];
								sprintf(str, "%d", (yyvsp[-1].number));
								addItem((yyvsp[-3].string), "Var", (yyvsp[-4].string), str, top(theStack), top(theStack),"");
							}
							/* if variable has been declared, print error message*/
							else
								printf("SEMANTIC ERROR: Var %s is already in the symbol table || Line: %d || Char: %d", (yyvsp[-3].string), lines, chars);
							showSymTable();
						}
#line 1784 "parser.tab.c"
    break;

  case 20:
#line 372 "parser.y"
                                {
					printf("RECOGNIZED RULE: Block || Line: %d || Char: %d\n", lines, chars);
					(yyval.ast) = (yyvsp[-1].ast);
				}
#line 1793 "parser.tab.c"
    break;

  case 21:
#line 377 "parser.y"
                                {
					printf("SYNTAX ERROR: Empty Block || Line: %d || Char: %d\n", lines, chars);
					(yyval.ast) = AST_node("");
				}
#line 1802 "parser.tab.c"
    break;

  case 22:
#line 386 "parser.y"
                                                                {
									(yyval.ast) = (yyvsp[-1].ast);
									(yyval.ast)->mid = (yyvsp[0].ast);
								}
#line 1811 "parser.tab.c"
    break;

  case 23:
#line 391 "parser.y"
                                                                {
									(yyval.ast) = AST_node("");
								}
#line 1819 "parser.tab.c"
    break;

  case 27:
#line 405 "parser.y"
                                                        {
								(yyval.ast) = AST_node("COMMA");
								(yyval.ast)->left = (yyvsp[-2].ast);
								(yyval.ast)->right = (yyvsp[0].ast);
							}
#line 1829 "parser.tab.c"
    break;

  case 29:
#line 415 "parser.y"
                                {
					(yyval.ast) = AST_node("EMPTY PARAM");
				}
#line 1837 "parser.tab.c"
    break;

  case 30:
#line 422 "parser.y"
                                        {
						/* create ats node for ID */
						(yyval.ast) = AST_node((yyvsp[0].string));

						// Symbol Table
						symTabAccess();
						/* check if id has been declared */
						int inSymTab = 0;
						struct stack_entry *entry; 
						/* if id has not been declared in the current scope, search in the previous scope */
						entry = theStack->head;
						while (entry != NULL){
							inSymTab = found((yyvsp[0].string), entry->data);
							if (inSymTab != 0){
								break;
							}
							entry = entry->next;
						}
						printf("looking for %s in symtab - found: %d \n", (yyvsp[0].string), inSymTab);
						/* if variable has not been declared */
						if (inSymTab == 0) 
						{
							printf("SEMANTIC ERROR: Varible %s was not declared || Line: %d || Char: %d\n", (yyvsp[0].string), lines, chars);
						}		
						/* IR code generation */
						strcpy((yyval.ast)->IRcode, (yyvsp[0].string));
					}
#line 1869 "parser.tab.c"
    break;

  case 31:
#line 450 "parser.y"
                                        {
						/* node for number */
						char str[1000];
						sprintf(str, "%d", (yyvsp[0].number));
						(yyval.ast) = AST_node(str);
						/* IR code generation */
						strcpy((yyval.ast)->IRcode, str);
					}
#line 1882 "parser.tab.c"
    break;

  case 32:
#line 459 "parser.y"
                                        {
						/* node for character */
						(yyval.ast) = AST_node((yyvsp[0].string));	
						/* IR code generation */
						strcpy((yyval.ast)->IRcode, (yyvsp[0].string));
					}
#line 1893 "parser.tab.c"
    break;

  case 33:
#line 466 "parser.y"
                                        {
						/* node for string */
						(yyval.ast) = AST_node((yyvsp[0].string));
						/* IR code generation */
						strcpy((yyval.ast)->IRcode, (yyvsp[0].string));
					}
#line 1904 "parser.tab.c"
    break;

  case 34:
#line 473 "parser.y"
                                        {
						(yyval.ast) = (yyvsp[-1].ast);
					}
#line 1912 "parser.tab.c"
    break;

  case 35:
#line 477 "parser.y"
                                        {
						// MIPS code
						// push parameter onto the stack
						// loops throught all row in our table, looking for matching scope
						
						for(int i=0; i<symTabIndex; i++){
							char *ret;
							ret = strstr(symTabItems[i].scope,(yyvsp[0].string));
							if( ret ){
								char *reg = getRegister();
								// #start func call add, push onto stack
								// lw $t0, addhehe_f
								// addiu $sp, $sp, -4                      #move stack pointer
								// sw $t0, 0($sp)                          #save to stack
								fprintf(MIPS, "lw %s, %s_%s\naddiu $sp, $sp, -4\nsw %s, 0($sp)\n",reg, symTabItems[i].scope, symTabItems[i].itemName, reg);
								freeReg(reg);
							}
						}
					}
#line 1936 "parser.tab.c"
    break;

  case 36:
#line 497 "parser.y"
                                        {
						/* node for function call */
						(yyval.ast) = AST_node((yyvsp[-4].string));
						(yyval.ast)->left = (yyvsp[-1].ast);
						(yyval.ast)->right = AST_node("");
				
						// Symbol Table
						symTabAccess();
						/* check if function has been declared */
						int inSymTab = found((yyvsp[-4].string), "global");
						printf("looking for %s in symtab - found: %d \n", (yyvsp[-4].string), inSymTab);
						/* if function has not been declared, print error message */
						if (inSymTab == 0) 
						{
							printf("SEMANTIC ERROR: : Varible %s was not declared || Line: %d || Char: %d\n", (yyvsp[-4].string), lines, chars);
						}
						/* get number of parameter in funciton */
						int numOfVar = numberOfVarInParameter((yyvsp[-4].string));
						/* to check how many variable that user passed into the function call */
						struct AST* holder = (yyvsp[-1].ast);
						// check if type is void
						if (strcmp(getType((yyvsp[-4].string), theStack), "void") == 0){
							printf("SEMANTIC ERROR: function call is used as an expression, the function must return a result || Line: %d || Char: %d\n", lines, chars);
						}

						// if function call has no varible in the parameter but function requires at least one 
						// if function requires just one varible in the parameter but the function call has more than 1 variable
						// if function requires no variable in the parameter but the function call has at least 1 variable
						// if function requires at least 2 in the parameter but the function call has less than 2 variables
						if ((numOfVar == 1 && strcmp(holder->nodeType, "COMMA") == 0) || (numOfVar == 0 && strcmp((yyvsp[-1].ast)->nodeType, "EMPTY PARAM") != 0 || (numOfVar > 1 && strcmp(holder->nodeType, "COMMA") != 0))){
							printf("SEMANTIC ERROR: Parameter size for function %s is incorrect, expected %d variables || Line: %d || Char: %d\n", (yyvsp[-4].string), numberOfVarInParameter((yyvsp[-4].string)), lines, chars);
						}
						/* if user did not pass any variable and function is not a void function */
						else if (strcmp((yyvsp[-1].ast)->nodeType, "EMPTY PARAM") == 0){
							if (numOfVar != 0){
								printf("SEMANTIC ERROR: Parameter size for function %s is incorrect, expected %d variables || Line: %d || Char: %d\n", (yyvsp[-4].string), numberOfVarInParameter((yyvsp[-4].string)), lines, chars);
							}
						}
						/* if function needs one variable in the parameter and function call has one variable in the parameter also */
						else if (strcmp(holder->nodeType, "COMMA") != 0 && strcmp(holder->nodeType, "EMPTY PARAM") != 0 && numOfVar == 1){
							char** funcPara = getVarInPara((yyvsp[-4].string));
							/* check if the type is correct */
							if (strcmp(funcPara[0], getType((yyvsp[-1].ast)->nodeType, theStack)) != 0){
								printf("SEMANTIC ERROR: Function call with incorrect argument type || Line: %d || Char: %d\n", lines, chars);
							}
						}
						else{
							struct AST* holder = (yyvsp[-1].ast);
							int index = 0;
							char** funcPara = getVarInPara((yyvsp[-4].string));		
							/* get type in an array */
							/* check with type of function parameters */
							while (holder != NULL){					
								// check if variable is declared
								int inSymTab = 0;
								struct stack_entry *entry = malloc(sizeof *entry); 
								entry = theStack->head;
								while (entry != NULL){
									inSymTab = found(holder->left->nodeType, entry->data);
									if (inSymTab != 0){
										break;
									}
									if (strcmp(holder->right->nodeType, "COMMA") != 0){
										inSymTab = found(holder->left->nodeType, entry->data);
										if (inSymTab != 0){
											break;
										}
									}
									entry = entry->next;
								}
								// check if variable type is matched
								if (inSymTab == 1){			
									if (strcmp(funcPara[index], getType(holder->left->nodeType, theStack)) != 0){
										printf("SEMANTIC ERROR: Function call with incorrect argument type. Function asks for %s at index %d, function call uses %s %s || Line: %d || Char: %d\n", funcPara[index], index, getType(holder->left->nodeType, theStack), holder->left->nodeType, lines, chars);
										break;
									}
									index += 1;
									if (strcmp(holder->right->nodeType, "COMMA") == 0){
										holder = holder->right;
									}
									else{
										if (strcmp(funcPara[index], getType(holder->right->nodeType, theStack)) != 0){
											printf("SEMANTIC ERROR: Function call with incorrect argument type. Function asks for %s at index %d, function call uses %s %s || Line: %d || Char: %d\n", funcPara[index], index, getType(holder->right->nodeType, theStack),holder->right->nodeType, lines, chars);
										}
										if (index+1 != numberOfVarInParameter((yyvsp[-4].string))){
											printf("SEMANTIC ERROR: Parameter size for function %s is incorrect, expected %d variables || Line: %d || Char: %d\n", (yyvsp[-4].string), numberOfVarInParameter((yyvsp[-4].string)), lines, chars);
										}
										break;
									}
								}				
								else{
									break;
								}				
							}
						}

						showSymTable();
						

						// IR code
						int currentA = 0;
						if (strcmp(holder->nodeType, "COMMA") != 0 && strcmp(holder->nodeType, "EMPTY PARAM") != 0){
							// lw $a0, A
							char* line;
							char line1[500] = "";
							strcat(line1, "lw ");
							strcat(line1, "$a");
							char str[1000];
							sprintf(str, "%d", currentA);
							strcat(line1, str);
							strcat(line1, ", ");
							strcat(line1, holder->IRcode);
							line = line1;
							writeIR(line1);

							// MIPS code
							char * reg = getRegister();
							// la $a0, addhehe_f   
					
							char** funcParaName = getVarNameInPara((yyvsp[-4].string));
							fprintf(MIPS, "la $a0, %s_%s\n", (yyvsp[-4].string), funcParaName[currentA]);  
							
							if (strcmp(getExprType(holder->IRcode), "id") == 0){
          			// lw $t0, main_b                              #load variable(s) for use	
								char* scope = getScope(holder->IRcode, theStack);
								fprintf(MIPS, "lw %s, %s_%s\n", reg, scope, holder->IRcode);
							}
							else if (strcmp(getExprType(holder->IRcode), "int") == 0){
								// li $t0, 2
								fprintf(MIPS, "li %s, %s\n", reg, holder->IRcode);    
							}
							else{
								freeReg(reg);
								reg = holder->IRcode;			
							}
							// move $a1, $t0                               #set new value
    		      // sw $a1, 0($a0)        
							fprintf(MIPS, "move $a1, %s\nsw $a1, 0($a0)\n", reg);
							freeReg(reg);
						}
						else if (strcmp((yyvsp[-1].ast)->nodeType, "EMPTY PARAM") != 0){
							while (holder != NULL){					
								// lw $a0, A
								char* line;
								char line1[500] = "";
								strcat(line1, "lw ");
								strcat(line1, "$a");
								char str[1000];
								sprintf(str, "%d", currentA);
								strcat(line1, str);
								strcat(line1, ", ");
								strcat(line1, holder->left->IRcode);
								line = line1;
								writeIR(line1);

								// MIPS code
								char * reg = getRegister();
								// la $a0, addhehe_f   
								char** funcParaName = getVarNameInPara((yyvsp[-4].string));
								fprintf(MIPS, "la $a0, %s_%s\n", (yyvsp[-4].string), funcParaName[currentA]);  
		
								if (strcmp(getExprType(holder->left->IRcode), "id") == 0){
									// lw $t0, main_b                              #load variable(s) for use	
									char* scope = getScope(holder->left->IRcode, theStack);
									fprintf(MIPS, "lw %s, %s_%s\n", reg, scope, holder->left->IRcode);
								}
								else if (strcmp(getExprType(holder->left->IRcode), "int") == 0){
									// li $t0, 2
									fprintf(MIPS, "li %s, %s\n", reg, holder->left->IRcode);    
								}
								else{
									freeReg(reg);
									reg = holder->left->IRcode;			
								}
								// move $a1, $t0                               #set new value
								// sw $a1, 0($a0)        
								fprintf(MIPS, "move $a1, %s\nsw $a1, 0($a0)\n", reg);
								freeReg(reg);
								currentA += 1;
								if (strcmp(holder->right->nodeType, "COMMA") == 0){
									holder = holder->right;
								}
								else{
									// lw $a0, A
									char* line;
									char line1[500] = "";
									strcat(line1, "lw ");
									strcat(line1, "$a");
									char str[1000];
									sprintf(str, "%d", currentA);
									strcat(line1, str);
									strcat(line1, ", ");
									strcat(line1, holder->right->IRcode);
									line = line1;
									writeIR(line1);
									// MIPS code
									char * reg = getRegister();
									// la $a0, addhehe_f   
									char** funcParaName = getVarNameInPara((yyvsp[-4].string));
									fprintf(MIPS, "la $a0, %s_%s\n", (yyvsp[-4].string), funcParaName[currentA]);  
									if (strcmp(getExprType(holder->right->IRcode), "id") == 0){
										// lw $t0, main_b                              #load variable(s) for use	
										char* scope = getScope(holder->right->IRcode, theStack);
										fprintf(MIPS, "lw %s, %s_%s\n", reg, scope, holder->right->IRcode);
									}
									else if (strcmp(getExprType(holder->right->IRcode), "int") == 0){
										// li $t0, 2
										fprintf(MIPS, "li %s, %s\n", reg, holder->right->IRcode);    
									}
									else{
										freeReg(reg);
										reg = holder->right->IRcode;			
									}
									// move $a1, $t0                               #set new value
									// sw $a1, 0($a0)        
									fprintf(MIPS, "move $a1, %s\nsw $a1, 0($a0)\n", reg);
									freeReg(reg);
									currentA += 1;
									break;
								}		
							}
						}
						// IR
						// jal Sum
						char* line;
						char line1[500] = "";
						strcat(line1, "jal ");
						strcat(line1, (yyvsp[-4].string));
						line = line1;
						writeIR(line1);
						
						
						// MIPS
						//  jal addhehe                           #call function
						fprintf(MIPS, "jal %s\n", (yyvsp[-4].string));

						// pop parameter onto the stack
						// loops throught all row in our table, looking for matching scope
						for(int i=symTabIndex-1; i>=0; i--){
							char *ret;
							ret = strstr(symTabItems[i].scope,(yyvsp[-4].string));
							if( ret ){
								char * reg = getRegister();
								// lw $t0, 0($sp)                              #store in register
								// addiu $sp, $sp, 4                           #move stack pointer
								// la $a0, addhehe_f                           #access address
								// move $a1, $t0                               #set new value
								// sw $a1, 0($a0)  
								fprintf(MIPS, "lw %s, 0($sp)\naddiu $sp, $sp, 4\nla $a0, %s_%s\nmove $a1, %s\nsw $a1, 0($a0)\n", reg, symTabItems[i].scope, symTabItems[i].itemName, reg);
								freeReg(reg);
							}
						}
						strcpy((yyval.ast)->IRcode, "$v0");
					}
#line 2195 "parser.tab.c"
    break;

  case 37:
#line 752 "parser.y"
                                        {
						/* node for array element */
						(yyval.ast) = AST_node("ARR");
						(yyval.ast)->left = AST_node((yyvsp[-3].string));
						(yyval.ast)->right = (yyvsp[-1].ast);
						/* if variable is not an array */
						if (!isArray((yyvsp[-3].string), theStack)){
							printf("SEMANTIC ERROR: Variable must be an array variable || Line: %d || Char: %d\n", lines, chars);
						}

						/* check if $3 is an int */
						char exprType[50]; 
						/* get type for binop expression */
						if ((strcmp((yyvsp[-1].ast)->nodeType, "!") == 0) || (strcmp((yyvsp[-1].ast)->nodeType, "==") == 0) || (strcmp((yyvsp[-1].ast)->nodeType, "!=") == 0) || (strcmp((yyvsp[-1].ast)->nodeType, "<=") == 0) || (strcmp((yyvsp[-1].ast)->nodeType, ">=") == 0) || (strcmp((yyvsp[-1].ast)->nodeType, "&&") == 0) || (strcmp((yyvsp[-1].ast)->nodeType, "||") == 0) || (strcmp((yyvsp[-1].ast)->nodeType, "<") == 0) || (strcmp((yyvsp[-1].ast)->nodeType, ">") == 0)){
							strcpy(exprType, "bool");
						}
						else if ((strcmp((yyvsp[-1].ast)->nodeType, "+") == 0) || (strcmp((yyvsp[-1].ast)->nodeType, "-") == 0) || (strcmp((yyvsp[-1].ast)->nodeType, "*") == 0) || (strcmp((yyvsp[-1].ast)->nodeType, "/") == 0)){
							strcpy(exprType, "int");
						}
						/* get type for array */
						else if ((strcmp((yyvsp[-1].ast)->nodeType, "ARR") == 0)){			
							strcpy(exprType, getTypeForArr((yyvsp[-1].ast)->left->nodeType, theStack));				
						}
						else{
							/* get type for id */
							regex_t reg;
							const char *regex="^[A-Za-z][A-Za-z0-9]*";
							int ret;
							char err[1024];
							ret = regcomp(&reg, regex, REG_EXTENDED);
							if (ret != 0) {
								regerror(ret, &reg, err, 1024);
								return 1;
							}
							int return_value;
							return_value = regexec(&reg, (yyvsp[-1].ast)->nodeType , 0, NULL, 0);
							regfree(&reg);
							if (return_value == 0){
								strcpy(exprType, getType((yyvsp[-1].ast)->nodeType, theStack));
							}
							else{
								/* get type for number */
								regex_t reg;
								const char *regex="^-?[0-9]+";
								int ret;
								char err[1024];
								//Read data into variable filecontent
								ret = regcomp(&reg, regex, REG_EXTENDED);
								if (ret != 0) {
									regerror(ret, &reg, err, 1024);
									return 1;
								}
								int return_value;
								return_value = regexec(&reg, (yyvsp[-1].ast)->nodeType , 0, NULL, 0);
								regfree(&reg);
								if (return_value == 0){
									strcpy(exprType, "int");
								}
								else{
									/* get type for character */
									regex_t reg;
									const char *regex="'[a-zA-Z]'";
									int ret;
									char err[1024];
									ret = regcomp(&reg, regex, REG_EXTENDED);
									if (ret != 0) {
										regerror(ret, &reg, err, 1024);
										return 1;
									}
									int return_value;
									return_value = regexec(&reg, (yyvsp[-1].ast)->nodeType , 0, NULL, 0);
									regfree(&reg);
									if (return_value == 0){
										strcpy(exprType, "char");
									}
									else{
										strcpy(exprType, ""); 
									}
								}
							}
						}
						/* if expr type is not int, print error message */
						if (strcmp(exprType, "int") != 0){
							printf("SEMANTIC ERROR: The type of expression must be int || Line: %d || Char: %d\n", lines, chars);
						}
						
						// IR code
						// char *reg = getRegister();
						// emitArray($3->IRcode, reg , $1);
						// strcpy($$->IRcode, reg);

						if (strcmp(top(theStack), "main") == 0){
							if (strcmp(getExprType((yyvsp[-1].ast)->IRcode), "int") == 0){
								// add var onto the symbol table
								char varNameHolder[50];
								strcpy(varNameHolder, (yyvsp[-3].string));
								strcat(varNameHolder, "[");
								strcat(varNameHolder, (yyvsp[-1].ast)->IRcode);
								strcat(varNameHolder, "]");
								strcpy((yyval.ast)->IRcode, getValue(varNameHolder, theStack));
							}
							else if (strcmp(getExprType((yyvsp[-1].ast)->IRcode), "id") == 0){
								// add var onto the symbol table
								char varNameHolder[50];
								strcpy(varNameHolder, (yyvsp[-3].string));
								strcat(varNameHolder, "[");
								char * index = getValue((yyvsp[-1].ast)->IRcode, theStack);
								strcat(varNameHolder, index);
								strcat(varNameHolder, "]");
								strcpy((yyval.ast)->IRcode, getValue(varNameHolder, theStack));												
							}
						}
						else{	
							char * reg = getRegister();
						

							if (strcmp(getExprType((yyvsp[-1].ast)->IRcode), "int") == 0){
								// li $t0, 2
								fprintf(MIPS,"li %s, %s\n", reg, (yyvsp[-1].ast)->IRcode);
							}
							else if (strcmp(getExprType((yyvsp[-1].ast)->IRcode), "id") == 0){
								char* scope = getScope((yyvsp[-1].ast)->IRcode, theStack);
								// lw $t0, addhehe_f
								fprintf(MIPS,"lw %s, %s_%s\n", reg, scope, (yyvsp[-1].ast)->IRcode);
							}
							else{
								freeReg(reg);
								reg = (yyvsp[-1].ast)->IRcode;
							}
							
							
							char * reg2 = getRegister();
							char* scope = getScope((yyvsp[-3].string), theStack);
							// li $t2, 4                                   #4 bits per word
							// mult $t1, $t2                               #calculate bit-index
							// mflo $t2                                    #obtain bit-index
							// lw $t1, glob_X($t2)   							
							fprintf(MIPS,"li %s, 4\nmult %s, %s\nmflo %s\nlw %s, %s_%s(%s)\n", reg2, reg, reg2, reg2, reg, scope, (yyvsp[-3].string), reg2);
							fprintf(IRcode," %s = %s[%s]\n", reg, (yyvsp[-3].string), (yyvsp[-1].ast)->IRcode); 
							freeReg(reg2);
							strcpy((yyval.ast)->IRcode, reg); 
							
						}
					}
#line 2344 "parser.tab.c"
    break;

  case 39:
#line 901 "parser.y"
                        {
				(yyval.ast) = AST_node("READ");
				(yyval.ast)->left = AST_node((yyvsp[-2].string));
				(yyval.ast)->right = AST_node("");
				printf("RECOGNIZED RULE: READ || %s || Line: %d || Char: %d\n", (yyvsp[-2].string), lines, chars);
				if(strcmp(getType((yyvsp[-2].string),theStack), "int") == 0){
					emitReadForInt((yyvsp[-2].string), getScope((yyvsp[-2].string), theStack));
				} else {
					printf("\n\nWARNING: MIPS not currently generating for char input!!!\n\n");
					emitReadForChar((yyvsp[-2].string), getScope((yyvsp[-2].string), theStack));
				}
			}
#line 2361 "parser.tab.c"
    break;

  case 40:
#line 914 "parser.y"
                        {
				printf("SYNTAX ERROR: Missing ID in Input || Line: %d || Char: %d\n", lines, chars);
			}
#line 2369 "parser.tab.c"
    break;

  case 41:
#line 918 "parser.y"
                        {
				printf("SYNTAX ERROR: Missing RPAREN after ID || Line: %d || Char: %d\n", lines, chars);
			}
#line 2377 "parser.tab.c"
    break;

  case 42:
#line 922 "parser.y"
                        {
				printf("SYNTAX ERROR: Missing LPAREN before ID|| Line: %d || Char: %d\n", lines, chars);
			}
#line 2385 "parser.tab.c"
    break;

  case 43:
#line 926 "parser.y"
                        {
				printf("SYNTAX ERROR: Missing SEMICOLON || Line: %d || Char: %d\n", lines, chars);
			}
#line 2393 "parser.tab.c"
    break;

  case 44:
#line 930 "parser.y"
                {
			/* node for !Expr */
			(yyval.ast) = AST_node((yyvsp[-1].string));
			(yyval.ast)->left = (yyvsp[0].ast);

			/* check out code comments on "ID LBRACK Expr RBRACK" rule */
			char exprType[50]; 
			if ((strcmp((yyvsp[0].ast)->nodeType, "!") == 0) || (strcmp((yyvsp[0].ast)->nodeType, "==") == 0) || (strcmp((yyvsp[0].ast)->nodeType, "!=") == 0) || (strcmp((yyvsp[0].ast)->nodeType, "<=") == 0) || (strcmp((yyvsp[0].ast)->nodeType, ">=") == 0) || (strcmp((yyvsp[0].ast)->nodeType, "&&") == 0) || (strcmp((yyvsp[0].ast)->nodeType, "||") == 0) || (strcmp((yyvsp[0].ast)->nodeType, "<") == 0) || (strcmp((yyvsp[0].ast)->nodeType, ">") == 0)){
				strcpy(exprType, "bool");
			}
			else if ((strcmp((yyvsp[0].ast)->nodeType, "+") == 0) || (strcmp((yyvsp[0].ast)->nodeType, "-") == 0) || (strcmp((yyvsp[0].ast)->nodeType, "*") == 0) || (strcmp((yyvsp[0].ast)->nodeType, "/") == 0)){
				strcpy(exprType, "int");
			}
			else if ((strcmp((yyvsp[0].ast)->nodeType, "ARR") == 0)){			
				strcpy(exprType, getTypeForArr((yyvsp[0].ast)->left->nodeType, theStack));				
			}
			else{
				regex_t reg;
				const char *regex="^[A-Za-z][A-Za-z0-9]*";
				int ret;
				char err[1024];
				//Read data into variable filecontent
				ret = regcomp(&reg, regex, REG_EXTENDED);
				if (ret != 0) {
					regerror(ret, &reg, err, 1024);
					return 1;
				}
				int return_value;
				return_value = regexec(&reg, (yyvsp[0].ast)->nodeType , 0, NULL, 0);
				regfree(&reg);
				if (return_value == 0){
					strcpy(exprType, getType((yyvsp[0].ast)->nodeType, theStack));
				}
				else{
					regex_t reg;
					const char *regex="^-?[0-9]+";
					int ret;
					char err[1024];
					//Read data into variable filecontent
					ret = regcomp(&reg, regex, REG_EXTENDED);
					if (ret != 0) {
						regerror(ret, &reg, err, 1024);
						return 1;
					}
					int return_value;
					return_value = regexec(&reg, (yyvsp[0].ast)->nodeType , 0, NULL, 0);
					regfree(&reg);
					if (return_value == 0){
						strcpy(exprType, "int");
					}
					else{
						/* get type for character */
						regex_t reg;
						const char *regex="'[a-zA-Z]'";
						int ret;
						char err[1024];
						ret = regcomp(&reg, regex, REG_EXTENDED);
						if (ret != 0) {
							regerror(ret, &reg, err, 1024);
							return 1;
						}
						int return_value;
						return_value = regexec(&reg, (yyvsp[0].ast)->nodeType , 0, NULL, 0);
						regfree(&reg);
						if (return_value == 0){
							strcpy(exprType, "char");
						}
						else{
							strcpy(exprType, ""); 
						}
					}
				}
			}
			/* if the expr type is not a boolean, print error message */
			if (strcmp(exprType, "bool") != 0){
				printf("SEMANTIC ERROR: The type of expression must be bool || Line: %d || Char: %d\n", lines, chars);
			}


			/*IR code for UNARYOP*/
			
			regex_t reg;
			const char *regex="^[A-Za-z][A-Za-z0-9]*";
			int ret;
			char err[1024];
			//Read data into variable filecontent
			ret = regcomp(&reg, regex, REG_EXTENDED);
			if (ret != 0) {
				regerror(ret, &reg, err, 1024);
				return 1;
			}
			int return_value;
			return_value = regexec(&reg, (yyvsp[0].ast)->IRcode , 0, NULL, 0);
			regfree(&reg);
			// if $2->IRcode match the pattern
			if (return_value == 0){
				strcpy((yyval.ast)->IRcode, (yyvsp[0].ast)->IRcode);
				char* line;
				char line1[500] = "";
				strcat(line1, (yyval.ast)->IRcode);
				strcat(line1, " = ");
				strcat(line1, "NOT ");
				strcat(line1, (yyvsp[0].ast)->IRcode);
				line = line1;
				writeIR(line1);
			}
		}
#line 2505 "parser.tab.c"
    break;

  case 45:
#line 1038 "parser.y"
                {
			/* node for binop */
			(yyval.ast) = AST_node((yyvsp[-1].string));
			(yyval.ast)->left = (yyvsp[-2].ast);
			(yyval.ast)->right = (yyvsp[0].ast);
			
			/* check out code comments on "ID LBRACK Expr RBRACK" rule */
			char exprType[50]; 
			if ((strcmp((yyvsp[0].ast)->nodeType, "!") == 0) || (strcmp((yyvsp[0].ast)->nodeType, "==") == 0) || (strcmp((yyvsp[0].ast)->nodeType, "!=") == 0) || (strcmp((yyvsp[0].ast)->nodeType, "<=") == 0) || (strcmp((yyvsp[0].ast)->nodeType, ">=") == 0) || (strcmp((yyvsp[0].ast)->nodeType, "&&") == 0) || (strcmp((yyvsp[0].ast)->nodeType, "||") == 0) || (strcmp((yyvsp[0].ast)->nodeType, "<") == 0) || (strcmp((yyvsp[0].ast)->nodeType, ">") == 0)){
				strcpy(exprType, "bool");
			}
			else if ((strcmp((yyvsp[0].ast)->nodeType, "+") == 0) || (strcmp((yyvsp[0].ast)->nodeType, "-") == 0) || (strcmp((yyvsp[0].ast)->nodeType, "*") == 0) || (strcmp((yyvsp[0].ast)->nodeType, "/") == 0)){
				strcpy(exprType, "int");
			}
			else if ((strcmp((yyvsp[0].ast)->nodeType, "ARR") == 0)){			
				strcpy(exprType, getTypeForArr((yyvsp[0].ast)->left->nodeType, theStack));				
			}
			else{
				regex_t reg;
				const char *regex="^[A-Za-z][A-Za-z0-9]*"; 
				int ret;
				char err[1024];
				//Read data into variable filecontent
				ret = regcomp(&reg, regex, REG_EXTENDED);
				if (ret != 0) {
					regerror(ret, &reg, err, 1024);
					return 1;
				}
				int return_value;
				return_value = regexec(&reg, (yyvsp[0].ast)->nodeType , 0, NULL, 0);
				regfree(&reg);
				if (return_value == 0){
					strcpy(exprType, getType((yyvsp[0].ast)->nodeType, theStack));
				}
				else{
					regex_t reg;
					const char *regex="^-?[0-9]+";
					int ret;
					char err[1024];
					//Read data into variable filecontent
					ret = regcomp(&reg, regex, REG_EXTENDED);
					if (ret != 0) {
						regerror(ret, &reg, err, 1024);
						return 1;
					}
					int return_value;
					return_value = regexec(&reg, (yyvsp[0].ast)->nodeType , 0, NULL, 0);
					regfree(&reg);
					if (return_value == 0){
						strcpy(exprType, "int");
					}
					else{
						/* get type for character */
						regex_t reg;
						const char *regex="'[a-zA-Z]'";
						int ret;
						char err[1024];
						ret = regcomp(&reg, regex, REG_EXTENDED);
						if (ret != 0) {
							regerror(ret, &reg, err, 1024);
							return 1;
						}
						int return_value;
						return_value = regexec(&reg, (yyvsp[0].ast)->nodeType , 0, NULL, 0);
						regfree(&reg);
						if (return_value == 0){
							strcpy(exprType, "char");
						}
						else{
							strcpy(exprType, ""); 
						}
					}
				}
			}
			
			/* if binop if && or ||, expect boolean expr */
			if (strcmp((yyvsp[-1].string), "&&") == 0 || strcmp((yyvsp[-1].string), "||") == 0){
				if (strcmp(exprType, "bool") != 0){
					printf("SEMANTIC ERROR: The type of expression must be boolean || Line: %d || Char: %d\n", lines, chars);
				}
			}
			/*  if binop if not && and ||, expect int expr*/
			else{
				if (strcmp(exprType, "int") != 0){
					printf("SEMANTIC ERROR: The type of expression must be int || Line: %d || Char: %d\n", lines, chars);
				}
			}
			/* check out code comments on "ID LBRACK Expr RBRACK" rule */
			char exprType2[50];
			if ((strcmp((yyvsp[-2].ast)->nodeType, "!") == 0) || (strcmp((yyvsp[-2].ast)->nodeType, "==") == 0) || (strcmp((yyvsp[-2].ast)->nodeType, "!=") == 0) || (strcmp((yyvsp[-2].ast)->nodeType, "<=") == 0) || (strcmp((yyvsp[-2].ast)->nodeType, ">=") == 0) || (strcmp((yyvsp[-2].ast)->nodeType, "&&") == 0) || (strcmp((yyvsp[-2].ast)->nodeType, "||") == 0) || (strcmp((yyvsp[-2].ast)->nodeType, "<") == 0) || (strcmp((yyvsp[-2].ast)->nodeType, ">") == 0)){
				strcpy(exprType2, "bool");
			}
			else if ((strcmp((yyvsp[-2].ast)->nodeType, "+") == 0) || (strcmp((yyvsp[-2].ast)->nodeType, "-") == 0) || (strcmp((yyvsp[-2].ast)->nodeType, "*") == 0) || (strcmp((yyvsp[-2].ast)->nodeType, "/") == 0)){
				strcpy(exprType2, "int");
			}
			else if ((strcmp((yyvsp[-2].ast)->nodeType, "ARR") == 0)){			
				strcpy(exprType2, getTypeForArr((yyvsp[-2].ast)->left->nodeType, theStack));				
			}
			else{
				regex_t reg;
				const char *regex="^[A-Za-z][A-Za-z0-9]*";
				int ret;
				char err[1024];
				//Read data into variable filecontent
				ret = regcomp(&reg, regex, REG_EXTENDED);
				if (ret != 0) {
					regerror(ret, &reg, err, 1024);
					return 1;
				}
				int return_value;
				return_value = regexec(&reg, (yyvsp[-2].ast)->nodeType , 0, NULL, 0);
				regfree(&reg);
				if (return_value == 0){
					strcpy(exprType2, getType((yyvsp[-2].ast)->nodeType, theStack));
				}
				else{
					regex_t reg;
					const char *regex="^-?[0-9]+";
					int ret;
					char err[1024];
					//Read data into variable filecontent
					ret = regcomp(&reg, regex, REG_EXTENDED);
					if (ret != 0) {
						regerror(ret, &reg, err, 1024);
						return 1;
					}
					int return_value;
					return_value = regexec(&reg, (yyvsp[-2].ast)->nodeType , 0, NULL, 0);
					regfree(&reg);
					if (return_value == 0){
						strcpy(exprType2, "int");
					}
					else{
						/* get type for character */
						regex_t reg;
						const char *regex="'[a-zA-Z]'";
						int ret;
						char err[1024];
						ret = regcomp(&reg, regex, REG_EXTENDED);
						if (ret != 0) {
							regerror(ret, &reg, err, 1024);
							return 1;
						}
						int return_value;
						return_value = regexec(&reg, (yyvsp[-2].ast)->nodeType , 0, NULL, 0);
						regfree(&reg);
						if (return_value == 0){
							strcpy(exprType2, "char");
						}
						else{
							strcpy(exprType2, ""); 
						}
					}
				}
			}
			/* do same thing with the $3 expr */
			if (strcmp((yyvsp[-1].string), "&&") == 0 || strcmp((yyvsp[-1].string), "||") == 0){
				if (strcmp(exprType2, "bool") != 0){
					printf("SEMANTIC ERROR: The type of expression must be boolean || Line: %d || Char: %d\n", lines, chars);
				}
			}
			else{
				if (strcmp(exprType2, "int") != 0){
					printf("SEMANTIC ERROR: The type of expression must be int || Line: %d || Char: %d\n", lines, chars);
				}
			}

	
			char * reg = getRegister();
			char * reg2 = getRegister();

			if (strcmp(getExprType((yyvsp[-2].ast)->IRcode), "int") == 0){
				// li $t0, 2
				fprintf(MIPS,"li %s, %s\n", reg, (yyvsp[-2].ast)->IRcode);
			}
			else if (strcmp(getExprType((yyvsp[-2].ast)->IRcode), "id") == 0){
				char* scope = getScope((yyvsp[-2].ast)->IRcode, theStack);
				// lw $t0, addhehe_f
				fprintf(MIPS,"lw %s, %s_%s\n", reg, scope, (yyvsp[-2].ast)->IRcode);
			}
			else{
				freeReg(reg);
				reg = (yyvsp[-2].ast)->IRcode;
			}

			if (strcmp(getExprType((yyvsp[0].ast)->IRcode), "int") == 0){
				// li $t0, 2
				fprintf(MIPS,"li %s, %s\n", reg2, (yyvsp[0].ast)->IRcode);
			}
			else if (strcmp(getExprType((yyvsp[0].ast)->IRcode), "id") == 0){
				char* scope = getScope((yyvsp[0].ast)->IRcode, theStack);
				// lw $t0, addhehe_f
				fprintf(MIPS,"lw %s, %s_%s\n", reg2, scope, (yyvsp[0].ast)->IRcode);
			}
			else{
				freeReg(reg2);
				reg2 = (yyvsp[0].ast)->IRcode;			
			}
			// char *ret;
			// ret = strstr("==",$2);
			if (strcmp("==",(yyvsp[-1].string)) == 0){
				// bne $t0, $t1, else_addNum_if_1
				fprintf(MIPS,"bne %s, %s, else_%s\n", reg, reg2, top(theStack));
			}
			else {
				// char *ret;
				// ret = strstr("!=",$2);
				if (strcmp("!=",(yyvsp[-1].string)) == 0){
					// beq $t0, $t1, else_addNum_if_1
					fprintf(MIPS,"beq %s, %s, else_%s\n", reg, reg2, top(theStack));
				}
				else {
					// char *ret;
					// ret = strstr("<=",$2);
					if (strcmp("<=",(yyvsp[-1].string)) == 0){
						// bgt $t0, $t1, else_addNum_if_1
						fprintf(MIPS,"bgt %s, %s, else_%s\n", reg, reg2, top(theStack));
					}
					else{
						// char *ret;
						// ret = strstr(">=",$2);
						if (strcmp(">=",(yyvsp[-1].string)) == 0){
							// blt $t0, $t1, else_addNum_if_1
							fprintf(MIPS,"blt %s, %s, else_%s\n", reg, reg2, top(theStack));
						}
						else{
							// char *ret;
							// ret = strstr("<",$2);
							if (strcmp("<",(yyvsp[-1].string)) == 0){
								// bge $t0, $t1, else_addNum_if_1
								fprintf(MIPS,"bge %s, %s, else_%s\n", reg, reg2, top(theStack));
							}
							else{
								// char *ret;
								// ret = strstr(">",$2);
								if (strcmp(">",(yyvsp[-1].string)) == 0){
									// ble $t0, $t1, else_addNum_if_1
									fprintf(MIPS,"ble %s, %s, else_%s\n", reg, reg2, top(theStack));
								}
							}
						}
					}
				}
			}
			freeReg(reg);
			freeReg(reg2);
			strcpy((yyval.ast)->IRcode, reg); 
			fprintf(IRcode," %s = %s %s %s\n", reg, (yyvsp[-2].ast)->IRcode, (yyvsp[-1].string), (yyvsp[0].ast)->IRcode);
		}
#line 2759 "parser.tab.c"
    break;

  case 46:
#line 1288 "parser.y"
                        {
				/* node for + op */
				(yyval.ast) = AST_node("+");
				(yyval.ast)->left = (yyvsp[-2].ast);
				(yyval.ast)->right = (yyvsp[0].ast);

				struct AST* node = (yyvsp[-2].ast);
				/* check out code comments on "ID LBRACK Expr RBRACK" rule */
				char exprType[50]; 
				if ((strcmp(node->nodeType, "!") == 0) || (strcmp(node->nodeType, "==") == 0) || (strcmp(node->nodeType, "!=") == 0) || (strcmp(node->nodeType, "<=") == 0) || (strcmp(node->nodeType, ">=") == 0) || (strcmp(node->nodeType, "&&") == 0) || (strcmp(node->nodeType, "||") == 0) || (strcmp(node->nodeType, "<") == 0) || (strcmp(node->nodeType, ">") == 0)){
					strcpy(exprType, "bool");
				}
				else if ((strcmp(node->nodeType, "+") == 0) || (strcmp(node->nodeType, "-") == 0) || (strcmp(node->nodeType, "*") == 0) || (strcmp(node->nodeType, "/") == 0)){
					strcpy(exprType, "int");
				}
				else if ((strcmp(node->nodeType, "ARR") == 0)){			
					strcpy(exprType, getTypeForArr(node->left->nodeType, theStack));				
				}
				else{
					regex_t reg;
					const char *regex="^[A-Za-z][A-Za-z0-9]*";
					int ret;
					char err[1024];
					//Read data into variable filecontent
					ret = regcomp(&reg, regex, REG_EXTENDED);
					if (ret != 0) {
						regerror(ret, &reg, err, 1024);
						return 1;
					}
					int return_value;
					return_value = regexec(&reg, node->nodeType , 0, NULL, 0);
					regfree(&reg);
					if (return_value == 0){
						strcpy(exprType, getType(node->nodeType, theStack));
					}
					else{
						regex_t reg;
						const char *regex="^-?[0-9]+";
						int ret;
						char err[1024];
						//Read data into variable filecontent
						ret = regcomp(&reg, regex, REG_EXTENDED);
						if (ret != 0) {
							regerror(ret, &reg, err, 1024);
							return 1;
						}
						int return_value;
						return_value = regexec(&reg, node->nodeType , 0, NULL, 0);
						regfree(&reg);
						if (return_value == 0){
							strcpy(exprType, "int");
						}
						else{
              regex_t reg;
              const char *regex="'[a-zA-Z]'";
              int ret;
              char err[1024];
              //Read data into variable filecontent
              ret = regcomp(&reg, regex, REG_EXTENDED);
              if (ret != 0) {
                regerror(ret, &reg, err, 1024);
                return 1;
              }
              int return_value;
              return_value = regexec(&reg, node->nodeType , 0, NULL, 0);
              regfree(&reg);
              if (return_value == 0){
                strcpy(exprType, "char");
              }
              else{
                strcpy(exprType, ""); 
              }
            }
          }
        }
				/* if expr type is not int, print error message */
				if (strcmp(exprType, "int") != 0){
					printf("SEMANTIC ERROR: The type of expression must be int || Line: %d || Char: %d\n", lines, chars);
				}				
				
				node = (yyvsp[0].ast);
				/* check out code comments on "ID LBRACK Expr RBRACK" rule */
				if ((strcmp(node->nodeType, "!") == 0) || (strcmp(node->nodeType, "==") == 0) || (strcmp(node->nodeType, "!=") == 0) || (strcmp(node->nodeType, "<=") == 0) || (strcmp(node->nodeType, ">=") == 0) || (strcmp(node->nodeType, "&&") == 0) || (strcmp(node->nodeType, "||") == 0) || (strcmp(node->nodeType, "<") == 0) || (strcmp(node->nodeType, ">") == 0)){
					strcpy(exprType, "bool");
				}
				else if ((strcmp(node->nodeType, "+") == 0) || (strcmp(node->nodeType, "-") == 0) || (strcmp(node->nodeType, "*") == 0) || (strcmp(node->nodeType, "/") == 0)){
					strcpy(exprType, "int");
				}
				else if ((strcmp(node->nodeType, "ARR") == 0)){			
					strcpy(exprType, getTypeForArr(node->left->nodeType, theStack));				
				}
				else{
					regex_t reg;
					const char *regex="^[A-Za-z][A-Za-z0-9]*";
					int ret;
					char err[1024];
					//Read data into variable filecontent
					ret = regcomp(&reg, regex, REG_EXTENDED);
					if (ret != 0) {
						regerror(ret, &reg, err, 1024);
						return 1;
					}
					int return_value;
					return_value = regexec(&reg, node->nodeType , 0, NULL, 0);
					regfree(&reg);
					if (return_value == 0){
						strcpy(exprType, getType(node->nodeType, theStack));
					}
					else{
						regex_t reg;
						const char *regex="^-?[0-9]+";
						int ret;
						char err[1024];
						//Read data into variable filecontent
						ret = regcomp(&reg, regex, REG_EXTENDED);
						if (ret != 0) {
							regerror(ret, &reg, err, 1024);
							return 1;
						}
						int return_value;
						return_value = regexec(&reg, node->nodeType , 0, NULL, 0);
						regfree(&reg);
						if (return_value == 0){
							strcpy(exprType, "int");
						}
						else{
              regex_t reg;
              const char *regex="'[a-zA-Z]'";
              int ret;
              char err[1024];
              //Read data into variable filecontent
              ret = regcomp(&reg, regex, REG_EXTENDED);
              if (ret != 0) {
                regerror(ret, &reg, err, 1024);
                return 1;
              }
              int return_value;
              return_value = regexec(&reg, node->nodeType , 0, NULL, 0);
              regfree(&reg);
              if (return_value == 0){
                strcpy(exprType, "char");
              }
              else{
                strcpy(exprType, ""); 
              }
            }
          }
        }
				/* if expr type is not int, print error message */
				if (strcmp(exprType, "int") != 0){
					printf("SEMANTIC ERROR: The type of expression must be int || Line: %d || Char: %d\n", lines, chars);
				}		




				// /* IR code generation */
				
				if (strcmp(top(theStack), "main") == 0){

					regex_t reg;
					const char *regex="^-?[0-9]+";
					int ret;
					char err[1024];
					//Read data into variable filecontent
					ret = regcomp(&reg, regex, REG_EXTENDED);
					if (ret != 0) {
						regerror(ret, &reg, err, 1024);
						return 1;
					}
					int return_value;
					return_value = regexec(&reg, (yyvsp[-2].ast)->IRcode , 0, NULL, 0);
					regfree(&reg);
					
					regex_t reg2;
					const char *regex2="^-?[0-9]+";
					int ret2;
					char err2[1024];
					//Read data into variable filecontent
					ret2 = regcomp(&reg2, regex2, REG_EXTENDED);
					if (ret2 != 0) {
						regerror(ret2, &reg2, err2, 1024);
						return 1;
					}
					int return_value2;
					return_value2 = regexec(&reg2, (yyvsp[0].ast)->IRcode , 0, NULL, 0);
					regfree(&reg2);

					if (return_value == 0 && return_value2 == 0){
						float left;
						sscanf((yyvsp[-2].ast)->IRcode, "%f", &left);
						float right;
						sscanf((yyvsp[0].ast)->IRcode, "%f", &right);
						float ans = left + right;
						int int_ans = (int)ans;					
						sprintf((yyval.ast)->IRcode, "%d", int_ans);
					}
					else if (return_value != 0 && return_value2 == 0){
						float left;
						char value[50];
						strcpy(value, getValue((yyvsp[-2].ast)->IRcode, theStack));
						sscanf(value, "%f", &left);
						float right;
						sscanf((yyvsp[0].ast)->IRcode, "%f", &right);
						float ans = left + right;
						int int_ans = (int)ans;			
						sprintf((yyval.ast)->IRcode, "%d", int_ans);
					}
					else if (return_value == 0 && return_value2 != 0){
						float left;
						sscanf((yyvsp[-2].ast)->IRcode, "%f", &left);
						float right;
						char value[50];
						strcpy(value, getValue((yyvsp[0].ast)->IRcode, theStack));
						sscanf(value, "%f", &right);
						float ans = left + right;
						int int_ans = (int)ans;					
						sprintf((yyval.ast)->IRcode, "%d", int_ans);
					}
					else if (return_value != 0 && return_value2 != 0){
						float left;
						char value[50];
						strcpy(value, getValue((yyvsp[-2].ast)->IRcode, theStack));
						sscanf(value, "%f", &left);
						float right;
						char value1[50];
						strcpy(value1, getValue((yyvsp[0].ast)->IRcode, theStack));
						sscanf(value1, "%f", &right);
						float ans = left + right;
						int int_ans = (int)ans;					
						sprintf((yyval.ast)->IRcode, "%d", int_ans);
					}
				}
				else{
					char * reg = getRegister();
					char * reg2 = getRegister();
					
					if (strcmp(getExprType((yyvsp[-2].ast)->IRcode), "int") == 0){
						if (strcmp((yyvsp[-2].ast)->IRcode, "0") != 0){
							// li $t0, 2
							fprintf(MIPS,"li %s, %s\n", reg, (yyvsp[-2].ast)->IRcode);
						}						
						else{
							freeReg(reg);
							reg = "";
						}
					}
					else if (strcmp(getExprType((yyvsp[-2].ast)->IRcode), "id") == 0){
						char* scope = getScope((yyvsp[-2].ast)->IRcode, theStack);
						// lw $t0, addhehe_f
						fprintf(MIPS,"lw %s, %s_%s\n", reg, scope, (yyvsp[-2].ast)->IRcode);
					}
					else{
						freeReg(reg);
						reg = (yyvsp[-2].ast)->IRcode;
					}

					if (strcmp(getExprType((yyvsp[0].ast)->IRcode), "int") == 0){
						if (strcmp((yyvsp[0].ast)->IRcode, "0") != 0){
						// li $t0, 2
						fprintf(MIPS,"li %s, %s\n", reg2, (yyvsp[0].ast)->IRcode);
						}
						else{
							freeReg(reg2);
							reg2 = "";
						}
					}
					else if (strcmp(getExprType((yyvsp[0].ast)->IRcode), "id") == 0){
						char* scope = getScope((yyvsp[0].ast)->IRcode, theStack);
						// lw $t0, addhehe_f
						fprintf(MIPS,"lw %s, %s_%s\n", reg2, scope, (yyvsp[0].ast)->IRcode);
					}
					else{
						freeReg(reg2);
						reg2 = (yyvsp[0].ast)->IRcode;			
					}

					// add $t0, $t0, $t1
					if (strcmp(reg, "") != 0 && strcmp(reg2, "") != 0)
					{
						fprintf(MIPS,"add %s, %s, %s\n", reg, reg, reg2);
						freeReg(reg2);
						strcpy((yyval.ast)->IRcode, reg); 
						fprintf(IRcode," %s = %s + %s\n", reg, (yyvsp[-2].ast)->IRcode, (yyvsp[0].ast)->IRcode);
					}
					else if (strcmp(reg, "") == 0 && strcmp(reg2, "") != 0){
						freeReg(reg);
						strcpy((yyval.ast)->IRcode, reg2); 
					}
					else if (strcmp(reg, "") != 0 && strcmp(reg2, "") == 0){
						freeReg(reg2);
						strcpy((yyval.ast)->IRcode, reg); 
					}
					else{
						// move $t0, $zero 
						reg = getRegister();
						fprintf(MIPS,"move %s, $zero\n", reg);						
						strcpy((yyval.ast)->IRcode, reg); 
					}
				}
			}
#line 3065 "parser.tab.c"
    break;

  case 47:
#line 1590 "parser.y"
                        {
				/* node for - op */
				(yyval.ast) = AST_node("-");
				(yyval.ast)->left = (yyvsp[-2].ast);
				(yyval.ast)->right = (yyvsp[0].ast);
				
				/* check out code comments on "ID LBRACK Expr RBRACK" rule */
				struct AST* node = (yyvsp[-2].ast);
				char exprType[50]; 
				if ((strcmp(node->nodeType, "!") == 0) || (strcmp(node->nodeType, "==") == 0) || (strcmp(node->nodeType, "!=") == 0) || (strcmp(node->nodeType, "<=") == 0) || (strcmp(node->nodeType, ">=") == 0) || (strcmp(node->nodeType, "&&") == 0) || (strcmp(node->nodeType, "||") == 0) || (strcmp(node->nodeType, "<") == 0) || (strcmp(node->nodeType, ">") == 0)){
					strcpy(exprType, "bool");
				}
				else if ((strcmp(node->nodeType, "+") == 0) || (strcmp(node->nodeType, "-") == 0) || (strcmp(node->nodeType, "*") == 0) || (strcmp(node->nodeType, "/") == 0)){
					strcpy(exprType, "int");
				}
				else if ((strcmp(node->nodeType, "ARR") == 0)){			
					strcpy(exprType, getTypeForArr(node->left->nodeType, theStack));				
				}
				else{
					regex_t reg;
					const char *regex="^[A-Za-z][A-Za-z0-9]*";
					int ret;
					char err[1024];
					//Read data into variable filecontent
					ret = regcomp(&reg, regex, REG_EXTENDED);
					if (ret != 0) {
						regerror(ret, &reg, err, 1024);
						return 1;
					}
					int return_value;
					return_value = regexec(&reg, node->nodeType , 0, NULL, 0);
					regfree(&reg);
					if (return_value == 0){
						strcpy(exprType, getType(node->nodeType, theStack));
					}
					else{
						regex_t reg;
						const char *regex="^-?[0-9]+";
						int ret;
						char err[1024];
						//Read data into variable filecontent
						ret = regcomp(&reg, regex, REG_EXTENDED);
						if (ret != 0) {
							regerror(ret, &reg, err, 1024);
							return 1;
						}
						int return_value;
						return_value = regexec(&reg, node->nodeType , 0, NULL, 0);
						regfree(&reg);
						if (return_value == 0){
							strcpy(exprType, "int");
						}
						else{
              regex_t reg;
              const char *regex="'[a-zA-Z]'";
              int ret;
              char err[1024];
              //Read data into variable filecontent
              ret = regcomp(&reg, regex, REG_EXTENDED);
              if (ret != 0) {
                regerror(ret, &reg, err, 1024);
                return 1;
              }
              int return_value;
              return_value = regexec(&reg, node->nodeType , 0, NULL, 0);
              regfree(&reg);
              if (return_value == 0){
                strcpy(exprType, "char");
              }
              else{
                strcpy(exprType, ""); 
              }
            }
          }
        }
				/* if expr type is not int, print error type */
				if (strcmp(exprType, "int") != 0){
					printf("SEMANTIC ERROR: The type of expression must be int || Line: %d || Char: %d\n", lines, chars);
				}				
				/* check out code comments on "ID LBRACK Expr RBRACK" rule */
				node = (yyvsp[0].ast);
				if ((strcmp(node->nodeType, "!") == 0) || (strcmp(node->nodeType, "==") == 0) || (strcmp(node->nodeType, "!=") == 0) || (strcmp(node->nodeType, "<=") == 0) || (strcmp(node->nodeType, ">=") == 0) || (strcmp(node->nodeType, "&&") == 0) || (strcmp(node->nodeType, "||") == 0) || (strcmp(node->nodeType, "<") == 0) || (strcmp(node->nodeType, ">") == 0)){
					strcpy(exprType, "bool");
				}
				else if ((strcmp(node->nodeType, "+") == 0) || (strcmp(node->nodeType, "-") == 0) || (strcmp(node->nodeType, "*") == 0) || (strcmp(node->nodeType, "/") == 0)){
					strcpy(exprType, "int");
				}
				else if ((strcmp(node->nodeType, "ARR") == 0)){			
					strcpy(exprType, getTypeForArr(node->left->nodeType, theStack));				
				}
				else{
					regex_t reg;
					const char *regex="^[A-Za-z][A-Za-z0-9]*";
					int ret;
					char err[1024];
					//Read data into variable filecontent
					ret = regcomp(&reg, regex, REG_EXTENDED);
					if (ret != 0) {
						regerror(ret, &reg, err, 1024);
						return 1;
					}
					int return_value;
					return_value = regexec(&reg, node->nodeType , 0, NULL, 0);
					regfree(&reg);
					if (return_value == 0){
						strcpy(exprType, getType(node->nodeType, theStack));
					}
					else{
						regex_t reg;
						const char *regex="^-?[0-9]+";
						int ret;
						char err[1024];
						//Read data into variable filecontent
						ret = regcomp(&reg, regex, REG_EXTENDED);
						if (ret != 0) {
							regerror(ret, &reg, err, 1024);
							return 1;
						}
						int return_value;
						return_value = regexec(&reg, node->nodeType , 0, NULL, 0);
						regfree(&reg);
						if (return_value == 0){
							strcpy(exprType, "int");
						}
						else{
              regex_t reg;
              const char *regex="'[a-zA-Z]'";
              int ret;
              char err[1024];
              //Read data into variable filecontent
              ret = regcomp(&reg, regex, REG_EXTENDED);
              if (ret != 0) {
                regerror(ret, &reg, err, 1024);
                return 1;
              }
              int return_value;
              return_value = regexec(&reg, node->nodeType , 0, NULL, 0);
              regfree(&reg);
              if (return_value == 0){
                strcpy(exprType, "char");
              }
              else{
                strcpy(exprType, ""); 
              }
            }
          }
        }
				/* if expr type is not int, print error message */
				if (strcmp(exprType, "int") != 0){
					printf("SEMANTIC ERROR: The type of expression must be int || Line: %d || Char: %d\n", lines, chars);
				}


				// /* IR code generation */
				
				if (strcmp(top(theStack), "main") == 0){
					regex_t reg;
					const char *regex="^-?[0-9]+";
					int ret;
					char err[1024];
					//Read data into variable filecontent
					ret = regcomp(&reg, regex, REG_EXTENDED);
					if (ret != 0) {
						regerror(ret, &reg, err, 1024);
						return 1;
					}
					int return_value;
					return_value = regexec(&reg, (yyvsp[-2].ast)->IRcode , 0, NULL, 0);
					regfree(&reg);
					
					regex_t reg2;
					const char *regex2="^-?[0-9]+";
					int ret2;
					char err2[1024];
					//Read data into variable filecontent
					ret2 = regcomp(&reg2, regex2, REG_EXTENDED);
					if (ret2 != 0) {
						regerror(ret2, &reg2, err2, 1024);
						return 1;
					}
					int return_value2;
					return_value2 = regexec(&reg2, (yyvsp[0].ast)->IRcode , 0, NULL, 0);
					regfree(&reg2);

					if (return_value == 0 && return_value2 == 0){
						float left;
						sscanf((yyvsp[-2].ast)->IRcode, "%f", &left);
						float right;
						sscanf((yyvsp[0].ast)->IRcode, "%f", &right);
						float ans = left - right;
						int int_ans = (int)ans;					
						sprintf((yyval.ast)->IRcode, "%d", int_ans);
					}
					else if (return_value != 0 && return_value2 == 0){
						float left;
						char value[50];
						strcpy(value, getValue((yyvsp[-2].ast)->IRcode, theStack));
						sscanf(value, "%f", &left);
						float right;
						sscanf((yyvsp[0].ast)->IRcode, "%f", &right);
						float ans = left - right;
						int int_ans = (int)ans;			
						sprintf((yyval.ast)->IRcode, "%d", int_ans);
					}
					else if (return_value == 0 && return_value2 != 0){
						float left;
						sscanf((yyvsp[-2].ast)->IRcode, "%f", &left);
						float right;
						char value[50];
						strcpy(value, getValue((yyvsp[0].ast)->IRcode, theStack));
						sscanf(value, "%f", &right);
						float ans = left - right;
						int int_ans = (int)ans;					
						sprintf((yyval.ast)->IRcode, "%d", int_ans);
					}
					else if (return_value != 0 && return_value2 != 0){
						float left;
						char value[50];
						strcpy(value, getValue((yyvsp[-2].ast)->IRcode, theStack));
						sscanf(value, "%f", &left);
						float right;
						char value1[50];
						strcpy(value1, getValue((yyvsp[0].ast)->IRcode, theStack));
						sscanf(value1, "%f", &right);
						float ans = left - right;
						int int_ans = (int)ans;					
						sprintf((yyval.ast)->IRcode, "%d", int_ans);
					}
				}
				else{
					char * reg = getRegister();
					char * reg2 = getRegister();
					if (strcmp((yyvsp[-2].ast)->IRcode, (yyvsp[0].ast)->IRcode) == 0){
						freeReg(reg2);
						strcpy((yyval.ast)->IRcode, reg);
						fprintf(MIPS,"move %s, $zero\n", reg);						
						strcpy((yyval.ast)->IRcode, reg); 
					}
					else{
						if (strcmp(getExprType((yyvsp[-2].ast)->IRcode), "int") == 0){
							// li $t0, 2
							fprintf(MIPS,"li %s, %s\n", reg, (yyvsp[-2].ast)->IRcode);
						}
						else if (strcmp(getExprType((yyvsp[-2].ast)->IRcode), "id") == 0){
							char* scope = getScope((yyvsp[-2].ast)->IRcode, theStack);
							// lw $t0, addhehe_f
							fprintf(MIPS,"lw %s, %s_%s\n", reg, scope, (yyvsp[-2].ast)->IRcode);
						}
						else{
							freeReg(reg);
							reg = (yyvsp[-2].ast)->IRcode;
						}

						if (strcmp(getExprType((yyvsp[0].ast)->IRcode), "int") == 0){
							// li $t0, 2
							fprintf(MIPS,"li %s, %s\n", reg2, (yyvsp[0].ast)->IRcode);
						}
						else if (strcmp(getExprType((yyvsp[0].ast)->IRcode), "id") == 0){
							char* scope = getScope((yyvsp[0].ast)->IRcode, theStack);
							// lw $t0, addhehe_f
							fprintf(MIPS,"lw %s, %s_%s\n", reg2, scope, (yyvsp[0].ast)->IRcode);
						}
						else{
							freeReg(reg2);
							reg2 = (yyvsp[0].ast)->IRcode;			
						}

						// sub $t0, $t0, $t1
						fprintf(MIPS,"sub %s, %s, %s\n", reg, reg, reg2);
						freeReg(reg2);
						strcpy((yyval.ast)->IRcode, reg); 
						fprintf(IRcode," %s = %s - %s\n", reg, (yyvsp[-2].ast)->IRcode, (yyvsp[0].ast)->IRcode);
					}
				}
			}
#line 3345 "parser.tab.c"
    break;

  case 48:
#line 1866 "parser.y"
                        {
				/* node for * op */
				(yyval.ast) = AST_node("*");
				(yyval.ast)->left = (yyvsp[-2].ast);
				(yyval.ast)->right = (yyvsp[0].ast);
				
				/* check out code comments on "ID LBRACK Expr RBRACK" rule */
				struct AST* node = (yyvsp[-2].ast);
				char exprType[50]; 
				if ((strcmp(node->nodeType, "!") == 0) || (strcmp(node->nodeType, "==") == 0) || (strcmp(node->nodeType, "!=") == 0) || (strcmp(node->nodeType, "<=") == 0) || (strcmp(node->nodeType, ">=") == 0) || (strcmp(node->nodeType, "&&") == 0) || (strcmp(node->nodeType, "||") == 0) || (strcmp(node->nodeType, "<") == 0) || (strcmp(node->nodeType, ">") == 0)){
					strcpy(exprType, "bool");
				}
				else if ((strcmp(node->nodeType, "+") == 0) || (strcmp(node->nodeType, "-") == 0) || (strcmp(node->nodeType, "*") == 0) || (strcmp(node->nodeType, "/") == 0)){
					strcpy(exprType, "int");
				}
				else if ((strcmp(node->nodeType, "ARR") == 0)){			
					strcpy(exprType, getTypeForArr(node->left->nodeType, theStack));				
				}
				else{
					regex_t reg;
					const char *regex="^[A-Za-z][A-Za-z0-9]*";
					int ret;
					char err[1024];
					//Read data into variable filecontent
					ret = regcomp(&reg, regex, REG_EXTENDED);
					if (ret != 0) {
						regerror(ret, &reg, err, 1024);
						return 1;
					}
					int return_value;
					return_value = regexec(&reg, node->nodeType , 0, NULL, 0);
					regfree(&reg);
					if (return_value == 0){
						strcpy(exprType, getType(node->nodeType, theStack));
					}
					else{
						regex_t reg;
						const char *regex="^-?[0-9]+";
						int ret;
						char err[1024];
						//Read data into variable filecontent
						ret = regcomp(&reg, regex, REG_EXTENDED);
						if (ret != 0) {
							regerror(ret, &reg, err, 1024);
							return 1;
						}
						int return_value;
						return_value = regexec(&reg, node->nodeType , 0, NULL, 0);
						regfree(&reg);
						if (return_value == 0){
							strcpy(exprType, "int");
						}
						else{
              regex_t reg;
              const char *regex="'[a-zA-Z]'";
              int ret;
              char err[1024];
              //Read data into variable filecontent
              ret = regcomp(&reg, regex, REG_EXTENDED);
              if (ret != 0) {
                regerror(ret, &reg, err, 1024);
                return 1;
              }
              int return_value;
              return_value = regexec(&reg, node->nodeType , 0, NULL, 0);
              regfree(&reg);
              if (return_value == 0){
                strcpy(exprType, "char");
              }
              else{
                strcpy(exprType, ""); 
              }
            }
          }
        }
				if (strcmp(exprType, "int") != 0){
					printf("SEMANTIC ERROR: The type of expression must be int || Line: %d || Char: %d\n", lines, chars);
				}				
				/* check out code comments on "ID LBRACK Expr RBRACK" rule */
				node = (yyvsp[0].ast);
				if ((strcmp(node->nodeType, "!") == 0) || (strcmp(node->nodeType, "==") == 0) || (strcmp(node->nodeType, "!=") == 0) || (strcmp(node->nodeType, "<=") == 0) || (strcmp(node->nodeType, ">=") == 0) || (strcmp(node->nodeType, "&&") == 0) || (strcmp(node->nodeType, "||") == 0) || (strcmp(node->nodeType, "<") == 0) || (strcmp(node->nodeType, ">") == 0)){
					strcpy(exprType, "bool");
				}
				else if ((strcmp(node->nodeType, "+") == 0) || (strcmp(node->nodeType, "-") == 0) || (strcmp(node->nodeType, "*") == 0) || (strcmp(node->nodeType, "/") == 0)){
					strcpy(exprType, "int");
				}
				else if ((strcmp(node->nodeType, "ARR") == 0)){			
					strcpy(exprType, getTypeForArr(node->left->nodeType, theStack));				
				}
				else{
					regex_t reg;
					const char *regex="^[A-Za-z][A-Za-z0-9]*";
					int ret;
					char err[1024];
					//Read data into variable filecontent
					ret = regcomp(&reg, regex, REG_EXTENDED);
					if (ret != 0) {
						regerror(ret, &reg, err, 1024);
						return 1;
					}
					int return_value;
					return_value = regexec(&reg, node->nodeType , 0, NULL, 0);
					regfree(&reg);
					if (return_value == 0){
						strcpy(exprType, getType(node->nodeType, theStack));
					}
					else{
						regex_t reg;
						const char *regex="^-?[0-9]+";
						int ret;
						char err[1024];
						//Read data into variable filecontent
						ret = regcomp(&reg, regex, REG_EXTENDED);
						if (ret != 0) {
							regerror(ret, &reg, err, 1024);
							return 1;
						}
						int return_value;
						return_value = regexec(&reg, node->nodeType , 0, NULL, 0);
						regfree(&reg);
						if (return_value == 0){
							strcpy(exprType, "int");
						}
						else{
              regex_t reg;
              const char *regex="'[a-zA-Z]'";
              int ret;
              char err[1024];
              //Read data into variable filecontent
              ret = regcomp(&reg, regex, REG_EXTENDED);
              if (ret != 0) {
                regerror(ret, &reg, err, 1024);
                return 1;
              }
              int return_value;
              return_value = regexec(&reg, node->nodeType , 0, NULL, 0);
              regfree(&reg);
              if (return_value == 0){
                strcpy(exprType, "char");
              }
              else{
                strcpy(exprType, ""); 
              }
            }
          }
        }
				if (strcmp(exprType, "int") != 0){
					printf("SEMANTIC ERROR: The type of expression must be int || Line: %d || Char: %d\n", lines, chars);
				}	


				// /* IR code generation */

				if (strcmp(top(theStack), "main") == 0){
					regex_t reg;
					const char *regex="^-?[0-9]+";
					int ret;
					char err[1024];
					//Read data into variable filecontent
					ret = regcomp(&reg, regex, REG_EXTENDED);
					if (ret != 0) {
						regerror(ret, &reg, err, 1024);
						return 1;
					}
					int return_value;
					return_value = regexec(&reg, (yyvsp[-2].ast)->IRcode , 0, NULL, 0);
					regfree(&reg);
					
					regex_t reg2;
					const char *regex2="^-?[0-9]+";
					int ret2;
					char err2[1024];
					//Read data into variable filecontent
					ret2 = regcomp(&reg2, regex2, REG_EXTENDED);
					if (ret2 != 0) {
						regerror(ret2, &reg2, err2, 1024);
						return 1;
					}
					int return_value2;
					return_value2 = regexec(&reg2, (yyvsp[0].ast)->IRcode , 0, NULL, 0);
					regfree(&reg2);

					if (return_value == 0 && return_value2 == 0){
						float left;
						sscanf((yyvsp[-2].ast)->IRcode, "%f", &left);
						float right;
						sscanf((yyvsp[0].ast)->IRcode, "%f", &right);
						float ans = left * right;
						int int_ans = (int)ans;					
						sprintf((yyval.ast)->IRcode, "%d", int_ans);
					}
					else if (return_value != 0 && return_value2 == 0){
						float left;
						char value[50];
						strcpy(value, getValue((yyvsp[-2].ast)->IRcode, theStack));
						sscanf(value, "%f", &left);
						float right;
						sscanf((yyvsp[0].ast)->IRcode, "%f", &right);
						float ans = left * right;
						int int_ans = (int)ans;			
						sprintf((yyval.ast)->IRcode, "%d", int_ans);
					}
					else if (return_value == 0 && return_value2 != 0){
						float left;
						sscanf((yyvsp[-2].ast)->IRcode, "%f", &left);
						float right;
						char value[50];
						strcpy(value, getValue((yyvsp[0].ast)->IRcode, theStack));
						sscanf(value, "%f", &right);
						float ans = left * right;
						int int_ans = (int)ans;					
						sprintf((yyval.ast)->IRcode, "%d", int_ans);
					}
					else if (return_value != 0 && return_value2 != 0){
						float left;
						char value[50];
						strcpy(value, getValue((yyvsp[-2].ast)->IRcode, theStack));
						sscanf(value, "%f", &left);
						float right;
						char value1[50];
						strcpy(value1, getValue((yyvsp[0].ast)->IRcode, theStack));
						sscanf(value1, "%f", &right);
						float ans = left * right;
						int int_ans = (int)ans;					
						sprintf((yyval.ast)->IRcode, "%d", int_ans);
					}
				}
				else{
					char * reg = getRegister();
					char * reg2 = getRegister();

					if (strcmp(getExprType((yyvsp[-2].ast)->IRcode), "int") == 0){
						if (strcmp((yyvsp[-2].ast)->IRcode, "1") != 0){
							// li $t0, 2
							fprintf(MIPS,"li %s, %s\n", reg, (yyvsp[-2].ast)->IRcode);
						}
						else{
							freeReg(reg);
							reg = "";
						}
					}
					else if (strcmp(getExprType((yyvsp[-2].ast)->IRcode), "id") == 0){
						char* scope = getScope((yyvsp[-2].ast)->IRcode, theStack);
						// lw $t0, addhehe_f
						fprintf(MIPS,"lw %s, %s_%s\n", reg, scope, (yyvsp[-2].ast)->IRcode);
					}
					else{
						freeReg(reg);
						reg = (yyvsp[-2].ast)->IRcode;
					}

					if (strcmp(getExprType((yyvsp[0].ast)->IRcode), "int") == 0){
						if (strcmp((yyvsp[0].ast)->IRcode, "1") != 0){
							// li $t0, 2
							fprintf(MIPS,"li %s, %s\n", reg2, (yyvsp[0].ast)->IRcode);
						}
						else{
							freeReg(reg2);
							reg2 = "";
						}
					}
					else if (strcmp(getExprType((yyvsp[0].ast)->IRcode), "id") == 0){
						char* scope = getScope((yyvsp[0].ast)->IRcode, theStack);
						// lw $t0, addhehe_f
						fprintf(MIPS,"lw %s, %s_%s\n", reg2, scope, (yyvsp[0].ast)->IRcode);
					}
					else{
						freeReg(reg2);
						reg2 = (yyvsp[0].ast)->IRcode;			
					}

					// mul $t0, $t0, $t1
					if (strcmp(reg, "") != 0 && strcmp(reg2, "") != 0)
					{
						fprintf(MIPS,"mul %s, %s, %s\n", reg, reg, reg2);
						freeReg(reg2);
						strcpy((yyval.ast)->IRcode, reg); 
						fprintf(IRcode," %s = %s * %s\n", reg, (yyvsp[-2].ast)->IRcode, (yyvsp[0].ast)->IRcode);
					}
					else if (strcmp(reg, "") == 0 && strcmp(reg2, "") != 0){
						freeReg(reg);
						strcpy((yyval.ast)->IRcode, reg2); 
					}
					else if (strcmp(reg, "") != 0 && strcmp(reg2, "") == 0){
						freeReg(reg2);
						strcpy((yyval.ast)->IRcode, reg); 
					}
					else{
						// li $t0, 1 
						reg = getRegister();
						fprintf(MIPS,"li %s, 1\n", reg);
						strcpy((yyval.ast)->IRcode, reg); 
					}
				}
			}
#line 3645 "parser.tab.c"
    break;

  case 49:
#line 2162 "parser.y"
                        {
				/* node for / op */
				(yyval.ast) = AST_node("/");
				(yyval.ast)->left = (yyvsp[-2].ast);
				(yyval.ast)->right = (yyvsp[0].ast);
				
				/* check out code comments on "ID LBRACK Expr RBRACK" rule */
				struct AST* node = (yyvsp[-2].ast);
				char exprType[50]; 
				if ((strcmp(node->nodeType, "!") == 0) || (strcmp(node->nodeType, "==") == 0) || (strcmp(node->nodeType, "!=") == 0) || (strcmp(node->nodeType, "<=") == 0) || (strcmp(node->nodeType, ">=") == 0) || (strcmp(node->nodeType, "&&") == 0) || (strcmp(node->nodeType, "||") == 0) || (strcmp(node->nodeType, "<") == 0) || (strcmp(node->nodeType, ">") == 0)){
					strcpy(exprType, "bool");
				}
				else if ((strcmp(node->nodeType, "+") == 0) || (strcmp(node->nodeType, "-") == 0) || (strcmp(node->nodeType, "*") == 0) || (strcmp(node->nodeType, "/") == 0)){
					strcpy(exprType, "int");
				}
				else if ((strcmp(node->nodeType, "ARR") == 0)){			
					strcpy(exprType, getTypeForArr(node->left->nodeType, theStack));				
				}
				else{
					regex_t reg;
					const char *regex="^[A-Za-z][A-Za-z0-9]*";
					int ret;
					char err[1024];
					//Read data into variable filecontent
					ret = regcomp(&reg, regex, REG_EXTENDED);
					if (ret != 0) {
						regerror(ret, &reg, err, 1024);
						return 1;
					}
					int return_value;
					return_value = regexec(&reg, node->nodeType , 0, NULL, 0);
					regfree(&reg);
					if (return_value == 0){
						strcpy(exprType, getType(node->nodeType, theStack));
					}
					else{
						regex_t reg;
						const char *regex="^-?[0-9]+";
						int ret;
						char err[1024];
						//Read data into variable filecontent
						ret = regcomp(&reg, regex, REG_EXTENDED);
						if (ret != 0) {
							regerror(ret, &reg, err, 1024);
							return 1;
						}
						int return_value;
						return_value = regexec(&reg, node->nodeType , 0, NULL, 0);
						regfree(&reg);
						if (return_value == 0){
							strcpy(exprType, "int");
						}
						else{
              regex_t reg;
              const char *regex="'[a-zA-Z]'";
              int ret;
              char err[1024];
              //Read data into variable filecontent
              ret = regcomp(&reg, regex, REG_EXTENDED);
              if (ret != 0) {
                regerror(ret, &reg, err, 1024);
                return 1;
              }
              int return_value;
              return_value = regexec(&reg, node->nodeType , 0, NULL, 0);
              regfree(&reg);
              if (return_value == 0){
                strcpy(exprType, "char");
              }
              else{
                strcpy(exprType, ""); 
              }
            }
          }
        }
				if (strcmp(exprType, "int") != 0){
					printf("SEMANTIC ERROR: The type of expression must be int || Line: %d || Char: %d\n", lines, chars);
				}				
				/* check out code comments on "ID LBRACK Expr RBRACK" rule */				
				node = (yyvsp[0].ast);
				if ((strcmp(node->nodeType, "!") == 0) || (strcmp(node->nodeType, "==") == 0) || (strcmp(node->nodeType, "!=") == 0) || (strcmp(node->nodeType, "<=") == 0) || (strcmp(node->nodeType, ">=") == 0) || (strcmp(node->nodeType, "&&") == 0) || (strcmp(node->nodeType, "||") == 0) || (strcmp(node->nodeType, "<") == 0) || (strcmp(node->nodeType, ">") == 0)){
					strcpy(exprType, "bool");
				}
				else if ((strcmp(node->nodeType, "+") == 0) || (strcmp(node->nodeType, "-") == 0) || (strcmp(node->nodeType, "*") == 0) || (strcmp(node->nodeType, "/") == 0)){
					strcpy(exprType, "int");
				}
				else if ((strcmp(node->nodeType, "ARR") == 0)){			
					strcpy(exprType, getTypeForArr(node->left->nodeType, theStack));				
				}
				else{
					regex_t reg;
					const char *regex="^[A-Za-z][A-Za-z0-9]*";
					int ret;
					char err[1024];
					//Read data into variable filecontent
					ret = regcomp(&reg, regex, REG_EXTENDED);
					if (ret != 0) {
						regerror(ret, &reg, err, 1024);
						return 1;
					}
					int return_value;
					return_value = regexec(&reg, node->nodeType , 0, NULL, 0);
					regfree(&reg);
					if (return_value == 0){
						strcpy(exprType, getType(node->nodeType, theStack));
					}
					else{
						regex_t reg;
						const char *regex="^-?[0-9]+";
						int ret;
						char err[1024];
						//Read data into variable filecontent
						ret = regcomp(&reg, regex, REG_EXTENDED);
						if (ret != 0) {
							regerror(ret, &reg, err, 1024);
							return 1;
						}
						int return_value;
						return_value = regexec(&reg, node->nodeType , 0, NULL, 0);
						regfree(&reg);
						if (return_value == 0){
							strcpy(exprType, "int");
						}
						else{
              regex_t reg;
              const char *regex="'[a-zA-Z]'";
              int ret;
              char err[1024];
              //Read data into variable filecontent
              ret = regcomp(&reg, regex, REG_EXTENDED);
              if (ret != 0) {
                regerror(ret, &reg, err, 1024);
                return 1;
              }
              int return_value;
              return_value = regexec(&reg, node->nodeType , 0, NULL, 0);
              regfree(&reg);
              if (return_value == 0){
                strcpy(exprType, "char");
              }
              else{
                strcpy(exprType, ""); 
              }
            }
          }
        }
				if (strcmp(exprType, "int") != 0){
					printf("SEMANTIC ERROR: The type of expression must be int || Line: %d || Char: %d\n", lines, chars);
				}			

				


				// /* IR code generation */
				
				if (strcmp(top(theStack), "main") == 0){
					regex_t reg;
					const char *regex="^-?[0-9]+";
					int ret;
					char err[1024];
					//Read data into variable filecontent
					ret = regcomp(&reg, regex, REG_EXTENDED);
					if (ret != 0) {
						regerror(ret, &reg, err, 1024);
						return 1;
					}
					int return_value;
					return_value = regexec(&reg, (yyvsp[-2].ast)->IRcode , 0, NULL, 0);
					regfree(&reg);
					
					regex_t reg2;
					const char *regex2="^-?[0-9]+";
					int ret2;
					char err2[1024];
					//Read data into variable filecontent
					ret2 = regcomp(&reg2, regex2, REG_EXTENDED);
					if (ret2 != 0) {
						regerror(ret2, &reg2, err2, 1024);
						return 1;
					}
					int return_value2;
					return_value2 = regexec(&reg2, (yyvsp[0].ast)->IRcode , 0, NULL, 0);
					regfree(&reg2);

					if (return_value == 0 && return_value2 == 0){
						float left;
						sscanf((yyvsp[-2].ast)->IRcode, "%f", &left);
						float right;
						sscanf((yyvsp[0].ast)->IRcode, "%f", &right);
						float ans = left / right;
						int int_ans = (int)ans;					
						sprintf((yyval.ast)->IRcode, "%d", int_ans);
					}
					else if (return_value != 0 && return_value2 == 0){
						float left;
						char value[50];
						strcpy(value, getValue((yyvsp[-2].ast)->IRcode, theStack));
						sscanf(value, "%f", &left);
						float right;
						sscanf((yyvsp[0].ast)->IRcode, "%f", &right);
						float ans = left / right;
						int int_ans = (int)ans;			
						sprintf((yyval.ast)->IRcode, "%d", int_ans);
					}
					else if (return_value == 0 && return_value2 != 0){
						float left;
						sscanf((yyvsp[-2].ast)->IRcode, "%f", &left);
						float right;
						char value[50];
						strcpy(value, getValue((yyvsp[0].ast)->IRcode, theStack));
						sscanf(value, "%f", &right);
						float ans = left / right;
						int int_ans = (int)ans;					
						sprintf((yyval.ast)->IRcode, "%d", int_ans);
					}
					else if (return_value != 0 && return_value2 != 0){
						float left;
						char value[50];
						strcpy(value, getValue((yyvsp[-2].ast)->IRcode, theStack));
						sscanf(value, "%f", &left);
						float right;
						char value1[50];
						strcpy(value1, getValue((yyvsp[0].ast)->IRcode, theStack));
						sscanf(value1, "%f", &right);
						float ans = left / right;
						int int_ans = (int)ans;					
						sprintf((yyval.ast)->IRcode, "%d", int_ans);
					}
				}
				else{
					char * reg = getRegister();
					char * reg2 = getRegister();

					if (strcmp(getExprType((yyvsp[-2].ast)->IRcode), "int") == 0){
						// li $t0, 2
						fprintf(MIPS,"li %s, %s\n", reg, (yyvsp[-2].ast)->IRcode);
					}
					else if (strcmp(getExprType((yyvsp[-2].ast)->IRcode), "id") == 0){
						char* scope = getScope((yyvsp[-2].ast)->IRcode, theStack);
						// lw $t0, addhehe_f
						fprintf(MIPS,"lw %s, %s_%s\n", reg, scope, (yyvsp[-2].ast)->IRcode);
					}
					else{
						freeReg(reg);
						reg = (yyvsp[-2].ast)->IRcode;
					}

					if (strcmp(getExprType((yyvsp[0].ast)->IRcode), "int") == 0){
						if (strcmp((yyvsp[0].ast)->IRcode, "1") != 0){
							// li $t0, 2
							fprintf(MIPS,"li %s, %s\n", reg2, (yyvsp[0].ast)->IRcode);
						}
						else{
							freeReg(reg2);
							reg2 = "";
						}
					}
					else if (strcmp(getExprType((yyvsp[0].ast)->IRcode), "id") == 0){
						char* scope = getScope((yyvsp[0].ast)->IRcode, theStack);
						// lw $t0, addhehe_f
						fprintf(MIPS,"lw %s, %s_%s\n", reg2, scope, (yyvsp[0].ast)->IRcode);
					}
					else{
						freeReg(reg2);
						reg2 = (yyvsp[0].ast)->IRcode;			
					}

					if (strcmp(reg2, "") != 0){				
						// div $t0, $t1
						// mflo $t0
						fprintf(MIPS,"div %s, %s\n", reg, reg2);
						fprintf(MIPS,"mflo %s\n", reg);
						freeReg(reg2);
						strcpy((yyval.ast)->IRcode, reg); 
						fprintf(IRcode," %s = %s / %s\n", reg, (yyvsp[-2].ast)->IRcode, (yyvsp[0].ast)->IRcode);
					}
					else {
						strcpy((yyval.ast)->IRcode, reg); 
					}
				}

			}
#line 3932 "parser.tab.c"
    break;

  case 50:
#line 2445 "parser.y"
                        {	
				printf("RECOGNIZED RULE: Variable Value Assignment || %s || Line: %d || Char: %d\n", (yyvsp[-2].string), lines, chars);
				(yyval.ast) = AST_node("EQ");
				(yyval.ast)->left = AST_node((yyvsp[-2].string));
				(yyval.ast)->right = (yyvsp[0].ast);

				// Symbol Table
				symTabAccess();
				int inSymTab = 0;
				struct stack_entry *entry = malloc(sizeof *entry); 
				entry = theStack->head;
				while (entry != NULL){
					inSymTab = found((yyvsp[-2].string), entry->data);
					if (inSymTab != 0){
						break;
					}
					entry = entry->next;
				}
				printf("looking for %s in symtab - found: %d \n", (yyvsp[-2].string), inSymTab);
				if (inSymTab == 0) 
				{
					printf("SEMANTIC ERROR: Varible %s was not declared || Line: %d || Char: %d\n", (yyvsp[-2].string), lines, chars);
				}	

				struct AST* node = (yyvsp[0].ast);
				char exprTypeForIR[50] = "";
				char exprType[50]; 
				if ((strcmp(node->nodeType, "!") == 0) || (strcmp(node->nodeType, "==") == 0) || (strcmp(node->nodeType, "!=") == 0) || (strcmp(node->nodeType, "<=") == 0) || (strcmp(node->nodeType, ">=") == 0) || (strcmp(node->nodeType, "&&") == 0) || (strcmp(node->nodeType, "||") == 0) || (strcmp(node->nodeType, "<") == 0) || (strcmp(node->nodeType, ">") == 0)){
					strcpy(exprType, "bool");
				}
				else if ((strcmp(node->nodeType, "+") == 0) || (strcmp(node->nodeType, "-") == 0) || (strcmp(node->nodeType, "*") == 0) || (strcmp(node->nodeType, "/") == 0)){
					strcpy(exprType, "int");
				}
				else if ((strcmp(node->nodeType, "ARR") == 0)){			
					strcpy(exprType, getTypeForArr(node->left->nodeType, theStack));
					strcpy(exprTypeForIR, "arr");				
				}
				else{
					regex_t reg;
					const char *regex="^[A-Za-z][A-Za-z0-9]*";
					int ret;
					char err[1024];
					//Read data into variable filecontent
					ret = regcomp(&reg, regex, REG_EXTENDED);
					if (ret != 0) {
						regerror(ret, &reg, err, 1024);
						return 1;
					}
					int return_value;
					return_value = regexec(&reg, node->nodeType , 0, NULL, 0);
					regfree(&reg);
					if (return_value == 0){
						strcpy(exprType, getType(node->nodeType, theStack));
					}
					else{
						regex_t reg;
						const char *regex="^-?[0-9]+";
						int ret;
						char err[1024];
						//Read data into variable filecontent
						ret = regcomp(&reg, regex, REG_EXTENDED);
						if (ret != 0) {
							regerror(ret, &reg, err, 1024);
							return 1;
						}
						int return_value;
						return_value = regexec(&reg, node->nodeType , 0, NULL, 0);
						regfree(&reg);
						if (return_value == 0){
							strcpy(exprType, "int");
						}
						else{
							regex_t reg;
							const char *regex="'[a-zA-Z]'";
							int ret;
							char err[1024];
							//Read data into variable filecontent
							ret = regcomp(&reg, regex, REG_EXTENDED);
							if (ret != 0) {
								regerror(ret, &reg, err, 1024);
								return 1;
							}
							int return_value;
							return_value = regexec(&reg, node->nodeType , 0, NULL, 0);
							regfree(&reg);
							if (return_value == 0){
								strcpy(exprType, "char");
							}
							else{
								strcpy(exprType, "");	
								strcpy(exprTypeForIR, "");	
							}
						}
					}
				}
			
				char idType[50]; 
				strcpy(idType, getType((yyvsp[-2].string), theStack));
				if (strcmp(exprType, idType) != 0){
					printf("SEMANTIC ERROR: The operands of EQ op must have the same type || Line: %d || Char: %d\n", lines, chars);
				}






				
				// IR code
			
				setVar((yyvsp[-2].string), (yyval.ast)->right->IRcode);
				regex_t reg;
				const char *regex="^-?[0-9]+";
				int ret;
				char err[1024];
				//Read data into variable filecontent
				ret = regcomp(&reg, regex, REG_EXTENDED);
				if (ret != 0) {
					regerror(ret, &reg, err, 1024);
					return 1;
				}
				int return_value;
				return_value = regexec(&reg, node->IRcode , 0, NULL, 0);
				regfree(&reg);
				if (return_value == 0){
					char* scope = getScope((yyvsp[-2].string), theStack);
					assignNumber((yyvsp[-2].string), (yyvsp[0].ast)->IRcode, scope);
					setValue((yyvsp[-2].string), (yyvsp[0].ast)->IRcode, theStack);
					showSymTable();
				}
				else{
					regex_t reg;
					const char *regex="^[$][tv][0-9]$";
					int ret;
					char err[1024];
					//Read data into variable filecontent
					ret = regcomp(&reg, regex, REG_EXTENDED);
					if (ret != 0) {
						regerror(ret, &reg, err, 1024);
						return 1;
					}
					int return_value;
					return_value = regexec(&reg, node->IRcode , 0, NULL, 0);
					regfree(&reg);
					if (return_value == 0){
						char* scope = getScope((yyvsp[-2].string), theStack);
						assignReg((yyvsp[-2].string), (yyvsp[0].ast)->IRcode, scope);
					}
					else{
						char* scopeL = getScope((yyvsp[-2].string), theStack);
						char* scopeR = getScope((yyvsp[0].ast)->IRcode, theStack);
						assignID((yyvsp[-2].string), (yyvsp[0].ast)->IRcode, scopeL, scopeR);
						char value[50];
						strcpy(value, getValue((yyvsp[0].ast)->IRcode, theStack));
						setValue((yyvsp[-2].string), value, theStack);
						showSymTable();
					}
				}

			}
#line 4097 "parser.tab.c"
    break;

  case 51:
#line 2607 "parser.y"
                        {
				printf("RECOGNIZED RULE: Variable Array Value Assignment:  || %s || Line: %d || Char: %d\n", (yyvsp[-5].string), lines, chars);
				(yyval.ast) = AST_node("EQ");
				(yyval.ast)->left = AST_node("ARR");
				(yyval.ast)->left->left = AST_node((yyvsp[-5].string));
				(yyval.ast)->left->right = (yyvsp[-3].ast);
				(yyval.ast)->right = (yyvsp[0].ast);

				if (!isArray((yyvsp[-5].string), theStack)){
					printf("SEMANTIC ERROR: Variable must be an array variable || Line: %d || Char: %d\n", lines, chars);
				}

				struct AST* node = (yyvsp[-3].ast);
				char exprType[50]; 
				if ((strcmp(node->nodeType, "!") == 0) || (strcmp(node->nodeType, "==") == 0) || (strcmp(node->nodeType, "!=") == 0) || (strcmp(node->nodeType, "<=") == 0) || (strcmp(node->nodeType, ">=") == 0) || (strcmp(node->nodeType, "&&") == 0) || (strcmp(node->nodeType, "||") == 0) || (strcmp(node->nodeType, "<") == 0) || (strcmp(node->nodeType, ">") == 0)){
					strcpy(exprType, "bool");
				}
				else if ((strcmp(node->nodeType, "+") == 0) || (strcmp(node->nodeType, "-") == 0) || (strcmp(node->nodeType, "*") == 0) || (strcmp(node->nodeType, "/") == 0)){
					strcpy(exprType, "int");
				}
				else if ((strcmp(node->nodeType, "ARR") == 0)){			
					strcpy(exprType, getTypeForArr(node->left->nodeType, theStack));				
				}
				else{
					regex_t reg;
					const char *regex="^[A-Za-z][A-Za-z0-9]*";
					int ret;
					char err[1024];
					//Read data into variable filecontent
					ret = regcomp(&reg, regex, REG_EXTENDED);
					if (ret != 0) {
						regerror(ret, &reg, err, 1024);
						return 1;
					}
					int return_value;
					return_value = regexec(&reg, node->nodeType , 0, NULL, 0);
					regfree(&reg);
					if (return_value == 0){
						strcpy(exprType, getType(node->nodeType, theStack));
					}
					else{
						regex_t reg;
						const char *regex="^-?[0-9]+";
						int ret;
						char err[1024];
						//Read data into variable filecontent
						ret = regcomp(&reg, regex, REG_EXTENDED);
						if (ret != 0) {
							regerror(ret, &reg, err, 1024);
							return 1;
						}
						int return_value;
						return_value = regexec(&reg, node->nodeType , 0, NULL, 0);
						regfree(&reg);
						if (return_value == 0){
							strcpy(exprType, "int");
						}
					else{	
              regex_t reg;
              const char *regex="'[a-zA-Z]'";
              int ret;
              char err[1024];
              //Read data into variable filecontent
              ret = regcomp(&reg, regex, REG_EXTENDED);
              if (ret != 0) {
                regerror(ret, &reg, err, 1024);
                return 1;
              }
              int return_value;
              return_value = regexec(&reg, node->nodeType , 0, NULL, 0);
              regfree(&reg);
              if (return_value == 0){
                strcpy(exprType, "char");
              }
              else{
                strcpy(exprType, ""); 
              }
            }
          }
        }
				if (strcmp(exprType, "int") != 0){
					printf("SEMANTIC ERROR: The type of expression must be int || Line: %d || Char: %d\n", lines, chars);
				}				

				node = (yyvsp[0].ast);
				if ((strcmp(node->nodeType, "!") == 0) || (strcmp(node->nodeType, "==") == 0) || (strcmp(node->nodeType, "!=") == 0) || (strcmp(node->nodeType, "<=") == 0) || (strcmp(node->nodeType, ">=") == 0) || (strcmp(node->nodeType, "&&") == 0) || (strcmp(node->nodeType, "||") == 0) || (strcmp(node->nodeType, "<") == 0) || (strcmp(node->nodeType, ">") == 0)){
					strcpy(exprType, "bool");
				}
				else if ((strcmp(node->nodeType, "+") == 0) || (strcmp(node->nodeType, "-") == 0) || (strcmp(node->nodeType, "*") == 0) || (strcmp(node->nodeType, "/") == 0)){
					strcpy(exprType, "int");
				}
				else if ((strcmp(node->nodeType, "ARR") == 0)){			
					strcpy(exprType, getTypeForArr(node->left->nodeType, theStack));				
				}
				else{
					regex_t reg;
					const char *regex="^[A-Za-z][A-Za-z0-9]*";
					int ret;
					char err[1024];
					//Read data into variable filecontent
					ret = regcomp(&reg, regex, REG_EXTENDED);
					if (ret != 0) {
						regerror(ret, &reg, err, 1024);
						return 1;
					}
					int return_value;
					return_value = regexec(&reg, node->nodeType , 0, NULL, 0);
					regfree(&reg);
					if (return_value == 0){
						strcpy(exprType, getType(node->nodeType, theStack));
					}
					else{
						regex_t reg;
						const char *regex="^-?[0-9]+";
						int ret;
						char err[1024];
						//Read data into variable filecontent
						ret = regcomp(&reg, regex, REG_EXTENDED);
						if (ret != 0) {
							regerror(ret, &reg, err, 1024);
							return 1;
						}
						int return_value;
						return_value = regexec(&reg, node->nodeType , 0, NULL, 0);
						regfree(&reg);
						if (return_value == 0){
							strcpy(exprType, "int");
						}
					else{
              regex_t reg;
              const char *regex="'[a-zA-Z]'";
              int ret;
              char err[1024];
              //Read data into variable filecontent
              ret = regcomp(&reg, regex, REG_EXTENDED);
              if (ret != 0) {
                regerror(ret, &reg, err, 1024);
                return 1;
              }
              int return_value;
              return_value = regexec(&reg, node->nodeType , 0, NULL, 0);
              regfree(&reg);
              if (return_value == 0){
                strcpy(exprType, "char");
              }
              else{
                strcpy(exprType, ""); 
              }
            }
          }
        }
				char idType[50]; 
				strcpy(idType, getTypeForArr((yyvsp[-5].string), theStack));
				if (strcmp(exprType, idType) != 0){
					printf("SEMANTIC ERROR: The operands of EQ op must have the same type || Line: %d || Char: %d\n", lines, chars);
				}				
				
				// // IR code
				char* line;
				char line1[500] = "";
				strcat(line1, (yyvsp[-5].string));
				strcat(line1, "[");
				strcat(line1, (yyvsp[-3].ast)->IRcode);
				strcat(line1,"]");
				line = line1;
				setVar(line1, (yyval.ast)->right->IRcode);
				freeReg((yyvsp[-3].ast)->IRcode);

				char * reg = getRegister();
				char * reg2 = getRegister();

				if (strcmp(getExprType((yyvsp[-3].ast)->IRcode), "int") == 0){
					assignArrayWithNumInBrackets((yyvsp[-3].ast)->IRcode, reg);
				}
				else if (strcmp(getExprType((yyvsp[-3].ast)->IRcode), "id") == 0){
					char* scope = getScope((yyvsp[-3].ast)->IRcode, theStack);
					assignArrayWithIdInBrackets((yyvsp[-3].ast)->IRcode, scope, reg);
				}
				else{
					assignArrayWithRegInBrackets((yyvsp[-3].ast)->IRcode, reg);
				}
				
				if (strcmp(getExprType((yyvsp[0].ast)->IRcode), "int") == 0){
					assignArrayToInt((yyvsp[0].ast)->IRcode, reg2);
					if (strcmp(getExprType((yyvsp[-3].ast)->IRcode), "int") == 0){
						// add var onto the symbol table
						char varNameHolder[90];
						strcpy(varNameHolder, (yyvsp[-5].string));
						strcat(varNameHolder, "[");
						strcat(varNameHolder, (yyvsp[-3].ast)->IRcode);
						strcat(varNameHolder, "]");
						
						char* varScope = getScope((yyvsp[-5].string), theStack);
						
						char * varType = getTypeForArr((yyvsp[-5].string), theStack);

						if (found(varNameHolder, varScope) == 0){
							addItem(varNameHolder, "Var", varType, "", varScope, "", (yyvsp[0].ast)->IRcode);
						}
						else{
							setValue(varNameHolder, (yyvsp[0].ast)->IRcode, theStack);
						}
						
					}
					else if (strcmp(getExprType((yyvsp[-3].ast)->IRcode), "id") == 0){
						// add var onto the symbol table
						char varNameHolder[90];
						strcpy(varNameHolder, (yyvsp[-5].string));
						strcat(varNameHolder, "[");
						char * index = getValue((yyvsp[-3].ast)->IRcode, theStack);
						strcat(varNameHolder, index);
						strcat(varNameHolder, "]");
						
						char* varScope = getScope((yyvsp[-5].string), theStack);
						
						char * varType = getTypeForArr((yyvsp[-5].string), theStack);
						
						if (found(varNameHolder, varScope) == 0){
							addItem(varNameHolder, "Var", varType, "", varScope, "", (yyvsp[0].ast)->IRcode);
						}
						else{
							setValue(varNameHolder, (yyvsp[0].ast)->IRcode, theStack);
						}

					}
				}
				else if (strcmp(getExprType((yyvsp[0].ast)->IRcode), "id") == 0){
					char* scope = getScope((yyvsp[0].ast)->IRcode, theStack);
					assignArrayToId((yyvsp[0].ast)->IRcode, scope, reg2);

					if (strcmp(getExprType((yyvsp[-3].ast)->IRcode), "int") == 0){
						// add var onto the symbol table
						char varNameHolder[90];
						strcpy(varNameHolder, (yyvsp[-5].string));
						strcat(varNameHolder, "[");
						strcat(varNameHolder, (yyvsp[-3].ast)->IRcode);
						strcat(varNameHolder, "]");
						
						char* varScope = getScope((yyvsp[-5].string), theStack);
						
						char * varType = getTypeForArr((yyvsp[-5].string), theStack);
						
						char * varValue = getValue((yyvsp[0].ast)->IRcode, theStack);

						if (found(varNameHolder, varScope) == 0){
							addItem(varNameHolder, "Var", varType, "", varScope, "", varValue);
						}
						else{
							setValue(varNameHolder, varValue, theStack);
						}
					}
					else if (strcmp(getExprType((yyvsp[-3].ast)->IRcode), "id") == 0){
						// add var onto the symbol table
						char varNameHolder[90];
						strcpy(varNameHolder, (yyvsp[-5].string));
						strcat(varNameHolder, "[");
						char * index = getValue((yyvsp[-3].ast)->IRcode, theStack);
						strcat(varNameHolder, index);
						strcat(varNameHolder, "]");
						
						char* varScope = getScope((yyvsp[-5].string), theStack);
						
						char * varType = getTypeForArr((yyvsp[-5].string), theStack);
						
						char * varValue = getValue((yyvsp[0].ast)->IRcode, theStack);

						if (found(varNameHolder, varScope) == 0){
							addItem(varNameHolder, "Var", varType, "", varScope, "", varValue);
						}
						else{
							setValue(varNameHolder, varValue, theStack);
						}
					}
				}
				else{
					assignArrayToReg((yyvsp[0].ast)->IRcode, reg2);
				}
				char* scope = getScope((yyvsp[-5].string), theStack);
				assignArrayToExpr((yyvsp[-5].string), scope, reg, reg2);
				freeReg(reg);
				freeReg(reg2);
				
			}
#line 4385 "parser.tab.c"
    break;

  case 52:
#line 2891 "parser.y"
                        {
				printf("SYNTAX ERROR: Missing Expr in Variable Value Assignment || Line: %d || Char: %d\n", lines, chars);
			}
#line 4393 "parser.tab.c"
    break;

  case 53:
#line 2895 "parser.y"
                {
			printf("SYNTAX ERROR: Missing Expr in Variable Array Value Assignment || Line: %d || Char: %d\n", lines, chars);
		}
#line 4401 "parser.tab.c"
    break;

  case 54:
#line 2903 "parser.y"
                        {
				(yyval.ast) = AST_node((yyvsp[0].string));
			}
#line 4409 "parser.tab.c"
    break;

  case 56:
#line 2908 "parser.y"
                        {
				printf("SYNTAX ERROR: Missing SEMICOLON || Line: %d || Char: %d\n", lines, chars);
			}
#line 4417 "parser.tab.c"
    break;

  case 57:
#line 2912 "parser.y"
                        {
				(yyval.ast) = AST_node("RETURN");
				(yyval.ast)->left = (yyvsp[-1].ast);
				printf("RECOGNIZED RULE: RETURN || Line: %d || Char: %d\n", lines, chars);

				struct AST* node = (yyvsp[-1].ast);
				char exprType[50]; 
				if ((strcmp(node->nodeType, "!") == 0) || (strcmp(node->nodeType, "==") == 0) || (strcmp(node->nodeType, "!=") == 0) || (strcmp(node->nodeType, "<=") == 0) || (strcmp(node->nodeType, ">=") == 0) || (strcmp(node->nodeType, "&&") == 0) || (strcmp(node->nodeType, "||") == 0) || (strcmp(node->nodeType, "<") == 0) || (strcmp(node->nodeType, ">") == 0)){
					strcpy(exprType, "bool");
				}
				else if ((strcmp(node->nodeType, "+") == 0) || (strcmp(node->nodeType, "-") == 0) || (strcmp(node->nodeType, "*") == 0) || (strcmp(node->nodeType, "/") == 0)){
					strcpy(exprType, "int");
				}
				else if ((strcmp(node->nodeType, "ARR") == 0)){			
					strcpy(exprType, getTypeForArr(node->left->nodeType, theStack));				
				}
				else{
					regex_t reg;
					const char *regex="^[A-Za-z][A-Za-z0-9]*";
					int ret;
					char err[1024];
					//Read data into variable filecontent
					ret = regcomp(&reg, regex, REG_EXTENDED);
					if (ret != 0) {
						regerror(ret, &reg, err, 1024);
						return 1;
					}
					int return_value;
					return_value = regexec(&reg, node->nodeType , 0, NULL, 0);
					regfree(&reg);
					if (return_value == 0){
						strcpy(exprType, getType(node->nodeType, theStack));
					}
					else{
						regex_t reg;
						const char *regex="^-?[0-9]+";
						int ret;
						char err[1024];
						//Read data into variable filecontent
						ret = regcomp(&reg, regex, REG_EXTENDED);
						if (ret != 0) {
							regerror(ret, &reg, err, 1024);
							return 1;
						}
						int return_value;
						return_value = regexec(&reg, node->nodeType , 0, NULL, 0);
						regfree(&reg);
						if (return_value == 0){
							strcpy(exprType, "int");
						}
						else{
              regex_t reg;
              const char *regex="'[a-zA-Z]'";
              int ret;
              char err[1024];
              //Read data into variable filecontent
              ret = regcomp(&reg, regex, REG_EXTENDED);
              if (ret != 0) {
                regerror(ret, &reg, err, 1024);
                return 1;
              }
              int return_value;
              return_value = regexec(&reg, node->nodeType , 0, NULL, 0);
              regfree(&reg);
              if (return_value == 0){
                strcpy(exprType, "char");
              }
              else{
                strcpy(exprType, ""); 
              }
            }
          }
        }
				char funcType[50];
				strcpy(funcType, getType(top(theStack), theStack));
				if (strcmp(exprType, funcType) != 0){
					printf("SEMANTIC ERROR: The expression in a return statement must have the same type as the declared result type of the enclosing function definition. Function type: %s. Return: %s || Line: %d || Char: %d\n",funcType, exprType, lines, chars);
				}
				// IR code
				// v0 = $2->IRcode
				freeReg((yyvsp[-1].ast)->IRcode);
				char* line;
				char line1[500] = "";
				strcat(line1, "v0 = ");
				strcat(line1, (yyvsp[-1].ast)->IRcode);
				line = line1;
				writeIR(line1);


				// MIPS code
				char * scope = top(theStack);
				if (strcmp(scope,"main") != 0){
					
					char * reg = getRegister();
					if (strcmp(getExprType((yyvsp[-1].ast)->IRcode), "int") == 0){
						// li $t0, 2
						fprintf(MIPS,"li %s, %s\n", reg, (yyvsp[-1].ast)->IRcode);
					}
					else if (strcmp(getExprType((yyvsp[-1].ast)->IRcode), "id") == 0){
						char* scope = getScope((yyvsp[-1].ast)->IRcode, theStack);
						// lw $t0, addhehe_f
						fprintf(MIPS,"lw %s, %s_%s\n", reg, scope, (yyvsp[-1].ast)->IRcode);
					}
					else{
						freeReg(reg);
						reg = (yyvsp[-1].ast)->IRcode;
					}
					// lw $v0, main_b
					fprintf(MIPS,"move $v0, %s\n", reg);
					fprintf(MIPS, "j return_func\n");
					freeReg(reg);
				}			
				else{						
					if (strcmp(scope, "main") == 0)
					{
						emitEndTimer();
					}
					fprintf(MIPS, "j end_%s\n", scope);
				}

			}
#line 4543 "parser.tab.c"
    break;

  case 58:
#line 3034 "parser.y"
                        {
				// MIPS code
				char * scope = top(theStack);
				if (strcmp(scope,"main") != 0){
					fprintf(MIPS, "j return_func\n");
				}			
				else{
					if (strcmp(scope, "main") == 0)
					{
						emitEndTimer();
					}
					fprintf(MIPS, "j end_%s\n", scope);
				}
				
				(yyval.ast) = AST_node("RETURN");
				printf("RECOGNIZED RULE: RETURN || Line: %d || Char: %d\n", lines, chars);
				if (strcmp(getType(top(theStack), theStack), "void") != 0){
					printf("SEMANTIC ERROR: A return statement must not have a return value unless it appears in the body of a function that is declared to return a value. || Line: %d || Char: %d\n", lines, chars);
				}
			}
#line 4568 "parser.tab.c"
    break;

  case 59:
#line 3055 "parser.y"
                        {
				printf("SYNTAX ERROR: Missing SEMICOLON || Line: %d || Char: %d\n", lines, chars);
			}
#line 4576 "parser.tab.c"
    break;

  case 60:
#line 3059 "parser.y"
                        {
				(yyval.ast) = AST_node("WRITE");
				(yyval.ast)->left = (yyvsp[-1].ast);
				(yyval.ast)->right = AST_node("");
				printf("RECOGNIZED RULE: WRITE || Line: %d || Char: %d\n", lines, chars);
				char c [400];
				strcpy(c, (yyvsp[-1].ast)->IRcode);
				if (c[0] == '"'){
					emitWrite((yyvsp[-1].ast)->IRcode);
					useroutnumber = emitMIPSWriteForString((yyvsp[-1].ast)->IRcode, userout, useroutnumber);
				}
				else{
					/* check out code comments on "ID LBRACK Expr RBRACK" rule */
					struct AST* node = (yyvsp[-1].ast);
					char exprType[50]; 
					if ((strcmp(node->nodeType, "!") == 0) || (strcmp(node->nodeType, "==") == 0) || (strcmp(node->nodeType, "!=") == 0) || (strcmp(node->nodeType, "<=") == 0) || (strcmp(node->nodeType, ">=") == 0) || (strcmp(node->nodeType, "&&") == 0) || (strcmp(node->nodeType, "||") == 0) || (strcmp(node->nodeType, "<") == 0) || (strcmp(node->nodeType, ">") == 0)){
						strcpy(exprType, "bool");
					}
					else if ((strcmp(node->nodeType, "+") == 0) || (strcmp(node->nodeType, "-") == 0) || (strcmp(node->nodeType, "*") == 0) || (strcmp(node->nodeType, "/") == 0)){
						strcpy(exprType, "int");
					}
					else if ((strcmp(node->nodeType, "ARR") == 0)){			
						strcpy(exprType, getTypeForArr(node->left->nodeType, theStack));				
					}
					else{
						regex_t reg;
						const char *regex="^[A-Za-z][A-Za-z0-9]*";
						int ret;
						char err[1024];
						//Read data into variable filecontent
						ret = regcomp(&reg, regex, REG_EXTENDED);
						if (ret != 0) {
							regerror(ret, &reg, err, 1024);
							return 1;
						}
						int return_value;
						return_value = regexec(&reg, node->nodeType , 0, NULL, 0);
						regfree(&reg);
						if (return_value == 0){
							strcpy(exprType, getType(node->nodeType, theStack));
						}
						else{
							regex_t reg;
							const char *regex="^-?[0-9]+";
							int ret;
							char err[1024];
							//Read data into variable filecontent
							ret = regcomp(&reg, regex, REG_EXTENDED);
							if (ret != 0) {
								regerror(ret, &reg, err, 1024);
								return 1;
							}
							int return_value;
							return_value = regexec(&reg, node->nodeType , 0, NULL, 0);
							regfree(&reg);
							if (return_value == 0){
								strcpy(exprType, "int");
							}
							else{
								regex_t reg;
								const char *regex="'[a-zA-Z]'";
								int ret;
								char err[1024];
								//Read data into variable filecontent
								ret = regcomp(&reg, regex, REG_EXTENDED);
								if (ret != 0) {
									regerror(ret, &reg, err, 1024);
									return 1;
								}
								int return_value;
								return_value = regexec(&reg, node->nodeType , 0, NULL, 0);
								regfree(&reg);
								if (return_value == 0){
									strcpy(exprType, "char");
								}
								else{
									strcpy(exprType, ""); 
								}
							}
						}
					}
					if (strcmp(exprType, "int") == 0){
						emitWriteForInt((yyvsp[-1].ast)->IRcode);
						emitMIPSWriteForInt((yyvsp[-1].ast)->IRcode, theStack, getScope((yyvsp[-1].ast)->IRcode, theStack));
					}
					else{
						emitWrite((yyvsp[-1].ast)->IRcode);
						useroutnumber = emitMIPSWriteForString((yyvsp[-1].ast)->IRcode, userout, useroutnumber);
					}	
				}
			}
#line 4672 "parser.tab.c"
    break;

  case 61:
#line 3151 "parser.y"
                        {
				printf("SYNTAX ERROR: Missing SEMICOLON || Line: %d || Char: %d\n", lines, chars);
			}
#line 4680 "parser.tab.c"
    break;

  case 62:
#line 3155 "parser.y"
                        {
				(yyval.ast) = AST_node("WRITELN");
				(yyval.ast)->left = AST_node("");
				(yyval.ast)->right = AST_node("");
				printf("RECOGNIZED RULE: WRITELN || Line: %d || Char: %d\n", lines, chars);
				emitWriteLnForString("\"\"");
				emitWriteNewLine();
			}
#line 4693 "parser.tab.c"
    break;

  case 63:
#line 3164 "parser.y"
                        {
				(yyval.ast) = AST_node("WRITELN");
				(yyval.ast)->left = (yyvsp[-1].ast);
				(yyval.ast)->right = AST_node("");
				printf("RECOGNIZED RULE: WRITELN || Line: %d || Char: %d\n", lines, chars);
				char c [400];
				strcpy(c, (yyvsp[-1].ast)->IRcode);
				if (c[0] == '"'){
					emitWriteLnForString((yyvsp[-1].ast)->IRcode);
					useroutnumber = emitWriteNewLineForString((yyvsp[-1].ast)->IRcode, userout, useroutnumber);
				}
				else{
					/* check out code comments on "ID LBRACK Expr RBRACK" rule */
					struct AST* node = (yyvsp[-1].ast);
					char exprType[50]; 
					if ((strcmp(node->nodeType, "!") == 0) || (strcmp(node->nodeType, "==") == 0) || (strcmp(node->nodeType, "!=") == 0) || (strcmp(node->nodeType, "<=") == 0) || (strcmp(node->nodeType, ">=") == 0) || (strcmp(node->nodeType, "&&") == 0) || (strcmp(node->nodeType, "||") == 0) || (strcmp(node->nodeType, "<") == 0) || (strcmp(node->nodeType, ">") == 0)){
						strcpy(exprType, "bool");
					}
					else if ((strcmp(node->nodeType, "+") == 0) || (strcmp(node->nodeType, "-") == 0) || (strcmp(node->nodeType, "*") == 0) || (strcmp(node->nodeType, "/") == 0)){
						strcpy(exprType, "int");
					}
					else if ((strcmp(node->nodeType, "ARR") == 0)){			
						strcpy(exprType, getTypeForArr(node->left->nodeType, theStack));				
					}
					else{
						regex_t reg;
						const char *regex="^[A-Za-z][A-Za-z0-9]*";
						int ret;
						char err[1024];
						//Read data into variable filecontent
						ret = regcomp(&reg, regex, REG_EXTENDED);
						if (ret != 0) {
							regerror(ret, &reg, err, 1024);
							return 1;
						}
						int return_value;
						return_value = regexec(&reg, node->nodeType , 0, NULL, 0);
						regfree(&reg);
						if (return_value == 0){
							strcpy(exprType, getType(node->nodeType, theStack));
						}
						else{
							regex_t reg;
							const char *regex="^-?[0-9]+";
							int ret;
							char err[1024];
							//Read data into variable filecontent
							ret = regcomp(&reg, regex, REG_EXTENDED);
							if (ret != 0) {
								regerror(ret, &reg, err, 1024);
								return 1;
							}
							int return_value;
							return_value = regexec(&reg, node->nodeType , 0, NULL, 0);
							regfree(&reg);
							if (return_value == 0){
								strcpy(exprType, "int");
							}
							else{
								regex_t reg;
								const char *regex="'[a-zA-Z]'";
								int ret;
								char err[1024];
								//Read data into variable filecontent
								ret = regcomp(&reg, regex, REG_EXTENDED);
								if (ret != 0) {
									regerror(ret, &reg, err, 1024);
									return 1;
								}
								int return_value;
								return_value = regexec(&reg, node->nodeType , 0, NULL, 0);
								regfree(&reg);
								if (return_value == 0){
									strcpy(exprType, "char");
								}
								else{
									strcpy(exprType, ""); 
								}
							}
						}
					}
					// if we are writing a number
					if (strcmp(exprType, "int") == 0){
						emitWriteLnForInt((yyvsp[-1].ast)->IRcode);
						emitWriteNewLineForInt((yyvsp[-1].ast)->IRcode, theStack, getScope((yyvsp[-1].ast)->IRcode, theStack));
					}
					// if we are writing something else
					else{
						emitWriteLn((yyvsp[-1].ast)->IRcode);
						emitWriteNewLine();
					}	
				}
			}
#line 4791 "parser.tab.c"
    break;

  case 64:
#line 3258 "parser.y"
                        {
				printf("SYNTAX ERROR: Missing SEMICOLON || Line: %d || Char: %d\n", lines, chars);
			}
#line 4799 "parser.tab.c"
    break;

  case 65:
#line 3262 "parser.y"
                        {
				(yyval.ast) = AST_node("BREAK");
				(yyval.ast)->left = AST_node("");
				(yyval.ast)->right = AST_node("");
				printf("RECOGNIZED RULE: BREAK || Line: %d || Char: %d\n", lines, chars);
				if (strcmp(top(theStack), "while") != 0){
					printf("SEMANTIC ERROR: All break statements must be contained within the body of a loop || Line: %d || Char: %d\n", lines, chars);
				}
			}
#line 4813 "parser.tab.c"
    break;

  case 66:
#line 3272 "parser.y"
                        {
				printf("SYNTAX ERROR: Missing SEMICOLON || Line: %d || Char: %d\n", lines, chars);
			}
#line 4821 "parser.tab.c"
    break;

  case 67:
#line 3276 "parser.y"
                        {
				// addNum_if_1:
				fprintf(MIPS, "%s_if_%d:\n", top(theStack), if_counter);
				char currentScope[1024];
				snprintf(currentScope, sizeof(currentScope), "%s_if_%d", top(theStack), if_counter);
				push(theStack, currentScope);
				if_counter++;
			}
#line 4834 "parser.tab.c"
    break;

  case 68:
#line 3285 "parser.y"
                        {
				emitStartIF();
			}
#line 4842 "parser.tab.c"
    break;

  case 69:
#line 3289 "parser.y"
                        {
				emitMidIFELSE((yyvsp[-2].ast)->IRcode); emitIFBLOCK();
			}
#line 4850 "parser.tab.c"
    break;

  case 70:
#line 3293 "parser.y"
                        {
				emitEndIFELSEBLOCK(); 
				// j end_else_addNum_if_1
				fprintf(MIPS, "j end_else_%s\n", top(theStack));
			}
#line 4860 "parser.tab.c"
    break;

  case 71:
#line 3299 "parser.y"
                        {
				emitELSEBLOCK();
				// else_addNum_if_1:
				fprintf(MIPS, "else_%s:\n", top(theStack));
			}
#line 4870 "parser.tab.c"
    break;

  case 72:
#line 3305 "parser.y"
                        {
				emitEndELSEBLOCK();freeReg((yyvsp[-8].ast)->IRcode);
				// end_else_addNum_if_1: 
				fprintf(MIPS, "end_else_%s:\n", top(theStack));
				pop(theStack);
			}
#line 4881 "parser.tab.c"
    break;

  case 73:
#line 3311 "parser.y"
                        {
				printf("RECOGNIZED RULE: IF-ELSE-STMT || Line: %d || Char: %d\n", lines, chars);
				(yyval.ast) = AST_node("IFELSE");
				(yyval.ast)->left = (yyvsp[-9].ast);
				(yyval.ast)->right = AST_node("IFELSE-TAIL");
				(yyval.ast)->right->left = (yyvsp[-5].ast);
				(yyval.ast)->right->right = (yyvsp[-1].ast);

				struct AST* node = (yyvsp[-9].ast);
				char exprType[50]; 
				if ((strcmp(node->nodeType, "!") == 0) || (strcmp(node->nodeType, "==") == 0) || (strcmp(node->nodeType, "!=") == 0) || (strcmp(node->nodeType, "<=") == 0) || (strcmp(node->nodeType, ">=") == 0) || (strcmp(node->nodeType, "&&") == 0) || (strcmp(node->nodeType, "||") == 0) || (strcmp(node->nodeType, "<") == 0) || (strcmp(node->nodeType, ">") == 0)){
					strcpy(exprType, "bool");
				}
				else if ((strcmp(node->nodeType, "+") == 0) || (strcmp(node->nodeType, "-") == 0) || (strcmp(node->nodeType, "*") == 0) || (strcmp(node->nodeType, "/") == 0)){
					strcpy(exprType, "int");
				}
				else if ((strcmp(node->nodeType, "ARR") == 0)){			
					strcpy(exprType, getTypeForArr(node->left->nodeType, theStack));				
				}
				else{
					regex_t reg;
					const char *regex="^[A-Za-z][A-Za-z0-9]*";
					int ret;
					char err[1024];
					//Read data into variable filecontent
					ret = regcomp(&reg, regex, REG_EXTENDED);
					if (ret != 0) {
						regerror(ret, &reg, err, 1024);
						return 1;
					}
					int return_value;
					return_value = regexec(&reg, node->nodeType , 0, NULL, 0);
					regfree(&reg);
					if (return_value == 0){
						strcpy(exprType, getType(node->nodeType, theStack));
					}
					else{
						regex_t reg;
						const char *regex="^-?[0-9]+";
						int ret;
						char err[1024];
						//Read data into variable filecontent
						ret = regcomp(&reg, regex, REG_EXTENDED);
						if (ret != 0) {
							regerror(ret, &reg, err, 1024);
							return 1;
						}
						int return_value;
						return_value = regexec(&reg, node->nodeType , 0, NULL, 0);
						regfree(&reg);
						if (return_value == 0){
							strcpy(exprType, "int");
						}
					else{
              regex_t reg;
              const char *regex="'[a-zA-Z]'";
              int ret;
              char err[1024];
              //Read data into variable filecontent
              ret = regcomp(&reg, regex, REG_EXTENDED);
              if (ret != 0) {
                regerror(ret, &reg, err, 1024);
                return 1;
              }
              int return_value;
              return_value = regexec(&reg, node->nodeType , 0, NULL, 0);
              regfree(&reg);
              if (return_value == 0){
                strcpy(exprType, "char");
              }
              else{
                strcpy(exprType, ""); 
              }
            }
          }
        }

				if (strcmp(exprType, "bool") != 0){
					printf("SEMANTIC ERROR: The type of expression must be bool || Line: %d || Char: %d\n", lines, chars);
				}	
			}
#line 4967 "parser.tab.c"
    break;

  case 74:
#line 3393 "parser.y"
                                       {emitStartIF();}
#line 4973 "parser.tab.c"
    break;

  case 75:
#line 3393 "parser.y"
                                                               {emitMidIF((yyvsp[-2].ast)->IRcode); emitIFBLOCK();}
#line 4979 "parser.tab.c"
    break;

  case 76:
#line 3393 "parser.y"
                                                                                                            {emitEndIFBLOCK(); freeReg((yyvsp[-4].ast)->IRcode);}
#line 4985 "parser.tab.c"
    break;

  case 77:
#line 3394 "parser.y"
                        {
				printf("RECOGNIZED RULE: IF-STMT || Line: %d || Char: %d\n", lines, chars);
				(yyval.ast) = AST_node("IF");
				(yyval.ast)->left = (yyvsp[-5].ast);
				(yyval.ast)->right = (yyvsp[-1].ast);
				
				struct AST* node = (yyvsp[-5].ast);
				char exprType[50]; 
				if ((strcmp(node->nodeType, "!") == 0) || (strcmp(node->nodeType, "==") == 0) || (strcmp(node->nodeType, "!=") == 0) || (strcmp(node->nodeType, "<=") == 0) || (strcmp(node->nodeType, ">=") == 0) || (strcmp(node->nodeType, "&&") == 0) || (strcmp(node->nodeType, "||") == 0) || (strcmp(node->nodeType, "<") == 0) || (strcmp(node->nodeType, ">") == 0)){
					strcpy(exprType, "bool");
				}
				else if ((strcmp(node->nodeType, "+") == 0) || (strcmp(node->nodeType, "-") == 0) || (strcmp(node->nodeType, "*") == 0) || (strcmp(node->nodeType, "/") == 0)){
					strcpy(exprType, "int");
				}
				else if ((strcmp(node->nodeType, "ARR") == 0)){			
					strcpy(exprType, getTypeForArr(node->left->nodeType, theStack));				
				}
				else{
					regex_t reg;
					const char *regex="^[A-Za-z][A-Za-z0-9]*";
					int ret;
					char err[1024];
					//Read data into variable filecontent
					ret = regcomp(&reg, regex, REG_EXTENDED);
					if (ret != 0) {
						regerror(ret, &reg, err, 1024);
						return 1;
					}
					int return_value;
					return_value = regexec(&reg, node->nodeType , 0, NULL, 0);
					regfree(&reg);
					if (return_value == 0){
						strcpy(exprType, getType(node->nodeType, theStack));
					}
					else{
						regex_t reg;
						const char *regex="^-?[0-9]+";
						int ret;
						char err[1024];
						//Read data into variable filecontent
						ret = regcomp(&reg, regex, REG_EXTENDED);
						if (ret != 0) {
							regerror(ret, &reg, err, 1024);
							return 1;
						}
						int return_value;
						return_value = regexec(&reg, node->nodeType , 0, NULL, 0);
						regfree(&reg);
						if (return_value == 0){
							strcpy(exprType, "int");
						}
						else{
              regex_t reg;
              const char *regex="'[a-zA-Z]'";
              int ret;
              char err[1024];
              //Read data into variable filecontent
              ret = regcomp(&reg, regex, REG_EXTENDED);
              if (ret != 0) {
                regerror(ret, &reg, err, 1024);
                return 1;
              }
              int return_value;
              return_value = regexec(&reg, node->nodeType , 0, NULL, 0);
              regfree(&reg);
              if (return_value == 0){
                strcpy(exprType, "char");
              }
              else{
                strcpy(exprType, ""); 
              }
            }
          }
        }

				if (strcmp(exprType, "bool") != 0){
					printf("SEMANTIC ERROR: The type of expression must be bool || Line: %d || Char: %d\n", lines, chars);
				}		

			}
#line 5070 "parser.tab.c"
    break;

  case 78:
#line 3477 "parser.y"
                        {
				emitStartWHILE(); 
				fprintf(MIPS, "%s_while_%d:\n", top(theStack), while_counter);
				char currentScope[1024];
				snprintf(currentScope, sizeof(currentScope), "%s_while_%d", top(theStack), while_counter);
				printf("CURRENT SCOPE: %s\n", currentScope);
				push(theStack, currentScope);
				while_counter++;
			}
#line 5084 "parser.tab.c"
    break;

  case 79:
#line 3487 "parser.y"
                        {
				emitMidWHILE((yyvsp[-1].ast)->IRcode); 
				char* scopeL = getScope((yyvsp[-1].ast)->left->IRcode, theStack); 
				char* scopeR = getScope((yyvsp[-1].ast)->right->IRcode, theStack); 
				emitWHILEBLOCK();
			}
#line 5095 "parser.tab.c"
    break;

  case 80:
#line 3494 "parser.y"
                        {
				emitRestartWHILE(); 
				emitEndWHILEBLOCK(); 
				freeReg((yyvsp[-3].ast)->IRcode);

				// j addNum_while_1
				// else_addNum_while_1:
				fprintf(MIPS, "j %s\nelse_%s:\n", top(theStack), top(theStack));
		
				pop(theStack);
				(yyval.ast) = AST_node("WHILE");
				(yyval.ast)->left = (yyvsp[-3].ast);
				(yyval.ast)->right = (yyvsp[0].ast);
				printf("RECOGNIZED RULE: WHILE-LOOP || Line: %d || Char: %d\n", lines, chars);
								
				struct AST* node = (yyvsp[-3].ast);
				char exprType[50]; 
				if ((strcmp(node->nodeType, "!") == 0) || (strcmp(node->nodeType, "==") == 0) || (strcmp(node->nodeType, "!=") == 0) || (strcmp(node->nodeType, "<=") == 0) || (strcmp(node->nodeType, ">=") == 0) || (strcmp(node->nodeType, "&&") == 0) || (strcmp(node->nodeType, "||") == 0) || (strcmp(node->nodeType, "<") == 0) || (strcmp(node->nodeType, ">") == 0)){
					strcpy(exprType, "bool");
				}
				else if ((strcmp(node->nodeType, "+") == 0) || (strcmp(node->nodeType, "-") == 0) || (strcmp(node->nodeType, "*") == 0) || (strcmp(node->nodeType, "/") == 0)){
					strcpy(exprType, "int");
				}
				else if ((strcmp(node->nodeType, "ARR") == 0)){			
					strcpy(exprType, getTypeForArr(node->left->nodeType, theStack));				
				}
				else{
					regex_t reg;
					const char *regex="^[A-Za-z][A-Za-z0-9]*";
					int ret;
					char err[1024];
					//Read data into variable filecontent
					ret = regcomp(&reg, regex, REG_EXTENDED);
					if (ret != 0) {
						regerror(ret, &reg, err, 1024);
						return 1;
					}
					int return_value;
					return_value = regexec(&reg, node->nodeType , 0, NULL, 0);
					regfree(&reg);
					if (return_value == 0){
						strcpy(exprType, getType(node->nodeType, theStack));
					}
					else{
						regex_t reg;
						const char *regex="^-?[0-9]+";
						int ret;
						char err[1024];
						//Read data into variable filecontent
						ret = regcomp(&reg, regex, REG_EXTENDED);
						if (ret != 0) {
							regerror(ret, &reg, err, 1024);
							return 1;
						}
						int return_value;
						return_value = regexec(&reg, node->nodeType , 0, NULL, 0);
						regfree(&reg);
						if (return_value == 0){
							strcpy(exprType, "int");
						}
						else{
              regex_t reg;
              const char *regex="'[a-zA-Z]'";
              int ret;
              char err[1024];
              //Read data into variable filecontent
              ret = regcomp(&reg, regex, REG_EXTENDED);
              if (ret != 0) {
                regerror(ret, &reg, err, 1024);
                return 1;
              }
              int return_value;
              return_value = regexec(&reg, node->nodeType , 0, NULL, 0);
              regfree(&reg);
              if (return_value == 0){
                strcpy(exprType, "char");
              }
              else{
                strcpy(exprType, ""); 
              }
            }
          }
        }

				if (strcmp(exprType, "bool") != 0){
					printf("SEMANTIC ERROR: The type of expression must be bool || Line: %d || Char: %d\n", lines, chars);
				}		
				
			}
#line 5189 "parser.tab.c"
    break;


#line 5193 "parser.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
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


#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[+*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 3586 "parser.y"


int main(int argc, char**argv)
{
	//timer start
	double duration = 0.0;
	clock_t start = clock();


	/* create scope stack, push global onto stack first */
	theStack = newStack();
	push(theStack, "global");
	/* create ifwhilestack */
	ifwhilestack = newStack();

	/*create stack for user output messages*/
	userout = newStack();

/*
	#ifdef YYDEBUG
		yydebug = 1;
	#endif
*/

/* Initialize files for writing IR and MIPS code */
	initIRcodeFile();
	initMIPScodeFile();
	
	// .text
	// .globl main
	// .ent main
	fprintf(MIPS,".text\n.globl main\n.ent main\n\n"); //emit start of MIPS file

	// return_func:                              
	// lw $ra, 0($sp)                          #restore return address
	// addiu $sp, $sp, 4                       #restore stack pointer
	// jr $ra                                  #jump back to return address
	// .end return_func
	fprintf(MIPS,"return_func:\nlw $ra, 0($sp)\naddiu $sp, $sp, 4\njr $ra\n.end return_func\n\n"); //emit Return function to exit function calls

/* Start compiler and create registers for use in IR and MIPS code. */
	printf("\n\n##### COMPILER STARTED #####\n\n");
	createRegisters();
	showRegisters();
	
/* Bison code for error when parsing */
	if (argc > 1){
	  if(!(yyin = fopen(argv[1], "r")))
          {
		perror(argv[1]);
		return(1);
	  }
	}
	yyparse();

/* emit end of main function to MIPS and add data section of MIPS code */
	exitMain();
	addData(useroutnumber, userout);

	//timer end
	clock_t finish = clock();
	duration += (double)(finish-start) / CLOCKS_PER_SEC;
	duration *= 1000;
	printf("\nCompiled in: %f milliseconds\n\n", duration);
	

}

//error function for parse errors
void yyerror(const char* s) {
	fprintf(stderr, "Parse error: %s\n", s);
	exit(1);
}
