%{

#include "Parser.h"
#include "grammar.hpp"

#include "GP/C/stringCase.h"

#include <string.h>
#include <ctype.h>

%}

WS				[ \t\r\n]
BOOL			(?i:(t(rue)?|f(alse)?|on|off|y(es)?|n(o)?))
TARGET_TYPE		(?i:app(lication)?|lib(rary)?|(unit)?test(ing)?)
WORD			[a-zA-Z_][a-zA-Z0-9_]*
NUMBER			[0-9]+(\.[0-9]*)?
FILE			[a-zA-Z0-9_./\\-]+

%s TARGET
%s QUOTED_STRING
%s TOOL
%s TARGET_TOOL

%%
	{
		BEGIN Parser_getState();
	}

#.+[\r\n]						{ Parser_prompt(); }

<<EOF>>							{ return T_EXIT; }
(?i:exit)/{WS}					{ return T_EXIT; }

(?i:target(s)?)/{WS}			{ return T_TARGET; }
(?i:config)/{WS}				{ return T_CONFIG; }
(?i:tool)/{WS}					{ return T_TOOL; }

(?i:h(elp)?)/{WS}				{ return T_HELP; }
(?i:list|show)/{WS}				{ return T_LIST; }

(?i:add)/{WS}					{ return T_ADD; }
(?i:edit)/{WS}					{ return T_EDIT; }
(?i:(rm|remove))/{WS}			{ return T_RM; }
(?i:set)/{WS}					{ return T_SET; }

(?i:path)/{WS}					{ return T_PATH; }
(?i:dep(endency)?)/{WS}			{ return T_DEPENDENCY; }

(?i:library|include)/{WS}	{
		strcpy(yylval.String, yytext);
		return T_CONFIG_PARAM;
	}

(?i:debug|verbose)/{WS}	{
		strcpy(yylval.String, yytext);
		return T_BOOL_OPTION;
	}

<TARGET>(?i:end|quit)/{WS}		{
		Parser_popState();
		return T_END;
	}

<TARGET>(?i:module(s)?)/{WS}	{ return T_MODULE; }
<TARGET>(?i:version)/{WS}		{ return T_VERSION; }
<TARGET>(?i:type)/{WS}			{ return T_TYPE; }

<TARGET>{TARGET_TYPE}/{WS}		{
		char firstChar = (char) tolower((int) yytext[0]);
		if (firstChar == 'a')		{ yylval.Natural = 0; }
		else if (firstChar == 'l')	{ yylval.Natural = 1; }
		else						{ yylval.Natural = 2; }
		return T_TARGET_TYPE;
	}

{BOOL}/{WS}						{
		strtolower(yytext);
		yylval.Boolean = !(strcmp(yytext, "true") &&
			strcmp(yytext, "on") &&
			strcmp(yytext, "yes"));
		return T_BOOL_VALUE;
	}

{NUMBER}/{WS}					{
		strcpy(yylval.String, yytext);
		return T_NUMBER;
	}

<QUOTED_STRING>\"				{
		Parser_popState();
		return '"';
	}

\"								{
		Parser_pushState(QUOTED_STRING);
		return '"';
	}


<QUOTED_STRING>{WORD}			{
		strcpy(yylval.String, yytext);
		return T_WORD;
	}
<QUOTED_STRING>{FILE}			{
		strcpy(yylval.String, yytext);
		return T_FILE;
	}

[\r\n]							{ return '\n'; }
[ \t]+							{ /* ignore whitespace */ }

%%

