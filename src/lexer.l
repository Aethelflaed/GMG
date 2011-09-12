%{

#include "grammar.hpp"
#include <string.h>

%}

%s TARGET
%s TARGET_NAME
%s TARGET_MODE
%s OPTION
%s OPTION_NAME
%s OPTION_VALUE

NAME		".+"

%%

<INITIAL>target				{BEGIN TARGET; return T_TARGET;}
<INITIAL>option				{BEGIN OPTION; return T_OPTION;}

<TARGET>add					{BEGIN TARGET_NAME; return T_ADD;}
<TARGET>edit				{BEGIN TARGET_NAME; return T_EDIT;}
<TARGET>rm					{BEGIN TARGET_NAME; return T_RM;}
<TARGET>list				{BEGIN TARGET_NAME; return T_LIST;}

<TARGET_NAME>{NAME}			{strcpy(yylval.string, yytext); BEGIN TARGET_MODE; return T_NAME;}

<OPTION>list				{strcpy(yylval.string, yytext); return T_LIST;}
<OPTION>set					{BEGIN OPTION_NAME; return T_SET;}

<OPTION_NAME>{NAME}			{strcpy(yylval.string, yytext); BEGIN OPTION_VALUE; return T_NAME;}
<OPTION_VALUE>{NAME}		{strcpy(yylval.string, yytext); BEGIN OPTION; return T_VALUE;}

<INITIAL>exit				{return T_END;}
exit						{BEGIN INITIAL;}

%%

