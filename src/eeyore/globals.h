#ifndef _GLOBALS_H_
#define _GLOBALS_H_

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "y.tab.h"

extern int lineno;

typedef enum {ADDTT, SUBTT, MULTT, DIVTT, MODTT, LTTT, MTTT, EQTT, NEQTT, ANDTT, ORTT, MINUSTT, NOTTT, PARENTT, PP1TT, PP2TT, MM1TT, MM2TT} TokenType;

/*Tree node struct*/

typedef enum {StmtK, ExpK} NodeKind;
typedef enum {RootK, VarDefnK, VarDeclK, FuncDeclK, FuncDefnK, SeqK, IfK, WhileK, AssignK, RetK, SExpK, DowhileK, ForK} StmtKind;
typedef enum {OpK, ConstK, IdK, FuncK} ExpKind;

typedef enum {Void,Integer,Boolean} ExpType;

#define MAXCHILDREN 3

typedef struct treeNode
{ struct treeNode * child[MAXCHILDREN];
    struct treeNode * sibling;
    int lineno;
    NodeKind nodekind;
    union { StmtKind stmt; ExpKind exp;} kind;
    union { TokenType op;
        int val;
        char * name; } attr;
    ExpType type; /* for type checking of exps */
} TreeNode;

#endif
