#include "globals.h"
#include "mytree.h"

TreeNode * newTreeNode(NodeKind kind)
{ TreeNode * t = (TreeNode *) malloc(sizeof(TreeNode));
    int i;
    if (t==NULL)
        fprintf(stderr, "Out of memory error at line %d\n",lineno);
    else {
		memset(t->param, 0, sizeof(t->param));
		t->nparam = 0;
        t->sibling = NULL;
		t->child = NULL;
		t->lineno = lineno;
        t->nodekind = kind;
    }
    return t;
}
