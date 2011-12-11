%{

#include "Parser.h"
#include "grammar.hpp"
#include <string.h>
#include <ctype.h>

%}

WS				[ \t\r\n]
BOOL			(?i:(t(rue)?|f(alse)?))
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
<INITIAL>(?i:exit)/{WS}			{ return T_EXIT; }

<INITIAL>(?i:target(s)?)/{WS}	{ return T_TARGET; }
<INITIAL>(?i:config)/{WS}		{ return T_CONFIG; }

h(elp)?/{WS}					{ return T_HELP; }
show/{WS}						{ return T_SHOW; }
list/{WS}						{ return T_LIST; }

add/{WS}						{ return T_ADD; }
edit/{WS}						{ return T_EDIT; }
(rm|remove)/{WS}				{ return T_RM; }
set/{WS}						{ return T_SET; }

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

