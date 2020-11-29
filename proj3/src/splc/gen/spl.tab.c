/* A Bison parser, made by GNU Bison 3.7.2.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.7.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "src/splc/spl.y"

    #include "lex.yy.c"
    #include "../ext/node.h"
    #include "../ext/ce.h"
    #include "../../spp/spp.h"
    #include "../../ssa/ssa.h"
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <fstream>
    void yyerror(const char* msg) { printf("FUCK"); }
    extern int err_cnt;
    extern ERROR err_arr[MAX_ERR];

#line 86 "src/splc/gen/spl.tab.c"

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

#include "spl.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_ERR = 3,                        /* ERR  */
  YYSYMBOL_INT = 4,                        /* INT  */
  YYSYMBOL_FLOAT = 5,                      /* FLOAT  */
  YYSYMBOL_CHAR = 6,                       /* CHAR  */
  YYSYMBOL_ID = 7,                         /* ID  */
  YYSYMBOL_TYPE = 8,                       /* TYPE  */
  YYSYMBOL_STRUCT = 9,                     /* STRUCT  */
  YYSYMBOL_IF = 10,                        /* IF  */
  YYSYMBOL_ELSE = 11,                      /* ELSE  */
  YYSYMBOL_WHILE = 12,                     /* WHILE  */
  YYSYMBOL_FOR = 13,                       /* FOR  */
  YYSYMBOL_RETURN = 14,                    /* RETURN  */
  YYSYMBOL_DOT = 15,                       /* DOT  */
  YYSYMBOL_SEMI = 16,                      /* SEMI  */
  YYSYMBOL_COMMA = 17,                     /* COMMA  */
  YYSYMBOL_ASSIGN = 18,                    /* ASSIGN  */
  YYSYMBOL_LT = 19,                        /* LT  */
  YYSYMBOL_LE = 20,                        /* LE  */
  YYSYMBOL_GT = 21,                        /* GT  */
  YYSYMBOL_GE = 22,                        /* GE  */
  YYSYMBOL_NE = 23,                        /* NE  */
  YYSYMBOL_EQ = 24,                        /* EQ  */
  YYSYMBOL_PLUS = 25,                      /* PLUS  */
  YYSYMBOL_MINUS = 26,                     /* MINUS  */
  YYSYMBOL_MUL = 27,                       /* MUL  */
  YYSYMBOL_DIV = 28,                       /* DIV  */
  YYSYMBOL_AND = 29,                       /* AND  */
  YYSYMBOL_OR = 30,                        /* OR  */
  YYSYMBOL_NOT = 31,                       /* NOT  */
  YYSYMBOL_LP = 32,                        /* LP  */
  YYSYMBOL_RP = 33,                        /* RP  */
  YYSYMBOL_LB = 34,                        /* LB  */
  YYSYMBOL_RB = 35,                        /* RB  */
  YYSYMBOL_LC = 36,                        /* LC  */
  YYSYMBOL_RC = 37,                        /* RC  */
  YYSYMBOL_BinaryOp_1 = 38,                /* BinaryOp_1  */
  YYSYMBOL_BinaryOp_2 = 39,                /* BinaryOp_2  */
  YYSYMBOL_BinaryOp_3 = 40,                /* BinaryOp_3  */
  YYSYMBOL_NON_TER = 41,                   /* NON_TER  */
  YYSYMBOL_EMPTY = 42,                     /* EMPTY  */
  YYSYMBOL_END = 43,                       /* END  */
  YYSYMBOL_UMINUS = 44,                    /* UMINUS  */
  YYSYMBOL_YYACCEPT = 45,                  /* $accept  */
  YYSYMBOL_Program = 46,                   /* Program  */
  YYSYMBOL_ExtDefList = 47,                /* ExtDefList  */
  YYSYMBOL_ExtDef = 48,                    /* ExtDef  */
  YYSYMBOL_ExtDecList = 49,                /* ExtDecList  */
  YYSYMBOL_Specifier = 50,                 /* Specifier  */
  YYSYMBOL_StructSpecifier = 51,           /* StructSpecifier  */
  YYSYMBOL_VarDec = 52,                    /* VarDec  */
  YYSYMBOL_FunDec = 53,                    /* FunDec  */
  YYSYMBOL_VarList = 54,                   /* VarList  */
  YYSYMBOL_ParamDec = 55,                  /* ParamDec  */
  YYSYMBOL_CompSt = 56,                    /* CompSt  */
  YYSYMBOL_StmtList = 57,                  /* StmtList  */
  YYSYMBOL_Stmt = 58,                      /* Stmt  */
  YYSYMBOL_OpenStmt = 59,                  /* OpenStmt  */
  YYSYMBOL_CloseStmt = 60,                 /* CloseStmt  */
  YYSYMBOL_DefList = 61,                   /* DefList  */
  YYSYMBOL_Def = 62,                       /* Def  */
  YYSYMBOL_DecList = 63,                   /* DecList  */
  YYSYMBOL_Dec = 64,                       /* Dec  */
  YYSYMBOL_ExpSuffix = 65,                 /* ExpSuffix  */
  YYSYMBOL_NullableExp = 66,               /* NullableExp  */
  YYSYMBOL_Exp = 67,                       /* Exp  */
  YYSYMBOL_Args = 68,                      /* Args  */
  YYSYMBOL_EID = 69                        /* EID  */
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
#define YYFINAL  15
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   461

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  45
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  25
/* YYNRULES -- Number of rules.  */
#define YYNRULES  107
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  193

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   299


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
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    53,    53,    59,    65,    69,    76,    83,    90,    93,
      98,   101,   105,   110,   119,   124,   130,   139,   147,   152,
     161,   170,   177,   181,   186,   190,   196,   201,   209,   214,
     220,   225,   234,   240,   244,   245,   247,   257,   269,   281,
     290,   293,   296,   299,   302,   305,   309,   316,   321,   328,
     340,   352,   361,   364,   369,   372,   377,   380,   383,   386,
     393,   399,   403,   410,   413,   416,   421,   426,   433,   438,
     447,   448,   449,   450,   451,   452,   453,   454,   455,   456,
     457,   459,   460,   462,   469,   476,   483,   490,   497,   504,
     511,   517,   523,   531,   538,   546,   553,   560,   565,   570,
     575,   580,   584,   588,   591,   596,   603,   604
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
  "\"end of file\"", "error", "\"invalid token\"", "ERR", "INT", "FLOAT",
  "CHAR", "ID", "TYPE", "STRUCT", "IF", "ELSE", "WHILE", "FOR", "RETURN",
  "DOT", "SEMI", "COMMA", "ASSIGN", "LT", "LE", "GT", "GE", "NE", "EQ",
  "PLUS", "MINUS", "MUL", "DIV", "AND", "OR", "NOT", "LP", "RP", "LB",
  "RB", "LC", "RC", "BinaryOp_1", "BinaryOp_2", "BinaryOp_3", "NON_TER",
  "EMPTY", "END", "UMINUS", "$accept", "Program", "ExtDefList", "ExtDef",
  "ExtDecList", "Specifier", "StructSpecifier", "VarDec", "FunDec",
  "VarList", "ParamDec", "CompSt", "StmtList", "Stmt", "OpenStmt",
  "CloseStmt", "DefList", "Def", "DecList", "Dec", "ExpSuffix",
  "NullableExp", "Exp", "Args", "EID", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299
};
#endif

#define YYPACT_NINF (-108)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-83)

#define yytable_value_is_error(Yyn) \
  ((Yyn) == YYTABLE_NINF)

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
       9,   185,  -108,     8,    12,  -108,     9,   202,  -108,  -108,
    -108,  -108,   -17,    29,    27,  -108,  -108,  -108,   159,   -11,
     -17,    29,   283,  -108,   111,    85,    41,  -108,     8,    71,
    -108,     8,     8,   318,   283,    13,  -108,     8,    20,    68,
      55,  -108,  -108,  -108,  -108,    80,    63,   145,   110,   162,
    -108,  -108,  -108,   139,   140,   142,   412,   412,   412,   412,
    -108,   146,   318,  -108,  -108,   175,    61,   163,  -108,  -108,
    -108,   172,   172,   118,  -108,   222,  -108,  -108,   412,  -108,
       8,    43,  -108,   375,   382,   412,    95,   123,   123,   164,
    -108,  -108,  -108,    72,   412,     8,   412,   412,   412,   412,
     412,   412,   412,   412,   367,  -108,  -108,   133,  -108,   226,
    -108,  -108,  -108,   184,   113,   189,   147,   212,   226,   121,
    -108,  -108,  -108,  -108,   243,  -108,   421,    -1,   236,   130,
     181,   174,    -1,   123,   394,  -108,   209,    51,  -108,   333,
     333,   333,   333,   333,   333,   412,  -108,  -108,  -108,  -108,
    -108,  -108,  -108,  -108,  -108,  -108,  -108,  -108,  -108,  -108,
    -108,   412,   394,  -108,  -108,   214,  -108,   225,  -108,   229,
    -108,  -108,  -108,  -108,  -108,  -108,   221,  -108,  -108,   333,
     333,   333,   412,  -108,  -108,  -108,  -108,  -108,  -108,   217,
     333,  -108,  -108
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,    14,     0,     0,     2,     0,     0,    15,   107,
     106,    10,     0,     0,    17,     1,     3,     6,     0,    12,
       0,    18,     0,    11,     0,     0,     0,     5,     0,     0,
       7,     0,     0,    33,     0,     0,    21,     0,     0,    26,
       0,     8,     9,    13,    18,     0,    68,     0,    66,     0,
     100,    98,    99,     0,     0,     0,     0,     0,     0,     0,
      47,     0,    33,    34,    35,     0,     0,    97,    60,    24,
      25,    30,    29,     0,    20,     0,    16,    19,     0,    63,
       0,     0,    62,     0,     0,    81,     0,    90,    91,     0,
      31,    32,    46,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    22,    23,     0,    27,    69,
      67,    64,    65,     0,     0,     0,     0,     0,    82,     0,
      48,    96,    54,    55,   103,    95,    87,    85,    88,    89,
       0,    83,    84,    86,     0,    93,   104,     0,    28,    81,
      81,    81,    81,    81,    81,    81,    52,    53,    94,    70,
      80,    71,    79,    77,    78,    72,    73,    74,    75,    76,
     102,     0,     0,    92,    41,    35,    40,    35,    36,    35,
      44,    58,    45,    59,    39,    51,     0,   105,   101,    81,
      81,    81,    81,    43,    57,    42,    56,    37,    49,     0,
      81,    38,    50
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -108,  -108,   239,  -108,   231,     7,  -108,    -3,   235,   178,
    -108,   129,   192,    93,  -107,   -73,    98,  -108,   -24,  -108,
     101,   -80,   -56,    96,    23
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     4,     5,     6,    18,    32,     8,    46,    12,    38,
      39,    60,    61,    62,    63,    64,    33,    34,    47,    48,
     160,    65,    66,   137,    67
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      86,    87,    88,    89,    19,   117,    28,     7,    49,    -4,
       1,     9,    15,     7,    95,    10,     9,     2,     3,    22,
      10,    73,   109,    29,    13,    19,    14,   114,   116,   118,
      21,    37,    71,   100,    72,   170,   172,   174,   124,   103,
     126,   127,   128,   129,   130,   131,   132,   133,   136,    69,
      70,    44,   162,    74,    44,    44,   110,    41,    44,   111,
      44,    24,    93,    25,    94,   176,   165,   167,   169,   171,
     173,   175,   183,   185,   187,    45,    95,   -82,    42,    96,
     112,    78,    37,   191,   163,    75,    31,    97,   122,   118,
      98,    99,    76,     2,     3,   100,   119,    29,    94,   101,
     102,   103,   189,    44,    71,   136,   184,   186,   188,   123,
      95,   120,    35,    96,   140,    77,    94,   192,   125,     2,
       3,    97,   -61,    40,    98,    99,   118,    80,    95,   100,
      44,    96,    68,   101,   102,   103,     9,   146,    95,    97,
      10,    23,    98,    99,    36,    95,   141,   100,   143,    30,
      94,   101,   102,   103,   105,   106,    97,   100,   147,    98,
      26,    79,    95,    81,   100,    96,   138,    94,   101,   102,
     103,    83,    84,    97,    85,    27,    98,    99,    82,    95,
     144,   100,    96,    90,    94,   101,   102,   103,     9,    95,
      97,    92,    10,    98,    99,   104,    95,   121,   100,    96,
      97,    11,   101,   102,   103,     9,    29,    97,   100,    10,
      98,    99,    94,   102,   103,   100,   148,   139,    17,   101,
     102,   103,   142,   107,    95,   179,   161,    96,   145,    94,
       2,     3,   164,   166,   168,    97,   180,   182,    98,    99,
     181,    95,    20,   100,    96,    16,   -83,   101,   102,   103,
     190,    95,    97,   108,    91,    98,    99,   177,    95,    43,
     100,    96,    97,   178,   101,   102,   103,     0,     0,    97,
     100,     0,    98,    99,   101,   102,   103,   100,     0,     0,
       0,   101,   102,   103,    31,     0,   -61,   -61,   -61,   -61,
     -61,     2,     3,   -61,     0,   -61,   -61,   -61,     0,   -61,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   -61,
       0,     0,     0,     0,   -61,   -61,     0,     0,     0,   -61,
     -61,     9,    50,    51,    52,    10,     0,     0,    53,     0,
      54,    55,    56,     0,   -81,     0,     9,    50,    51,    52,
      10,     0,     0,    53,    57,    54,    55,    56,     0,    58,
      59,     0,     0,     0,    22,     0,     0,     0,     0,    57,
       0,     0,     0,     0,    58,    59,     0,     0,   134,    22,
       9,    50,    51,    52,    10,     0,   113,     0,     9,    50,
      51,    52,    10,   115,     0,     9,    50,    51,    52,    10,
       0,     0,     0,    57,     0,     0,     0,     0,    58,    59,
     135,    57,     0,     0,     0,     0,    58,    59,    57,   149,
     150,   151,   152,    58,    59,     9,    50,    51,    52,    10,
       0,     0,     0,   153,   154,     0,   155,     0,   156,     0,
       0,     0,   157,   158,   159,     0,    95,     0,    57,    96,
       0,     0,     0,    58,    59,     0,     0,    97,     0,     0,
      98,    99,     0,     0,     0,   100,     0,     0,     0,   101,
     102,   103
};

static const yytype_int16 yycheck[] =
{
      56,    57,    58,    59,     7,    85,    17,     0,    32,     0,
       1,     3,     0,     6,    15,     7,     3,     8,     9,    36,
       7,     1,    78,    34,     1,    28,     3,    83,    84,    85,
       7,    24,    35,    34,    37,   142,   143,   144,    94,    40,
      96,    97,    98,    99,   100,   101,   102,   103,   104,    36,
      37,    28,     1,    33,    31,    32,    80,    16,    35,    16,
      37,    32,     1,    36,     3,   145,   139,   140,   141,   142,
     143,   144,   179,   180,   181,     4,    15,    16,    37,    18,
      37,    18,    75,   190,    33,    17,     1,    26,    16,   145,
      29,    30,    37,     8,     9,    34,     1,    34,     3,    38,
      39,    40,   182,    80,   107,   161,   179,   180,   181,    37,
      15,    16,     1,    18,     1,    35,     3,   190,    95,     8,
       9,    26,    37,    25,    29,    30,   182,    17,    15,    34,
     107,    18,    34,    38,    39,    40,     3,    16,    15,    26,
       7,    12,    29,    30,    33,    15,    33,    34,     1,    20,
       3,    38,    39,    40,    36,    37,    26,    34,    37,    29,
       1,    16,    15,     1,    34,    18,    33,     3,    38,    39,
      40,    32,    32,    26,    32,    16,    29,    30,    16,    15,
      33,    34,    18,    37,     3,    38,    39,    40,     3,    15,
      26,    16,     7,    29,    30,    32,    15,    33,    34,    18,
      26,    16,    38,    39,    40,     3,    34,    26,    34,     7,
      29,    30,     3,    39,    40,    34,    35,    33,    16,    38,
      39,    40,    33,     1,    15,    11,    17,    18,    16,     3,
       8,     9,   139,   140,   141,    26,    11,    16,    29,    30,
      11,    15,     7,    34,    18,     6,     3,    38,    39,    40,
      33,    15,    26,    75,    62,    29,    30,   161,    15,    28,
      34,    18,    26,   162,    38,    39,    40,    -1,    -1,    26,
      34,    -1,    29,    30,    38,    39,    40,    34,    -1,    -1,
      -1,    38,    39,    40,     1,    -1,     3,     4,     5,     6,
       7,     8,     9,    10,    -1,    12,    13,    14,    -1,    16,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    26,
      -1,    -1,    -1,    -1,    31,    32,    -1,    -1,    -1,    36,
      37,     3,     4,     5,     6,     7,    -1,    -1,    10,    -1,
      12,    13,    14,    -1,    16,    -1,     3,     4,     5,     6,
       7,    -1,    -1,    10,    26,    12,    13,    14,    -1,    31,
      32,    -1,    -1,    -1,    36,    -1,    -1,    -1,    -1,    26,
      -1,    -1,    -1,    -1,    31,    32,    -1,    -1,     1,    36,
       3,     4,     5,     6,     7,    -1,     1,    -1,     3,     4,
       5,     6,     7,     1,    -1,     3,     4,     5,     6,     7,
      -1,    -1,    -1,    26,    -1,    -1,    -1,    -1,    31,    32,
      33,    26,    -1,    -1,    -1,    -1,    31,    32,    26,    15,
      16,    17,    18,    31,    32,     3,     4,     5,     6,     7,
      -1,    -1,    -1,    29,    30,    -1,    32,    -1,    34,    -1,
      -1,    -1,    38,    39,    40,    -1,    15,    -1,    26,    18,
      -1,    -1,    -1,    31,    32,    -1,    -1,    26,    -1,    -1,
      29,    30,    -1,    -1,    -1,    34,    -1,    -1,    -1,    38,
      39,    40
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     1,     8,     9,    46,    47,    48,    50,    51,     3,
       7,    16,    53,    69,    69,     0,    47,    16,    49,    52,
      53,    69,    36,    56,    32,    36,     1,    16,    17,    34,
      56,     1,    50,    61,    62,     1,    33,    50,    54,    55,
      61,    16,    37,    49,    69,     4,    52,    63,    64,    63,
       4,     5,     6,    10,    12,    13,    14,    26,    31,    32,
      56,    57,    58,    59,    60,    66,    67,    69,    61,    36,
      37,    52,    52,     1,    33,    17,    37,    35,    18,    16,
      17,     1,    16,    32,    32,    32,    67,    67,    67,    67,
      37,    57,    16,     1,     3,    15,    18,    26,    29,    30,
      34,    38,    39,    40,    32,    36,    37,     1,    54,    67,
      63,    16,    37,     1,    67,     1,    67,    66,    67,     1,
      16,    33,    16,    37,    67,    69,    67,    67,    67,    67,
      67,    67,    67,    67,     1,    33,    67,    68,    33,    33,
       1,    33,    33,     1,    33,    16,    16,    37,    35,    15,
      16,    17,    18,    29,    30,    32,    34,    38,    39,    40,
      65,    17,     1,    33,    58,    60,    58,    60,    58,    60,
      59,    60,    59,    60,    59,    60,    66,    68,    65,    11,
      11,    11,    16,    59,    60,    59,    60,    59,    60,    66,
      33,    59,    60
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    45,    46,    47,    47,    48,    48,    48,    48,    48,
      48,    48,    49,    49,    50,    50,    51,    51,    52,    52,
      53,    53,    53,    53,    53,    53,    54,    54,    54,    55,
      55,    56,    57,    57,    58,    58,    59,    59,    59,    59,
      59,    59,    59,    59,    59,    59,    60,    60,    60,    60,
      60,    60,    60,    60,    60,    60,    60,    60,    60,    60,
      61,    61,    62,    62,    62,    62,    63,    63,    64,    64,
      65,    65,    65,    65,    65,    65,    65,    65,    65,    65,
      65,    66,    66,    67,    67,    67,    67,    67,    67,    67,
      67,    67,    67,    67,    67,    67,    67,    67,    67,    67,
      67,    67,    67,    67,    68,    68,    69,    69
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     0,     3,     2,     3,     4,     4,
       2,     3,     1,     3,     1,     1,     5,     2,     1,     4,
       4,     3,     5,     5,     4,     4,     1,     3,     4,     2,
       2,     4,     2,     0,     1,     1,     5,     7,     9,     5,
       5,     5,     7,     7,     5,     5,     2,     1,     3,     7,
       9,     5,     4,     4,     3,     3,     7,     7,     5,     5,
       2,     0,     3,     3,     4,     4,     1,     3,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     1,     3,     3,     3,     3,     3,     3,     3,
       2,     2,     4,     3,     4,     3,     3,     1,     1,     1,
       1,     5,     4,     3,     1,     3,     1,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

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

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


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
# ifndef YY_LOCATION_PRINT
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yykind < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yykind], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
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
                       &yyvsp[(yyi + 1) - (yynrhs)]);
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
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
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

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

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
  YY_STACK_PRINT (yyss, yyssp);

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
#  undef YYSTACK_RELOCATE
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
  case 2: /* Program: ExtDefList  */
#line 53 "src/splc/spl.y"
                    {
        NODE* cur = new_node("Program", 1, NON_TER, (yyvsp[0].node)->lineno);
        insert(cur, (yyvsp[0].node));
        set_root(cur);
    }
#line 1326 "src/splc/gen/spl.tab.c"
    break;

  case 3: /* ExtDefList: ExtDef ExtDefList  */
#line 59 "src/splc/spl.y"
                              {
        NODE* cur = new_node("ExtDefList", 1, NON_TER, (yyvsp[-1].node)->lineno);
        insert(cur, (yyvsp[-1].node));
        insert(cur, (yyvsp[0].node));
        (yyval.node) = cur;
    }
#line 1337 "src/splc/gen/spl.tab.c"
    break;

  case 4: /* ExtDefList: %empty  */
#line 65 "src/splc/spl.y"
             {
        (yyval.node) = NULL;
    }
#line 1345 "src/splc/gen/spl.tab.c"
    break;

  case 5: /* ExtDef: Specifier ExtDecList SEMI  */
#line 69 "src/splc/spl.y"
                                  {
        NODE* cur = new_node("ExtDef", 1, NON_TER, (yyvsp[-2].node)->lineno);
        insert(cur, (yyvsp[-2].node));
        insert(cur, (yyvsp[-1].node));
        insert(cur, (yyvsp[0].node));
        (yyval.node) = cur;
    }
#line 1357 "src/splc/gen/spl.tab.c"
    break;

  case 6: /* ExtDef: Specifier SEMI  */
#line 76 "src/splc/spl.y"
                     {
        NODE* cur = new_node("ExtDef", 2, NON_TER, (yyvsp[-1].node)->lineno);
        insert(cur, (yyvsp[-1].node));
        insert(cur, (yyvsp[0].node));
        (yyval.node) = cur;
    }
#line 1368 "src/splc/gen/spl.tab.c"
    break;

  case 7: /* ExtDef: Specifier FunDec CompSt  */
#line 83 "src/splc/spl.y"
                              {
        NODE* cur = new_node("ExtDef", 3, NON_TER, (yyvsp[-2].node)->lineno);
        insert(cur, (yyvsp[-2].node));
        insert(cur, (yyvsp[-1].node));
        insert(cur, (yyvsp[0].node));
        (yyval.node) = cur;
    }
#line 1380 "src/splc/gen/spl.tab.c"
    break;

  case 8: /* ExtDef: Specifier ExtDecList error SEMI  */
#line 90 "src/splc/spl.y"
                                      {
        add_err(ErrorType::SYNTAX, (yyvsp[-3].node)->lineno, "Missing Semicolon", "");
    }
#line 1388 "src/splc/gen/spl.tab.c"
    break;

  case 9: /* ExtDef: Specifier ExtDecList error RC  */
#line 93 "src/splc/spl.y"
                                    {
        unput('}');
        add_err(ErrorType::SYNTAX, (yyvsp[-3].node)->lineno, "Missing Semicolon", "");
        
    }
#line 1398 "src/splc/gen/spl.tab.c"
    break;

  case 10: /* ExtDef: error SEMI  */
#line 98 "src/splc/spl.y"
                 {
        add_err(ErrorType::SYNTAX, (yyvsp[0].node)->lineno, "Missing Specifier", "");
    }
#line 1406 "src/splc/gen/spl.tab.c"
    break;

  case 11: /* ExtDef: error FunDec CompSt  */
#line 101 "src/splc/spl.y"
                          {
        add_err(ErrorType::SYNTAX, (yyvsp[-1].node)->lineno, "Missing Specifier", "");
    }
#line 1414 "src/splc/gen/spl.tab.c"
    break;

  case 12: /* ExtDecList: VarDec  */
#line 105 "src/splc/spl.y"
                   {
        NODE* cur = new_node("ExtDecList", 1, NON_TER, (yyvsp[0].node)->lineno);
        insert(cur, (yyvsp[0].node));
        (yyval.node) = cur;
    }
#line 1424 "src/splc/gen/spl.tab.c"
    break;

  case 13: /* ExtDecList: VarDec COMMA ExtDecList  */
#line 110 "src/splc/spl.y"
                              {
        NODE* cur = new_node("ExtDecList", 2, NON_TER, (yyvsp[-2].node)->lineno);
        insert(cur, (yyvsp[-2].node));
        insert(cur, (yyvsp[-1].node));
        insert(cur, (yyvsp[0].node));
        (yyval.node) = cur;
    }
#line 1436 "src/splc/gen/spl.tab.c"
    break;

  case 14: /* Specifier: TYPE  */
#line 119 "src/splc/spl.y"
                {
        NODE* cur = new_node("Specifier", 1, NON_TER, (yyvsp[0].node)->lineno);
        insert(cur, (yyvsp[0].node));
        (yyval.node) = cur;
    }
#line 1446 "src/splc/gen/spl.tab.c"
    break;

  case 15: /* Specifier: StructSpecifier  */
#line 124 "src/splc/spl.y"
                      {
        NODE* cur = new_node("Specifier", 2, NON_TER, (yyvsp[0].node)->lineno);
        insert(cur, (yyvsp[0].node));
        (yyval.node) = cur;
    }
#line 1456 "src/splc/gen/spl.tab.c"
    break;

  case 16: /* StructSpecifier: STRUCT EID LC DefList RC  */
#line 130 "src/splc/spl.y"
                                          {
        NODE* cur = new_node("StructSpecifier", 1, NON_TER, (yyvsp[-4].node)->lineno);
        insert(cur, (yyvsp[-4].node));
        insert(cur, (yyvsp[-3].node));
        insert(cur, (yyvsp[-2].node));
        insert(cur, (yyvsp[-1].node));
        insert(cur, (yyvsp[0].node));
        (yyval.node) = cur;
    }
#line 1470 "src/splc/gen/spl.tab.c"
    break;

  case 17: /* StructSpecifier: STRUCT EID  */
#line 139 "src/splc/spl.y"
                 {
        NODE* cur = new_node("StructSpecifier", 2, NON_TER, (yyvsp[-1].node)->lineno);
        insert(cur, (yyvsp[-1].node));
        insert(cur, (yyvsp[0].node));
        (yyval.node) = cur;
    }
#line 1481 "src/splc/gen/spl.tab.c"
    break;

  case 18: /* VarDec: EID  */
#line 147 "src/splc/spl.y"
            {
        NODE* cur = new_node("VarDec", 1, NON_TER, (yyvsp[0].node)->lineno);
        insert(cur, (yyvsp[0].node));
        (yyval.node) = cur;
    }
#line 1491 "src/splc/gen/spl.tab.c"
    break;

  case 19: /* VarDec: VarDec LB INT RB  */
#line 152 "src/splc/spl.y"
                       {
        NODE* cur = new_node("VarDec", 2, NON_TER, (yyvsp[-3].node)->lineno);
        insert(cur, (yyvsp[-3].node));
        insert(cur, (yyvsp[-2].node));
        insert(cur, (yyvsp[-1].node));
        insert(cur, (yyvsp[0].node));
        (yyval.node) = cur;
    }
#line 1504 "src/splc/gen/spl.tab.c"
    break;

  case 20: /* FunDec: EID LP VarList RP  */
#line 161 "src/splc/spl.y"
                          {
        NODE* cur = new_node("FunDec", 1, NON_TER, (yyvsp[-3].node)->lineno);
        fflush(stdout);
        insert(cur, (yyvsp[-3].node));
        insert(cur, (yyvsp[-2].node));
        insert(cur, (yyvsp[-1].node));
        insert(cur, (yyvsp[0].node));
        (yyval.node) = cur;
    }
#line 1518 "src/splc/gen/spl.tab.c"
    break;

  case 21: /* FunDec: EID LP RP  */
#line 170 "src/splc/spl.y"
                {
        NODE* cur = new_node("FunDec", 2, NON_TER, (yyvsp[-2].node)->lineno);
        insert(cur, (yyvsp[-2].node));
        insert(cur, (yyvsp[-1].node));
        insert(cur, (yyvsp[0].node));
        (yyval.node) = cur;
    }
#line 1530 "src/splc/gen/spl.tab.c"
    break;

  case 22: /* FunDec: EID LP VarList error LC  */
#line 177 "src/splc/spl.y"
                              {
        unput('{');
        add_err(ErrorType::SYNTAX, (yyvsp[-4].node)->lineno, "Missing Right Parenthesis", "");
    }
#line 1539 "src/splc/gen/spl.tab.c"
    break;

  case 23: /* FunDec: EID LP VarList error RC  */
#line 181 "src/splc/spl.y"
                              {
        unput('}');
        add_err(ErrorType::SYNTAX, (yyvsp[-4].node)->lineno, "Missing Right Parenthesis", "");
        
    }
#line 1549 "src/splc/gen/spl.tab.c"
    break;

  case 24: /* FunDec: EID LP error LC  */
#line 186 "src/splc/spl.y"
                      {
        unput('{');
        add_err(ErrorType::SYNTAX, (yyvsp[-3].node)->lineno, "Missing Right Parenthesis", "");
    }
#line 1558 "src/splc/gen/spl.tab.c"
    break;

  case 25: /* FunDec: EID LP error RC  */
#line 190 "src/splc/spl.y"
                      {
        unput('}');
        add_err(ErrorType::SYNTAX, (yyvsp[-3].node)->lineno, "Missing Right Parenthesis", "");
        
    }
#line 1568 "src/splc/gen/spl.tab.c"
    break;

  case 26: /* VarList: ParamDec  */
#line 196 "src/splc/spl.y"
                  {
        NODE* cur = new_node("VarList", 1, NON_TER, (yyvsp[0].node)->lineno);
        insert(cur, (yyvsp[0].node));
        (yyval.node) = cur;
    }
#line 1578 "src/splc/gen/spl.tab.c"
    break;

  case 27: /* VarList: ParamDec COMMA VarList  */
#line 201 "src/splc/spl.y"
                             {
        NODE* cur = new_node("VarList", 2, NON_TER, (yyvsp[-2].node)->lineno);
        insert(cur, (yyvsp[-2].node));
        insert(cur, (yyvsp[-1].node));
        insert(cur, (yyvsp[0].node));
        (yyval.node) = cur;
    }
#line 1590 "src/splc/gen/spl.tab.c"
    break;

  case 28: /* VarList: ParamDec COMMA error RP  */
#line 209 "src/splc/spl.y"
                              {
        unput(')');
        add_err(ErrorType::SYNTAX, (yyvsp[-3].node)->lineno, "Extra Comma", "");
    }
#line 1599 "src/splc/gen/spl.tab.c"
    break;

  case 29: /* ParamDec: Specifier VarDec  */
#line 214 "src/splc/spl.y"
                           {
        NODE* cur = new_node("ParamDec", 1, NON_TER, (yyvsp[-1].node)->lineno);
        insert(cur, (yyvsp[-1].node));
        insert(cur, (yyvsp[0].node));
        (yyval.node) = cur;
}
#line 1610 "src/splc/gen/spl.tab.c"
    break;

  case 30: /* ParamDec: error VarDec  */
#line 220 "src/splc/spl.y"
                   {
        add_err(ErrorType::SYNTAX, (yyvsp[0].node)->lineno, "Missing Specifier", "");
}
#line 1618 "src/splc/gen/spl.tab.c"
    break;

  case 31: /* CompSt: LC DefList StmtList RC  */
#line 225 "src/splc/spl.y"
                               {
        NODE* cur = new_node("CompSt", 1, NON_TER, (yyvsp[-3].node)->lineno);
        insert(cur, (yyvsp[-3].node));
        insert(cur, (yyvsp[-2].node));
        insert(cur, (yyvsp[-1].node));
        insert(cur, (yyvsp[0].node));
        (yyval.node) = cur;
}
#line 1631 "src/splc/gen/spl.tab.c"
    break;

  case 32: /* StmtList: Stmt StmtList  */
#line 234 "src/splc/spl.y"
                        {
        NODE* cur = new_node("StmtList", 1, NON_TER, (yyvsp[-1].node)->lineno);
        insert(cur, (yyvsp[-1].node));
        insert(cur, (yyvsp[0].node));
        (yyval.node) = cur;
    }
#line 1642 "src/splc/gen/spl.tab.c"
    break;

  case 33: /* StmtList: %empty  */
#line 240 "src/splc/spl.y"
             { 
        (yyval.node) = NULL;
    }
#line 1650 "src/splc/gen/spl.tab.c"
    break;

  case 36: /* OpenStmt: IF LP Exp RP Stmt  */
#line 247 "src/splc/spl.y"
                            {
        NODE* cur = new_node("Stmt", 1, NON_TER, (yyvsp[-4].node)->lineno);
        insert(cur, (yyvsp[-4].node));
        insert(cur, (yyvsp[-3].node));
        insert(cur, (yyvsp[-2].node));
        insert(cur, (yyvsp[-1].node));
        insert(cur, (yyvsp[0].node));
        (yyval.node) = cur;
    }
#line 1664 "src/splc/gen/spl.tab.c"
    break;

  case 37: /* OpenStmt: IF LP Exp RP CloseStmt ELSE OpenStmt  */
#line 257 "src/splc/spl.y"
                                           {
        NODE* cur = new_node("Stmt", 2, NON_TER, (yyvsp[-6].node)->lineno);
        insert(cur, (yyvsp[-6].node));
        insert(cur, (yyvsp[-5].node));
        insert(cur, (yyvsp[-4].node));
        insert(cur, (yyvsp[-3].node));
        insert(cur, (yyvsp[-2].node));
        insert(cur, (yyvsp[-1].node));
        insert(cur, (yyvsp[0].node));
        (yyval.node) = cur;
    }
#line 1680 "src/splc/gen/spl.tab.c"
    break;

  case 38: /* OpenStmt: FOR LP NullableExp SEMI NullableExp SEMI NullableExp RP OpenStmt  */
#line 269 "src/splc/spl.y"
                                                                       {
        NODE* cur = new_node("Stmt", 3, NON_TER, (yyvsp[-8].node)->lineno);
        insert(cur, (yyvsp[-8].node));
        insert(cur, (yyvsp[-7].node));
        insert(cur, (yyvsp[-6].node));
        insert(cur, (yyvsp[-5].node));
        insert(cur, (yyvsp[-4].node));
        insert(cur, (yyvsp[-3].node));
        insert(cur, (yyvsp[-2].node));
        insert(cur, (yyvsp[-1].node));
        insert(cur, (yyvsp[0].node));
    }
#line 1697 "src/splc/gen/spl.tab.c"
    break;

  case 39: /* OpenStmt: WHILE LP Exp RP OpenStmt  */
#line 281 "src/splc/spl.y"
                               {
        NODE* cur = new_node("Stmt", 4, NON_TER, (yyvsp[-4].node)->lineno);
        insert(cur, (yyvsp[-4].node));
        insert(cur, (yyvsp[-3].node));
        insert(cur, (yyvsp[-2].node));
        insert(cur, (yyvsp[-1].node));
        insert(cur, (yyvsp[0].node));
        (yyval.node) = cur;
    }
#line 1711 "src/splc/gen/spl.tab.c"
    break;

  case 40: /* OpenStmt: IF LP Exp error Stmt  */
#line 290 "src/splc/spl.y"
                           {
        add_err(ErrorType::SYNTAX, (yyvsp[-4].node)->lineno, "Missing Right Parenthesis", "");
    }
#line 1719 "src/splc/gen/spl.tab.c"
    break;

  case 41: /* OpenStmt: IF LP error RP Stmt  */
#line 293 "src/splc/spl.y"
                          {
        add_err(ErrorType::SYNTAX, (yyvsp[-4].node)->lineno, "Missing Expression", "");
    }
#line 1727 "src/splc/gen/spl.tab.c"
    break;

  case 42: /* OpenStmt: IF LP Exp error CloseStmt ELSE OpenStmt  */
#line 296 "src/splc/spl.y"
                                              {
        add_err(ErrorType::SYNTAX, (yyvsp[-6].node)->lineno, "Missing Right Parenthesis", "");
    }
#line 1735 "src/splc/gen/spl.tab.c"
    break;

  case 43: /* OpenStmt: IF LP error RP CloseStmt ELSE OpenStmt  */
#line 299 "src/splc/spl.y"
                                             {
        add_err(ErrorType::SYNTAX, (yyvsp[-6].node)->lineno, "Missing Expression", "");
    }
#line 1743 "src/splc/gen/spl.tab.c"
    break;

  case 44: /* OpenStmt: WHILE LP error RP OpenStmt  */
#line 302 "src/splc/spl.y"
                                 {
        add_err(ErrorType::SYNTAX, (yyvsp[-4].node)->lineno, "Missing Expression", "");
    }
#line 1751 "src/splc/gen/spl.tab.c"
    break;

  case 45: /* OpenStmt: WHILE LP Exp error OpenStmt  */
#line 305 "src/splc/spl.y"
                                  {
        add_err(ErrorType::SYNTAX, (yyvsp[-4].node)->lineno, "Missing Right Parenthesis", "");
    }
#line 1759 "src/splc/gen/spl.tab.c"
    break;

  case 46: /* CloseStmt: NullableExp SEMI  */
#line 309 "src/splc/spl.y"
                            {
        NODE* cur = new_node("Stmt", 5, NON_TER, (yyvsp[-1].node)->lineno);
        insert(cur, (yyvsp[-1].node));
        insert(cur, (yyvsp[0].node));
        (yyval.node) = cur;
    }
#line 1770 "src/splc/gen/spl.tab.c"
    break;

  case 47: /* CloseStmt: CompSt  */
#line 316 "src/splc/spl.y"
             {
        NODE* cur = new_node("Stmt", 6, NON_TER, (yyvsp[0].node)->lineno);
        insert(cur, (yyvsp[0].node));
        (yyval.node) = cur;
    }
#line 1780 "src/splc/gen/spl.tab.c"
    break;

  case 48: /* CloseStmt: RETURN Exp SEMI  */
#line 321 "src/splc/spl.y"
                      {        
        NODE* cur = new_node("Stmt", 7, NON_TER, (yyvsp[-2].node)->lineno);
        insert(cur, (yyvsp[-2].node));
        insert(cur, (yyvsp[-1].node));
        insert(cur, (yyvsp[0].node));
        (yyval.node) = cur;
    }
#line 1792 "src/splc/gen/spl.tab.c"
    break;

  case 49: /* CloseStmt: IF LP Exp RP CloseStmt ELSE CloseStmt  */
#line 328 "src/splc/spl.y"
                                            {
        NODE* cur = new_node("Stmt", 8, NON_TER, (yyvsp[-6].node)->lineno);
        insert(cur, (yyvsp[-6].node));
        insert(cur, (yyvsp[-5].node));
        insert(cur, (yyvsp[-4].node));
        insert(cur, (yyvsp[-3].node));
        insert(cur, (yyvsp[-2].node));
        insert(cur, (yyvsp[-1].node));
        insert(cur, (yyvsp[0].node));
        (yyval.node) = cur;
    }
#line 1808 "src/splc/gen/spl.tab.c"
    break;

  case 50: /* CloseStmt: FOR LP NullableExp SEMI NullableExp SEMI NullableExp RP CloseStmt  */
#line 340 "src/splc/spl.y"
                                                                        {
        NODE* cur = new_node("Stmt", 9, NON_TER, (yyvsp[-8].node)->lineno);
        insert(cur, (yyvsp[-8].node));
        insert(cur, (yyvsp[-7].node));
        insert(cur, (yyvsp[-6].node));
        insert(cur, (yyvsp[-5].node));
        insert(cur, (yyvsp[-4].node));
        insert(cur, (yyvsp[-3].node));
        insert(cur, (yyvsp[-2].node));
        insert(cur, (yyvsp[-1].node));
        insert(cur, (yyvsp[0].node));
    }
#line 1825 "src/splc/gen/spl.tab.c"
    break;

  case 51: /* CloseStmt: WHILE LP Exp RP CloseStmt  */
#line 352 "src/splc/spl.y"
                                {
        NODE* cur = new_node("Stmt", 10, NON_TER, (yyvsp[-4].node)->lineno);
        insert(cur, (yyvsp[-4].node));
        insert(cur, (yyvsp[-3].node));
        insert(cur, (yyvsp[-2].node));
        insert(cur, (yyvsp[-1].node));
        insert(cur, (yyvsp[0].node));
        (yyval.node) = cur;
    }
#line 1839 "src/splc/gen/spl.tab.c"
    break;

  case 52: /* CloseStmt: RETURN Exp error SEMI  */
#line 361 "src/splc/spl.y"
                            {     
        add_err(ErrorType::SYNTAX, (yyvsp[-3].node)->lineno, "Missing Semicolon", "");   
    }
#line 1847 "src/splc/gen/spl.tab.c"
    break;

  case 53: /* CloseStmt: RETURN Exp error RC  */
#line 364 "src/splc/spl.y"
                          {
        unput('}');
        add_err(ErrorType::SYNTAX, (yyvsp[-3].node)->lineno, "Missing Semicolon", "");
        
    }
#line 1857 "src/splc/gen/spl.tab.c"
    break;

  case 54: /* CloseStmt: Exp error SEMI  */
#line 369 "src/splc/spl.y"
                     {
        add_err(ErrorType::SYNTAX, (yyvsp[-2].node)->lineno, "Missing Semicolon", "");
    }
#line 1865 "src/splc/gen/spl.tab.c"
    break;

  case 55: /* CloseStmt: Exp error RC  */
#line 372 "src/splc/spl.y"
                   {
        unput('}');
        add_err(ErrorType::SYNTAX, (yyvsp[-2].node)->lineno, "Missing Semicolon", "");
        
    }
#line 1875 "src/splc/gen/spl.tab.c"
    break;

  case 56: /* CloseStmt: IF LP Exp error CloseStmt ELSE CloseStmt  */
#line 377 "src/splc/spl.y"
                                               {
        add_err(ErrorType::SYNTAX, (yyvsp[-6].node)->lineno, "Missing Semicolon", "");   
    }
#line 1883 "src/splc/gen/spl.tab.c"
    break;

  case 57: /* CloseStmt: IF LP error RP CloseStmt ELSE CloseStmt  */
#line 380 "src/splc/spl.y"
                                              {
        add_err(ErrorType::SYNTAX, (yyvsp[-6].node)->lineno, "Missing Expression", "");   
    }
#line 1891 "src/splc/gen/spl.tab.c"
    break;

  case 58: /* CloseStmt: WHILE LP error RP CloseStmt  */
#line 383 "src/splc/spl.y"
                                  {
        add_err(ErrorType::SYNTAX, (yyvsp[-4].node)->lineno, "Missing Expression", "");   
    }
#line 1899 "src/splc/gen/spl.tab.c"
    break;

  case 59: /* CloseStmt: WHILE LP Exp error CloseStmt  */
#line 386 "src/splc/spl.y"
                                   {
        add_err(ErrorType::SYNTAX, (yyvsp[-4].node)->lineno, "Missing Semicolon", "");   
    }
#line 1907 "src/splc/gen/spl.tab.c"
    break;

  case 60: /* DefList: Def DefList  */
#line 393 "src/splc/spl.y"
                     {
        NODE* cur = new_node("DefList", 1, NON_TER, (yyvsp[-1].node)->lineno);
        insert(cur, (yyvsp[-1].node));
        insert(cur, (yyvsp[0].node));
        (yyval.node) = cur;
    }
#line 1918 "src/splc/gen/spl.tab.c"
    break;

  case 61: /* DefList: %empty  */
#line 399 "src/splc/spl.y"
             { 
        (yyval.node) = NULL;
    }
#line 1926 "src/splc/gen/spl.tab.c"
    break;

  case 62: /* Def: Specifier DecList SEMI  */
#line 403 "src/splc/spl.y"
                            {
        NODE* cur = new_node("Def", 1, NON_TER, (yyvsp[-2].node)->lineno);
        insert(cur, (yyvsp[-2].node));
        insert(cur, (yyvsp[-1].node));
        insert(cur, (yyvsp[0].node));
        (yyval.node) = cur;
    }
#line 1938 "src/splc/gen/spl.tab.c"
    break;

  case 63: /* Def: error DecList SEMI  */
#line 410 "src/splc/spl.y"
                         {
        add_err(ErrorType::SYNTAX, yylineno, "Missing Specifier", "");
    }
#line 1946 "src/splc/gen/spl.tab.c"
    break;

  case 64: /* Def: Specifier DecList error SEMI  */
#line 413 "src/splc/spl.y"
                                   {
        add_err(ErrorType::SYNTAX, (yyvsp[-3].node)->lineno, "Missing Semicolon", "");
    }
#line 1954 "src/splc/gen/spl.tab.c"
    break;

  case 65: /* Def: Specifier DecList error RC  */
#line 416 "src/splc/spl.y"
                                 {
        unput('}');
        add_err(ErrorType::SYNTAX, (yyvsp[-3].node)->lineno, "Missing Semicolon", "");
        
    }
#line 1964 "src/splc/gen/spl.tab.c"
    break;

  case 66: /* DecList: Dec  */
#line 421 "src/splc/spl.y"
             {
        NODE* cur = new_node("DecList", 1, NON_TER, (yyvsp[0].node)->lineno);
        insert(cur, (yyvsp[0].node));
        (yyval.node) = cur;
    }
#line 1974 "src/splc/gen/spl.tab.c"
    break;

  case 67: /* DecList: Dec COMMA DecList  */
#line 426 "src/splc/spl.y"
                        {
        NODE* cur = new_node("DecList", 2, NON_TER, (yyvsp[-2].node)->lineno);
        insert(cur, (yyvsp[-2].node));
        insert(cur, (yyvsp[-1].node));
        insert(cur, (yyvsp[0].node));
        (yyval.node) = cur;
    }
#line 1986 "src/splc/gen/spl.tab.c"
    break;

  case 68: /* Dec: VarDec  */
#line 433 "src/splc/spl.y"
            {
        NODE* cur = new_node("Dec", 1, NON_TER, (yyvsp[0].node)->lineno);
        insert(cur, (yyvsp[0].node));
        (yyval.node) = cur;
}
#line 1996 "src/splc/gen/spl.tab.c"
    break;

  case 69: /* Dec: VarDec ASSIGN Exp  */
#line 438 "src/splc/spl.y"
                       {
        NODE* cur = new_node("Dec", 2, NON_TER, (yyvsp[-2].node)->lineno);
        insert(cur, (yyvsp[-2].node));
        insert(cur, (yyvsp[-1].node));
        insert(cur, (yyvsp[0].node));
        (yyval.node) = cur;
    }
#line 2008 "src/splc/gen/spl.tab.c"
    break;

  case 81: /* NullableExp: %empty  */
#line 459 "src/splc/spl.y"
                    { (yyval.node) = new_node("Null", 0, NON_TER, yylineno); }
#line 2014 "src/splc/gen/spl.tab.c"
    break;

  case 83: /* Exp: Exp BinaryOp_1 Exp  */
#line 462 "src/splc/spl.y"
                        {
        NODE* cur = new_node("Exp", 1, NON_TER, (yyvsp[-2].node)->lineno);
        insert(cur, (yyvsp[-2].node));
        insert(cur, (yyvsp[-1].node));
        insert(cur, (yyvsp[0].node));
        (yyval.node) = cur;
    }
#line 2026 "src/splc/gen/spl.tab.c"
    break;

  case 84: /* Exp: Exp BinaryOp_2 Exp  */
#line 469 "src/splc/spl.y"
                         {
        NODE* cur = new_node("Exp", 2, NON_TER, (yyvsp[-2].node)->lineno);
        insert(cur, (yyvsp[-2].node));
        insert(cur, (yyvsp[-1].node));
        insert(cur, (yyvsp[0].node));
        (yyval.node) = cur;
    }
#line 2038 "src/splc/gen/spl.tab.c"
    break;

  case 85: /* Exp: Exp MINUS Exp  */
#line 476 "src/splc/spl.y"
                    {
        NODE* cur = new_node("Exp", 2, NON_TER, (yyvsp[-2].node)->lineno);
        insert(cur, (yyvsp[-2].node));
        insert(cur, (yyvsp[-1].node));
        insert(cur, (yyvsp[0].node));
        (yyval.node) = cur;
    }
#line 2050 "src/splc/gen/spl.tab.c"
    break;

  case 86: /* Exp: Exp BinaryOp_3 Exp  */
#line 483 "src/splc/spl.y"
                         {
        NODE* cur = new_node("Exp", 3, NON_TER, (yyvsp[-2].node)->lineno);
        insert(cur, (yyvsp[-2].node));
        insert(cur, (yyvsp[-1].node));
        insert(cur, (yyvsp[0].node));
        (yyval.node) = cur;
    }
#line 2062 "src/splc/gen/spl.tab.c"
    break;

  case 87: /* Exp: Exp ASSIGN Exp  */
#line 490 "src/splc/spl.y"
                     {
        NODE* cur = new_node("Exp", 4, NON_TER, (yyvsp[-2].node)->lineno);
        insert(cur, (yyvsp[-2].node));
        insert(cur, (yyvsp[-1].node));
        insert(cur, (yyvsp[0].node));
        (yyval.node) = cur;
    }
#line 2074 "src/splc/gen/spl.tab.c"
    break;

  case 88: /* Exp: Exp AND Exp  */
#line 497 "src/splc/spl.y"
                  {
        NODE* cur = new_node("Exp", 5, NON_TER, (yyvsp[-2].node)->lineno);
        insert(cur, (yyvsp[-2].node));
        insert(cur, (yyvsp[-1].node));
        insert(cur, (yyvsp[0].node));
        (yyval.node) = cur;
    }
#line 2086 "src/splc/gen/spl.tab.c"
    break;

  case 89: /* Exp: Exp OR Exp  */
#line 504 "src/splc/spl.y"
                 {
        NODE* cur = new_node("Exp", 6, NON_TER, (yyvsp[-2].node)->lineno);
        insert(cur, (yyvsp[-2].node));
        insert(cur, (yyvsp[-1].node));
        insert(cur, (yyvsp[0].node));
        (yyval.node) = cur;
    }
#line 2098 "src/splc/gen/spl.tab.c"
    break;

  case 90: /* Exp: MINUS Exp  */
#line 511 "src/splc/spl.y"
                             {
        NODE* cur = new_node("Exp", 7, NON_TER, (yyvsp[-1].node)->lineno);
        insert(cur, (yyvsp[-1].node));
        insert(cur, (yyvsp[0].node));
        (yyval.node) = cur;
    }
#line 2109 "src/splc/gen/spl.tab.c"
    break;

  case 91: /* Exp: NOT Exp  */
#line 517 "src/splc/spl.y"
              {
        NODE* cur = new_node("Exp", 8, NON_TER, (yyvsp[-1].node)->lineno);
        insert(cur, (yyvsp[-1].node));
        insert(cur, (yyvsp[0].node));
        (yyval.node) = cur;
    }
#line 2120 "src/splc/gen/spl.tab.c"
    break;

  case 92: /* Exp: EID LP Args RP  */
#line 523 "src/splc/spl.y"
                     {
        NODE* cur = new_node("Exp", 9, NON_TER, (yyvsp[-3].node)->lineno);
        insert(cur, (yyvsp[-3].node));
        insert(cur, (yyvsp[-2].node));
        insert(cur, (yyvsp[-1].node));
        insert(cur, (yyvsp[0].node));
        (yyval.node) = cur;
    }
#line 2133 "src/splc/gen/spl.tab.c"
    break;

  case 93: /* Exp: EID LP RP  */
#line 531 "src/splc/spl.y"
                {
        NODE* cur = new_node("Exp", 10, NON_TER, (yyvsp[-2].node)->lineno);
        insert(cur, (yyvsp[-2].node));
        insert(cur, (yyvsp[-1].node));
        insert(cur, (yyvsp[0].node));
        (yyval.node) = cur;
    }
#line 2145 "src/splc/gen/spl.tab.c"
    break;

  case 94: /* Exp: Exp LB Exp RB  */
#line 538 "src/splc/spl.y"
                    {
        NODE* cur = new_node("Exp", 11, NON_TER, (yyvsp[-3].node)->lineno);
        insert(cur, (yyvsp[-3].node));
        insert(cur, (yyvsp[-2].node));
        insert(cur, (yyvsp[-1].node));
        insert(cur, (yyvsp[0].node));
        (yyval.node) = cur;
    }
#line 2158 "src/splc/gen/spl.tab.c"
    break;

  case 95: /* Exp: Exp DOT EID  */
#line 546 "src/splc/spl.y"
                  {
        NODE* cur = new_node("Exp", 12, NON_TER, (yyvsp[-2].node)->lineno);
        insert(cur, (yyvsp[-2].node));
        insert(cur, (yyvsp[-1].node));
        insert(cur, (yyvsp[0].node));
        (yyval.node) = cur;
    }
#line 2170 "src/splc/gen/spl.tab.c"
    break;

  case 96: /* Exp: LP Exp RP  */
#line 553 "src/splc/spl.y"
                {
        NODE* cur = new_node("Exp", 13, NON_TER, (yyvsp[-2].node)->lineno);
        insert(cur, (yyvsp[-2].node));
        insert(cur, (yyvsp[-1].node));
        insert(cur, (yyvsp[0].node));
        (yyval.node) = cur;
    }
#line 2182 "src/splc/gen/spl.tab.c"
    break;

  case 97: /* Exp: EID  */
#line 560 "src/splc/spl.y"
          {
        NODE* cur = new_node("Exp", 14, NON_TER, (yyvsp[0].node)->lineno);
        insert(cur, (yyvsp[0].node));
        (yyval.node) = cur;
    }
#line 2192 "src/splc/gen/spl.tab.c"
    break;

  case 98: /* Exp: FLOAT  */
#line 565 "src/splc/spl.y"
            {
        NODE* cur = new_node("Exp", 15, NON_TER, (yyvsp[0].node)->lineno);
        insert(cur, (yyvsp[0].node));
        (yyval.node) = cur;
    }
#line 2202 "src/splc/gen/spl.tab.c"
    break;

  case 99: /* Exp: CHAR  */
#line 570 "src/splc/spl.y"
           {
        NODE* cur = new_node("Exp", 16, NON_TER, (yyvsp[0].node)->lineno);
        insert(cur, (yyvsp[0].node));
        (yyval.node) = cur;
    }
#line 2212 "src/splc/gen/spl.tab.c"
    break;

  case 100: /* Exp: INT  */
#line 575 "src/splc/spl.y"
          {
        NODE* cur = new_node("Exp", 17, NON_TER, (yyvsp[0].node)->lineno);
        insert(cur, (yyvsp[0].node));
        (yyval.node) = cur;
    }
#line 2222 "src/splc/gen/spl.tab.c"
    break;

  case 101: /* Exp: EID LP Args error ExpSuffix  */
#line 580 "src/splc/spl.y"
                                  {
        yyless(strlen((yyvsp[0].node)->node_val));
        add_err(ErrorType::SYNTAX, (yyvsp[-4].node)->lineno, "Missing Right Parenthesis", "");
    }
#line 2231 "src/splc/gen/spl.tab.c"
    break;

  case 102: /* Exp: EID LP error ExpSuffix  */
#line 584 "src/splc/spl.y"
                             {
        yyless(strlen((yyvsp[0].node)->node_val));
        add_err(ErrorType::SYNTAX, (yyvsp[-3].node)->lineno, "Missing Right Parenthesis.", "");
    }
#line 2240 "src/splc/gen/spl.tab.c"
    break;

  case 103: /* Exp: Exp ERR Exp  */
#line 588 "src/splc/spl.y"
                  {
        
    }
#line 2248 "src/splc/gen/spl.tab.c"
    break;

  case 104: /* Args: Exp  */
#line 591 "src/splc/spl.y"
          {
        NODE* cur = new_node("Args", 1, NON_TER, (yyvsp[0].node)->lineno);
        insert(cur, (yyvsp[0].node));
        (yyval.node) = cur;
    }
#line 2258 "src/splc/gen/spl.tab.c"
    break;

  case 105: /* Args: Exp COMMA Args  */
#line 596 "src/splc/spl.y"
                    {
        NODE* cur = new_node("Args", 2, NON_TER, (yyvsp[-2].node)->lineno);
        insert(cur, (yyvsp[-2].node));
        insert(cur, (yyvsp[-1].node));
        insert(cur, (yyvsp[0].node));
        (yyval.node) = cur;
    }
#line 2270 "src/splc/gen/spl.tab.c"
    break;

  case 107: /* EID: ERR  */
#line 604 "src/splc/spl.y"
          {
        (yyval.node) = new_node("Null", 0, NON_TER, (yyvsp[0].node)->lineno);
    }
#line 2278 "src/splc/gen/spl.tab.c"
    break;


#line 2282 "src/splc/gen/spl.tab.c"

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


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

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


#if !defined yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturn;
#endif


/*-------------------------------------------------------.
| yyreturn -- parsing is finished, clean up and return.  |
`-------------------------------------------------------*/
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
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 608 "src/splc/spl.y"

int main(int argc,char *argv[])
{
    std::fstream fin, fout;
    std::string path = std::string(argv[1]);
    fin.open(argv[1]);

    std::string out = path.substr(0, path.length()-3) + "out";
    fout.open(out, std::ios::out);
    freopen(out.c_str(), "w", stdout);

    auto token = into_lines(fin);
    token = file_inclusion(token);
    std::string proc_input = to_str(token);
    yy_switch_to_buffer(yy_scan_string(proc_input.c_str()));
    yyparse();
    for(int i = 0; i < err_cnt; i++)
        print_err(err_arr+i);
    IRList irs = semantic_analysis(get_root());
    for (auto i : irs) {
        std::cout << i.str() << std::endl;
    }
    return 0;
}
