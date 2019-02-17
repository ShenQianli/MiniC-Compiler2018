/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     TYPE = 258,
     IF = 259,
     ELSE = 260,
     WHILE = 261,
     MAIN = 262,
     RETURN = 263,
     DO = 264,
     FOR = 265,
     AND = 266,
     OR = 267,
     EQ = 268,
     NEQ = 269,
     PP = 270,
     MM = 271,
     NUM = 272,
     ID = 273
   };
#endif
/* Tokens.  */
#define TYPE 258
#define IF 259
#define ELSE 260
#define WHILE 261
#define MAIN 262
#define RETURN 263
#define DO 264
#define FOR 265
#define AND 266
#define OR 267
#define EQ 268
#define NEQ 269
#define PP 270
#define MM 271
#define NUM 272
#define ID 273




/* Copy the first part of user declarations.  */
#line 1 "MiniC.y"

#include "globals.h"
#include "mytree.h"


extern TreeNode * root;
int yylex();
int yyerror(char *);



/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 13 "MiniC.y"
{
    int vint;
    char * vstr;
    struct treeNode * vtree;
}
/* Line 193 of yacc.c.  */
#line 149 "y.tab.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 162 "y.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
}
#endif

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
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
  yytype_int16 yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   431

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  36
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  14
/* YYNRULES -- Number of rules.  */
#define YYNRULES  60
/* YYNRULES -- Number of states.  */
#define YYNSTATES  150

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   273

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    26,     2,     2,     2,    15,     2,     2,
      32,    33,    13,    11,    31,    12,     2,    14,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    27,
      17,    28,    16,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    29,     2,    30,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    34,     2,    35,     2,     2,     2,     2,
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
       5,     6,     7,     8,     9,    10,    18,    19,    20,    21,
      22,    23,    24,    25
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     6,     9,    12,    15,    16,    20,    26,
      33,    36,    41,    47,    49,    53,    56,    59,    60,    68,
      77,    83,    90,    98,   101,   102,   106,   112,   120,   126,
     136,   141,   149,   151,   155,   158,   166,   168,   172,   176,
     180,   184,   188,   192,   196,   200,   204,   208,   212,   216,
     221,   223,   225,   228,   231,   234,   237,   240,   243,   247,
     252
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      37,     0,    -1,    38,    45,    -1,    38,    39,    -1,    38,
      43,    -1,    38,    44,    -1,    -1,     3,    25,    27,    -1,
       3,    25,    28,    49,    27,    -1,     3,    25,    29,    24,
      30,    27,    -1,     3,    25,    -1,     3,    25,    29,    30,
      -1,     3,    25,    29,    24,    30,    -1,    40,    -1,    41,
      31,    40,    -1,    42,    44,    -1,    42,    47,    -1,    -1,
       3,    25,    32,    33,    34,    42,    35,    -1,     3,    25,
      32,    41,    33,    34,    42,    35,    -1,     3,    25,    32,
      33,    27,    -1,     3,    25,    32,    41,    33,    27,    -1,
       3,     7,    32,    33,    34,    42,    35,    -1,    46,    47,
      -1,    -1,    34,    46,    35,    -1,     4,    32,    49,    33,
      47,    -1,     4,    32,    49,    33,    47,     5,    47,    -1,
       6,    32,    49,    33,    47,    -1,    10,    32,    47,    49,
      27,    25,    22,    33,    47,    -1,    25,    28,    49,    27,
      -1,    25,    29,    49,    30,    28,    49,    27,    -1,    39,
      -1,     8,    49,    27,    -1,    49,    27,    -1,     9,    47,
       6,    32,    49,    33,    27,    -1,    49,    -1,    48,    31,
      49,    -1,    49,    11,    49,    -1,    49,    12,    49,    -1,
      49,    13,    49,    -1,    49,    14,    49,    -1,    49,    15,
      49,    -1,    49,    16,    49,    -1,    49,    17,    49,    -1,
      49,    20,    49,    -1,    49,    21,    49,    -1,    49,    18,
      49,    -1,    49,    19,    49,    -1,    25,    29,    49,    30,
      -1,    24,    -1,    25,    -1,    12,    49,    -1,    26,    49,
      -1,    22,    25,    -1,    23,    25,    -1,    25,    22,    -1,
      25,    23,    -1,    32,    49,    33,    -1,    25,    32,    48,
      33,    -1,    25,    32,    33,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    36,    36,    44,    55,    66,    78,    81,    87,    97,
     107,   113,   119,   129,   131,   141,   152,   164,   167,   174,
     184,   190,   199,   203,   215,   218,   223,   229,   236,   242,
     255,   262,   270,   272,   277,   282,   290,   292,   302,   310,
     318,   326,   334,   342,   350,   358,   366,   374,   382,   391,
     398,   404,   410,   417,   424,   433,   442,   451,   460,   467,
     475
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "TYPE", "IF", "ELSE", "WHILE", "MAIN",
  "RETURN", "DO", "FOR", "'+'", "'-'", "'*'", "'/'", "'%'", "'>'", "'<'",
  "AND", "OR", "EQ", "NEQ", "PP", "MM", "NUM", "ID", "'!'", "';'", "'='",
  "'['", "']'", "','", "'('", "')'", "'{'", "'}'", "$accept", "Program",
  "DDSeq", "VarDefn", "VarDecl", "VarDeclSeq", "FuncBody", "FuncDefn",
  "FuncDecl", "MainFunc", "StmtSeq", "Stmt", "ExpSeq", "Exp", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,    43,    45,    42,    47,    37,    62,    60,   266,   267,
     268,   269,   270,   271,   272,   273,    33,    59,    61,    91,
      93,    44,    40,    41,   123,   125
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    36,    37,    38,    38,    38,    38,    39,    39,    39,
      40,    40,    40,    41,    41,    42,    42,    42,    43,    43,
      44,    44,    45,    46,    46,    47,    47,    47,    47,    47,
      47,    47,    47,    47,    47,    47,    48,    48,    49,    49,
      49,    49,    49,    49,    49,    49,    49,    49,    49,    49,
      49,    49,    49,    49,    49,    49,    49,    49,    49,    49,
      49
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     2,     2,     2,     0,     3,     5,     6,
       2,     4,     5,     1,     3,     2,     2,     0,     7,     8,
       5,     6,     7,     2,     0,     3,     5,     7,     5,     9,
       4,     7,     1,     3,     2,     7,     1,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     4,
       1,     1,     2,     2,     2,     2,     2,     2,     3,     4,
       3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       6,     0,     0,     1,     0,     3,     4,     5,     2,     0,
       0,     0,     7,     0,     0,     0,     0,     0,     0,     0,
      50,    51,     0,     0,     0,     0,     0,     0,    13,     0,
      17,    52,    54,    55,    56,    57,     0,     0,    53,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     8,     0,    10,    20,    17,     0,     0,     0,     0,
      60,     0,    36,    58,    38,    39,    40,    41,    42,    43,
      44,    47,    48,    45,    46,     9,     0,     0,    14,    21,
      17,     0,     0,     0,     0,     0,     0,    51,    24,    22,
      32,    15,    16,     0,    49,     0,    59,     0,    11,    18,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    34,    37,    12,    19,     0,     0,     0,    33,     0,
       0,     0,     0,     0,    25,    23,     0,     0,     0,     0,
       0,     0,    30,    49,     0,    26,    28,     0,     0,     0,
       0,     0,     0,     0,    27,    35,     0,    31,     0,    29
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     1,     2,    90,    28,    29,    58,     6,    91,     8,
     110,    92,    61,    93
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -69
static const yytype_int16 yypact[] =
{
     -69,    19,    17,   -69,    -4,   -69,   -69,   -69,   -69,    11,
      30,    36,   -69,   -10,    28,     5,    40,   -10,    52,    66,
     -69,   108,   -10,   -10,   308,    62,    68,    -9,   -69,    23,
     -69,   221,   -69,   -69,   -69,   -69,   -10,   138,   -69,   200,
     -10,   -10,   -10,   -10,   -10,   -10,   -10,   -10,   -10,   -10,
     -10,   -69,    67,    73,   -69,   -69,   100,    21,    41,   268,
     -69,    37,   410,   -69,   221,   221,   173,   173,   173,   -69,
     -69,   252,   107,   -69,   -69,   -69,    16,    75,   -69,   -69,
     -69,    79,    89,    93,   -10,   176,    97,    83,   -69,   -69,
     -69,   -69,   -69,   325,   -69,   -10,   -69,   109,   -69,   -69,
     110,   177,   -10,   -10,   342,   113,   135,   176,   -10,   -10,
     143,   -69,   410,   -69,   -69,     8,   211,   234,   -69,   -22,
     111,   -10,   359,   288,   -69,   -69,   121,    55,   176,   176,
     -10,   376,   -69,   126,   129,   152,   -69,   245,   133,   -10,
     176,   132,   150,   393,   -69,   -69,   140,   -69,   176,   -69
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -69,   -69,   -69,   172,   120,    72,   -54,   -69,   179,   -69,
     -69,   -68,   -69,   -13
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      24,    77,    17,     9,    31,    12,    13,    14,    26,    38,
      39,    26,    18,    19,    20,    21,    22,   106,    54,     3,
       4,    10,    23,    59,    62,    55,   100,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    27,   121,
      97,   126,   125,    11,    81,    82,    98,    83,    79,    84,
      85,    86,    25,    17,    56,    80,    57,    12,    13,    14,
     135,   136,    15,    18,    19,    20,    87,    22,    95,    16,
      96,   104,   144,    23,    30,    88,    89,    32,    81,    82,
     149,    83,   112,    84,    85,    86,    56,    17,   134,   116,
     117,    33,    52,    53,    75,   122,   123,    18,    19,    20,
      87,    22,    76,    26,   101,    34,    35,    23,   131,    88,
      99,   108,   109,    81,    82,    37,    83,   137,    84,    85,
      86,   102,    17,    45,    46,   103,   143,    49,    50,   107,
      34,    35,    18,    19,    20,    87,    22,    36,   119,   113,
      37,   120,    23,   130,    88,   114,   105,    82,    54,    83,
      17,    84,    85,    86,   139,    17,    79,   140,   142,   145,
      18,    19,    20,    21,    22,    18,    19,    20,    87,    22,
      23,    60,   146,   148,     5,    23,    78,    88,   124,   105,
      82,     7,    83,     0,    84,    85,    86,   127,    17,    45,
      46,    47,    48,    49,    50,     0,     0,     0,    18,    19,
      20,    87,    22,     0,    12,    13,    14,     0,    23,   115,
      88,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    63,    42,    43,    44,    45,    46,    47,
      48,    49,    50,     0,   128,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,   129,    45,    46,
       0,    48,    49,    50,     0,     0,     0,     0,   141,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
       0,     0,     0,     0,     0,     0,     0,     0,    94,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
       0,     0,     0,     0,     0,     0,     0,     0,   133,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
       0,     0,     0,     0,     0,    51,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,     0,     0,     0,
       0,     0,   111,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,     0,     0,     0,     0,     0,   118,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,     0,     0,     0,     0,     0,   132,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,     0,     0,
       0,     0,     0,   138,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,     0,     0,     0,     0,     0,
     147,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50
};

static const yytype_int16 yycheck[] =
{
      13,    55,    12,     7,    17,    27,    28,    29,     3,    22,
      23,     3,    22,    23,    24,    25,    26,    85,    27,     0,
       3,    25,    32,    36,    37,    34,    80,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    33,   107,
      24,    33,   110,    32,     3,     4,    30,     6,    27,     8,
       9,    10,    24,    12,    31,    34,    33,    27,    28,    29,
     128,   129,    32,    22,    23,    24,    25,    26,    31,    33,
      33,    84,   140,    32,    34,    34,    35,    25,     3,     4,
     148,     6,    95,     8,     9,    10,    31,    12,    33,   102,
     103,    25,    30,    25,    27,   108,   109,    22,    23,    24,
      25,    26,    29,     3,    25,    22,    23,    32,   121,    34,
      35,    28,    29,     3,     4,    32,     6,   130,     8,     9,
      10,    32,    12,    16,    17,    32,   139,    20,    21,    32,
      22,    23,    22,    23,    24,    25,    26,    29,    25,    30,
      32,     6,    32,    32,    34,    35,     3,     4,    27,     6,
      12,     8,     9,    10,    28,    12,    27,     5,    25,    27,
      22,    23,    24,    25,    26,    22,    23,    24,    25,    26,
      32,    33,    22,    33,     2,    32,    56,    34,    35,     3,
       4,     2,     6,    -1,     8,     9,    10,   115,    12,    16,
      17,    18,    19,    20,    21,    -1,    -1,    -1,    22,    23,
      24,    25,    26,    -1,    27,    28,    29,    -1,    32,    32,
      34,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    33,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    -1,    33,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    33,    16,    17,
      -1,    19,    20,    21,    -1,    -1,    -1,    -1,    33,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    30,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    30,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      -1,    -1,    -1,    -1,    -1,    27,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    -1,    -1,    -1,
      -1,    -1,    27,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    -1,    -1,    -1,    -1,    -1,    27,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    -1,    -1,    -1,    -1,    -1,    27,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    -1,    -1,
      -1,    -1,    -1,    27,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    -1,    -1,    -1,    -1,    -1,
      27,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    37,    38,     0,     3,    39,    43,    44,    45,     7,
      25,    32,    27,    28,    29,    32,    33,    12,    22,    23,
      24,    25,    26,    32,    49,    24,     3,    33,    40,    41,
      34,    49,    25,    25,    22,    23,    29,    32,    49,    49,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    27,    30,    25,    27,    34,    31,    33,    42,    49,
      33,    48,    49,    33,    49,    49,    49,    49,    49,    49,
      49,    49,    49,    49,    49,    27,    29,    42,    40,    27,
      34,     3,     4,     6,     8,     9,    10,    25,    34,    35,
      39,    44,    47,    49,    30,    31,    33,    24,    30,    35,
      42,    25,    32,    32,    49,     3,    47,    32,    28,    29,
      46,    27,    49,    30,    35,    32,    49,    49,    27,    25,
       6,    47,    49,    49,    35,    47,    33,    41,    33,    33,
      32,    49,    27,    30,    33,    47,    47,    49,    27,    28,
       5,    33,    25,    49,    47,    27,    22,    27,    33,    47
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

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
#ifndef	YYINITDEPTH
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
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
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
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
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
	    /* Fall through.  */
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

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;


      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
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
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

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
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

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
#line 37 "MiniC.y"
    {
            root = newStmtNode(RootK);
            root->child[0] = (yyvsp[(1) - (2)].vtree);
            root->child[1] = (yyvsp[(2) - (2)].vtree);
        }
    break;

  case 3:
#line 45 "MiniC.y"
    {
            TreeNode * t = (yyvsp[(1) - (2)].vtree);
            if(t != NULL){
                while (t->sibling != NULL)
                t = t->sibling;
                t->sibling = (yyvsp[(2) - (2)].vtree);
                (yyval.vtree) = (yyvsp[(1) - (2)].vtree);
            }
            else (yyval.vtree) = (yyvsp[(2) - (2)].vtree);
        }
    break;

  case 4:
#line 56 "MiniC.y"
    {
            TreeNode * t = (yyvsp[(1) - (2)].vtree);
            if(t != NULL){
                while (t->sibling != NULL)
                t = t->sibling;
                t->sibling = (yyvsp[(2) - (2)].vtree);
                (yyval.vtree) = (yyvsp[(1) - (2)].vtree);
            }
            else (yyval.vtree) = (yyvsp[(2) - (2)].vtree);
        }
    break;

  case 5:
#line 67 "MiniC.y"
    {
            TreeNode * t = (yyvsp[(1) - (2)].vtree);
            if(t != NULL){
                while (t->sibling != NULL)
                t = t->sibling;
                t->sibling = (yyvsp[(2) - (2)].vtree);
                (yyval.vtree) = (yyvsp[(1) - (2)].vtree);
            }
            else (yyval.vtree) = (yyvsp[(2) - (2)].vtree);
        }
    break;

  case 6:
#line 78 "MiniC.y"
    {(yyval.vtree) = NULL;}
    break;

  case 7:
#line 82 "MiniC.y"
    {
            (yyval.vtree) = newStmtNode(VarDefnK);
            (yyval.vtree) -> child[0] = newExpNode(IdK);
            (yyval.vtree) -> child[0] -> attr.name = strdup((yyvsp[(2) - (3)].vstr));
        }
    break;

  case 8:
#line 88 "MiniC.y"
    {
			(yyval.vtree) = newStmtNode(VarDefnK);
			(yyval.vtree) -> child[0] = newExpNode(IdK);
			(yyval.vtree) -> child[0] -> attr.name = strdup((yyvsp[(2) - (5)].vstr));
			(yyval.vtree) -> sibling = newStmtNode(AssignK);
			(yyval.vtree) -> sibling -> child[0] = newExpNode(IdK);
			(yyval.vtree) -> sibling -> child[0] -> attr.name = strdup((yyvsp[(2) - (5)].vstr));
			(yyval.vtree) -> sibling -> child[2] = (yyvsp[(4) - (5)].vtree);
		}
    break;

  case 9:
#line 98 "MiniC.y"
    {
            (yyval.vtree) = newStmtNode(VarDefnK);
            (yyval.vtree) -> child[0] = newExpNode(IdK);
            (yyval.vtree) -> child[0] -> attr.name = strdup((yyvsp[(2) - (6)].vstr));
            (yyval.vtree) -> child[1] = newExpNode(ConstK);
            (yyval.vtree) -> child[1] -> attr.val = (yyvsp[(4) - (6)].vint);
        }
    break;

  case 10:
#line 108 "MiniC.y"
    {
            (yyval.vtree) = newStmtNode(VarDeclK);
            (yyval.vtree) -> child[0] = newExpNode(IdK);
            (yyval.vtree) -> child[0] -> attr.name = strdup((yyvsp[(2) - (2)].vstr));
        }
    break;

  case 11:
#line 114 "MiniC.y"
    {
            (yyval.vtree) = newStmtNode(VarDeclK);
            (yyval.vtree) -> child[0] = newExpNode(IdK);
            (yyval.vtree) -> child[0] -> attr.name = strdup((yyvsp[(2) - (4)].vstr));
        }
    break;

  case 12:
#line 120 "MiniC.y"
    {
            (yyval.vtree) = newStmtNode(VarDeclK);
            (yyval.vtree) -> child[0] = newExpNode(IdK);
            (yyval.vtree) -> child[0] -> attr.name = strdup((yyvsp[(2) - (5)].vstr));
//            $$ -> child[1] = newExpNode(ConstK);
//            $$ -> child[1] -> attr.val = $4;
        }
    break;

  case 13:
#line 130 "MiniC.y"
    {(yyval.vtree) = (yyvsp[(1) - (1)].vtree);}
    break;

  case 14:
#line 132 "MiniC.y"
    {
            TreeNode * t = (yyvsp[(1) - (3)].vtree);
            while (t->sibling != NULL)
            t = t->sibling;
            t->sibling = (yyvsp[(3) - (3)].vtree);
            (yyval.vtree) = (yyvsp[(1) - (3)].vtree);
        }
    break;

  case 15:
#line 142 "MiniC.y"
    {
            TreeNode * t = (yyvsp[(1) - (2)].vtree);
            if(t != NULL){
                while (t->sibling != NULL)
                t = t->sibling;
                t->sibling = (yyvsp[(2) - (2)].vtree);
                (yyval.vtree) = (yyvsp[(1) - (2)].vtree);
            }
            else (yyval.vtree) = (yyvsp[(2) - (2)].vtree);
        }
    break;

  case 16:
#line 153 "MiniC.y"
    {
            TreeNode * t = (yyvsp[(1) - (2)].vtree);
            if(t != NULL){
                while (t->sibling != NULL)
                t = t->sibling;
                t->sibling = (yyvsp[(2) - (2)].vtree);
                (yyval.vtree) = (yyvsp[(1) - (2)].vtree);
            }
            else (yyval.vtree) = (yyvsp[(2) - (2)].vtree);
        }
    break;

  case 17:
#line 164 "MiniC.y"
    {(yyval.vtree) = NULL;}
    break;

  case 18:
#line 168 "MiniC.y"
    {
            (yyval.vtree) = newStmtNode(FuncDefnK);
            (yyval.vtree) -> child[0] = newExpNode(IdK);
            (yyval.vtree) -> child[0] -> attr.name = strdup((yyvsp[(2) - (7)].vstr));
            (yyval.vtree) -> child[2] = (yyvsp[(6) - (7)].vtree);
        }
    break;

  case 19:
#line 175 "MiniC.y"
    {
            (yyval.vtree) = newStmtNode(FuncDefnK);
            (yyval.vtree) -> child[0] = newExpNode(IdK);
            (yyval.vtree) -> child[0] -> attr.name = strdup((yyvsp[(2) - (8)].vstr));
            (yyval.vtree) -> child[1] = (yyvsp[(4) - (8)].vtree);
            (yyval.vtree) -> child[2] = (yyvsp[(7) - (8)].vtree);
        }
    break;

  case 20:
#line 185 "MiniC.y"
    {
            (yyval.vtree) = newStmtNode(FuncDeclK);
            (yyval.vtree) -> child[0] = newExpNode(IdK);
            (yyval.vtree) -> child[0] -> attr.name = strdup((yyvsp[(2) - (5)].vstr));
        }
    break;

  case 21:
#line 191 "MiniC.y"
    {
            (yyval.vtree) = newStmtNode(FuncDeclK);
            (yyval.vtree) -> child[0] = newExpNode(IdK);
            (yyval.vtree) -> child[0] -> attr.name = strdup((yyvsp[(2) - (6)].vstr));
            (yyval.vtree) -> child[1] = (yyvsp[(4) - (6)].vtree);
        }
    break;

  case 22:
#line 200 "MiniC.y"
    {(yyval.vtree) = (yyvsp[(6) - (7)].vtree);}
    break;

  case 23:
#line 204 "MiniC.y"
    {
            TreeNode * t = (yyvsp[(1) - (2)].vtree);
            if(t != NULL){
                while (t->sibling != NULL)
                    t = t->sibling;
                t->sibling = (yyvsp[(2) - (2)].vtree);
                (yyval.vtree) = (yyvsp[(1) - (2)].vtree);
            }
            else (yyval.vtree) = (yyvsp[(2) - (2)].vtree);
        }
    break;

  case 24:
#line 215 "MiniC.y"
    {(yyval.vtree) = NULL;}
    break;

  case 25:
#line 219 "MiniC.y"
    {
            (yyval.vtree) = newStmtNode(SeqK);
            (yyval.vtree) -> child[0] = (yyvsp[(2) - (3)].vtree);
        }
    break;

  case 26:
#line 224 "MiniC.y"
    {
            (yyval.vtree) = newStmtNode(IfK);
            (yyval.vtree) -> child[0] = (yyvsp[(3) - (5)].vtree);
            (yyval.vtree) -> child[1] = (yyvsp[(5) - (5)].vtree);
        }
    break;

  case 27:
#line 230 "MiniC.y"
    {
            (yyval.vtree) = newStmtNode(IfK);
            (yyval.vtree) -> child[0] = (yyvsp[(3) - (7)].vtree);
            (yyval.vtree) -> child[1] = (yyvsp[(5) - (7)].vtree);
            (yyval.vtree) -> child[2] = (yyvsp[(7) - (7)].vtree);
        }
    break;

  case 28:
#line 237 "MiniC.y"
    {
            (yyval.vtree) = newStmtNode(WhileK);
            (yyval.vtree) -> child[0] = (yyvsp[(3) - (5)].vtree);
            (yyval.vtree) -> child[1] = (yyvsp[(5) - (5)].vtree);
        }
    break;

  case 29:
#line 243 "MiniC.y"
    {
			(yyval.vtree) = (yyvsp[(3) - (9)].vtree);
			(yyval.vtree) -> sibling = newStmtNode(ForK);
			(yyval.vtree) -> sibling -> child[0] = (yyvsp[(4) - (9)].vtree);
			(yyval.vtree) -> sibling -> child[1] = newExpNode(OpK);
			(yyval.vtree) -> sibling -> child[1] -> child[0] = newExpNode(IdK);
			(yyval.vtree) -> sibling -> child[1] -> child[0] -> attr.name = strdup((yyvsp[(6) - (9)].vstr));
			(yyval.vtree) -> sibling -> child[1] -> child[0] -> type = Integer;
			(yyval.vtree) -> sibling -> child[1] -> attr.op = PP2TT;
			(yyval.vtree) -> sibling -> child[1] -> type = Integer;
			(yyval.vtree) -> sibling -> child[2] = (yyvsp[(9) - (9)].vtree);
		}
    break;

  case 30:
#line 256 "MiniC.y"
    {
            (yyval.vtree) = newStmtNode(AssignK);
            (yyval.vtree) -> child[0] = newExpNode(IdK);
            (yyval.vtree) -> child[0] -> attr.name = strdup((yyvsp[(1) - (4)].vstr));
            (yyval.vtree) -> child[2] = (yyvsp[(3) - (4)].vtree);
        }
    break;

  case 31:
#line 263 "MiniC.y"
    {
            (yyval.vtree) = newStmtNode(AssignK);
            (yyval.vtree) -> child[0] = newExpNode(IdK);
            (yyval.vtree) -> child[0] -> attr.name = strdup((yyvsp[(1) - (7)].vstr));
            (yyval.vtree) -> child[1] = (yyvsp[(3) - (7)].vtree);
            (yyval.vtree) -> child[2] = (yyvsp[(6) - (7)].vtree);
        }
    break;

  case 32:
#line 271 "MiniC.y"
    {(yyval.vtree) = (yyvsp[(1) - (1)].vtree);}
    break;

  case 33:
#line 273 "MiniC.y"
    {
            (yyval.vtree) = newStmtNode(RetK);
            (yyval.vtree) -> child[0] = (yyvsp[(2) - (3)].vtree);
        }
    break;

  case 34:
#line 278 "MiniC.y"
    {
            (yyval.vtree) = newStmtNode(SExpK);
            (yyval.vtree) -> child[0] = (yyvsp[(1) - (2)].vtree);
        }
    break;

  case 35:
#line 283 "MiniC.y"
    {
			(yyval.vtree) = newStmtNode(DowhileK);
			(yyval.vtree) -> child[0] = (yyvsp[(2) - (7)].vtree);
			(yyval.vtree) -> child[1] = (yyvsp[(5) - (7)].vtree);
		}
    break;

  case 36:
#line 291 "MiniC.y"
    {(yyval.vtree) = (yyvsp[(1) - (1)].vtree);}
    break;

  case 37:
#line 293 "MiniC.y"
    {
            TreeNode * t = (yyvsp[(1) - (3)].vtree);
            while (t->sibling != NULL)
            t = t->sibling;
            t->sibling = (yyvsp[(3) - (3)].vtree);
            (yyval.vtree) = (yyvsp[(1) - (3)].vtree);
        }
    break;

  case 38:
#line 303 "MiniC.y"
    {
    (yyval.vtree) = newExpNode(OpK);
    (yyval.vtree) -> child[0] = (yyvsp[(1) - (3)].vtree);
    (yyval.vtree) -> child[1] = (yyvsp[(3) - (3)].vtree);
    (yyval.vtree) -> attr.op = ADDTT;
    (yyval.vtree) -> type = Integer;
}
    break;

  case 39:
#line 311 "MiniC.y"
    {
    (yyval.vtree) = newExpNode(OpK);
    (yyval.vtree) -> child[0] = (yyvsp[(1) - (3)].vtree);
    (yyval.vtree) -> child[1] = (yyvsp[(3) - (3)].vtree);
    (yyval.vtree) -> attr.op = SUBTT;
    (yyval.vtree) -> type = Integer;
}
    break;

  case 40:
#line 319 "MiniC.y"
    {
    (yyval.vtree) = newExpNode(OpK);
    (yyval.vtree) -> child[0] = (yyvsp[(1) - (3)].vtree);
    (yyval.vtree) -> child[1] = (yyvsp[(3) - (3)].vtree);
    (yyval.vtree) -> attr.op = MULTT;
    (yyval.vtree) -> type = Integer;
}
    break;

  case 41:
#line 327 "MiniC.y"
    {
    (yyval.vtree) = newExpNode(OpK);
    (yyval.vtree) -> child[0] = (yyvsp[(1) - (3)].vtree);
    (yyval.vtree) -> child[1] = (yyvsp[(3) - (3)].vtree);
    (yyval.vtree) -> attr.op = DIVTT;
    (yyval.vtree) -> type = Integer;
}
    break;

  case 42:
#line 335 "MiniC.y"
    {
    (yyval.vtree) = newExpNode(OpK);
    (yyval.vtree) -> child[0] = (yyvsp[(1) - (3)].vtree);
    (yyval.vtree) -> child[1] = (yyvsp[(3) - (3)].vtree);
    (yyval.vtree) -> attr.op = MODTT;
    (yyval.vtree) -> type = Integer;
}
    break;

  case 43:
#line 343 "MiniC.y"
    {
    (yyval.vtree) = newExpNode(OpK);
    (yyval.vtree) -> child[0] = (yyvsp[(1) - (3)].vtree);
    (yyval.vtree) -> child[1] = (yyvsp[(3) - (3)].vtree);
    (yyval.vtree) -> attr.op = MTTT;
    (yyval.vtree) -> type = Boolean;
}
    break;

  case 44:
#line 351 "MiniC.y"
    {
    (yyval.vtree) = newExpNode(OpK);
    (yyval.vtree) -> child[0] = (yyvsp[(1) - (3)].vtree);
    (yyval.vtree) -> child[1] = (yyvsp[(3) - (3)].vtree);
    (yyval.vtree) -> attr.op = LTTT;
    (yyval.vtree) -> type = Boolean;
}
    break;

  case 45:
#line 359 "MiniC.y"
    {
    (yyval.vtree) = newExpNode(OpK);
    (yyval.vtree) -> child[0] = (yyvsp[(1) - (3)].vtree);
    (yyval.vtree) -> child[1] = (yyvsp[(3) - (3)].vtree);
    (yyval.vtree) -> attr.op = EQTT;
    (yyval.vtree) -> type = Boolean;
}
    break;

  case 46:
#line 367 "MiniC.y"
    {
    (yyval.vtree) = newExpNode(OpK);
    (yyval.vtree) -> child[0] = (yyvsp[(1) - (3)].vtree);
    (yyval.vtree) -> child[1] = (yyvsp[(3) - (3)].vtree);
    (yyval.vtree) -> attr.op = NEQTT;
    (yyval.vtree) -> type = Boolean;
}
    break;

  case 47:
#line 375 "MiniC.y"
    {
    (yyval.vtree) = newExpNode(OpK);
    (yyval.vtree) -> child[0] = (yyvsp[(1) - (3)].vtree);
    (yyval.vtree) -> child[1] = (yyvsp[(3) - (3)].vtree);
    (yyval.vtree) -> attr.op = ANDTT;
    (yyval.vtree) -> type = Boolean;
}
    break;

  case 48:
#line 383 "MiniC.y"
    {
    (yyval.vtree) = newExpNode(OpK);
    (yyval.vtree) -> child[0] = (yyvsp[(1) - (3)].vtree);
    (yyval.vtree) -> child[1] = (yyvsp[(3) - (3)].vtree);
    (yyval.vtree) -> attr.op = ORTT;
    (yyval.vtree) -> type = Boolean;
    
}
    break;

  case 49:
#line 392 "MiniC.y"
    {
    (yyval.vtree) = newExpNode(IdK);
    (yyval.vtree) -> attr.name = strdup((yyvsp[(1) - (4)].vstr));
    (yyval.vtree) -> child[0] = (yyvsp[(3) - (4)].vtree);
    (yyval.vtree) -> type = Integer;
}
    break;

  case 50:
#line 399 "MiniC.y"
    {
    (yyval.vtree) = newExpNode(ConstK);
    (yyval.vtree) -> attr.val = (yyvsp[(1) - (1)].vint);
    (yyval.vtree) -> type = Integer;
}
    break;

  case 51:
#line 405 "MiniC.y"
    {
    (yyval.vtree) = newExpNode(IdK);
    (yyval.vtree) -> attr.name = strdup((yyvsp[(1) - (1)].vstr));
    (yyval.vtree) -> type = Integer;
}
    break;

  case 52:
#line 411 "MiniC.y"
    {
    (yyval.vtree) = newExpNode(OpK);
    (yyval.vtree) -> child[0] = (yyvsp[(2) - (2)].vtree);
    (yyval.vtree) -> attr.op = MINUSTT;
    (yyval.vtree) -> type = Integer;
}
    break;

  case 53:
#line 418 "MiniC.y"
    {
    (yyval.vtree) = newExpNode(OpK);
    (yyval.vtree) -> child[0] = (yyvsp[(2) - (2)].vtree);
    (yyval.vtree) -> attr.op = NOTTT;
    (yyval.vtree) -> type = Boolean;
}
    break;

  case 54:
#line 425 "MiniC.y"
    {
	(yyval.vtree) = newExpNode(OpK);
	(yyval.vtree) -> child[0] = newExpNode(IdK);
	(yyval.vtree) -> child[0] -> attr.name = strdup((yyvsp[(2) - (2)].vstr));
	(yyval.vtree) -> child[0] -> type = Integer;
	(yyval.vtree) -> attr.op = PP1TT;
	(yyval.vtree) -> type = Integer;
}
    break;

  case 55:
#line 434 "MiniC.y"
    {
	(yyval.vtree) = newExpNode(OpK);
	(yyval.vtree) -> child[0] = newExpNode(IdK);
	(yyval.vtree) -> child[0] -> attr.name = strdup((yyvsp[(2) - (2)].vstr));
	(yyval.vtree) -> child[0] -> type = Integer;
	(yyval.vtree) -> attr.op = MM1TT;
	(yyval.vtree) -> type = Integer;
}
    break;

  case 56:
#line 443 "MiniC.y"
    {
	(yyval.vtree) = newExpNode(OpK);
	(yyval.vtree) -> child[0] = newExpNode(IdK);
	(yyval.vtree) -> child[0] -> attr.name = strdup((yyvsp[(1) - (2)].vstr));
	(yyval.vtree) -> child[0] -> type = Integer;
	(yyval.vtree) -> attr.op = PP2TT;
	(yyval.vtree) -> type = Integer;
}
    break;

  case 57:
#line 452 "MiniC.y"
    {
	(yyval.vtree) = newExpNode(OpK);
	(yyval.vtree) -> child[0] = newExpNode(IdK);
	(yyval.vtree) -> child[0] -> attr.name = strdup((yyvsp[(1) - (2)].vstr));
	(yyval.vtree) -> child[0] -> type = Integer;
	(yyval.vtree) -> attr.op = MM2TT;
	(yyval.vtree) -> type = Integer;
}
    break;

  case 58:
#line 461 "MiniC.y"
    {
    (yyval.vtree) = newExpNode(OpK);
    (yyval.vtree) -> child[0] = (yyvsp[(2) - (3)].vtree);
    (yyval.vtree) -> attr.op = PARENTT;
    (yyval.vtree) -> type = (yyvsp[(2) - (3)].vtree) -> type;
}
    break;

  case 59:
#line 468 "MiniC.y"
    {
    (yyval.vtree) = newExpNode(FuncK);
    (yyval.vtree) -> child[0] = newExpNode(IdK);
    (yyval.vtree) -> child[0] -> attr.name = strdup((yyvsp[(1) - (4)].vstr));
    (yyval.vtree) -> child[1] = (yyvsp[(3) - (4)].vtree);
    (yyval.vtree) -> type = Integer;
}
    break;

  case 60:
#line 476 "MiniC.y"
    {
    (yyval.vtree) = newExpNode(FuncK);
    (yyval.vtree) -> child[0] = newExpNode(IdK);
    (yyval.vtree) -> child[0] -> attr.name = strdup((yyvsp[(1) - (3)].vstr));
    (yyval.vtree) -> type = Integer;
}
    break;


/* Line 1267 of yacc.c.  */
#line 2128 "y.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
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

  /* Else will try to reuse look-ahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
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

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;


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

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
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
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


#line 483 "MiniC.y"


int yyerror(char *message)
{
    fprintf(stderr, "Syntax error at line %d: %s\n",lineno,message);
    return 1;
}

