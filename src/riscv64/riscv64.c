#include <stdio.h>
#include <string.h>
#include "globals.h"
#include "mytree.h"
#include "riscv64.h"

static int stk;

static void riscv64Error(int lineno, char * message){
	if(lineno > 0)
		fprintf(stderr,"riscv64 generation error at line %d: %s\n", lineno, message);
	else
		fprintf(stderr,"riscv64 generation error: %s\n", message);
	exit(1);
}

static void riscv64Warning(int lineno, char * message){
	fprintf(stderr,"riscv64 generation warning at line %d: %s\n", lineno, message);
}

void GenRISCV64(TreeNode * root, FILE * f){
	if(root -> nodekind != RootK){
		riscv64Error(-1, "unexpected node kind in GenRISCV64, RootK expected");
	}
	TreeNode * t = root -> child;
	fprintf(f, "\t.text\n");
	while(t != NULL){
		if(t -> nodekind == VarDeclK){
			if(t -> nparam == 2){
				fprintf(f, "\t.comm\t%s,%d,%d\n", t -> param[0].name, 4, 4);
			}
			else{
				fprintf(f, "\t.comm\t%s,%d,%d\n", t -> param[0].name, t -> param[2].val, 8);
			}
		}
		else if(t -> nodekind == FuncK){
			stk = (t -> param[2].val/4+1)*16;
			char * name = t -> param[0].name+2;
			fprintf(f, "\t.align\t2\n\t.global\t%s\n\t.type\t%s,@function\n", name, name);
			fprintf(f, "%s:\n\tadd\tsp,sp,-%d\n\tsw\tra,%d(sp)\n", name, stk, stk-4);
			TreeNode * tt = t -> child;
			while(tt != NULL){
				switch(tt -> exprkind){
					case OpK:
						switch(tt -> op){
							case ADDTT:
								fprintf(f, "\tadd\t%s,%s,%s\n", tt->param[0].name, tt->param[1].name, tt->param[2].name);
								break;
							case SUBTT:
								fprintf(f, "\tsub\t%s,%s,%s\n", tt->param[0].name, tt->param[1].name, tt->param[2].name);
								break;
							case MULTT:
								fprintf(f, "\tmul\t%s,%s,%s\n", tt->param[0].name, tt->param[1].name, tt->param[2].name);
								break;
							case DIVTT:
								fprintf(f, "\tdiv\t%s,%s,%s\n", tt->param[0].name, tt->param[1].name, tt->param[2].name);
								break;
							case MODTT:
								fprintf(f, "\trem\t%s,%s,%s\n", tt->param[0].name, tt->param[1].name, tt->param[2].name);
								break;
							case LTTT:
								fprintf(f, "\tslt\t%s,%s,%s\n", tt->param[0].name, tt->param[1].name, tt->param[2].name);
								break;
							case MTTT:
								fprintf(f, "\tsgt\t%s,%s,%s\n", tt->param[0].name, tt->param[1].name, tt->param[2].name);
								break;
							case EQTT:
								fprintf(f, "\txor\t%s,%s,%s\n\tseqz\t%s,%s\n", tt->param[0].name, tt->param[1].name, tt->param[2].name, tt->param[0].name, tt->param[0].name);
								break;
							case NEQTT:
								fprintf(f, "\txor\t%s,%s,%s\n\tsnez\t%s,%s\n", tt->param[0].name, tt->param[1].name, tt->param[2].name, tt->param[0].name, tt->param[0].name);
								break;
							case ANDTT:
								fprintf(f, "\tseqz\t%s,%s\n\tadd\t%s,%s,-1\n\tand\t%s,%s,%s\n\tsnez\t%s,%s\n", tt->param[0].name, tt->param[1].name, tt->param[0].name, tt->param[0].name, tt->param[0].name, tt->param[0].name, tt->param[2].name, tt->param[0].name, tt->param[0].name);
								break;
							case ORTT:
								fprintf(f, "\tor\t%s,%s,%s\n\tsnez\t%s,%s\n", tt->param[0].name, tt->param[1].name, tt->param[2].name, tt->param[0].name, tt->param[0].name);
								break;
							case ADD2TT:
								fprintf(f, "\tadd\t%s,%s,%d\n", tt->param[0].name, tt->param[1].name, tt->param[2].val);
								break;
							case LT2TT:
								fprintf(f, "\tslti\t%s,%s,%d\n", tt->param[0].name, tt->param[1].name, tt->param[2].val);
								break;
							case MINUSTT:
								fprintf(f, "\tsub\t%s,%s,%s\n", tt->param[0].name, "x0", tt->param[1].name);
								break;
							case NOTTT:
								fprintf(f, "\txor\t%s,%s,%s\n\tseqz\t%s,%s\n", tt->param[0].name, tt->param[1].name, "x0", tt->param[0].name, tt->param[0].name);
								break;
							case ASS1TT:
								fprintf(f, "\tmv\t%s,%s\n", tt->param[0].name, tt->param[1].name);
								break;
							case ASS2TT:
								fprintf(f, "\tli\t%s,%d\n", tt->param[0].name, tt->param[1].val);
								break;
							case ASS3TT:
								fprintf(f, "\tlw\t%s,%d(%s)\n", tt->param[0].name, tt->param[2].val, tt->param[1].name);
								break;
							case ASS4TT:
								fprintf(f, "\tsw\t%s,%d(%s)\n", tt->param[2].name, tt->param[1].val, tt->param[0].name);
								break;
							default:
								break;
						}
						break;
					case IfK:
						switch (tt->op) {
							case EQTT:
								fprintf(f, "\tbeq\t%s,%s,%s\n", tt->param[0].name, tt->param[1].name, tt->param[2].name);
								break;
							case NEQTT:
								fprintf(f, "\tbne\t%s,%s,%s\n", tt->param[0].name, tt->param[1].name, tt->param[2].name);
								break;
							case MTTT:
								fprintf(f, "\tbgt\t%s,%s,%s\n", tt->param[0].name, tt->param[1].name, tt->param[2].name);
								break;
							case LTTT:
								fprintf(f, "\tblt\t%s,%s,%s\n", tt->param[0].name, tt->param[1].name, tt->param[2].name);
								break;
							default:
								break;
						}
						break;
					case GotoK:
						fprintf(f, "\tj\t%s\n", tt->param[0].name);
						break;
					case LabelK:
						fprintf(f, "%s:\n", tt->param[0].name);
						break;
					case CallK:
						fprintf(f, "\tcall\t%s\n", tt->param[0].name+2);
						break;
					case StoreK:
						fprintf(f, "\tsw\t%s,%d(sp)\n", tt->param[0].name, tt->param[1].val*4);
						break;
					case LoadK:
						if(tt->nparam == 2){
							fprintf(f, "\tlw\t%s,%d(sp)\n", tt->param[1].name, tt->param[0].val*4);
						}
						else{
							char * reg = tt->param[2].name;
							char * var = tt->param[0].name;
							fprintf(f, "\tlui\t%s,%%hi(%s)\n\tlw\t%s,%%lo(%s)(%s)\n", reg, var, reg, var, reg);
						}
						break;
					case LoadaddrK:
						if(tt->nparam == 2){
							fprintf(f, "\tadd\t%s,sp,%d\n", tt->param[1].name, tt->param[0].val*4);
						}
						else{
							char * reg = tt->param[2].name;
							char * var = tt->param[0].name;
							fprintf(f, "\tlui\t%s,%%hi(%s)\n\tadd\t%s,%s,%%lo(%s)\n", reg, var, reg, reg, var);
						}
						break;
					case RetK:
						fprintf(f,"\tlw\tra,%d(sp)\n\tadd\tsp,sp,%d\n\tjr\tra\n", stk-4, stk);
						break;
					default:
						break;
				}
				tt = tt -> sibling;
			}
			fprintf(f, "\t.size\t%s,.-%s\n\n", name, name);
		}
		else
			riscv64Error(t->lineno, "unexpected nodekind in GenRISCV64");
		t = t -> sibling;
	}
}
