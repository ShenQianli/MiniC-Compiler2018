#ifndef _GLOBALS_H_
#define _GLOBALS_H_

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "y.tab.h"

extern int lineno;

typedef enum {ADDTT, SUBTT, MULTT, DIVTT, MODTT, LTTT, MTTT, EQTT, NEQTT, ANDTT, ORTT, ADD2TT, LT2TT, MINUSTT, NOTTT, ASS1TT, ASS2TT, ASS3TT, ASS4TT} TokenType;
typedef enum {RootK, FuncK, VarDeclK, ExprK} NodeKind;
typedef enum {OpK, IfK, GotoK, LabelK, CallK, RetK, StoreK, LoadK, LoadaddrK} ExprKind;

#define MAXPARAM 3

typedef struct treeNode
{
	int nparam;
	union{int val;char * name;} param[MAXPARAM];
    struct treeNode * sibling;
	struct treeNode * child;
	int lineno;
    NodeKind nodekind;
	ExprKind exprkind;
    TokenType op;
} TreeNode;

#endif

