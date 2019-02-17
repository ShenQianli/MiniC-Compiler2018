NUM [1-9][0-9]*|0
ID [a-zA-Z_][a-zA-Z0-9_]*

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
[' '\t]				{fprintf(stderr, "%s", yytext);}
\n				    {fprintf(stderr, "%s", yytext);lineno++;}
\/\/.*				{fprintf(stderr, "%s", yytext);}
","                 {fprintf(stderr, "%s", yytext);return *yytext;}
"++"				{fprintf(stderr, "%s", yytext);return PP;}
"--"				{fprintf(stderr, "%s", yytext);return MM;}
"=="				{fprintf(stderr, "%s", yytext);return EQ;}
"!="				{fprintf(stderr, "%s", yytext);return NEQ;}
"&&"				{fprintf(stderr, "%s", yytext);return AND;}
"||"				{fprintf(stderr, "%s", yytext);return OR;}
"+"                 {fprintf(stderr, "%s", yytext);return *yytext;}
"-"                 {fprintf(stderr, "%s", yytext);return *yytext;}
"*"                 {fprintf(stderr, "%s", yytext);return *yytext;}
"/"                 {fprintf(stderr, "%s", yytext);return *yytext;}
"="                 {fprintf(stderr, "%s", yytext);return *yytext;}
"("                 {fprintf(stderr, "%s", yytext);return *yytext;}
")"                 {fprintf(stderr, "%s", yytext);return *yytext;}
"{"                 {fprintf(stderr, "%s", yytext);return *yytext;}
"}"                 {fprintf(stderr, "%s", yytext);return *yytext;}
"["                 {fprintf(stderr, "%s", yytext);return *yytext;}
"]"                 {fprintf(stderr, "%s", yytext);return *yytext;}
";"                 {fprintf(stderr, "%s", yytext);return *yytext;}
"!"                 {fprintf(stderr, "%s", yytext);return *yytext;}
"<"                 {fprintf(stderr, "%s", yytext);return *yytext;}
">"                 {fprintf(stderr, "%s", yytext);return *yytext;}
"%"                 {fprintf(stderr, "%s", yytext);return *yytext;}

"int"				{fprintf(stderr, "%s", yytext);return TYPE;}
"if"				{fprintf(stderr, "%s", yytext);return IF;}
"else"				{fprintf(stderr, "%s", yytext);return ELSE;}
"while"				{fprintf(stderr, "%s", yytext);return WHILE;}
"main"				{fprintf(stderr, "%s", yytext);return MAIN;}
"return"			{fprintf(stderr, "%s", yytext);return RETURN;}
"do"				{fprintf(stderr, "%s", yytext);return DO;}
"for"				{fprintf(stderr, "%s", yytext);return FOR;}

{NUM}				{fprintf(stderr, "%s", yytext);yylval.vint = (int)strtod(yytext,NULL);return NUM;}
{ID} 				{fprintf(stderr, "%s", yytext);yylval.vstr = strdup(yytext);return ID;}

. 					{fprintf(stderr, "%s", yytext);strcpy(msg, "Unknown character -> ");
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
