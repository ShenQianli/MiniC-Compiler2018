#ifndef _MYSTACK_H_
#define _MYSTACK_H_
#include "globals.h"

typedef enum {CK, TK, tK, pK} sNodeKind;

typedef struct mystacknode{
    sNodeKind kind;
    int val;
    char name[30];
}sNode;

sNode * newsNode(sNodeKind kind, int val);

void mypush(sNode * t);

sNode * mypop();

#endif

