%{

#include "Parser.h"
#include "grammar.hpp"
#include <string.h>
#include <ctype.h>

%}

WS				[ \t\r\n]
BOOL			(?i:(t(r(u(e)?)?)?|f(a(l(s(e)?)?)?)?))
TARGET_TYPE		(?i:app(lication)?|lib(rary)?|(unit)?test(ing)?)
WORD			[a-zA-Z_][a-zA-Z0-9_]*
NUMBER			[0-9]+(\.[0-9]*)?
FILE			[a-zA-Z0-9_./\\-]+

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
h(elp)?/{WS}					{ return T_HELP; }

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
<TARGET>type/{WS}				{ return T_TYPE; }

<TARGET>{TARGET_TYPE}/{WS}		{
		char firstChar = (char) tolower((int) yytext[0]);
		if (firstChar == 'a')		{ yylval.integer = 0; }
		else if (firstChar == 'l')	{ yylval.integer = 1; }
		else						{ yylval.integer = 2; }
		return T_TARGET_TYPE;
	}

{BOOL}/{WS}						{
		char firstChar = (char) tolower((int) yytext[0]);
		yylval.boolean = firstChar == 't';
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

