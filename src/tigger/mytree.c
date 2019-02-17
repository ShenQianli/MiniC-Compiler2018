#include "globals.h"
#include "mytree.h"

TreeNode * newTreeNode(NodeKind kind)
{ TreeNode * t = (TreeNode *) malloc(sizeof(TreeNode));
    int i;
    if (t==NULL)
        fprintf(stderr, "Out of memory error at line %d\n",lineno);
    else {
        for (i=0;i<MAXCHILDREN;i++) t->child[i] = NULL;
        t->sibling = NULL;
		t->lineno = lineno;
        t->nodekind = kind;
    }
    return t;
}
