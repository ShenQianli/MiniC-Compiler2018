#ifndef _LSRA_H_
#define _LSRA_H_
#include "globals.h"

#define MAXREGISTOR 18
#define MAXINTERVAL 1000
#define MAXSTACKPLACE 999
#define MAXLOCALARRAY 100

#define TRIVIAL 0
#define NAIVE 1
#define BB 2

#define sBIAS 0
#define sNUM 12
#define tBIAS 12
#define tNUM 7
#define aBIAS 19
#define aNUM 8
#define STACKBIAS 27

int LSRA_cnt;

typedef struct interval{
	int start;
	int end;
	char * var_name;
	int reg;
}Interval;

typedef struct chainNode{
	Interval * i;
	struct chainNode * next;
}ChainNode;

Interval * AllInterval[MAXINTERVAL];
int nInterval;

ChainNode * ActiveInterval;
int nActiveInterval;
/* Maintain in chain list, in order of increasing END point */

int RegStack[MAXREGISTOR];
int pRegStack;

int nStackLocation;

char * LocationSearch(char * var_name);

int RegUsed[MAXREGISTOR];

int nLocalArray;
char * LocalArrayName[MAXLOCALARRAY];
int LocalArraySize[MAXLOCALARRAY];
int LocalArrayAddr[MAXLOCALARRAY];
int LocalArraySpace;

int LocalArrayAddrSearch(char * name);

void LinearScanRegisterAllocation(TreeNode * root, int mode);

#endif
