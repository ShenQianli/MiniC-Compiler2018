#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "globals.h"
#include "LSRA.h"

#define MAXLABEL 1000

static int LabelLineno[MAXLABEL];

static void LSRAError(char * message){
	fprintf(stderr, "LSRA generation error: %s\n", message);
	exit(1);
}

static void RegStackPush(int r_n){
	pRegStack++;
	if(pRegStack >= MAXREGISTOR)
		LSRAError("push when stack is full");
	RegStack[pRegStack] = r_n;
	return;
}

static int RegStackPop(){
	if(pRegStack == -1)
		LSRAError("pop when stack is empty");
	return RegStack[pRegStack--];
}

static void RegStackClear(){
	pRegStack = -1;
}

static void init(){
	LSRA_cnt = 0;
	memset(AllInterval, 0, sizeof(AllInterval));
	nInterval = 0;
	ActiveInterval = NULL;
	nActiveInterval = 0;
	RegStackClear();
	for(int i = MAXREGISTOR - 1; i >= 0; --i)
		RegStackPush(i);
	nStackLocation = 0;
	memset(RegUsed, 0, sizeof(RegUsed));
	nLocalArray = 0;
	memset(LocalArrayName, 0, sizeof(LocalArrayName));
	memset(LocalArraySize, 0, sizeof(LocalArraySize));
	memset(LocalArrayAddr, 0, sizeof(LocalArrayAddr));
	LocalArraySpace = 0;
	memset(LabelLineno, -1, sizeof(LabelLineno));
}

int IntervalSearch(char * name){
	for(int i = 0; i < nInterval; ++i){
		if(!strcmp(name, AllInterval[i] -> var_name))
			return i;
	}
	return -1;
}

static void AddInterval(TreeNode * root, int mode){
	if(root == NULL || root -> nodekind != MarkK){
		return;
	}
	if(root -> attr.name[0] != 'T' && root -> attr.name[0] != 't')
		return;
	int n = IntervalSearch(root -> attr.name);
	if(n == -1){
		Interval * t = (Interval *) malloc(sizeof(Interval));
		t -> start = LSRA_cnt;
		t -> end = LSRA_cnt;
		t -> var_name = strdup(root -> attr.name);
		AllInterval[nInterval++] = t;
	}
	else{
		if(mode == TRIVIAL){}
		else if(mode == NAIVE){
			AllInterval[n] -> end = LSRA_cnt;
		}
	}
	return;
}

static void GenInterval(TreeNode * root, int mode){
	if(root -> nodekind != FuncK){
		LSRAError("unexpected node kind in GenInterval, FuncK expected");
	}
	TreeNode * t = root -> child[1];
	if(t != NULL && t -> nodekind != InsK){
		LSRAError("unexpected node kind in GenInterval, InsK expected");
	}
	while(t != NULL){
		int tmp = -1;
		switch(t -> inskind){
			case VarDeclK:
				if(t -> child[1] != NULL){
					LocalArrayName[nLocalArray] = t -> child[0] -> attr.name;
					LocalArraySize[nLocalArray] = t -> child[1] -> attr.val / 4;
					if(nLocalArray == 0){
						LocalArrayAddr[nLocalArray] = 0;
					}
					else{
						LocalArrayAddr[nLocalArray] = LocalArrayAddr[nLocalArray-1] + LocalArraySize[nLocalArray];
					}
					LocalArraySpace += LocalArraySize[nLocalArray];
					nLocalArray++;
				}
				break;
			case OpK:
				AddInterval(t -> child[0], mode);
				AddInterval(t -> child[1], mode);
				AddInterval(t -> child[2], mode);
				break;
			case IfK:
				AddInterval(t -> child[0], mode);
				AddInterval(t -> child[1], mode);
				break;
			case GotoK:
				tmp = LabelLineno[(int)strtod(t -> child[0] -> attr.name + sizeof(char), NULL)];
				if(tmp >= 0){
					// label before goto
					if(mode == NAIVE){
						for(int i = 0 ; i < nInterval; ++i){
							if(AllInterval[i] -> end > tmp && AllInterval[i] -> end < LSRA_cnt){
								AllInterval[i] -> end = LSRA_cnt;
							}
							if(AllInterval[i] -> start > tmp && AllInterval[i] -> start < LSRA_cnt){
								AllInterval[i] -> start = tmp;
							}
						}
					}
				}
				break;
			case LabelK:
				LabelLineno[(int)strtod(t -> child[0] -> attr.name + sizeof(char),NULL)] = LSRA_cnt;
				break;
			case ParamK:
				AddInterval(t -> child[0], mode);
				break;
			case CallK:
				AddInterval(t -> child[0], mode);
				break;
			case RetK:
				AddInterval(t -> child[0], mode);
				break;
			default:
				break;
		}
		t = t -> sibling;
		LSRA_cnt++;
	}
	if(mode == TRIVIAL){
		for(int i = 0; i < nInterval; ++i){
			AllInterval[i] -> start = 0;
			AllInterval[i] -> end = LSRA_cnt - 1;
		}
	}
}

static void AddActiveInterval(Interval * i){
	ChainNode * c = (ChainNode *) malloc(sizeof(ChainNode));
	c -> i = i;
	c -> next = NULL;
	ChainNode * loc = ActiveInterval;
	if(loc == NULL) ActiveInterval = c;
	else{
		if(loc -> i -> end > c -> i -> end){
			/* add to head*/
			c -> next = loc;
			ActiveInterval = c;
		}
		else{
			while(loc -> next != NULL && loc -> next -> i -> end <= c -> i -> end)
				loc = loc -> next;
			c -> next = loc -> next;
			loc -> next = c;
		}
	}
	nActiveInterval++;
	return;
}

static void RemoveActiveInterval(ChainNode * c){
	if(c == ActiveInterval)
		ActiveInterval = c -> next;
	else{
		ChainNode * tc = ActiveInterval;
		while(tc != NULL && tc -> next != c){
			tc = tc -> next;
		}
		if(tc == NULL)
			LSRAError("remove inexistent active interval");
		else{
			tc -> next = c -> next;
			nActiveInterval--;
		}
	}
	return;
}

static void ExpireOldInterval(Interval * i){
	ChainNode * c = ActiveInterval;
	while(c != NULL){
		Interval * j = c -> i;
		if(j -> end >= i -> start)
			return;
		RemoveActiveInterval(c);
		RegStackPush(j -> reg);
		c = c -> next;
	}
	return;
}

static int NewStackLocation(){
	int ret = STACKBIAS + nStackLocation;
	nStackLocation++;
	return ret;
}

static void SpillAtInterval(Interval * i){
	ChainNode * c = ActiveInterval;
	if(c == NULL) return;
	while(c -> next != NULL)
		c = c -> next;
	Interval * spill = c -> i;
	if(spill -> end > i -> end){
		i -> reg = spill -> reg;
		spill -> reg = NewStackLocation();
		RemoveActiveInterval(c);
		AddActiveInterval(i);
	}
	else
		i -> reg = NewStackLocation();
	return;
}

static int cmp(const void * a, const void * b){
	return (*(Interval **)a) -> start - (*(Interval **)b) -> start;
}

static void LSRAPrint(char * FuncName, FILE * f){
	fprintf(f, "\n%s LSRA result\n", FuncName);
	for(int i = 0; i < nInterval; ++i){
		fprintf(f, "\t%s : start(%d) end(%d) ",
			   AllInterval[i] -> var_name, AllInterval[i] -> start,
			   AllInterval[i] -> end);
		if(AllInterval[i] -> reg < MAXREGISTOR)
			fprintf(f, "reg(%d)\n", AllInterval[i] -> reg);
		else
			fprintf(f, "stk(%d)\n", AllInterval[i] -> reg);
	}
	fprintf(f, "End LSRA result\n\n");
}

char * LocationSearch(char * var_name){
	char tmp[4] = {'\0'};
	if(var_name[0] == 'p'){
		strcpy(tmp, var_name);
		tmp[0] = 'a';
		return strdup(tmp);
	}
	int n = IntervalSearch(var_name);
	if(n == -1){
		LSRAError("Variable not included in interval array");
	}
	n = AllInterval[n] -> reg;
	if(n >= sBIAS && n < sBIAS + sNUM ) tmp[0] = 's';
	else if(n >= tBIAS && n < tBIAS + tNUM){
		tmp[0] = 't';
		n = n - tBIAS;
	}
	else{
		tmp[0] = 'e';
		n -= STACKBIAS;
		if(n > MAXSTACKPLACE){
			LSRAError("Too much extra memory needed");
		}
	}
	int p = 1;
	if(n == 0) tmp[p++] = '0';
	else{
		if(n/100 > 0){
			tmp[p++] = '0' + (n/100);
			n %= 100;
			if(n == 0){
				tmp[p++] = '0';
				tmp[p++] = '0';
			}
		}
		if(n/10 > 0){
			tmp[p++] = '0' + (n/10);
			n %= 10;
			if(n == 0){
				tmp[p++] = '0';
			}
		}
		if(n > 0){
			tmp[p++] = '0' + n;
		}
	}
	tmp[p++] = '\0';
	return strdup(tmp);
}

int LocalArrayAddrSearch(char * name){
	for(int i = 0 ; i < nLocalArray; ++i){
		if(!strcmp(LocalArrayName[i], name)){
			return LocalArrayAddr[i];
		}
	}
	return -1;
}

void LinearScanRegisterAllocation(TreeNode * root, int mode){
	if(root -> nodekind != FuncK){
		LSRAError("unexpected node kind in LinearScanRegisterAllocation, FuncK expected");
	}
	init();
	GenInterval(root, mode);
	qsort(AllInterval, nInterval, sizeof(Interval*), cmp);
	for(int _ = 0; _ < nInterval; ++_){
		Interval * i = AllInterval[_];
		ExpireOldInterval(i);
		if(nActiveInterval == MAXREGISTOR){
			SpillAtInterval(i);
		}
		else{
			i -> reg = RegStackPop();
			RegUsed[i -> reg] = 1;
			AddActiveInterval(i);
		}
	}
	for(int _ = 0; _ < nLocalArray; ++_){
		LocalArrayAddr[_] += STACKBIAS + nStackLocation;
	}
	LSRAPrint(root -> attr.name, stderr);
}
