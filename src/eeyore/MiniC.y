%{
#include "globals.h"
#include "mytree.h"


extern TreeNode * root;
int yylex();
int yyerror(char *);

%}

%union
{
    int vint;
    char * vstr;
    struct treeNode * vtree;
}

%token TYPE IF ELSE WHILE MAIN RETURN DO FOR
%token '+' '-' '*' '/' '%' '>' '<'
%token AND OR EQ NEQ PP MM

%token <vint> NUM
%token <vstr> ID
%type <vtree> Program DDSeq VarDefn VarDecl VarDeclSeq FuncBody FuncDecl FuncDefn MainFunc StmtSeq Stmt ExpSeq Exp

%left '+' '-'
%left '*' '/' '%'
%left AND
%left OR
%left '<' '>' EQ NEQ
%left '!'

%%
Program
    :   DDSeq MainFunc
        {
            root = newStmtNode(RootK);
            root->child[0] = $1;
            root->child[1] = $2;
        }

DDSeq
    :   DDSeq VarDefn
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
    |   DDSeq FuncDefn
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
    |   DDSeq FuncDecl
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
    |   /* Empty */
        {$$ = NULL;}

VarDefn
    :   TYPE ID ';'
        {
            $$ = newStmtNode(VarDefnK);
            $$ -> child[0] = newExpNode(IdK);
            $$ -> child[0] -> attr.name = strdup($2);
        }
	|	TYPE ID '=' Exp ';'
		{
			$$ = newStmtNode(VarDefnK);
			$$ -> child[0] = newExpNode(IdK);
			$$ -> child[0] -> attr.name = strdup($2);
			$$ -> sibling = newStmtNode(AssignK);
			$$ -> sibling -> child[0] = newExpNode(IdK);
			$$ -> sibling -> child[0] -> attr.name = strdup($2);
			$$ -> sibling -> child[2] = $4;
		}
    |   TYPE ID '[' NUM ']' ';'
        {
            $$ = newStmtNode(VarDefnK);
            $$ -> child[0] = newExpNode(IdK);
            $$ -> child[0] -> attr.name = strdup($2);
            $$ -> child[1] = newExpNode(ConstK);
            $$ -> child[1] -> attr.val = $4;
        }

VarDecl
    :   TYPE ID
        {
            $$ = newStmtNode(VarDeclK);
            $$ -> child[0] = newExpNode(IdK);
            $$ -> child[0] -> attr.name = strdup($2);
        }
    |   TYPE ID '[' ']'
        {
            $$ = newStmtNode(VarDeclK);
            $$ -> child[0] = newExpNode(IdK);
            $$ -> child[0] -> attr.name = strdup($2);
        }
    |   TYPE ID '[' NUM ']'
        {
            $$ = newStmtNode(VarDeclK);
            $$ -> child[0] = newExpNode(IdK);
            $$ -> child[0] -> attr.name = strdup($2);
//            $$ -> child[1] = newExpNode(ConstK);
//            $$ -> child[1] -> attr.val = $4;
        }

VarDeclSeq
    :   VarDecl
        {$$ = $1;}
    |   VarDeclSeq ',' VarDecl
        {
            TreeNode * t = $1;
            while (t->sibling != NULL)
            t = t->sibling;
            t->sibling = $3;
            $$ = $1;
        }

FuncBody
    :   FuncBody FuncDecl
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
    |   FuncBody Stmt
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
    |   /* Empty */
        {$$ = NULL;}

FuncDefn
    :   TYPE ID '(' ')' '{' FuncBody '}'
        {
            $$ = newStmtNode(FuncDefnK);
            $$ -> child[0] = newExpNode(IdK);
            $$ -> child[0] -> attr.name = strdup($2);
            $$ -> child[2] = $6;
        }
    |   TYPE ID '(' VarDeclSeq ')' '{' FuncBody '}'
        {
            $$ = newStmtNode(FuncDefnK);
            $$ -> child[0] = newExpNode(IdK);
            $$ -> child[0] -> attr.name = strdup($2);
            $$ -> child[1] = $4;
            $$ -> child[2] = $7;
        }

FuncDecl
    :   TYPE ID '(' ')' ';'
        {
            $$ = newStmtNode(FuncDeclK);
            $$ -> child[0] = newExpNode(IdK);
            $$ -> child[0] -> attr.name = strdup($2);
        }
    |   TYPE ID '(' VarDeclSeq ')' ';'
        {
            $$ = newStmtNode(FuncDeclK);
            $$ -> child[0] = newExpNode(IdK);
            $$ -> child[0] -> attr.name = strdup($2);
            $$ -> child[1] = $4;
        }

MainFunc
    :   TYPE MAIN '(' ')' '{' FuncBody '}'
        {$$ = $6;}

StmtSeq
    :   StmtSeq Stmt
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
    |   /* Empty */
        {$$ = NULL;}

Stmt
    :   '{' StmtSeq '}'
        {
            $$ = newStmtNode(SeqK);
            $$ -> child[0] = $2;
        }
    |   IF '(' Exp ')' Stmt
        {
            $$ = newStmtNode(IfK);
            $$ -> child[0] = $3;
            $$ -> child[1] = $5;
        }
    |   IF '(' Exp ')' Stmt ELSE Stmt
        {
            $$ = newStmtNode(IfK);
            $$ -> child[0] = $3;
            $$ -> child[1] = $5;
            $$ -> child[2] = $7;
        }
    |   WHILE '(' Exp ')' Stmt
        {
            $$ = newStmtNode(WhileK);
            $$ -> child[0] = $3;
            $$ -> child[1] = $5;
        }
	|	FOR '(' Stmt Exp ';' ID PP ')' Stmt
		{
			$$ = $3;
			$$ -> sibling = newStmtNode(ForK);
			$$ -> sibling -> child[0] = $4;
			$$ -> sibling -> child[1] = newExpNode(OpK);
			$$ -> sibling -> child[1] -> child[0] = newExpNode(IdK);
			$$ -> sibling -> child[1] -> child[0] -> attr.name = strdup($6);
			$$ -> sibling -> child[1] -> child[0] -> type = Integer;
			$$ -> sibling -> child[1] -> attr.op = PP2TT;
			$$ -> sibling -> child[1] -> type = Integer;
			$$ -> sibling -> child[2] = $9;
		}
    |   ID '=' Exp ';'
        {
            $$ = newStmtNode(AssignK);
            $$ -> child[0] = newExpNode(IdK);
            $$ -> child[0] -> attr.name = strdup($1);
            $$ -> child[2] = $3;
        }
    |   ID '[' Exp ']' '=' Exp ';'
        {
            $$ = newStmtNode(AssignK);
            $$ -> child[0] = newExpNode(IdK);
            $$ -> child[0] -> attr.name = strdup($1);
            $$ -> child[1] = $3;
            $$ -> child[2] = $6;
        }
    |   VarDefn
        {$$ = $1;}
    |   RETURN Exp ';'
        {
            $$ = newStmtNode(RetK);
            $$ -> child[0] = $2;
        }
    |   Exp ';'
        {
            $$ = newStmtNode(SExpK);
            $$ -> child[0] = $1;
        }
	|	DO Stmt WHILE '(' Exp ')' ';'
		{
			$$ = newStmtNode(DowhileK);
			$$ -> child[0] = $2;
			$$ -> child[1] = $5;
		}

ExpSeq
    :   Exp
        {$$ = $1;}
    |   ExpSeq ',' Exp
        {
            TreeNode * t = $1;
            while (t->sibling != NULL)
            t = t->sibling;
            t->sibling = $3;
            $$ = $1;
        }

Exp
    :   Exp '+' Exp
{
    $$ = newExpNode(OpK);
    $$ -> child[0] = $1;
    $$ -> child[1] = $3;
    $$ -> attr.op = ADDTT;
    $$ -> type = Integer;
}
    |   Exp '-' Exp
{
    $$ = newExpNode(OpK);
    $$ -> child[0] = $1;
    $$ -> child[1] = $3;
    $$ -> attr.op = SUBTT;
    $$ -> type = Integer;
}
    |   Exp '*' Exp
{
    $$ = newExpNode(OpK);
    $$ -> child[0] = $1;
    $$ -> child[1] = $3;
    $$ -> attr.op = MULTT;
    $$ -> type = Integer;
}
    |   Exp '/' Exp
{
    $$ = newExpNode(OpK);
    $$ -> child[0] = $1;
    $$ -> child[1] = $3;
    $$ -> attr.op = DIVTT;
    $$ -> type = Integer;
}
    |   Exp '%' Exp
{
    $$ = newExpNode(OpK);
    $$ -> child[0] = $1;
    $$ -> child[1] = $3;
    $$ -> attr.op = MODTT;
    $$ -> type = Integer;
}
    |   Exp '>' Exp
{
    $$ = newExpNode(OpK);
    $$ -> child[0] = $1;
    $$ -> child[1] = $3;
    $$ -> attr.op = MTTT;
    $$ -> type = Boolean;
}
    |   Exp '<' Exp
{
    $$ = newExpNode(OpK);
    $$ -> child[0] = $1;
    $$ -> child[1] = $3;
    $$ -> attr.op = LTTT;
    $$ -> type = Boolean;
}
    |   Exp EQ Exp
{
    $$ = newExpNode(OpK);
    $$ -> child[0] = $1;
    $$ -> child[1] = $3;
    $$ -> attr.op = EQTT;
    $$ -> type = Boolean;
}
    |   Exp NEQ Exp
{
    $$ = newExpNode(OpK);
    $$ -> child[0] = $1;
    $$ -> child[1] = $3;
    $$ -> attr.op = NEQTT;
    $$ -> type = Boolean;
}
    |   Exp AND Exp
{
    $$ = newExpNode(OpK);
    $$ -> child[0] = $1;
    $$ -> child[1] = $3;
    $$ -> attr.op = ANDTT;
    $$ -> type = Boolean;
}
    |   Exp OR Exp
{
    $$ = newExpNode(OpK);
    $$ -> child[0] = $1;
    $$ -> child[1] = $3;
    $$ -> attr.op = ORTT;
    $$ -> type = Boolean;
    
}
    |   ID '[' Exp ']'
{
    $$ = newExpNode(IdK);
    $$ -> attr.name = strdup($1);
    $$ -> child[0] = $3;
    $$ -> type = Integer;
}
    |   NUM
{
    $$ = newExpNode(ConstK);
    $$ -> attr.val = $1;
    $$ -> type = Integer;
}
    |   ID
{
    $$ = newExpNode(IdK);
    $$ -> attr.name = strdup($1);
    $$ -> type = Integer;
}
    |   '-' Exp
{
    $$ = newExpNode(OpK);
    $$ -> child[0] = $2;
    $$ -> attr.op = MINUSTT;
    $$ -> type = Integer;
}
    |   '!' Exp
{
    $$ = newExpNode(OpK);
    $$ -> child[0] = $2;
    $$ -> attr.op = NOTTT;
    $$ -> type = Boolean;
}
	|   PP ID
{
	$$ = newExpNode(OpK);
	$$ -> child[0] = newExpNode(IdK);
	$$ -> child[0] -> attr.name = strdup($2);
	$$ -> child[0] -> type = Integer;
	$$ -> attr.op = PP1TT;
	$$ -> type = Integer;
}
	|   MM ID
{
	$$ = newExpNode(OpK);
	$$ -> child[0] = newExpNode(IdK);
	$$ -> child[0] -> attr.name = strdup($2);
	$$ -> child[0] -> type = Integer;
	$$ -> attr.op = MM1TT;
	$$ -> type = Integer;
}
	|   ID PP
{
	$$ = newExpNode(OpK);
	$$ -> child[0] = newExpNode(IdK);
	$$ -> child[0] -> attr.name = strdup($1);
	$$ -> child[0] -> type = Integer;
	$$ -> attr.op = PP2TT;
	$$ -> type = Integer;
}
	|   ID MM
{
	$$ = newExpNode(OpK);
	$$ -> child[0] = newExpNode(IdK);
	$$ -> child[0] -> attr.name = strdup($1);
	$$ -> child[0] -> type = Integer;
	$$ -> attr.op = MM2TT;
	$$ -> type = Integer;
}
    |   '(' Exp ')'
{
    $$ = newExpNode(OpK);
    $$ -> child[0] = $2;
    $$ -> attr.op = PARENTT;
    $$ -> type = $2 -> type;
}
    |   ID '(' ExpSeq ')'
{
    $$ = newExpNode(FuncK);
    $$ -> child[0] = newExpNode(IdK);
    $$ -> child[0] -> attr.name = strdup($1);
    $$ -> child[1] = $3;
    $$ -> type = Integer;
}
    |   ID '(' ')'
{
    $$ = newExpNode(FuncK);
    $$ -> child[0] = newExpNode(IdK);
    $$ -> child[0] -> attr.name = strdup($1);
    $$ -> type = Integer;
}

%%

int yyerror(char *message)
{
    fprintf(stderr, "Syntax error at line %d: %s\n",lineno,message);
    return 1;
}
