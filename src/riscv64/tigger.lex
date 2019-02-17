NUM -?[1-9][0-9]*|0
FUNC f_([a-zA-Z_][a-zA-Z0-9_]*)
LABEL l([1-9][0-9]*|0)
REG x0|s0|s1|s2|s3|s4|s5|s6|s7|s8|s9|s10|s11|t0|t1|t2|t3|t4|t5|t6|a0|a1|a2|a3|a4|a5|a6|a7
VAR v([1-9][0-9]*|0)

%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "globals.h"
#include "y.tab.h"

void lexicalError(char * message);
extern int yyerror(const char *);
char msg[100]="";

%}

%option yylineno

%%
[' '\t]			{fprintf(stderr, "%s", yytext);}
\n			    {fprintf(stderr, "%s", yytext);lineno++;}
\/\/.*			{fprintf(stderr, "%s", yytext);}
"=="			{fprintf(stderr, "%s", yytext);return EQ;}
"!="			{fprintf(stderr, "%s", yytext);return NEQ;}
"&&"			{fprintf(stderr, "%s", yytext);return AND;}
"||"			{fprintf(stderr, "%s", yytext);return OR;}
"+"             {fprintf(stderr, "%s", yytext);return *yytext;}
"-"             {fprintf(stderr, "%s", yytext);return *yytext;}
"*"             {fprintf(stderr, "%s", yytext);return *yytext;}
"/"             {fprintf(stderr, "%s", yytext);return *yytext;}
"="             {fprintf(stderr, "%s", yytext);return *yytext;}
"["             {fprintf(stderr, "%s", yytext);return *yytext;}
"]"             {fprintf(stderr, "%s", yytext);return *yytext;}
":"             {fprintf(stderr, "%s", yytext);return *yytext;}
"!"             {fprintf(stderr, "%s", yytext);return *yytext;}
"<"             {fprintf(stderr, "%s", yytext);return *yytext;}
">"             {fprintf(stderr, "%s", yytext);return *yytext;}
"%"             {fprintf(stderr, "%s", yytext);return *yytext;}

"if"			{fprintf(stderr, "%s", yytext);return IF;}
"load"			{fprintf(stderr, "%s", yytext);return LOAD;}
"loadaddr"		{fprintf(stderr, "%s", yytext);return LOADADDR;}
"store"			{fprintf(stderr, "%s", yytext);return STORE;}
"malloc"		{fprintf(stderr, "%s", yytext);return MALLOC;}
"goto"			{fprintf(stderr, "%s", yytext);return GOTO;}
"call"			{fprintf(stderr, "%s", yytext);return CALL;}
"return"		{fprintf(stderr, "%s", yytext);return RETURN;}
"end"			{fprintf(stderr, "%s", yytext);return END;}

{FUNC}			{fprintf(stderr, "%s", yytext);yylval.str = strdup(yytext);return FUNC;}
{LABEL} 		{fprintf(stderr, "%s", yytext);yylval.str = strdup(yytext);return LABEL;}
{REG}			{fprintf(stderr, "%s", yytext);yylval.str = strdup(yytext);return REG;}
{NUM}			{fprintf(stderr, "%s", yytext);yylval.val = (int)strtod(yytext,NULL);return NUM;}
{VAR}			{fprintf(stderr, "%s", yytext);yylval.str = strdup(yytext);return VAR;}
. 				{fprintf(stderr, "%s", yytext);strcpy(msg, "Unknown character -> ");
				strcat(msg, yytext);
				lexicalError(msg);
				exit(1);}
%%

void lexicalError(char * message){
    fprintf(stderr,"lexical error at line %d: %s\n", yylineno, message);
    exit(1);
}

int yywrap()
{
    return 1;
}
