#include "globals.h"
#include "mytree.h"
#include "optimize.h"

static int USE(char * reg, TreeNode * t){
	switch(t -> exprkind){
		case OpK:
			switch(t->op){
				case ADDTT:
				case SUBTT:
				case MULTT:
				case DIVTT:
				case MODTT:
				case LTTT:
				case MTTT:
				case EQTT:
				case NEQTT:
				case ANDTT:
				case ORTT:
					if(!strcmp(reg, t->param[1].name) || !strcmp(reg, t->param[2].name))
						return 1;
					break;
				case ADD2TT:
				case LT2TT:
				case MINUSTT:
				case NOTTT:
				case ASS1TT:
					if(!strcmp(reg, t->param[1].name))
						return 1;
					break;
				case ASS2TT:
					break;
				case ASS3TT:
					if(!strcmp(reg, t->param[1].name))
						return 1;
					break;
				case ASS4TT:
					if(!strcmp(reg, t->param[0].name) || !strcmp(reg, t->param[2].name))
						return 1;
					break;
				default:
					break;
			}
			break;
		case IfK:
			if(!strcmp(reg, t->param[0].name) || !strcmp(reg, t->param[1].name))
				return 1;
			break;
		case GotoK:
			break;
		case LabelK:
			break;
		case CallK:
			break;
		case RetK:
			break;
		case StoreK:
			if(!strcmp(reg, t->param[0].name))
				return 1;
			break;
		case LoadK:
			break;
		case LoadaddrK:
			break;
		default:
			break;
	}
	return 0;
}

static char * DEF(TreeNode * t){
	switch(t -> exprkind){
		case OpK:
			if(t -> op != ASS4TT)
				return t->param[0].name;
			break;
		case IfK:
			break;
		case GotoK:
			break;
		case LabelK:
			break;
		case CallK:
			break;
		case RetK:
			break;
		case StoreK:
			break;
		case LoadK:
		case LoadaddrK:
			return t->param[t->nparam-1].name;
		default:
			break;
	}
	return NULL;
}

void TiggerTreeOptimize(TreeNode * root){
	if(root -> nodekind == RootK){
		TreeNode * t = root -> child;
		while(t != NULL){
			if(t -> nodekind == FuncK)
				TiggerTreeOptimize(t);
			t = t -> sibling;
		}
	}
	else if(root -> nodekind == FuncK){
		TreeNode * t = root -> child;
		TreeNode * p = NULL;
		/*remove dead DEF*/
		while(t != NULL){
			int flag = 0;
			char * def = DEF(t);
			if(def != NULL){
				TreeNode * tt = t -> sibling;
				while(tt != NULL){
					if(tt -> exprkind == IfK || tt -> exprkind == GotoK || tt -> exprkind == CallK || tt -> exprkind == RetK) break;
					if(USE(def, tt)) break;
					char * def_ = DEF(tt);
					if(def_ != NULL && !strcmp(def, def_)){
						flag = 1;
						break;
					}
					tt = tt -> sibling;
				}
			}
			else if(t -> exprkind == StoreK){
				char * name = t -> param[0].name;
				int loc = t -> param[1].val;
				TreeNode * tt = t -> sibling;
				TreeNode * pp = t;
				while(tt != NULL){
					if(tt -> exprkind == IfK || tt -> exprkind == GotoK || tt -> exprkind == CallK || tt -> exprkind == LabelK || tt ->exprkind == RetK) break;
					if(tt -> exprkind == LoadK && tt -> nparam == 2 && !strcmp(tt -> param[1].name, name) && tt -> param[0].val == loc){
						pp -> sibling = tt -> sibling;
					}
					char * def_ = DEF(tt);
					if(def_ != NULL && !strcmp(name, def_)) break;
					if(pp -> sibling != tt -> sibling) pp = tt;
					tt = tt -> sibling;
				}
			}
			if(flag){
				if(p == NULL)
					root -> child = t -> sibling;
				else
					p -> sibling = t -> sibling;
			}
			else{
				p = t;
			}
			t = t -> sibling;
		}
		/*record effective stack locations*/
		int used[27] = {0};
		t = root -> child;
		while(t != NULL){
			if((t -> exprkind == LoadK || t -> exprkind == LoadaddrK) && t -> nparam == 2 && t -> param[0].val < 27){
				used[t -> param[0].val] = 1;
			}
			t = t -> sibling;
		}
		/*remove dead STORE*/
		t = root -> child;
		p = NULL;
		while(t != NULL){
			if(t -> exprkind == StoreK && t -> param[1].val < 27 && used[t -> param[1].val] == 0){
				if(p == NULL)
					root -> child = t -> sibling;
				else
					p -> sibling = t -> sibling;
				t = t -> sibling;
			}
			else{
				p = t;
				t = t -> sibling;
			}
		}
		int bias[27] = {0};
		for(int i = 1; i < 27; ++i){
			bias[i] = bias[i-1] + 1 - used[i-1];
		}
		/*remove dead stack locations and mapping*/
		t = root -> child;
		while(t != NULL){
			if(t -> exprkind == StoreK){
				if(t -> param[1].val < 27)
					t -> param[1].val -= bias[t -> param[1].val];
				else
					t -> param[1].val -= bias[26];
			}
			if((t -> exprkind == LoadK || t -> exprkind == LoadaddrK) && t -> nparam == 2){
				if(t -> param[0].val < 27)
					t -> param[0].val -= bias[t -> param[0].val];
				else
					t -> param[0].val -= bias[26];
			}
			t = t -> sibling;
		}
		root -> param[2].val -= bias[26] + 1 - used[26];
//		printf("%s : %d\n", root -> param[0].name, root -> param[2].val);
//		for(int i = 0; i < 27; ++i){
//			printf("%d %d %d\n", i, used[i], bias[i]);
//		}
	}
	else{
		fprintf(stderr, "unexpected node kind in TiggerTreeOptimize, RootK or FuncK expected\n");
		exit(1);
	}
}
