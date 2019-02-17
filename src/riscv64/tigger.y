%{
#include "globals.h"
#include "mytree.h"

extern TreeNode * root;
int yylex();
int yyerror(char *);

%}

%union
{
	int val;
    char * str;
    struct treeNode * treenode;
}

%token IF LOAD LOADADDR STORE MALLOC GOTO CALL RETURN END
%token '+' '-' '*' '/' '=' '[' ']' ':' '!' '>' '<' '%'
%token AND OR EQ NEQ

%token <val> NUM
%token <str> VAR
%token <str> REG
%token <str> LABEL
%token <str> FUNC
%type <val> OP1 OP2 LogicalOP
%type <treenode> Program Dseq VarDecl FuncDecl Eseq Expr

%%

Program
:	Dseq
{
	$$ = newTreeNode(RootK);
	$$ -> child = $1;
	root = $$;
}

Dseq
:	Dseq VarDecl
{
	TreeNode * t = $1;
	if(t != NULL){
		while (t->sibling != NULL) t = t->sibling;
		t->sibling = $2;
		$$ = $1;
	}
	else $$ = $2;
}
|	Dseq FuncDecl
{
	TreeNode * t = $1;
	if(t != NULL){
		while (t->sibling != NULL) t = t->sibling;
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
:	VAR '=' NUM
{
	$$ = newTreeNode(VarDeclK);
	$$ -> param[$$->nparam++].name = strdup($1);
	$$ -> param[$$->nparam++].val = $3;
}
|	VAR '=' MALLOC NUM
{
	$$ = newTreeNode(VarDeclK);
	$$ -> param[$$->nparam++].name = strdup($1);
	$$ -> nparam++;
	$$ -> param[$$->nparam++].val = $4;
}

FuncDecl
:	FUNC '[' NUM ']' '[' NUM ']' Eseq END FUNC
{
	if(strcmp($1, $10)){
		yyerror("unmatched function declaration");
	}
	$$ = newTreeNode(FuncK);
	$$ -> child = $8;
	$$ -> param[$$->nparam++].name = strdup($1);
	$$ -> param[$$->nparam++].val = $3;
	$$ -> param[$$->nparam++].val = $6;
}

Eseq
:	Eseq Expr
{
	TreeNode * t = $1;
	if(t != NULL){
		while (t->sibling != NULL) t = t->sibling;
		t->sibling = $2;
		$$ = $1;
	}
	else $$ = $2;
}
|	/*Empty*/
{
	$$ = NULL;
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
:	REG '=' REG OP2 REG
{
	$$ = newTreeNode(ExprK);
	$$ -> exprkind = OpK;
	switch($4){
		case '+':
			$$ -> op = ADDTT;
			break;
		case '-':
			$$ -> op = SUBTT;
			break;
		case '*':
			$$ -> op = MULTT;
			break;
		case '/':
			$$ -> op = DIVTT;
			break;
		case '%':
			$$ -> op = MODTT;
			break;
		case '&':
			$$ -> op = ANDTT;
			break;
		case '|':
			$$ -> op = ORTT;
			break;
		case '=':
			$$ -> op = EQTT;
			break;
		case '!':
			$$ -> op = NEQTT;
			break;
		case '>':
			$$ -> op = MTTT;
			break;
		case '<':
			$$ -> op = LTTT;
			break;
		default:
			break;
	}
	$$ -> param[$$->nparam++].name = strdup($1);
	$$ -> param[$$->nparam++].name = strdup($3);
	$$ -> param[$$->nparam++].name = strdup($5);
}
|	REG '=' REG OP2 NUM
{
	$$ = newTreeNode(ExprK);
	$$ -> exprkind = OpK;
	switch($4){
		case '+':
			$$ -> op = ADD2TT;
			break;
		case '<':
			$$ -> op = LT2TT;
			break;
		default:
			yyerror("unexpected operator in expression 'Reg = Reg OP2 <INTERGER>', only '+', '<' permitterd");
	}
	$$ -> param[$$->nparam++].name = strdup($1);
	$$ -> param[$$->nparam++].name = strdup($3);
	$$ -> param[$$->nparam++].val = $5;
}
|	REG '=' OP1 REG
{
	$$ = newTreeNode(ExprK);
	$$ -> exprkind = OpK;
	switch($3){
		case '-':
			$$ -> op = MINUSTT;
			break;
		case '!':
			$$ -> op = NOTTT;
			break;
		default:
			break;
	}
	$$ -> param[$$->nparam++].name = strdup($1);
	$$ -> param[$$->nparam++].name = strdup($4);
}
|	REG '=' REG
{
	$$ = newTreeNode(ExprK);
	$$ -> exprkind = OpK;
	$$ -> op = ASS1TT;
	$$ -> param[$$->nparam++].name = strdup($1);
	$$ -> param[$$->nparam++].name = strdup($3);
}
|	REG '=' NUM
{
	$$ = newTreeNode(ExprK);
	$$ -> exprkind = OpK;
	$$ -> op = ASS2TT;
	$$ -> param[$$->nparam++].name = strdup($1);
	$$ -> param[$$->nparam++].val = $3;
	
}
|	REG '=' REG '[' NUM ']'
{
	$$ = newTreeNode(ExprK);
	$$ -> exprkind = OpK;
	$$ -> op = ASS3TT;
	$$ -> param[$$->nparam++].name = strdup($1);
	$$ -> param[$$->nparam++].name = strdup($3);
	$$ -> param[$$->nparam++].val = $5;
}
|	REG '[' NUM ']' '=' REG
{
	$$ = newTreeNode(ExprK);
	$$ -> exprkind = OpK;
	$$ -> op = ASS4TT;
	$$ -> param[$$->nparam++].name = strdup($1);
	$$ -> param[$$->nparam++].val = $3;
	$$ -> param[$$->nparam++].name = strdup($6);
}
|	IF REG LogicalOP REG GOTO LABEL
{
	$$ = newTreeNode(ExprK);
	$$ -> exprkind = IfK;
	switch($3){
		case '=':
			$$ -> op = EQTT;
			break;
		case '!':
			$$ -> op = NEQTT;
			break;
		case '>':
			$$ -> op = MTTT;
			break;
		case '<':
			$$ -> op = LTTT;
			break;
		default:
			break;
	}
	$$ -> param[$$->nparam++].name = strdup($2);
	$$ -> param[$$->nparam++].name = strdup($4);
	$$ -> param[$$->nparam++].name = strdup($6);
}
|	GOTO LABEL
{
	$$ = newTreeNode(ExprK);
	$$ -> exprkind = GotoK;
	$$ -> param[$$->nparam++].name = strdup($2);
}
|	LABEL ':'
{
	$$ = newTreeNode(ExprK);
	$$ -> exprkind = LabelK;
	$$ -> param[$$->nparam++].name = strdup($1);
}
|	CALL FUNC
{
	$$ = newTreeNode(ExprK);
	$$ -> exprkind = CallK;
	$$ -> param[$$->nparam++].name = strdup($2);
}
|	RETURN
{
	$$ = newTreeNode(ExprK);
	$$ -> exprkind = RetK;
}
|	STORE REG NUM
{
	$$ = newTreeNode(ExprK);
	$$ -> exprkind = StoreK;
	$$ -> param[$$->nparam++].name = strdup($2);
	$$ -> param[$$->nparam++].val = $3;
}
|	LOAD NUM REG
{
	$$ = newTreeNode(ExprK);
	$$ -> exprkind = LoadK;
	$$ -> param[$$->nparam++].val = $2;
	$$ -> param[$$->nparam++].name = strdup($3);
}
|	LOAD VAR REG
{
	$$ = newTreeNode(ExprK);
	$$ -> exprkind = LoadK;
	$$ -> param[$$->nparam++].name = strdup($2);
	$$ -> nparam++;
	$$ -> param[$$->nparam++].name = strdup($3);
}
|	LOADADDR NUM REG
{
	$$ = newTreeNode(ExprK);
	$$ -> exprkind = LoadaddrK;
	$$ -> param[$$->nparam++].val = $2;
	$$ -> param[$$->nparam++].name = strdup($3);
}
|	LOADADDR VAR REG
{
	$$ = newTreeNode(ExprK);
	$$ -> exprkind = LoadaddrK;
	$$ -> param[$$->nparam++].name = strdup($2);
	$$ -> nparam++;
	$$ -> param[$$->nparam++].name = strdup($3);
}
%%

int yyerror(char *message)
{
    fprintf(stderr, "Syntax error at line %d: %s\n",lineno,message);
    exit(1);
}
