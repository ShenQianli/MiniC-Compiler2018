#include "globals.h"
#include "mytree.h"
#include "optimize.h"

void EeyoreTreeOptimize(TreeNode * root){
	if(root -> nodekind == RootK){
		TreeNode * t = root -> child[0];
		while(t != NULL){
			if(t -> nodekind == FuncK){
				EeyoreTreeOptimize(t);
			}
			t = t -> sibling;
		}
	}
	else if(root -> nodekind == FuncK){
		TreeNode * ins = root -> child[1];
		while(ins != NULL){
			if((ins -> inskind == OpK || ins -> inskind == CallK) && ins -> sibling != NULL){
				TreeNode * nextins = ins -> sibling;
				if(nextins -> inskind == OpK && nextins -> attr.op == ASSTT && nextins -> child[2] == NULL && nextins -> child[1] -> nodekind == MarkK && nextins -> child[1] -> attr.name[0] == 't' && !strcmp(ins -> child[0] -> attr.name, nextins -> child[1] -> attr.name)){
					ins -> child[0] -> attr.name = nextins -> child[0] -> attr.name;
					ins -> sibling = nextins -> sibling;
				}
			}
			if(ins -> inskind == LabelK && ins -> sibling != NULL){
				TreeNode * nextins = ins -> sibling;
				if(nextins -> inskind == LabelK){
					TreeNode * t = root -> child[1];
					while(t != NULL){
						if(t -> inskind == GotoK && !strcmp(nextins -> child[0] -> attr.name, t -> child[0] -> attr.name)){
							t -> child[0] -> attr.name = ins -> child[0] -> attr.name;
						}
						if(t -> inskind == IfK && !strcmp(nextins -> child[0] -> attr.name, t -> child[2] -> attr.name)){
							t -> child[2] -> attr.name = ins -> child[0] -> attr.name;
						}
						t = t -> sibling;
					}
					ins -> sibling = nextins -> sibling;
				}
			}
			ins = ins -> sibling;
		}
	}
	else{
		fprintf(stderr, "unexpected node kind in EeyoreTreeOptimize, RootK or FuncK expected\n");
		exit(1);
	}
}
