%{

#include "parser.h"
#include "grammar.hpp"
#include <string.h>

extern void prompt();
extern ParserState state;

%}

WS			[ \t\r\n]
BOOL		0|1|[tT]([rR]([uU]([eE])?)?)?|[fF]([aA]([lL]([sS]([eE])?)?)?)?
WORD		[a-zA-Z_][a-zA-Z0-9_]*
NUMBER		[0-9]+(\.[0-9]*)?

%s TARGET

%%
	{
		/* Initialization code */
		if (state == TARGET)
		{
			BEGIN TARGET;
		}
	}

<<EOF>>					{return T_EXIT;}
<INITIAL>exit/{WS}		{return T_EXIT;}

<INITIAL>target/{WS}			{return T_TARGET;}
<INITIAL>option/{WS}			{return T_OPTION;}

<INITIAL>add					{return T_ADD;}
<INITIAL>edit				{return T_EDIT;}
<INITIAL>rm					{return T_RM;}
<INITIAL>list				{return T_LIST;}

<INITIAL>list/{WS}			{return T_LIST;}
<INITIAL>set/{WS}			{return T_SET;}

{BOOL}/{WS}			{
		char firstChar = yytext[0];
		yylval.boolean = (firstChar == 't' || firstChar == 'T' || firstChar == '1');
		return T_BOOL_VALUE;
	}

<INITIAL>debug|verbose		{
		strcpy(yylval.string, yytext);
		return T_BOOL_OPTION;
	}

\"					{return '"';}
{WORD}				{
		strcpy(yylval.string, yytext);
		return T_WORD;
	}

[\r\n]				{ prompt(); }
[ \t]+				{/* ignore whitespace */}

%%

