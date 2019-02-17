#include <stdio.h>
#include "globals.h"
#include "mystack.h"

#define MAXSTACKDEPTH 500

sNode * mystack[MAXSTACKDEPTH];

int top = -1;

sNode * newsNode(sNodeKind kind, int val){
    sNode * t = (sNode *) malloc(sizeof(sNode));
    t -> kind = kind;
    t -> val = val;
    t -> name[0] = '\0';
    switch (kind) {
        case CK:
            break;
        case TK:
            t -> name[0] = 'T';
            break;
        case tK:
            t -> name[0] = 't';
            break;
        case pK:
            t -> name[0] = 'p';
            break;
        default:
            return t;
    }
    sprintf((t -> name) + strlen(t -> name), "%d", t -> val);
    return t;
}

void mypush(sNode * t){
    mystack[++top] = t;
}

sNode * mypop(){
    if(top < 0){
        fprintf(stderr, "pop when stack is empty\n");
        exit(1);
    }
    return mystack[top--];
}


