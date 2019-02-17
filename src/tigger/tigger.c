#include <stdio.h>
#include <string.h>
#include "globals.h"
#include "mytree.h"
#include "tigger.h"
#include "LSRA.h"

#define MAXGLOBALVAR 100
#define REGSTORE 0
#define REGLOAD 1

static int tab_n;
static char * GlobalVar[MAXGLOBALVAR];
static int nGlobalVar;
static char * cur_func;
static int para_cnt;
static int FreeReg[MAXREGISTOR];
static int nFreeReg;
static int pFreeReg;

static void tiggerError(int lineno, char * message){
    if(lineno > 0)
        fprintf(stderr,"tigger generation error at line %d: %s\n", lineno, message);
    else
        fprintf(stderr,"tigger generation error: %s\n", message);
    exit(1);
}

static void tiggerWarning(int lineno, char * message){
    fprintf(stderr,"tigger generation warning at line %d: %s\n", lineno, message);
}

static void AddGlobalVar(TreeNode * root, FILE * f){
	if(root -> nodekind != InsK || root -> inskind != VarDeclK){
		tiggerError(-1, "unexpected node kind in AddGlobalVar, InsK & VarDeclK expected");
	}
	GlobalVar[nGlobalVar] = strdup(root -> child[0] -> attr.name);
	if(root -> child[1] == NULL){
		fprintf(f, "v%d = 0\n", nGlobalVar);
	}
	else{
		fprintf(f, "v%d = malloc %d\n", nGlobalVar, root -> child[1] -> attr.val);
	}
	nGlobalVar++;
}

static int GlobalVarSearch(char * name){
	int i;
	for(i = 0; i < nGlobalVar; ++i){
		if(!strcmp(name, GlobalVar[i]))
			return i;
	}
	return -1;
}

static void PrintTab(FILE * f){
    int i;
    for(i = 0; i < tab_n; ++i)
        fprintf(f, "\t");
}

static int RegtoLoc(char * reg){
	if(reg == NULL) return -1;
	if(reg[0] == 's'){
		return (int)strtod(reg+sizeof(char), NULL) + sBIAS;
	}
	if(reg[0] == 't'){
		return (int)strtod(reg+sizeof(char), NULL) + tBIAS;
	}
	if(reg[0] == 'a'){
		return (int)strtod(reg+sizeof(char), NULL) + aBIAS;
	}
	return -1;
}

static char * LoctoReg(int loc){
	int n;
	char reg[4] = {'\0'};
	if(loc >= sBIAS && loc < sBIAS + sNUM){
		reg[0] = 's';
		n = loc - sBIAS;
	}
	else if(loc >= tBIAS && loc < tBIAS + tNUM){
		reg[0] = 't';
		n = loc - tBIAS;
	}
	else if(loc >= aBIAS && loc < aBIAS + aNUM){
		reg[0] = 'a';
		n = loc - aBIAS;
	}
	else return NULL;
	int p = 1;
	if(n == 0) reg[p++] = '0';
	else{
		if(n/10 > 0){
			reg[p++] = '0' + (n/10);
			n %= 10;
			if(n == 0){
				reg[p++] = '0';
			}
		}
		if(n > 0){
			reg[p++] = '0' + n;
		}
	}
	reg[p++] = '\0';
	return strdup(reg);
}

static void RegSL(char * reg, int mode, FILE * f){
	int loc = RegtoLoc(reg);
	if(loc == -1)
		tiggerError(-1, "Unknown RegSL reg type");
	PrintTab(f);
	if(mode == REGSTORE)
		fprintf(f, "store %s %d\n", reg, loc);
	else if(mode == REGLOAD)
		fprintf(f, "load %d %s\n", loc, reg);
	else
		tiggerError(-1, "Unknown RegSL mode");
}

static void RegBatchSL(char c, int mode, FILE * f){
	int bias, loops;
	switch(c){
		case 's':
			bias = sBIAS;
			loops = sNUM;
			break;
		case 't':
			bias = tBIAS;
			loops = tNUM;
			break;
		case 'a':
			bias = aBIAS;
			loops = aNUM;
			break;
		default:
			tiggerError(-1, "Unknown RegBatchSL reg type");
	}
	for(int i = 0; i < loops; ++i){
		if(c == 'a'&& mode == REGLOAD && i == 0) continue;
		PrintTab(f);
		if(mode == REGSTORE)
			fprintf(f, "store %c%d %d\n", c, i, i + bias);
		else if(mode == REGLOAD)
			fprintf(f, "load %d %c%d\n", i + bias, c, i);
		else
			tiggerError(-1, "Unknown RegBatchSL mode");
	}
}

static void GenOpCode(TreeNode * root, FILE * f){
	if(root -> child[2] == NULL){
		char op[4] = {'\0'};
		switch(root -> attr.op){
			case ASSTT:
				break;
			case MINUSTT:
				strcpy(op, "- ");
				break;
			case NOTTT:
				strcpy(op, "! ");
				break;
			default:
				/*never hit*/
				tiggerError(root -> lineno, "Unexpected op in GenCode");
		}
		char * name;
		int nx = -1, ny = -1;
		int locx = -1, locy = -1;
		char * X = NULL;
		char * Y = NULL;
		char tmpx[4] = {'t'}, tmpy[4] = {'t'};
		int xx = -1, yy = -1;
		int FreeY = 0;
		name = root -> child[0] -> attr.name;
		nx = GlobalVarSearch(name);
		X = LocationSearch(name);
		if(root -> child[1] -> nodekind == MarkK){
			name = root -> child[1] -> attr.name;
			ny = GlobalVarSearch(name);
			Y = LocationSearch(name);
		}
		if(X[0] == 'e'){
			locx = (int)strtod(X+sizeof(char), NULL) + STACKBIAS;
			for(xx = 0; xx < tNUM; ++xx){
				tmpx[1] = '0' + xx;
				if(strcmp(tmpx, X) && (Y == NULL || strcmp(tmpx, Y)))
					break;
			}
			X = tmpx;
		}
		if(Y == NULL || Y[0] == 'e'){
			if(Y == NULL && pFreeReg < nFreeReg){
				Y = LoctoReg(FreeReg[pFreeReg++]);
				FreeY = 1;
			}
			else{
				if(Y != NULL)
					locy = (int)strtod(Y+sizeof(char), NULL) + STACKBIAS;
				for(yy = 0; yy < tNUM; ++yy){
					tmpy[1] = '0' + yy;
					if(strcmp(tmpy, X) && (Y == NULL || strcmp(tmpy, Y)))
						break;
				}
				Y = tmpy;
			}
		}
		if(xx >= 0){
			RegSL(X, REGSTORE, f);
		}
		if(FreeY){
			PrintTab(f);fprintf(f, "%s = %d\n", Y, root -> child[1] -> attr.val);
		}
		if(ny >= 0){
			PrintTab(f);fprintf(f, "load v%d %s\n", ny, Y);
		}
		else if(yy >= 0){
			RegSL(Y, REGSTORE, f);
			if(locy >= 0){
				PrintTab(f);fprintf(f, "load %d %s\n", locy, Y);
			}
			else{
				PrintTab(f);fprintf(f, "%s = %d\n", Y, root -> child[1] -> attr.val);
			}
		}
		PrintTab(f);fprintf(f, "%s = %s%s\n", X, op, Y);
		if(nx >= 0){
			PrintTab(f);fprintf(f, "loadaddr v%d t6\n", nx);
			PrintTab(f);fprintf(f, "t6[0] = %s\n", X);
		}
		else if(locx >= 0){
			PrintTab(f);fprintf(f, "store %s %d\n", X, locx);
		}
		if(xx >= 0){
			RegSL(X, REGLOAD, f);
		}
		if(ny < 0 && yy >= 0){
			RegSL(Y, REGLOAD, f);
		}
	}
	else {
		char op[4] = {'\0'};
		switch(root -> attr.op){
			case ADDTT:
				strcpy(op, "+");
				break;
			case SUBTT:
				strcpy(op, "-");
				break;
			case MULTT:
				strcpy(op, "*");
				break;
			case DIVTT:
				strcpy(op, "/");
				break;
			case MODTT:
				strcpy(op, "%");
				break;
			case LTTT:
				strcpy(op, "<");
				break;
			case MTTT:
				strcpy(op, ">");
				break;
			case EQTT:
				strcpy(op, "==");
				break;
			case NEQTT:
				strcpy(op, "!=");
				break;
			case ANDTT:
				strcpy(op, "&&");
				break;
			case ORTT:
				strcpy(op, "||");
				break;
			case ASSTT:
				break;
			case SASSTT:
				break;
			default:
				/*never hit*/
				tiggerError(root -> lineno, "Unexpected op in GenCode");
		}
		char * name;
		int nx = -1, ny = -1, nz = -1;
		int locx = -1, locy = -1, locz = -1;
		char * X = NULL;
		char * Y = NULL;
		char * Z = NULL;
		char tmpx[4] = {'t'}, tmpy[4] = {'t'}, tmpz[4] = {'t'};
		int xx = -1, yy = -1, zz = -1;
		int FreeY = 0, FreeZ = 0;
		name = root -> child[0] -> attr.name;
		nx = GlobalVarSearch(name);
		X = LocationSearch(name);
		if(root -> child[1] -> nodekind == MarkK){
			name = root -> child[1] -> attr.name;
			ny = GlobalVarSearch(name);
			Y = LocationSearch(name);
		}
		if(root -> child[2] -> nodekind == MarkK){
			name = root -> child[2] -> attr.name;
			nz = GlobalVarSearch(name);
			Z = LocationSearch(name);
		}
		if(X[0] == 'e'){
			locx = (int)strtod(X+sizeof(char), NULL) + STACKBIAS;
			for(xx = 0; xx < tNUM; ++xx){
				tmpx[1] = '0' + xx;
				if(strcmp(tmpx, X) && (Y == NULL || strcmp(tmpx, Y)) && (Z == NULL || strcmp(tmpx, Z)))
					break;
			}
			X = tmpx;
		}
		if(Y == NULL || Y[0] == 'e'){
			if(Y == NULL && pFreeReg < nFreeReg){
				Y = LoctoReg(FreeReg[pFreeReg++]);
				FreeY = 1;
			}
			else{
				if(Y != NULL)
					locy = (int)strtod(Y+sizeof(char), NULL) + STACKBIAS;
				for(yy = 0; yy < tNUM; ++yy){
					tmpy[1] = '0' + yy;
					if(strcmp(tmpy, X) && (Y == NULL || strcmp(tmpy, Y)) && (Z == NULL || strcmp(tmpy, Z)))
						break;
				}
				Y = tmpy;
			}
		}
		if(Z == NULL || Z[0] == 'e'){
			if(Z == NULL && pFreeReg < nFreeReg){
				Z = LoctoReg(FreeReg[pFreeReg++]);
				FreeZ = 1;
			}
			else{
				if(Z != NULL)
					locz = (int)strtod(Z+sizeof(char), NULL) + STACKBIAS;
				for(zz = 0; zz < tNUM; ++zz){
					tmpz[1] = '0' + zz;
					if(strcmp(tmpz, X) && (Y == NULL || strcmp(tmpz, Y)) && (Z == NULL || strcmp(tmpz, Z)))
						break;
				}
				Z = tmpz;
			}
		}
		if(xx >= 0){
			RegSL(X, REGSTORE, f);
		}
		if(FreeY){
			PrintTab(f);fprintf(f, "%s = %d\n", Y, root -> child[1] -> attr.val);
		}
		if(ny >= 0){
			if(root -> attr.op == ASSTT){
				PrintTab(f);fprintf(f, "loadaddr v%d %s\n", ny, Y);
			}
			else{
				PrintTab(f);fprintf(f, "load v%d %s\n", ny, Y);
			}
		}
		else if(yy >= 0){
			RegSL(Y, REGSTORE, f);
			if(locy >= 0){
				if(root -> attr.op == ASSTT){
					int addr = LocalArrayAddrSearch(root -> child[1] -> attr.name);
					PrintTab(f);fprintf(f, "loadaddr %d %s\n", addr, Y);
				}
				else{
					PrintTab(f);fprintf(f, "load %d %s\n", locy, Y);
				}
			}
			else{
				PrintTab(f);fprintf(f, "%s = %d\n", Y, root -> child[1] -> attr.val);
			}
		}
		else if(root -> attr.op == ASSTT){
			int addr = LocalArrayAddrSearch(root -> child[1] -> attr.name);
			PrintTab(f);fprintf(f, "loadaddr %d %s\n", addr, Y);
		}
		if(FreeZ){
			PrintTab(f);fprintf(f, "%s = %d\n", Z, root -> child[2] -> attr.val);
		}
		if(nz >= 0){
			PrintTab(f);fprintf(f, "load v%d %s\n", nz, Z);
		}
		else if(zz >= 0){
			RegSL(Z, REGSTORE, f);
			if(locz >= 0){
				PrintTab(f);fprintf(f, "load %d %s\n", locz, Z);
			}
			else{
				PrintTab(f);fprintf(f, "%s = %d\n", Z, root -> child[2] -> attr.val);
			}
		}
		if(root -> attr.op == ASSTT){
			PrintTab(f);fprintf(f, "t6 = %s + %s\n", Y, Z);
			PrintTab(f);fprintf(f, "%s = t6[0]\n", X);
		}
		else if(root -> attr.op == SASSTT){
			if(nx >= 0){
				PrintTab(f);fprintf(f, "loadaddr v%d %s\n", nx, X);
			}
			else if(xx >= 0){
				RegSL(X, REGSTORE, f);
				int addr = LocalArrayAddrSearch(root -> child[0] -> attr.name);
				PrintTab(f);fprintf(f, "loadaddr %d %s\n", addr, X);
			}
			PrintTab(f);fprintf(f, "t6 = %s + %s\n", X, Y);
			PrintTab(f);fprintf(f, "t6[0] = %s\n", Z);
		}
		else{
			PrintTab(f);fprintf(f, "%s = %s %s %s\n", X, Y, op, Z);
		}
		if(nx >= 0 && root -> attr.op != SASSTT){
			PrintTab(f);fprintf(f, "loadaddr v%d t6\n", nx);
			PrintTab(f);fprintf(f, "t6[0] = %s\n", X);
		}
		else if(locx >= 0 && root -> attr.op != SASSTT){
			PrintTab(f);fprintf(f, "store %s %d\n", X, locx);
		}
		if(xx >= 0){
			RegSL(X, REGLOAD, f);
		}
		if(ny < 0 && yy >= 0){
			RegSL(Y, REGLOAD, f);
		}
		if(nz < 0 && zz >= 0){
			RegSL(Z, REGLOAD, f);
		}
	}
	pFreeReg = 0;
}

static void GenCode(TreeNode * root, FILE * f){
	if(root -> nodekind != InsK){
		tiggerError(-1, "unexpected node kind in GenCode, InsK expected");
	}
	switch(root -> inskind){
		case VarDeclK:
			break;
		case OpK:
			GenOpCode(root, f);
			break;
		case IfK:
			/*our Eeyore garantee the condition has the form "RightVal == 0"*/
			if(root -> attr.op != EQTT || root -> child[1] -> nodekind != ConstK
			   || root -> child[1] -> attr.val != 0){
				tiggerError(root -> lineno, "Unexpected condition");
			}
			if(root -> child[0] -> nodekind == ConstK){
				PrintTab(f);fprintf(f, "t6 = %d\n", root -> child[0] -> attr.val);
			}
			else if(root -> child[0] -> nodekind == MarkK){
				char * name = root -> child[0] -> attr.name;
				int n = GlobalVarSearch(name);
				if(n >= 0){
					PrintTab(f);fprintf(f, "load v%d t6\n", n);
				}
				else{
					char * tmp = LocationSearch(name);
					if(tmp[0] == 'e'){
						int loc = (int)strtod(tmp+sizeof(char), NULL) + STACKBIAS;
						PrintTab(f);fprintf(f, "load %d t6\n", loc);
					}
					else{
						PrintTab(f);fprintf(f, "t6 = %s\n", tmp);
					}
				}
			}
			else{
				/*never hit*/
				tiggerError(-1, "Unknown Rval kind in GenCode");
			}
			PrintTab(f);fprintf(f, "if t6 == x0 goto %s\n", root -> child[2] -> attr.name);
			break;
		case GotoK:
			PrintTab(f);fprintf(f, "goto %s\n", root -> child[0] -> attr.name);
			break;
		case LabelK:
			fprintf(f, "%s:\n", root -> child[0] -> attr.name);
			break;
		case ParamK:
		{
			char * funcname = root -> child[1] -> attr.name;
			char r[5];
			sprintf(r, "a%d", para_cnt);
			RegSL(r, REGSTORE, f);
			if(root -> child[0] -> nodekind == ConstK){
				PrintTab(f);fprintf(f, "a%d = %d\n", para_cnt, root -> child[0] -> attr.val);
			}
			else if(root -> child[0] -> nodekind == MarkK){
				char * name = root -> child[0] -> attr.name;
				int n = GlobalVarSearch(name);
				if(n >= 0){
					PrintTab(f);fprintf(f, "load v%d a%d\n", n, para_cnt);
				}
				else{
					char * tmp = LocationSearch(name);
					if(tmp[0] == 'e'){
						int loc = (int)strtod(tmp+sizeof(char), NULL) + STACKBIAS;
						PrintTab(f);fprintf(f, "load %d a%d\n", loc, para_cnt);
					}
					else{
						PrintTab(f);fprintf(f, "a%d = %s\n", para_cnt, tmp);
					}
				}
			}
			else{
				/*never hit*/
				tiggerError(-1, "Unknown parameter kind in GenCode");
			}
			para_cnt++;
			break;
		}
		case CallK:
		{
			char * funcname = root -> child[1] -> attr.name;
			if(strcmp(funcname, "f_getint") && strcmp(funcname, "f_getchar")){
				RegBatchSL('t', REGSTORE, f);
			}
			if(para_cnt == 0){
				RegSL("a0", REGSTORE, f);
			}
			int cnt = para_cnt;
			para_cnt = 0;
			PrintTab(f);
			fprintf(f, "call %s\n", funcname);
			if(strcmp(funcname, "f_getint") && strcmp(funcname, "f_getchar")){
				RegBatchSL('t', REGLOAD, f);
			}
			char r[5] = "a1";
			for(int i = 1; i < cnt; ++i){
				r[1] = '0' + i;
				RegSL(r, REGLOAD, f);
			}
			char * name = root -> child[0] -> attr.name;
			char * tmp = LocationSearch(name);
			int n = GlobalVarSearch(name);
			if(n >= 0){
				PrintTab(f);fprintf(f, "loadaddr v%d t6\n", n);
				PrintTab(f);fprintf(f, "t6[0] = a0\n");
			}
			else{
				if(tmp[0] == 'e'){
					int loc = (int)strtod(tmp+sizeof(char), NULL) + STACKBIAS;
					PrintTab(f);fprintf(f, "store a0 %d\n", loc);
				}
				else{
					PrintTab(f);fprintf(f, "%s = a0\n", tmp);
				}
			}
			if(!strcmp(tmp, "a0"))
				RegSL("a0", REGLOAD, f);
			break;
		}
		case RetK:
			if(root -> child[0] -> nodekind == MarkK){
				int n = GlobalVarSearch(root -> child[0] -> attr.name);
				if(n >= 0){
					PrintTab(f);fprintf(f, "load v%d a0\n", n);
					if(strcmp(cur_func, "f_main")){
						RegBatchSL('s', REGLOAD, f);
					}
					PrintTab(f);fprintf(f, "return\n");
					return;
				}
				char * tmp = LocationSearch(root -> child[0] -> attr.name);
				if(tmp[0] == 'e'){
					int loc = (int)strtod(tmp+sizeof(char), NULL) + STACKBIAS;
					PrintTab(f);fprintf(f, "load %d a0\n", loc);
					if(strcmp(cur_func, "f_main")){
						RegBatchSL('s', REGLOAD, f);
					}
					PrintTab(f);fprintf(f, "return\n");
				}
				else{
					PrintTab(f);fprintf(f, "a0 = %s\n", tmp);
					if(strcmp(cur_func, "f_main")){
						RegBatchSL('s', REGLOAD, f);
					}
					PrintTab(f);fprintf(f, "return\n");
				}
			}
			else if(root -> child[0] -> nodekind == ConstK){
				PrintTab(f);fprintf(f, "a0 = %d\n", root -> child[0] -> attr.val);
				if(strcmp(cur_func, "f_main")){
					RegBatchSL('s', REGLOAD, f);
				}
				PrintTab(f);fprintf(f, "return\n");
			}
			else{
				/*never hit*/
				tiggerError(root -> lineno, "Unknown return type");
			}
			break;
		default:
			/*never hit*/
			tiggerError(-1, "Unknown instruction kind in GenCode");
			break;
	}
}

void GenTigger(TreeNode * root, FILE * f, int mode){
	if(root -> nodekind != RootK){
		tiggerError(-1, "unexpected node kind in GenTigger, RootK expected");
	}
	TreeNode * t = root -> child[0];
	while(t != NULL){
		if(t -> nodekind == InsK && t -> inskind == VarDeclK){
			AddGlobalVar(t, f);
		}
		else if(t -> nodekind == FuncK){
			LinearScanRegisterAllocation(t, mode);
			nFreeReg = 0;
			pFreeReg = 0;
			for(int i = 0; i < MAXREGISTOR; ++i){
				if(RegUsed[i] == 0){
					FreeReg[nFreeReg++] = i;
				}
			}
			fprintf(f, "%s [%d] [%d]\n", t -> attr.name, t -> child[0] -> attr.val, STACKBIAS+nStackLocation+LocalArraySpace);
			cur_func = t -> attr.name;
			tab_n++;
			if(strcmp(cur_func, "f_main")){
				RegBatchSL('s', REGSTORE, f);
			}
			TreeNode * ins = t -> child[1];
			while(ins != NULL){
				GenCode(ins, f);
				ins = ins -> sibling;
			}
			tab_n--;
			fprintf(f, "end %s\n", t -> attr.name);
		}
		else{
			tiggerError(-1, "unexpected node kind in GenTigger, FuncK or InsK expected");
		}
		t = t -> sibling;
	}
}
