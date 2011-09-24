%{

#include "grammar.hpp"
#include <string.h>

extern void prompt();

%}

WORD		[a-zA-Z_][a-zA-Z0-9_]+
WS			[ \t\r\n]
BOOL		0|1|[tT]([rR]([uU]([eE])?)?)?|[fF]([aA]([lL]([sS]([eE])?)?)?)?

%%

exit/{WS}			{return T_EXIT;}

target/{WS}			{return T_TARGET;}
option/{WS}			{return T_OPTION;}

add					{return T_ADD;}
edit				{return T_EDIT;}
rm					{return T_RM;}
list				{return T_LIST;}

list/{WS}			{return T_LIST;}
set/{WS}			{return T_SET;}

{BOOL}/{WS}			{
		char firstChar = yytext[0];
		yylval.boolean = (firstChar == 't' || firstChar == 'T' || firstChar == '1');
		return T_BOOL_VALUE;
	}

debug|verbose		{
		strcpy(yylval.string, yytext);
		return T_BOOL_OPTION;
	}

[\r\n]				{ prompt(); }
[ \t]+				{/* ignore whitespace */}
.					{/* ignore others */}

%%

