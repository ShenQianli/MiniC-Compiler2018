%{
#include "globals.h"
#include "mytree.h"

extern TreeNode * root;
int yylex();
int yyerror(char *);
TreeNode * ParamBUF[10];
int pParamBUF = 0;

%}

%union
{
	int val;
    char * str;
    struct treeNode * treenode;
}

%token VAR IF GOTO PARAM CALL RETURN END
%token '+' '-' '*' '/' '=' '[' ']' ':' '!' '>' '<' '%'
%token AND OR EQ NEQ

%token <val> NUM
%token <str> ID
%token <str> LABEL
%token <str> FUNC
%type <val> OP1 OP2 LogicalOP
%type <treenode> Program Dseq VarDecl FuncDecl EDseq RVal Expr

%%

Program
:	Dseq
{
	$$ = newTreeNode(RootK);
	$$ -> child[0] = $1;
	root = $$;
}

Dseq
:	Dseq VarDecl
{
	TreeNode * t = $1;
	if(t != NULL){
		while (t->sibling != NULL)
		t = t->sibling;
		t->sibling = $2;
		$$ = $1;
	}
	else $$ = $2;
}
|	Dseq FuncDecl
{
	TreeNode * t = $1;
	if(t != NULL){
		while (t->sibling != NULL)
		t = t->sibling;
		t->sibling = $2;
		$$ = $1;
	}
	else $$ = $2;
}
|	/*Empty*/
{
	$$ = NULL;
}

VarDecl
:	VAR ID
{
	$$ = newTreeNode(InsK);
	$$ -> inskind = VarDeclK;
	$$ -> child[0] = newTreeNode(MarkK);
	$$ -> child[0] -> attr.name = strdup($2);
}
|	VAR NUM ID
{
	$$ = newTreeNode(InsK);
	$$ -> inskind = VarDeclK;
	$$ -> child[0] = newTreeNode(MarkK);
	$$ -> child[0] -> attr.name = strdup($3);
	$$ -> child[1] = newTreeNode(ConstK);
	$$ -> child[1] -> attr.val = $2;
}

FuncDecl
:	FUNC '[' NUM ']' EDseq END FUNC
{
	$$ = newTreeNode(FuncK);
	$$ -> attr.name = strdup($1);
	$$ -> child[0] = newTreeNode(ConstK);
	$$ -> child[0] -> attr.val = $3;
	$$ -> child[1] = $5;
}

EDseq
:	EDseq Expr
{
	TreeNode * t = $1;
	if(t != NULL){
		while (t->sibling != NULL)
			t = t->sibling;
		t->sibling = $2;
		$$ = $1;
	}
	else $$ = $2;
}
|	EDseq VarDecl
{
	TreeNode * t = $1;
	if(t != NULL){
		while (t->sibling != NULL)
			t = t->sibling;
		t->sibling = $2;
		$$ = $1;
	}
	else $$ = $2;
}
|	/*Empty*/
{
	$$ = NULL;
}

RVal
:	ID
{
	$$ = newTreeNode(MarkK);
	$$ -> attr.name = strdup($1);
}
|	NUM
{
	$$ = newTreeNode(ConstK);
	$$ -> attr.val = $1;
}

OP1
:	'-'	{$$ = '-';}
|	'!'	{$$ = '!';}

OP2
:	'+'	{$$ = '+';}
|	'-'	{$$ = '-';}
|	'*'	{$$ = '*';}
|	'/'	{$$ = '/';}
|	'%'	{$$ = '%';}
|	AND	{$$ = '&';}
|	OR	{$$ = '|';}
|	EQ	{$$ = '=';}
|	NEQ	{$$ = '!';}
|	'>'	{$$ = '>';}
|	'<'	{$$ = '<';}

LogicalOP
:	EQ	{$$ = '=';}
|	NEQ	{$$ = '!';}
|	'>'	{$$ = '>';}
|	'<'	{$$ = '<';}

Expr
:	ID '=' RVal OP2 RVal
{
	$$ = newTreeNode(InsK);
	$$ -> inskind = OpK;
	switch($4){
		case '+':
			$$ -> attr.op = ADDTT;
			break;
		case '-':
			$$ -> attr.op = SUBTT;
			break;
		case '*':
			$$ -> attr.op = MULTT;
			break;
		case '/':
			$$ -> attr.op = DIVTT;
			break;
		case '%':
			$$ -> attr.op = MODTT;
			break;
		case '&':
			$$ -> attr.op = ANDTT;
			break;
		case '|':
			$$ -> attr.op = ORTT;
			break;
		case '=':
			$$ -> attr.op = EQTT;
			break;
		case '!':
			$$ -> attr.op = NEQTT;
			break;
		case '>':
			$$ -> attr.op = MTTT;
			break;
		case '<':
			$$ -> attr.op = LTTT;
			break;
		default:
			break;
	}
	$$ -> child[0] = newTreeNode(MarkK);
	$$ -> child[0] -> attr.name = strdup($1);
	$$ -> child[1] = $3;
	$$ -> child[2] = $5;
}
|	ID '=' OP1 RVal
{
	$$ = newTreeNode(InsK);
	$$ -> inskind = OpK;
	switch($3){
		case '-':
			$$ -> attr.op = MINUSTT;
			break;
		case '!':
			$$ -> attr.op = NOTTT;
			break;
		default:
			break;
	}
	$$ -> child[0] = newTreeNode(MarkK);
	$$ -> child[0] -> attr.name = strdup($1);
	$$ -> child[1] = $4;
}
|	ID '=' RVal
{
	$$ = newTreeNode(InsK);
	$$ -> inskind = OpK;
	$$ -> attr.op = ASSTT;
	$$ -> child[0] = newTreeNode(MarkK);
	$$ -> child[0] -> attr.name = strdup($1);
	$$ -> child[1] = $3;
}
|	ID '[' RVal ']' '=' RVal
{
	$$ = newTreeNode(InsK);
	$$ -> inskind = OpK;
	$$ -> attr.op = SASSTT;
	$$ -> child[0] = newTreeNode(MarkK);
	$$ -> child[0] -> attr.name = strdup($1);
	$$ -> child[1] = $3;
	$$ -> child[2] = $6;
}
|	ID '=' ID '[' RVal ']'
{
	$$ = newTreeNode(InsK);
	$$ -> inskind = OpK;
	$$ -> attr.op = ASSTT;
	$$ -> child[0] = newTreeNode(MarkK);
	$$ -> child[0] -> attr.name = strdup($1);
	$$ -> child[1] = newTreeNode(MarkK);
	$$ -> child[1] -> attr.name = strdup($3);
	$$ -> child[2] = $5;
}
|	IF RVal LogicalOP RVal GOTO LABEL
{
	$$ = newTreeNode(InsK);
	$$ -> inskind = IfK;
	switch($3){
		case '=':
			$$ -> attr.op = EQTT;
			break;
		case '!':
			$$ -> attr.op = NEQTT;
			break;
		case '>':
			$$ -> attr.op = MTTT;
			break;
		case '<':
			$$ -> attr.op = LTTT;
			break;
		default:
			break;
	}
	$$ -> child[0] = $2;
	$$ -> child[1] = $4;
	$$ -> child[2] = newTreeNode(MarkK);
	$$ -> child[2] -> attr.name = strdup($6);
}
|	GOTO LABEL
{
	$$ = newTreeNode(InsK);
	$$ -> inskind = GotoK;
	$$ -> child[0] = newTreeNode(MarkK);
	$$ -> child[0] -> attr.name = strdup($2);
}
|	LABEL ':'
{
	$$ = newTreeNode(InsK);
	$$ -> inskind = LabelK;
	$$ -> child[0] = newTreeNode(MarkK);
	$$ -> child[0] -> attr.name = strdup($1);
}
|	PARAM RVal
{
	$$ = newTreeNode(InsK);
	$$ -> inskind = ParamK;
	$$ -> child[0] = $2;
	$$ -> child[1] = newTreeNode(MarkK);
	ParamBUF[pParamBUF++] = $$;
}
|	ID '=' CALL FUNC
{
	$$ = newTreeNode(InsK);
	$$ -> inskind = CallK;
	$$ -> child[0] = newTreeNode(MarkK);
	$$ -> child[0] -> attr.name = strdup($1);
	$$ -> child[1] = newTreeNode(MarkK);
	$$ -> child[1] -> attr.name = strdup($4);
	for(int i = 0; i < pParamBUF; ++i){
		ParamBUF[i] -> child[1] -> attr.name = strdup($4);
	}
	pParamBUF = 0;
}
|	RETURN RVal
{
	$$ = newTreeNode(InsK);
	$$ -> inskind = RetK;
	$$ -> child[0] = $2;
}

%%

int yyerror(char *message)
{
    fprintf(stderr, "Syntax error at line %d: %s\n",lineno,message);
    return 1;
}
