#include <stdio.h>
#include <string.h>
#include "globals.h"
#include "mytree.h"
#include "eeyore.h"
#include "mystack.h"

#define MAXTVAR 1000
#define MAXtVAR 1000
#define MAXFUNC 200
#define MAXPARA 200

static int tab_n = 0;

static int T_n = 0;
static int T_n_saved = 0;
static char* T_name[MAXTVAR];
static int T_size[MAXTVAR];

static int t_n = 0;

static int p_n = 0;
static char* p_name[MAXFUNC][MAXPARA];

static int F_n = 0;
static int cur_F = -2;
static int main_rtned;
static char* F_name[MAXFUNC];
static int F_pn[MAXFUNC];
static int F_defned[MAXFUNC];
static int F_rtned[MAXFUNC];

static int l_n = 0;

static void eeyoreError(int lineno, char * message){
    if(lineno > 0)
        fprintf(stderr,"Eeyore generation error at line %d: %s\n", lineno, message);
    else
        fprintf(stderr,"Eeyore generation error: %s\n", message);
    exit(1);
}

static void warning(int lineno, char * message){
    fprintf(stderr,"Eeyore generation warning at line %d: %s\n", lineno, message);
}

static void program(TreeNode * node, FILE * f){
    TreeNode * t = node -> child[0];
    while(t != NULL){
        gen_eeyore(t, f);
        t = t -> sibling;
    }
    fprintf(f, "f_main [0]\n");
    cur_F = -1;
    tab_n++;
    p_n = 0;
    t = node -> child[1];
    while(t != NULL){
        gen_eeyore(t, f);
        t = t -> sibling;
    }
    if(!main_rtned)
        eeyoreError(node->lineno, "main function with no return");
    fprintf(f, "end f_main\n");
    tab_n--;
}

static void print_tab(FILE * f){
    int i;
    for(i = 0; i < tab_n; ++i)
        fprintf(f, "\t");
}

static int var_search(char * name){
    int i;
    for(i = 0; i < T_n; ++i){
        if(!strcmp(name, T_name[i]))
            return i;
    }
    return -1;
}

static int func_search(char * name){
    int i;
    for(i = 0; i < F_n; ++i){
        if(!strcmp(name, F_name[i]))
            return i;
    }
    if(!strcmp(name, "getint") || !strcmp(name, "putint")
       || !strcmp(name, "getchar") || !strcmp(name, "putchar")){
        return -1;
    }
    return -2;
}

static int para_search(char * name, int number){
	if(number < 0){
		char msg[100];
		sprintf(msg, "parameter search in main func"); // never hit
		warning(-1, msg);
		return -1;
	}
    int i;
    for(i = 0; i < F_pn[number]; ++i){
        if(!strcmp(name, p_name[number][i]))
            return i;
    }
    return -1;
}

static ExpType type_check(TreeNode * node){
	char msg[100];
	if(node == NULL){
		sprintf(msg, "type check for NULL node"); // never hit
		warning(node -> lineno, msg);
		return Void;
	}
	if(node -> nodekind != ExpK){
		sprintf(msg, "type check for Stmt node"); // never hit
		warning(node -> lineno, msg);
		return Void;
	}
	if(node -> kind.exp == OpK){
		switch (node -> attr.op) {
			case EQTT:
			case NEQTT:
			case MTTT:
			case LTTT:
				if(node -> child[0] -> type != Integer || node -> child[1] -> type != Integer){
					sprintf(msg, "comparison with unexpected type");
					warning(node -> lineno, msg);
				}
				break;
			default:
				if(node -> type != node -> child[0] -> type){
					sprintf(msg, "operation with unexpected type");
					warning(node -> lineno, msg);
				}
				if(node -> child[1] != NULL && node -> type != node -> child[1] -> type){
					sprintf(msg, "operation with unexpected type");
					warning(node -> lineno, msg);
				}
				break;
		}
		
	}
	return node -> type;
}

static void vardefn(TreeNode * node, FILE * f){
    if(var_search(node->child[0]->attr.name) >= 0)
        eeyoreError(node->lineno, "variable redefine");
	if(cur_F >= 0 && para_search(node->child[0]->attr.name, cur_F) >= 0)
		eeyoreError(node->lineno, "variable with same name to parameter");
    print_tab(f);
    T_name[T_n] = strdup(node->child[0]->attr.name);
    if(node->child[1] != NULL){
        T_size[T_n] = 4 * (node->child[1]->attr.val);
        fprintf(f, "var %d T%d\n", T_size[T_n], T_n);
    }
    else{
        T_size[T_n] = 0;
        fprintf(f, "var T%d\n", T_n);
    }
    T_n++;
}

static void funcdecl(TreeNode * node, FILE * f){
    char * name = node->child[0]->attr.name;
    if(func_search(name) >= 0)
        eeyoreError(node->lineno, "function redeclare");
    F_name[F_n] = strdup(name);
    F_pn[F_n] = 0;
    TreeNode * t = node->child[1];
    while(t != NULL){
        p_name[F_n][F_pn[F_n]++] = strdup(t-> child[0] -> attr.name);
        t = t->sibling;
    }
    if(!strcmp(name, "getint") ||
       !strcmp(name, "getchar")){
        if(F_pn[F_n] != 0)
            eeyoreError(node->lineno, "wrong declaration of built-in function");
        F_defned[F_n] = 1;
        F_rtned[F_n] = 1;
    }
    else if(!strcmp(name, "putint") ||
       !strcmp(name, "putchar")){
        if(F_pn[F_n] != 1)
            eeyoreError(node->lineno, "wrong declaration of built-in function");
        F_defned[F_n] = 1;
        F_rtned[F_n] = 1;
    }
    else{
        F_defned[F_n] = 0;
        F_rtned[F_n] = 0;
    }
    F_n++;
}

static void funcdefn(TreeNode * node, FILE * f){
    int i;
    char * name = node->child[0]->attr.name;
    i = func_search(name);
    if(i == -1){
        eeyoreError(node->lineno, "definition of built-in function");
    }
    if(i == -2){
        F_name[F_n] = strdup(name);
        TreeNode * t = node ->child[1];
        while(t != NULL){
            p_name[F_n][F_pn[F_n]++] = strdup(t-> child[0] -> attr.name);
            t = t->sibling;
        }
        F_defned[F_n] = 0;
        F_rtned[F_n] = 0;
        i = F_n;
        F_n++;
    }
    fprintf(f, "f_%s [%d]\n", name, F_pn[i]);
    T_n_saved = T_n;
    cur_F = i;
    tab_n++;
    p_n = 0;
    TreeNode * t = node -> child[2];
    while(t != NULL){
        gen_eeyore(t, f);
        t = t -> sibling;
    }
    if(!F_rtned[i]){
        char msg[100];
        sprintf(msg, "function -> %s with no return", name);
        eeyoreError(node->lineno, msg);
    }
    fprintf(f, "end f_%s\n", name);
    int j;
    for(j = T_n_saved ; j < T_n; ++j){
        T_name[j][0] = '\0';
    }
    tab_n--;
}

static void gen_if(TreeNode * node, FILE * f){
	if(node -> child[0] -> type != Boolean){
		char msg[100];
		sprintf(msg, "condition with unexpected type");
		warning(node -> lineno, msg);
	}
    int l_n_saved;
    gen_eeyore(node -> child[0], f);
    sNode * t = mypop();
    print_tab(f);
    fprintf(f, "if %s == 0 goto l%d\n", t -> name, l_n);
    l_n_saved = l_n;
    l_n++;
    gen_eeyore(node->child[1], f);
	if(node -> child[2] == NULL && node -> child[1] -> kind.stmt == IfK && node -> child[1] -> child[2] != NULL){
		warning(node -> lineno, "dangling else");
	}
    if(node -> child[2] != NULL){
        print_tab(f);
        fprintf(f, "goto l%d\nl%d:\n", l_n, l_n_saved);
        l_n_saved = l_n;
        l_n++;
        gen_eeyore(node->child[2], f);
    }
    fprintf(f, "l%d:\n", l_n_saved);
}

static void stmtseq(TreeNode * node, FILE * f){
    TreeNode * t = node -> child[0];
    while(t != NULL){
        gen_eeyore(t, f);
        t = t ->sibling;
    }
}

static void gen_while(TreeNode * node, FILE * f){
	if(node -> child[0] -> type != Boolean){
		char msg[100];
		sprintf(msg, "condition with unexpected type");
		warning(node -> lineno, msg);
	}
    int l_n_saved1, l_n_saved2;
    l_n_saved1 = l_n;
    fprintf(f, "l%d:\n", l_n);
    l_n++;
    gen_eeyore(node -> child[0], f);
    sNode * t = mypop();
    print_tab(f);
    fprintf(f, "if %s == 0 goto l%d\n", t -> name, l_n);
    l_n_saved2 = l_n;
    l_n++;
    gen_eeyore(node -> child[1], f);
    print_tab(f);
    fprintf(f, "goto l%d\n", l_n_saved1);
    fprintf(f, "l%d:\n", l_n_saved2);
}

static void gen_dowhile(TreeNode * node, FILE * f){
	if(node -> child[1] -> type != Boolean){
		char msg[100];
		sprintf(msg, "condition with unexpected type");
		warning(node -> lineno, msg);
	}
	int l_n_saved1;
	l_n_saved1 = l_n;
	fprintf(f, "l%d:\n", l_n);
	l_n++;
	gen_eeyore(node -> child[0], f);
	gen_eeyore(node -> child[1], f);
	sNode * t = mypop();
	print_tab(f);
	fprintf(f, "if %s == 0 goto l%d\n", t -> name, l_n_saved1);
}

static void gen_for(TreeNode * node, FILE * f){
	if(node -> child[0] -> type != Boolean){
		char msg[100];
		sprintf(msg, "condition with unexpected type");
		warning(node -> lineno, msg);
	}
	int l_n_saved1, l_n_saved2, l_n_saved3;
	print_tab(f);
	fprintf(f, "goto l%d\n", l_n);
	l_n_saved1 = l_n;
	l_n++;
	fprintf(f, "l%d:\n", l_n);
	l_n_saved2 = l_n;
	l_n++;
	gen_eeyore(node -> child[1], f);
	fprintf(f, "l%d:\n", l_n_saved1);
	gen_eeyore(node -> child[0], f);
	sNode * t = mypop();
	print_tab(f);
	fprintf(f, "if %s == 0 goto l%d\n", t -> name, l_n);
	l_n_saved3 = l_n;
	l_n++;
	gen_eeyore(node->child[2], f);
	print_tab(f);
	fprintf(f, "goto l%d\n", l_n_saved2);
	fprintf(f, "l%d:\n", l_n_saved3);
}

static void assign(TreeNode * node, FILE * f){
	if(node -> child[2] -> type != Integer){
		char msg[100];
		sprintf(msg, "assign with unexpected type");
		warning(node -> lineno, msg);
	}
    if(node -> child[1] == NULL){
        gen_eeyore(node -> child[0], f);
        gen_eeyore(node -> child[2], f);
        sNode * b = mypop();
        sNode * a = mypop();
        print_tab(f);
        fprintf(f, "%s = %s\n", a->name, b->name);
    }
    else{
		if(node -> child[1] -> type != Integer){
			char msg[100];
			sprintf(msg, "index with unexpected type");
			warning(node -> lineno, msg);
		}
        gen_eeyore(node -> child[0], f);
        gen_eeyore(node -> child[1], f);
        sNode * t = mypop();
        print_tab(f);
        fprintf(f, "var t%d\n", t_n);
        print_tab(f);
        fprintf(f, "t%d = 4 * %s\n",t_n, t->name);
        mypush(newsNode(tK, t_n));
        t_n++;
        gen_eeyore(node -> child[2], f);
        sNode * c = mypop();
        sNode * b = mypop();
        sNode * a = mypop();
        print_tab(f);
        fprintf(f, "%s [%s] = %s\n", a->name, b->name, c->name);
    }
}

static void ret(TreeNode * node, FILE * f){
    if(cur_F >= 0)
        F_rtned[cur_F] = 1;
    else
        main_rtned = 1;
	if(node -> child[0] -> type != Integer){
		char msg[100];
		sprintf(msg, "return with unexpected type");
		warning(node -> lineno, msg);
	}
    gen_eeyore(node -> child[0], f);
    sNode * t = mypop();
    print_tab(f);
    fprintf(f, "return %s\n", t -> name);
}

static void Sexp(TreeNode * node, FILE * f){
    warning(node->lineno, "expression as statement");
    gen_eeyore(node -> child[0], f);
    mypop();
}

static void exp_op(TreeNode * node, FILE * f){
	type_check(node);
    sNode * a;
    sNode * b;
    gen_eeyore(node -> child[0], f);
    if(node -> child[1] != NULL){
        gen_eeyore(node -> child[1], f);
        b = mypop();
    }
    a = mypop();
    switch(node -> attr.op){
        case ADDTT:
            print_tab(f);
            fprintf(f, "var t%d\n", t_n);
            print_tab(f);
            fprintf(f, "t%d = %s + %s\n", t_n, a->name, b->name);
            break;
        case SUBTT:
            print_tab(f);
            fprintf(f, "var t%d\n", t_n);
            print_tab(f);
            fprintf(f, "t%d = %s - %s\n", t_n, a->name, b->name);
            break;
        case MULTT:
            print_tab(f);
            fprintf(f, "var t%d\n", t_n);
            print_tab(f);
            fprintf(f, "t%d = %s * %s\n", t_n, a->name, b->name);
            break;
        case DIVTT:
            print_tab(f);
            fprintf(f, "var t%d\n", t_n);
            print_tab(f);
            fprintf(f, "t%d = %s / %s\n", t_n, a->name, b->name);
            break;
        case MODTT:
            print_tab(f);
            fprintf(f, "var t%d\n", t_n);
            print_tab(f);
            fprintf(f, "t%d = %s %c %s\n", t_n, a->name, '%', b->name);
            break;
        case LTTT:
            print_tab(f);
            fprintf(f, "var t%d\n", t_n);
            print_tab(f);
            fprintf(f, "t%d = %s < %s\n", t_n, a->name, b->name);
            break;
        case MTTT:
            print_tab(f);
            fprintf(f, "var t%d\n", t_n);
            print_tab(f);
            fprintf(f, "t%d = %s > %s\n", t_n, a->name, b->name);
            break;
        case EQTT:
            print_tab(f);
            fprintf(f, "var t%d\n", t_n);
            print_tab(f);
            fprintf(f, "t%d = %s == %s\n", t_n, a->name, b->name);
            break;
        case NEQTT:
            print_tab(f);
            fprintf(f, "var t%d\n", t_n);
            print_tab(f);
            fprintf(f, "t%d = %s != %s\n", t_n, a->name, b->name);
            break;
        case MINUSTT:
            print_tab(f);
            fprintf(f, "var t%d\n", t_n);
            print_tab(f);
            fprintf(f, "t%d = - %s\n", t_n, a->name);
            break;
		case PP1TT:
			print_tab(f);
			fprintf(f, "%s = %s + 1\n", a->name, a->name);
			print_tab(f);
			fprintf(f, "var t%d\n", t_n);
			print_tab(f);
			fprintf(f, "t%d = %s\n", t_n, a->name);
			break;
		case MM1TT:
			print_tab(f);
			fprintf(f, "%s = %s - 1\n", a->name, a->name);
			print_tab(f);
			fprintf(f, "var t%d\n", t_n);
			print_tab(f);
			fprintf(f, "t%d = %s\n", t_n, a->name);
			break;
		case PP2TT:
			print_tab(f);
			fprintf(f, "var t%d\n", t_n);
			print_tab(f);
			fprintf(f, "t%d = %s\n", t_n, a->name);
			print_tab(f);
			fprintf(f, "%s = %s + 1\n", a->name, a->name);
			break;
		case MM2TT:
			print_tab(f);
			fprintf(f, "var t%d\n", t_n);
			print_tab(f);
			fprintf(f, "t%d = %s\n", t_n, a->name);
			print_tab(f);
			fprintf(f, "%s = %s - 1\n", a->name, a->name);
			break;
        case NOTTT:
            print_tab(f);
            fprintf(f, "var t%d\n", t_n);
            print_tab(f);
            fprintf(f, "t%d = ! %s\n", t_n, a->name);
            break;
        case PARENTT:
            mypush(a);
            return;
        case ANDTT:
            print_tab(f);
            fprintf(f, "var t%d\n", t_n);
            print_tab(f);
            fprintf(f, "t%d = %s && %s\n", t_n, a->name, b->name);
            break;
        case ORTT:
            print_tab(f);
            fprintf(f, "var t%d\n", t_n);
            print_tab(f);
            fprintf(f, "t%d = %s || %s\n", t_n, a->name, b->name);
            break;
        default:
           return;
    }
    mypush(newsNode(tK, t_n));
    t_n++;
}

static void exp_const(TreeNode * node, FILE * f){
    mypush(newsNode(CK, node -> attr.val));
}

static void exp_id(TreeNode * node, FILE * f){
    int i;
    if(cur_F == -1){
        i = var_search(node -> attr.name);
        if(i >= 0){
            mypush(newsNode(TK, i));
            if(node -> child[0] != NULL){
				if(type_check(node -> child[0]) != Integer){
					char msg[100];
					sprintf(msg, "index with unexpected type");
					warning(node -> lineno, msg);
				}
                sNode * s = mypop();
                gen_eeyore(node -> child[0], f);
                sNode * t = mypop();
                print_tab(f);
                fprintf(f, "var t%d\n", t_n);
                print_tab(f);
                fprintf(f, "t%d = 4 * %s\n", t_n, t -> name);
                mypush(newsNode(tK, t_n));
                t_n++;
                t = mypop();
                print_tab(f);
                fprintf(f, "var t%d\n", t_n);
                print_tab(f);
                fprintf(f, "t%d = %s [%s]\n", t_n, s -> name, t -> name);
                mypush(newsNode(tK, t_n));
                t_n++;
            }
        }
        else{
            char msg[100];
            sprintf(msg, "undefined variable -> %s in function -> main", node -> attr.name);
            eeyoreError(node -> lineno, msg);
        }
    }
    else{
        i = para_search(node -> attr.name, cur_F);
        if(i >= 0){
            mypush(newsNode(pK, i));
            if(node -> child[0] != NULL){
				if(type_check(node -> child[0]) != Integer){
					char msg[100];
					sprintf(msg, "index with unexpected type");
					warning(node -> lineno, msg);
				}
                sNode * s = mypop();
                gen_eeyore(node -> child[0], f);
                sNode * t = mypop();
                print_tab(f);
                fprintf(f, "var t%d\n", t_n);
                print_tab(f);
                fprintf(f, "t%d = 4 * %s\n", t_n, t -> name);
                mypush(newsNode(tK, t_n));
                t_n++;
                t = mypop();
                print_tab(f);
                fprintf(f, "var t%d\n", t_n);
                print_tab(f);
                fprintf(f, "t%d = %s [%s]\n", t_n, s -> name, t -> name);
                mypush(newsNode(tK, t_n));
                t_n++;
            }
        }
        else{
            i = var_search(node -> attr.name);
            if(i >= 0){
                mypush(newsNode(TK, i));
                if(node -> child[0] != NULL){
					if(type_check(node -> child[0]) != Integer){
						char msg[100];
						sprintf(msg, "index with unexpected type");
						warning(node -> lineno, msg);
					}
                    sNode * s = mypop();
                    gen_eeyore(node -> child[0], f);
                    sNode * t = mypop();
                    print_tab(f);
                    fprintf(f, "var t%d\n", t_n);
                    print_tab(f);
                    fprintf(f, "t%d = 4 * %s\n", t_n, t -> name);
                    mypush(newsNode(tK, t_n));
                    t_n++;
                    t = mypop();
                    print_tab(f);
                    fprintf(f, "var t%d\n", t_n);
                    print_tab(f);
                    fprintf(f, "t%d = %s [%s]\n", t_n, s -> name, t -> name);
                    mypush(newsNode(tK, t_n));
                    t_n++;
                }
            }
            else{
                char msg[100];
                sprintf(msg, "undefined variable -> %s in function -> %s", node -> attr.name,  F_name[cur_F]);
                eeyoreError(node -> lineno, msg);
            }
        }
    }
}

static void exp_func(TreeNode * node, FILE * f){
    sNode * parameter[MAXPARA];
    char * name = node -> child[0] -> attr.name;
    int i = func_search(name);
    if(i == -2){
        char msg[100];
        sprintf(msg, "call of undeclared function -> %s", name);
        eeyoreError(node -> lineno, msg);
    }
    if(i == -1){
        char msg[100];
        sprintf(msg, "call of undeclared built-in function -> %s", name);
        warning(node -> lineno, msg);
    }
    TreeNode * t = node -> child[1];
    int p_cnt = 0;
    while(t != NULL){
        gen_eeyore(t, f);
        t = t -> sibling;
        parameter[p_cnt++] = mypop();
    }
    if((i >= 0 && p_cnt < F_pn[i]) || (!strcmp(name, "putint") && p_cnt < 1)
       || (!strcmp(name, "putchar") && p_cnt < 1)){
        char tmsg[100];
        sprintf(tmsg, "too few parameters for function -> %s", name);
        eeyoreError(node -> lineno, tmsg);
    }
    if((i >= 0 && p_cnt > F_pn[i]) || (!strcmp(name, "putint") && p_cnt > 1)
       || (!strcmp(name, "putchar") && p_cnt > 1)
       || (!strcmp(name, "getint") && p_cnt > 0)
       || (!strcmp(name, "getchar") && p_cnt > 0)){
        char tmsg[100];
        sprintf(tmsg, "too many parameters for function -> %s", name);
        eeyoreError(node -> lineno, tmsg);
    }
    int j;
    for(j = 0; j < p_cnt; ++j){
        print_tab(f);
        fprintf(f, "param %s\n", parameter[j] -> name);
    }
    print_tab(f);
    fprintf(f, "var t%d\n", t_n);
    print_tab(f);
    fprintf(f, "t%d = call f_%s\n", t_n, name);
    mypush(newsNode(tK, t_n));
    t_n++;
}

void gen_eeyore(TreeNode * node, FILE * f){
    if(node == NULL){
        eeyoreError(0, "NULL syntaxtree node");//never hit
        return;
    }
    if(node -> nodekind == StmtK){
        switch(node -> kind.stmt){
            case RootK:
                program(node, f);
                break;
            case VarDefnK:
                vardefn(node, f);
                break;
            case VarDeclK:
                //never hit
                return;
            case FuncDeclK:
                funcdecl(node, f);
                break;
            case FuncDefnK:
                funcdefn(node, f);
                break;
            case SeqK:
                stmtseq(node, f);
                break;
            case IfK:
                gen_if(node, f);
                break;
            case WhileK:
                gen_while(node, f);
                break;
            case AssignK:
                assign(node, f);
                break;
            case RetK:
                ret(node, f);
                break;
            case SExpK:
                Sexp(node, f);
                break;
			case DowhileK:
				gen_dowhile(node, f);
			case ForK:
				gen_for(node, f);
				break;
            default:
                break;
        }
    }
    else if(node -> nodekind == ExpK){
        switch(node -> kind.exp){
            case OpK:
                exp_op(node, f);
                break;
            case ConstK:
                exp_const(node, f);
                break;
            case IdK:
                exp_id(node, f);
                break;
            case FuncK:
                exp_func(node, f);
                break;
            default:
                break;
        }
    }
    else eeyoreError(node->lineno, "Unknown node kind");//never hit
}
