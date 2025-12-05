/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
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
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 2 "ss.y"

#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>
#include "ast.h"

int yylex();
void yyerror(const char *s);
extern int yylineno;
extern FILE *yyin;
Node *root = nullptr;

bool has_parse_error = false;
bool has_lex_error = false;
// 来自 semantic.cpp 的变量
extern bool has_semantic_error;

#line 90 "ss.tab.c"

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

#include "ss.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_INTTK = 3,                      /* INTTK  */
  YYSYMBOL_FLOATTK = 4,                    /* FLOATTK  */
  YYSYMBOL_VOIDTK = 5,                     /* VOIDTK  */
  YYSYMBOL_ID = 6,                         /* ID  */
  YYSYMBOL_INTCON = 7,                     /* INTCON  */
  YYSYMBOL_OCTCON = 8,                     /* OCTCON  */
  YYSYMBOL_HEXCON = 9,                     /* HEXCON  */
  YYSYMBOL_FLOATCON = 10,                  /* FLOATCON  */
  YYSYMBOL_STRCON = 11,                    /* STRCON  */
  YYSYMBOL_IF = 12,                        /* IF  */
  YYSYMBOL_ELSE = 13,                      /* ELSE  */
  YYSYMBOL_WHILE = 14,                     /* WHILE  */
  YYSYMBOL_BREAK = 15,                     /* BREAK  */
  YYSYMBOL_CONTINUE = 16,                  /* CONTINUE  */
  YYSYMBOL_RETURN = 17,                    /* RETURN  */
  YYSYMBOL_EQL = 18,                       /* EQL  */
  YYSYMBOL_NEQ = 19,                       /* NEQ  */
  YYSYMBOL_LEQ = 20,                       /* LEQ  */
  YYSYMBOL_GEQ = 21,                       /* GEQ  */
  YYSYMBOL_AND = 22,                       /* AND  */
  YYSYMBOL_OR = 23,                        /* OR  */
  YYSYMBOL_LOWER_THAN_ELSE = 24,           /* LOWER_THAN_ELSE  */
  YYSYMBOL_25_ = 25,                       /* ';'  */
  YYSYMBOL_26_ = 26,                       /* ','  */
  YYSYMBOL_27_ = 27,                       /* '='  */
  YYSYMBOL_28_ = 28,                       /* '['  */
  YYSYMBOL_29_ = 29,                       /* ']'  */
  YYSYMBOL_30_ = 30,                       /* '('  */
  YYSYMBOL_31_ = 31,                       /* ')'  */
  YYSYMBOL_32_ = 32,                       /* '{'  */
  YYSYMBOL_33_ = 33,                       /* '}'  */
  YYSYMBOL_34_ = 34,                       /* '<'  */
  YYSYMBOL_35_ = 35,                       /* '>'  */
  YYSYMBOL_36_ = 36,                       /* '+'  */
  YYSYMBOL_37_ = 37,                       /* '-'  */
  YYSYMBOL_38_ = 38,                       /* '*'  */
  YYSYMBOL_39_ = 39,                       /* '/'  */
  YYSYMBOL_YYACCEPT = 40,                  /* $accept  */
  YYSYMBOL_CompUnit = 41,                  /* CompUnit  */
  YYSYMBOL_Decl = 42,                      /* Decl  */
  YYSYMBOL_VarDecl = 43,                   /* VarDecl  */
  YYSYMBOL_VarDefList = 44,                /* VarDefList  */
  YYSYMBOL_BType = 45,                     /* BType  */
  YYSYMBOL_VarDef = 46,                    /* VarDef  */
  YYSYMBOL_InitVal = 47,                   /* InitVal  */
  YYSYMBOL_FuncDef = 48,                   /* FuncDef  */
  YYSYMBOL_FuncFParams = 49,               /* FuncFParams  */
  YYSYMBOL_FuncFParam = 50,                /* FuncFParam  */
  YYSYMBOL_Block = 51,                     /* Block  */
  YYSYMBOL_BlockItemList = 52,             /* BlockItemList  */
  YYSYMBOL_BlockItem = 53,                 /* BlockItem  */
  YYSYMBOL_Stmt = 54,                      /* Stmt  */
  YYSYMBOL_Exp = 55,                       /* Exp  */
  YYSYMBOL_LOrExp = 56,                    /* LOrExp  */
  YYSYMBOL_LAndExp = 57,                   /* LAndExp  */
  YYSYMBOL_EqExp = 58,                     /* EqExp  */
  YYSYMBOL_RelExp = 59,                    /* RelExp  */
  YYSYMBOL_AddExp = 60,                    /* AddExp  */
  YYSYMBOL_MulExp = 61,                    /* MulExp  */
  YYSYMBOL_UnaryExp = 62,                  /* UnaryExp  */
  YYSYMBOL_FuncRParams = 63,               /* FuncRParams  */
  YYSYMBOL_PrimaryExp = 64,                /* PrimaryExp  */
  YYSYMBOL_LVal = 65                       /* LVal  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




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

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
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
typedef yytype_int8 yy_state_t;

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


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

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
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE) \
             + YYSIZEOF (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

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
#define YYFINAL  9
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   142

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  40
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  26
/* YYNRULES -- Number of rules.  */
#define YYNRULES  70
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  121

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   279


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      30,    31,    38,    36,    26,    37,     2,    39,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    25,
      34,    27,    35,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    28,     2,    29,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    32,     2,    33,     2,     2,     2,     2,
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
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    39,    39,    40,    41,    42,    45,    47,    56,    60,
      66,    67,    68,    71,    75,    81,    90,    92,   100,   111,
     112,   115,   122,   128,   129,   136,   136,   138,   144,   148,
     154,   160,   161,   167,   171,   175,   179,   183,   184,   187,
     188,   189,   190,   191,   192,   193,   194,   195,   196,   197,
     198,   199,   200,   201,   202,   203,   205,   206,   210,   215,
     221,   228,   229,   232,   233,   234,   235,   236,   237,   240,
     244
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "INTTK", "FLOATTK",
  "VOIDTK", "ID", "INTCON", "OCTCON", "HEXCON", "FLOATCON", "STRCON", "IF",
  "ELSE", "WHILE", "BREAK", "CONTINUE", "RETURN", "EQL", "NEQ", "LEQ",
  "GEQ", "AND", "OR", "LOWER_THAN_ELSE", "';'", "','", "'='", "'['", "']'",
  "'('", "')'", "'{'", "'}'", "'<'", "'>'", "'+'", "'-'", "'*'", "'/'",
  "$accept", "CompUnit", "Decl", "VarDecl", "VarDefList", "BType",
  "VarDef", "InitVal", "FuncDef", "FuncFParams", "FuncFParam", "Block",
  "BlockItemList", "BlockItem", "Stmt", "Exp", "LOrExp", "LAndExp",
  "EqExp", "RelExp", "AddExp", "MulExp", "UnaryExp", "FuncRParams",
  "PrimaryExp", "LVal", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-76)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
       4,   -76,   -76,   -76,    66,   -76,   -76,    -1,   -76,   -76,
     -76,   -76,    46,    -9,   -76,    94,    94,    50,   -76,    31,
      15,   -76,   -76,   -76,   -76,    94,   -76,   -76,    33,    42,
      32,    71,    72,    77,   -76,   -76,    39,    43,    55,    76,
      12,   -76,    83,   -76,     5,    64,    94,    94,    94,    94,
      94,    94,    94,    94,    94,    94,    94,   -76,   -76,   -76,
     -76,     4,    55,   -76,   -76,   -76,    26,   -76,    42,    32,
      71,    71,    72,    72,    77,    77,   -76,   -76,    78,    16,
     -76,   -76,   -76,    94,   -76,   -76,    93,    95,    88,   103,
      53,   -76,   -76,    31,   -76,   -76,   -76,    17,    90,   -76,
      94,    94,   -76,   -76,   -76,   106,   107,   -76,    94,   102,
     104,   -76,   -76,   109,    82,    82,   -76,   123,   -76,    82,
     -76
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,    10,    11,    12,     0,     5,     6,     0,     4,     1,
       3,     2,    13,     0,     8,     0,     0,     0,     7,     0,
      69,    65,    66,    67,    68,     0,    14,    16,    39,    40,
      42,    44,    47,    50,    53,    56,    64,     0,     0,     0,
       0,    19,    13,     9,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    15,    23,    17,
      21,     0,     0,    60,    57,    61,     0,    63,    41,    43,
      45,    46,    48,    49,    51,    52,    54,    55,     0,     0,
      20,    18,    59,     0,    58,    70,     0,     0,     0,     0,
       0,    22,    25,     0,    31,    24,    26,     0,    64,    62,
       0,     0,    37,    38,    33,     0,    30,    28,     0,     0,
       0,    32,    29,     0,     0,     0,    27,    34,    36,     0,
      35
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -76,   -76,    -2,   -76,   -76,   -14,   118,   -76,   134,   -76,
      79,    -4,   -76,   -76,   -35,   -15,   -76,    96,    92,    73,
      69,    74,    75,   -76,   -76,   -75
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     4,     5,     6,    13,     7,    14,    26,     8,    40,
      41,    94,    79,    95,    96,    97,    28,    29,    30,    31,
      32,    33,    34,    66,    35,    36
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      27,    37,    10,    39,    98,    12,    63,     1,     2,     3,
      45,    20,    21,    22,    23,    24,    18,    19,   106,     1,
       2,     3,    20,    21,    22,    23,    24,    82,    86,    65,
      87,    88,    89,    90,    59,    25,    64,    42,    61,    98,
      98,    78,   107,    62,    98,    44,    25,    39,    58,    91,
      48,    49,    83,     1,     2,     3,    46,    84,    81,    20,
      21,    22,    23,    24,    47,    93,     9,    56,    99,     1,
       2,     3,    57,    15,    16,   105,    17,    92,   104,   117,
     118,    38,    60,    25,   120,   109,   110,    58,    20,    21,
      22,    23,    24,   113,    86,    67,    87,    88,    89,    90,
      20,    21,    22,    23,    24,    50,    51,    85,    52,    53,
      15,    16,    25,   102,    58,    54,    55,   108,    56,    72,
      73,    70,    71,   100,    25,   101,    74,    75,   103,    76,
      77,   111,   112,   114,   116,   115,   119,    43,    11,    69,
      80,     0,    68
};

static const yytype_int8 yycheck[] =
{
      15,    16,     4,    17,    79,     6,     1,     3,     4,     5,
      25,     6,     7,     8,     9,    10,    25,    26,     1,     3,
       4,     5,     6,     7,     8,     9,    10,     1,    12,    44,
      14,    15,    16,    17,    38,    30,    31,     6,    26,   114,
     115,    56,    25,    31,   119,    30,    30,    61,    32,    33,
      18,    19,    26,     3,     4,     5,    23,    31,    62,     6,
       7,     8,     9,    10,    22,    79,     0,    28,    83,     3,
       4,     5,    29,    27,    28,    90,    30,    79,    25,   114,
     115,    31,     6,    30,   119,   100,   101,    32,     6,     7,
       8,     9,    10,   108,    12,    31,    14,    15,    16,    17,
       6,     7,     8,     9,    10,    34,    35,    29,    36,    37,
      27,    28,    30,    25,    32,    38,    39,    27,    28,    50,
      51,    48,    49,    30,    30,    30,    52,    53,    25,    54,
      55,    25,    25,    31,    25,    31,    13,    19,     4,    47,
      61,    -1,    46
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     4,     5,    41,    42,    43,    45,    48,     0,
      42,    48,     6,    44,    46,    27,    28,    30,    25,    26,
       6,     7,     8,     9,    10,    30,    47,    55,    56,    57,
      58,    59,    60,    61,    62,    64,    65,    55,    31,    45,
      49,    50,     6,    46,    30,    55,    23,    22,    18,    19,
      34,    35,    36,    37,    38,    39,    28,    29,    32,    51,
       6,    26,    31,     1,    31,    55,    63,    31,    57,    58,
      59,    59,    60,    60,    61,    61,    62,    62,    55,    52,
      50,    51,     1,    26,    31,    29,    12,    14,    15,    16,
      17,    33,    42,    45,    51,    53,    54,    55,    65,    55,
      30,    30,    25,    25,    25,    55,     1,    25,    27,    55,
      55,    25,    25,    55,    31,    31,    25,    54,    54,    13,
      54
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    40,    41,    41,    41,    41,    42,    43,    44,    44,
      45,    45,    45,    46,    46,    46,    47,    48,    48,    49,
      49,    50,    51,    52,    52,    53,    53,    54,    54,    54,
      54,    54,    54,    54,    54,    54,    54,    54,    54,    55,
      56,    56,    57,    57,    58,    58,    58,    59,    59,    59,
      60,    60,    60,    61,    61,    61,    62,    62,    62,    62,
      62,    63,    63,    64,    64,    64,    64,    64,    64,    65,
      65
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     2,     1,     1,     1,     3,     1,     3,
       1,     1,     1,     1,     3,     4,     1,     5,     6,     1,
       3,     2,     3,     0,     2,     1,     1,     4,     2,     3,
       2,     1,     3,     2,     5,     7,     5,     2,     2,     1,
       1,     3,     1,     3,     1,     3,     3,     1,     3,     3,
       1,     3,     3,     1,     3,     3,     1,     3,     4,     4,
       3,     1,     3,     3,     1,     1,     1,     1,     1,     1,
       4
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


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

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF

/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


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


/* YYLOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

# ifndef YYLOCATION_PRINT

#  if defined YY_LOCATION_PRINT

   /* Temporary convenience wrapper in case some people defined the
      undocumented and private YY_LOCATION_PRINT macros.  */
#   define YYLOCATION_PRINT(File, Loc)  YY_LOCATION_PRINT(File, *(Loc))

#  elif defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
}

#   define YYLOCATION_PRINT  yy_location_print_

    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT(File, Loc)  YYLOCATION_PRINT(File, &(Loc))

#  else

#   define YYLOCATION_PRINT(File, Loc) ((void) 0)
    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT  YYLOCATION_PRINT

#  endif
# endif /* !defined YYLOCATION_PRINT */


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (yylocationp);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  YYLOCATION_PRINT (yyo, yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yykind, yyvaluep, yylocationp);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp,
                 int yyrule)
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
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)],
                       &(yylsp[(yyi + 1) - (yynrhs)]));
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
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






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YY_USE (yyvaluep);
  YY_USE (yylocationp);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

    /* The location stack: array, bottom, top.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls = yylsa;
    YYLTYPE *yylsp = yyls;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[3];



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  yylsp[0] = yylloc;
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
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
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
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yyls1, yysize * YYSIZEOF (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

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

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      yyerror_range[1] = yylloc;
      goto yyerrlab1;
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
  *++yylsp = yylloc;

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

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* CompUnit: CompUnit FuncDef  */
#line 39 "ss.y"
                            { (yyval.node)=(yyvsp[-1].node); (yyval.node)->child.push_back((yyvsp[0].node)); }
#line 1343 "ss.tab.c"
    break;

  case 3: /* CompUnit: CompUnit Decl  */
#line 40 "ss.y"
                            { (yyval.node)=(yyvsp[-1].node); (yyval.node)->child.push_back((yyvsp[0].node)); }
#line 1349 "ss.tab.c"
    break;

  case 4: /* CompUnit: FuncDef  */
#line 41 "ss.y"
                            { root = new Node("CompUnit", (yylsp[0]).first_line); root->child.push_back((yyvsp[0].node)); (yyval.node)=root; }
#line 1355 "ss.tab.c"
    break;

  case 5: /* CompUnit: Decl  */
#line 42 "ss.y"
                            { root = new Node("CompUnit", (yylsp[0]).first_line); root->child.push_back((yyvsp[0].node)); (yyval.node)=root; }
#line 1361 "ss.tab.c"
    break;

  case 6: /* Decl: VarDecl  */
#line 45 "ss.y"
                   { (yyval.node)=(yyvsp[0].node); }
#line 1367 "ss.tab.c"
    break;

  case 7: /* VarDecl: BType VarDefList ';'  */
#line 47 "ss.y"
                                {
             (yyval.node) = new Node("VarDecl", (yylsp[-2]).first_line);
             (yyval.node)->child.push_back((yyvsp[-2].node));
             for(auto c : (yyvsp[-1].node)->child) {
                 (yyval.node)->child.push_back(c);
             }
         }
#line 1379 "ss.tab.c"
    break;

  case 8: /* VarDefList: VarDef  */
#line 56 "ss.y"
                    {
                (yyval.node) = new Node("VarDefList", (yylsp[0]).first_line);
                (yyval.node)->child.push_back((yyvsp[0].node));
            }
#line 1388 "ss.tab.c"
    break;

  case 9: /* VarDefList: VarDefList ',' VarDef  */
#line 60 "ss.y"
                                    {
                (yyval.node) = (yyvsp[-2].node);
                (yyval.node)->child.push_back((yyvsp[0].node));
            }
#line 1397 "ss.tab.c"
    break;

  case 10: /* BType: INTTK  */
#line 66 "ss.y"
                   { (yyval.node) = new Node("BType", (yylsp[0]).first_line); (yyval.node)->child.push_back(new Node("Type",0,"int")); }
#line 1403 "ss.tab.c"
    break;

  case 11: /* BType: FLOATTK  */
#line 67 "ss.y"
                   { (yyval.node) = new Node("BType", (yylsp[0]).first_line); (yyval.node)->child.push_back(new Node("Type",0,"float")); }
#line 1409 "ss.tab.c"
    break;

  case 12: /* BType: VOIDTK  */
#line 68 "ss.y"
                   { (yyval.node) = new Node("BType", (yylsp[0]).first_line); (yyval.node)->child.push_back(new Node("Type",0,"void")); }
#line 1415 "ss.tab.c"
    break;

  case 13: /* VarDef: ID  */
#line 71 "ss.y"
              {
             (yyval.node) = new Node("VarDef", (yylsp[0]).first_line);
             (yyval.node)->child.push_back(new Node("Ident", (yylsp[0]).first_line, *(yyvsp[0].str)));
         }
#line 1424 "ss.tab.c"
    break;

  case 14: /* VarDef: ID '=' InitVal  */
#line 75 "ss.y"
                          {
             (yyval.node) = new Node("VarDef", (yylsp[-2]).first_line);
             (yyval.node)->child.push_back(new Node("Ident", (yylsp[-2]).first_line, *(yyvsp[-2].str)));
             (yyval.node)->child.push_back(new Node("ASSIGN", 0));
             (yyval.node)->child.push_back((yyvsp[0].node));
         }
#line 1435 "ss.tab.c"
    break;

  case 15: /* VarDef: ID '[' Exp ']'  */
#line 81 "ss.y"
                          { // 简化: 仅支持一维数组，多维类似
             (yyval.node) = new Node("VarDef", (yylsp[-3]).first_line);
             (yyval.node)->child.push_back(new Node("Ident", (yylsp[-3]).first_line, *(yyvsp[-3].str)));
             Node* dims = new Node("ArrayDims", (yylsp[-2]).first_line);
             dims->child.push_back((yyvsp[-1].node));
             (yyval.node)->child.push_back(dims);
         }
#line 1447 "ss.tab.c"
    break;

  case 16: /* InitVal: Exp  */
#line 90 "ss.y"
               { (yyval.node) = new Node("InitVal", (yylsp[0]).first_line); (yyval.node)->child.push_back((yyvsp[0].node)); }
#line 1453 "ss.tab.c"
    break;

  case 17: /* FuncDef: BType ID '(' ')' Block  */
#line 92 "ss.y"
                                  {
             (yyval.node) = new Node("FuncDef", (yylsp[-4]).first_line);
             Node* ft = new Node("FuncType", (yylsp[-4]).first_line);
             ft->child.push_back((yyvsp[-4].node)->child[0]); // Type
             (yyval.node)->child.push_back(ft);
             (yyval.node)->child.push_back(new Node("Ident", (yylsp[-3]).first_line, *(yyvsp[-3].str)));
             (yyval.node)->child.push_back((yyvsp[0].node));
         }
#line 1466 "ss.tab.c"
    break;

  case 18: /* FuncDef: BType ID '(' FuncFParams ')' Block  */
#line 100 "ss.y"
                                              {
             (yyval.node) = new Node("FuncDef", (yylsp[-5]).first_line);
             Node* ft = new Node("FuncType", (yylsp[-5]).first_line);
             ft->child.push_back((yyvsp[-5].node)->child[0]);
             (yyval.node)->child.push_back(ft);
             (yyval.node)->child.push_back(new Node("Ident", (yylsp[-4]).first_line, *(yyvsp[-4].str)));
             (yyval.node)->child.push_back((yyvsp[-2].node));
             (yyval.node)->child.push_back((yyvsp[0].node));
         }
#line 1480 "ss.tab.c"
    break;

  case 19: /* FuncFParams: FuncFParam  */
#line 111 "ss.y"
                         { (yyval.node) = new Node("FuncFParams", (yylsp[0]).first_line); (yyval.node)->child.push_back((yyvsp[0].node)); }
#line 1486 "ss.tab.c"
    break;

  case 20: /* FuncFParams: FuncFParams ',' FuncFParam  */
#line 112 "ss.y"
                                         { (yyval.node)=(yyvsp[-2].node); (yyval.node)->child.push_back((yyvsp[0].node)); }
#line 1492 "ss.tab.c"
    break;

  case 21: /* FuncFParam: BType ID  */
#line 115 "ss.y"
                      {
               (yyval.node) = new Node("FuncFParam", (yylsp[-1]).first_line);
               (yyval.node)->child.push_back((yyvsp[-1].node));
               (yyval.node)->child.push_back(new Node("Ident", (yylsp[0]).first_line, *(yyvsp[0].str)));
           }
#line 1502 "ss.tab.c"
    break;

  case 22: /* Block: '{' BlockItemList '}'  */
#line 122 "ss.y"
                                 {
             (yyval.node) = new Node("Block", (yylsp[-2]).first_line);
             if((yyvsp[-1].node)) (yyval.node)->child.push_back((yyvsp[-1].node));
         }
#line 1511 "ss.tab.c"
    break;

  case 23: /* BlockItemList: %empty  */
#line 128 "ss.y"
                            { (yyval.node) = nullptr; }
#line 1517 "ss.tab.c"
    break;

  case 24: /* BlockItemList: BlockItemList BlockItem  */
#line 129 "ss.y"
                                        {
                  if(!(yyvsp[-1].node)) (yyval.node) = new Node("BlockItemList", (yylsp[0]).first_line);
                  else (yyval.node) = (yyvsp[-1].node);
                  (yyval.node)->child.push_back((yyvsp[0].node));
              }
#line 1527 "ss.tab.c"
    break;

  case 25: /* BlockItem: Decl  */
#line 136 "ss.y"
                 { (yyval.node)=(yyvsp[0].node); }
#line 1533 "ss.tab.c"
    break;

  case 26: /* BlockItem: Stmt  */
#line 136 "ss.y"
                                   { (yyval.node)=(yyvsp[0].node); }
#line 1539 "ss.tab.c"
    break;

  case 27: /* Stmt: LVal '=' Exp ';'  */
#line 138 "ss.y"
                             {
              (yyval.node) = new Node("Stmt", (yylsp[-3]).first_line);
              (yyval.node)->child.push_back((yyvsp[-3].node));
              (yyval.node)->child.push_back(new Node("ASSIGN",0));
              (yyval.node)->child.push_back((yyvsp[-1].node));
          }
#line 1550 "ss.tab.c"
    break;

  case 28: /* Stmt: Exp ';'  */
#line 144 "ss.y"
                    {
              (yyval.node) = new Node("Stmt", (yylsp[-1]).first_line);
              (yyval.node)->child.push_back((yyvsp[-1].node)); // 可能是函数调用语句
          }
#line 1559 "ss.tab.c"
    break;

  case 29: /* Stmt: Exp error ';'  */
#line 148 "ss.y"
                          {
              // 错误恢复：遇到错误后插入分号，仍然构建Stmt节点
              // 这样可以在报告语法错误后继续语义分析
              (yyval.node) = new Node("Stmt", (yylsp[-2]).first_line);
              (yyval.node)->child.push_back((yyvsp[-2].node));
          }
#line 1570 "ss.tab.c"
    break;

  case 30: /* Stmt: Exp error  */
#line 154 "ss.y"
                      {
              // 错误恢复：遇到错误时（如缺少分号），仍然构建Stmt节点
              // 这样可以在报告语法错误后继续语义分析
              (yyval.node) = new Node("Stmt", (yylsp[-1]).first_line);
              (yyval.node)->child.push_back((yyvsp[-1].node));
          }
#line 1581 "ss.tab.c"
    break;

  case 31: /* Stmt: Block  */
#line 160 "ss.y"
                  { (yyval.node)=(yyvsp[0].node); }
#line 1587 "ss.tab.c"
    break;

  case 32: /* Stmt: RETURN Exp ';'  */
#line 161 "ss.y"
                           {
              (yyval.node) = new Node("Stmt", (yylsp[-2]).first_line);
              Node* ret = new Node("Return", (yylsp[-2]).first_line);
              ret->child.push_back((yyvsp[-1].node));
              (yyval.node)->child.push_back(ret);
          }
#line 1598 "ss.tab.c"
    break;

  case 33: /* Stmt: RETURN ';'  */
#line 167 "ss.y"
                       {
              (yyval.node) = new Node("Stmt", (yylsp[-1]).first_line);
              (yyval.node)->child.push_back(new Node("Return", (yylsp[-1]).first_line));
          }
#line 1607 "ss.tab.c"
    break;

  case 34: /* Stmt: IF '(' Exp ')' Stmt  */
#line 171 "ss.y"
                                                      {
              (yyval.node) = new Node("IfStmt", (yylsp[-4]).first_line);
              (yyval.node)->child.push_back((yyvsp[-2].node)); (yyval.node)->child.push_back((yyvsp[0].node));
          }
#line 1616 "ss.tab.c"
    break;

  case 35: /* Stmt: IF '(' Exp ')' Stmt ELSE Stmt  */
#line 175 "ss.y"
                                          {
              (yyval.node) = new Node("IfStmt", (yylsp[-6]).first_line);
              (yyval.node)->child.push_back((yyvsp[-4].node)); (yyval.node)->child.push_back((yyvsp[-2].node)); (yyval.node)->child.push_back((yyvsp[0].node));
          }
#line 1625 "ss.tab.c"
    break;

  case 36: /* Stmt: WHILE '(' Exp ')' Stmt  */
#line 179 "ss.y"
                                   {
              (yyval.node) = new Node("WhileStmt", (yylsp[-4]).first_line);
              (yyval.node)->child.push_back((yyvsp[-2].node)); (yyval.node)->child.push_back((yyvsp[0].node));
          }
#line 1634 "ss.tab.c"
    break;

  case 37: /* Stmt: BREAK ';'  */
#line 183 "ss.y"
                      { (yyval.node) = new Node("BreakStmt", (yylsp[-1]).first_line); }
#line 1640 "ss.tab.c"
    break;

  case 38: /* Stmt: CONTINUE ';'  */
#line 184 "ss.y"
                         { (yyval.node) = new Node("ContinueStmt", (yylsp[-1]).first_line); }
#line 1646 "ss.tab.c"
    break;

  case 39: /* Exp: LOrExp  */
#line 187 "ss.y"
                   { (yyval.node)=(yyvsp[0].node); }
#line 1652 "ss.tab.c"
    break;

  case 40: /* LOrExp: LAndExp  */
#line 188 "ss.y"
                    { (yyval.node)=(yyvsp[0].node); }
#line 1658 "ss.tab.c"
    break;

  case 41: /* LOrExp: LOrExp OR LAndExp  */
#line 189 "ss.y"
                              { (yyval.node)=new Node("LOrExp",(yylsp[-2]).first_line); (yyval.node)->child.push_back((yyvsp[-2].node)); (yyval.node)->child.push_back((yyvsp[0].node)); }
#line 1664 "ss.tab.c"
    break;

  case 42: /* LAndExp: EqExp  */
#line 190 "ss.y"
                  { (yyval.node)=(yyvsp[0].node); }
#line 1670 "ss.tab.c"
    break;

  case 43: /* LAndExp: LAndExp AND EqExp  */
#line 191 "ss.y"
                              { (yyval.node)=new Node("LAndExp",(yylsp[-2]).first_line); (yyval.node)->child.push_back((yyvsp[-2].node)); (yyval.node)->child.push_back((yyvsp[0].node)); }
#line 1676 "ss.tab.c"
    break;

  case 44: /* EqExp: RelExp  */
#line 192 "ss.y"
                   { (yyval.node)=(yyvsp[0].node); }
#line 1682 "ss.tab.c"
    break;

  case 45: /* EqExp: EqExp EQL RelExp  */
#line 193 "ss.y"
                             { (yyval.node)=new Node("EqExp",(yylsp[-2]).first_line,"=="); (yyval.node)->child.push_back((yyvsp[-2].node)); (yyval.node)->child.push_back((yyvsp[0].node)); }
#line 1688 "ss.tab.c"
    break;

  case 46: /* EqExp: EqExp NEQ RelExp  */
#line 194 "ss.y"
                             { (yyval.node)=new Node("EqExp",(yylsp[-2]).first_line,"!="); (yyval.node)->child.push_back((yyvsp[-2].node)); (yyval.node)->child.push_back((yyvsp[0].node)); }
#line 1694 "ss.tab.c"
    break;

  case 47: /* RelExp: AddExp  */
#line 195 "ss.y"
                   { (yyval.node)=(yyvsp[0].node); }
#line 1700 "ss.tab.c"
    break;

  case 48: /* RelExp: RelExp '<' AddExp  */
#line 196 "ss.y"
                              { (yyval.node)=new Node("RelExp",(yylsp[-2]).first_line,"<"); (yyval.node)->child.push_back((yyvsp[-2].node)); (yyval.node)->child.push_back((yyvsp[0].node)); }
#line 1706 "ss.tab.c"
    break;

  case 49: /* RelExp: RelExp '>' AddExp  */
#line 197 "ss.y"
                              { (yyval.node)=new Node("RelExp",(yylsp[-2]).first_line,">"); (yyval.node)->child.push_back((yyvsp[-2].node)); (yyval.node)->child.push_back((yyvsp[0].node)); }
#line 1712 "ss.tab.c"
    break;

  case 50: /* AddExp: MulExp  */
#line 198 "ss.y"
                   { (yyval.node)=(yyvsp[0].node); }
#line 1718 "ss.tab.c"
    break;

  case 51: /* AddExp: AddExp '+' MulExp  */
#line 199 "ss.y"
                              { (yyval.node)=new Node("AddExp",(yylsp[-2]).first_line,"+"); (yyval.node)->child.push_back((yyvsp[-2].node)); (yyval.node)->child.push_back((yyvsp[0].node)); }
#line 1724 "ss.tab.c"
    break;

  case 52: /* AddExp: AddExp '-' MulExp  */
#line 200 "ss.y"
                              { (yyval.node)=new Node("AddExp",(yylsp[-2]).first_line,"-"); (yyval.node)->child.push_back((yyvsp[-2].node)); (yyval.node)->child.push_back((yyvsp[0].node)); }
#line 1730 "ss.tab.c"
    break;

  case 53: /* MulExp: UnaryExp  */
#line 201 "ss.y"
                     { (yyval.node)=(yyvsp[0].node); }
#line 1736 "ss.tab.c"
    break;

  case 54: /* MulExp: MulExp '*' UnaryExp  */
#line 202 "ss.y"
                                { (yyval.node)=new Node("MulExp",(yylsp[-2]).first_line,"*"); (yyval.node)->child.push_back((yyvsp[-2].node)); (yyval.node)->child.push_back((yyvsp[0].node)); }
#line 1742 "ss.tab.c"
    break;

  case 55: /* MulExp: MulExp '/' UnaryExp  */
#line 203 "ss.y"
                                { (yyval.node)=new Node("MulExp",(yylsp[-2]).first_line,"/"); (yyval.node)->child.push_back((yyvsp[-2].node)); (yyval.node)->child.push_back((yyvsp[0].node)); }
#line 1748 "ss.tab.c"
    break;

  case 56: /* UnaryExp: PrimaryExp  */
#line 205 "ss.y"
                       { (yyval.node)=(yyvsp[0].node); }
#line 1754 "ss.tab.c"
    break;

  case 57: /* UnaryExp: ID '(' ')'  */
#line 206 "ss.y"
                       {
              (yyval.node) = new Node("FuncCall", (yylsp[-2]).first_line);
              (yyval.node)->child.push_back(new Node("Ident", (yylsp[-2]).first_line, *(yyvsp[-2].str)));
          }
#line 1763 "ss.tab.c"
    break;

  case 58: /* UnaryExp: ID '(' FuncRParams ')'  */
#line 210 "ss.y"
                                   {
              (yyval.node) = new Node("FuncCall", (yylsp[-3]).first_line);
              (yyval.node)->child.push_back(new Node("Ident", (yylsp[-3]).first_line, *(yyvsp[-3].str)));
              (yyval.node)->child.push_back((yyvsp[-1].node));
          }
#line 1773 "ss.tab.c"
    break;

  case 59: /* UnaryExp: ID '(' FuncRParams error  */
#line 215 "ss.y"
                                     {
              // 错误恢复：允许缺少右括号的函数调用
              (yyval.node) = new Node("FuncCall", (yylsp[-3]).first_line);
              (yyval.node)->child.push_back(new Node("Ident", (yylsp[-3]).first_line, *(yyvsp[-3].str)));
              (yyval.node)->child.push_back((yyvsp[-1].node));
          }
#line 1784 "ss.tab.c"
    break;

  case 60: /* UnaryExp: ID '(' error  */
#line 221 "ss.y"
                         {
              // 错误恢复：允许缺少参数和右括号的函数调用
              (yyval.node) = new Node("FuncCall", (yylsp[-2]).first_line);
              (yyval.node)->child.push_back(new Node("Ident", (yylsp[-2]).first_line, *(yyvsp[-2].str)));
          }
#line 1794 "ss.tab.c"
    break;

  case 61: /* FuncRParams: Exp  */
#line 228 "ss.y"
                  { (yyval.node) = new Node("FuncRParams", (yylsp[0]).first_line); (yyval.node)->child.push_back((yyvsp[0].node)); }
#line 1800 "ss.tab.c"
    break;

  case 62: /* FuncRParams: FuncRParams ',' Exp  */
#line 229 "ss.y"
                                  { (yyval.node)=(yyvsp[-2].node); (yyval.node)->child.push_back((yyvsp[0].node)); }
#line 1806 "ss.tab.c"
    break;

  case 63: /* PrimaryExp: '(' Exp ')'  */
#line 232 "ss.y"
                         { (yyval.node)=(yyvsp[-1].node); }
#line 1812 "ss.tab.c"
    break;

  case 64: /* PrimaryExp: LVal  */
#line 233 "ss.y"
                  { (yyval.node)=(yyvsp[0].node); }
#line 1818 "ss.tab.c"
    break;

  case 65: /* PrimaryExp: INTCON  */
#line 234 "ss.y"
                    { (yyval.node) = new Node("Number", (yylsp[0]).first_line); (yyval.node)->child.push_back(new Node("INTCON",0,*(yyvsp[0].str))); }
#line 1824 "ss.tab.c"
    break;

  case 66: /* PrimaryExp: OCTCON  */
#line 235 "ss.y"
                    { (yyval.node) = new Node("Number", (yylsp[0]).first_line); (yyval.node)->child.push_back(new Node("INTCON",0,*(yyvsp[0].str))); }
#line 1830 "ss.tab.c"
    break;

  case 67: /* PrimaryExp: HEXCON  */
#line 236 "ss.y"
                    { (yyval.node) = new Node("Number", (yylsp[0]).first_line); (yyval.node)->child.push_back(new Node("INTCON",0,*(yyvsp[0].str))); }
#line 1836 "ss.tab.c"
    break;

  case 68: /* PrimaryExp: FLOATCON  */
#line 237 "ss.y"
                      { (yyval.node) = new Node("Number", (yylsp[0]).first_line); (yyval.node)->child.push_back(new Node("FLOATCON",0,*(yyvsp[0].str))); }
#line 1842 "ss.tab.c"
    break;

  case 69: /* LVal: ID  */
#line 240 "ss.y"
               {
              (yyval.node) = new Node("LVal", (yylsp[0]).first_line);
              (yyval.node)->child.push_back(new Node("Ident", (yylsp[0]).first_line, *(yyvsp[0].str)));
          }
#line 1851 "ss.tab.c"
    break;

  case 70: /* LVal: LVal '[' Exp ']'  */
#line 244 "ss.y"
                             {
              (yyval.node) = (yyvsp[-3].node);
              (yyval.node)->child.push_back(new Node("Index", (yylsp[-2]).first_line)); // 标记下标
              (yyval.node)->child.back()->child.push_back((yyvsp[-1].node));
          }
#line 1861 "ss.tab.c"
    break;


#line 1865 "ss.tab.c"

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
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;
  *++yylsp = yyloc;

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
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  yyerror_range[1] = yylloc;
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
                      yytoken, &yylval, &yylloc);
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
  ++yynerrs;

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

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  ++yylsp;
  YYLLOC_DEFAULT (*yylsp, yyerror_range, 2);

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, yylsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 250 "ss.y"


void yyerror(const char *s){
    has_parse_error = true;
    printf("Error type B at Line %d: %s\n", yylineno, s);
}

void Node::print(int dep){
    for(int i=0;i<dep;i++) putchar(' ');
    printf("%s",name.c_str());
    if(line) printf(" (%d)",line);
    if(!attr.empty()) printf(": %s",attr.c_str());
    putchar('\n');
    for(auto c:child) if(c) c->print(dep+2);
}

int main(int argc,char **argv){
    if(argc<2){fprintf(stderr,"Usage: %s <file.sy>\n",argv[0]); return 1;}
    FILE *f=fopen(argv[1],"r");
    if(!f){perror(argv[1]); return 1;}
    yyin=f;
    yyparse();
    
    // 即使有语法错误，如果AST已构建，也尝试进行语义分析以报告语义错误
    // 语法错误已经在yyerror中报告了
    if(!has_lex_error && root) {
        // 进行语义分析
        semantic_analysis(root);
        // 如果没有语义错误，可打印 AST 验证或输出 success（根据任务要求）
        // if(!has_semantic_error) printf("success\n");
    }
    fclose(f);
    return 0;
}
