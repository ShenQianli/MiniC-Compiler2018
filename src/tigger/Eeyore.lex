NUM [1-9][0-9]*|0
FUNC f_([a-zA-Z_][a-zA-Z0-9_]*)
LABEL l([1-9][0-9]*|0)
ID [T|t|p]([1-9][0-9]*|0)


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

"var"			{fprintf(stderr, "%s", yytext);return VAR;}
"if"			{fprintf(stderr, "%s", yytext);return IF;}
"goto"			{fprintf(stderr, "%s", yytext);return GOTO;}
"param"			{fprintf(stderr, "%s", yytext);return PARAM;}
"call"			{fprintf(stderr, "%s", yytext);return CALL;}
"return"		{fprintf(stderr, "%s", yytext);return RETURN;}
"end"			{fprintf(stderr, "%s", yytext);return END;}

{FUNC}			{fprintf(stderr, "%s", yytext);yylval.str = strdup(yytext);return FUNC;}
{LABEL} 		{fprintf(stderr, "%s", yytext);yylval.str = strdup(yytext);return LABEL;}
{ID}			{fprintf(stderr, "%s", yytext);yylval.str = strdup(yytext);return ID;}
{NUM}			{fprintf(stderr, "%s", yytext);yylval.val = (int)strtod(yytext,NULL);return NUM;}
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
