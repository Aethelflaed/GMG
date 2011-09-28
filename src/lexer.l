%{

#include "Parser.h"
#include "grammar.hpp"
#include <string.h>

%}

WS			[ \t\r\n]
BOOL		[tT]([rR]([uU]([eE])?)?)?|[fF]([aA]([lL]([sS]([eE])?)?)?)?
WORD		[a-zA-Z_][a-zA-Z0-9_]*
NUMBER		[0-9]+(\.[0-9]*)?
FILE		[a-zA-Z0-9_./\\-]+

%s TARGET

%%
	{
		if (Parser_getState() == TARGET)
		{
			BEGIN TARGET;
		}
	}

<<EOF>>							{ return T_EXIT; }
<INITIAL>exit/{WS}				{ return T_EXIT; }

<INITIAL>target(s)?/{WS}		{ return T_TARGET; }
<INITIAL>option(s)?/{WS}		{ return T_OPTION; }

add/{WS}						{ return T_ADD; }
list/{WS}						{ return T_LIST; }
set/{WS}						{ return T_SET; }
rm/{WS}							{ return T_RM; }

<INITIAL>edit/{WS}				{ return T_EDIT; }

<INITIAL>(debug|verbose)/{WS}	{
		strcpy(yylval.string, yytext);
		return T_BOOL_OPTION;
	}

<TARGET>(end|quit)/{WS}			{
		BEGIN INITIAL;
		return T_END;
	}

<TARGET>module(s)?/{WS}			{ return T_MODULE; }
<TARGET>version/{WS}			{ return T_VERSION; }
<TARGET>show/{WS}				{ return T_SHOW; }

{BOOL}/{WS}						{
		char firstChar = yytext[0];
		yylval.boolean = (firstChar == 't' || firstChar == 'T');
		return T_BOOL_VALUE;
	}

{NUMBER}/{WS}					{
		strcpy(yylval.string, yytext);
		return T_NUMBER;
	}

\"								{ return '"'; }
{WORD}							{
		strcpy(yylval.string, yytext);
		return T_WORD;
	}
{FILE}							{
		strcpy(yylval.string, yytext);
		return T_FILE;
	}

[\r\n]							{ Parser_prompt(); }
[ \t]+							{ /* ignore whitespace */ }

%%

