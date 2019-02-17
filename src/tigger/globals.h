#ifndef _GLOBALS_H_
#define _GLOBALS_H_

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "y.tab.h"

extern int lineno;

typedef enum {ADDTT, SUBTT, MULTT, DIVTT, MODTT, LTTT, MTTT, EQTT, NEQTT, ANDTT, ORTT, MINUSTT, NOTTT, ASSTT, SASSTT} TokenType;
typedef enum {RootK, FuncK, InsK, MarkK, ConstK} NodeKind;
typedef enum {VarDeclK, OpK, IfK, GotoK, LabelK, ParamK, CallK, RetK} InsKind;

#define MAXCHILDREN 3

typedef struct treeNode
{ struct treeNode * child[MAXCHILDREN];
    struct treeNode * sibling;
    int lineno;
    NodeKind nodekind;
	InsKind inskind;
    union { TokenType op;
        int val;
        char * name; } attr;
} TreeNode;

#endif
