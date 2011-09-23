%{

#include "grammar.hpp"
#include <string.h>

%}

NAME		".+"
WORD		[a-zA-Z_][a-zA-Z0-9_]+
VALUE		[a-z0-9]+
WS			[ \t\r\n]

%%

target/{WS}			{return T_TARGET;}
option/{WS}			{return T_OPTION;}

add					{return T_ADD;}
edit				{return T_EDIT;}
rm					{return T_RM;}
list				{return T_LIST;}

{NAME}				{strcpy(yylval.string, yytext); return T_NAME;}

list/{WS}			{strcpy(yylval.string, yytext); return T_LIST;}
set/{WS}			{return T_SET;}

{WORD}/{WS}			{strcpy(yylval.string, yytext); return T_NAME;}
{VALUE}/{WS}		{yylval.integer = (int) yytext[0]; return T_VALUE;}

exit				{return T_END;}

[ \t\n]+			/*ignore whitespace*/

%%

