%{

#include "Parser.h"
#include "grammar.hpp"

#include "GP/Strings/case.h"

#include <string.h>
#include <ctype.h>

%}

WS				[ \t\r\n]
BOOL			(?i:t(rue)?|f(alse)?|on|off|y(es)?|n(o)?)
TARGET_TYPE		(?i:((app(lication)?)|(lib(rary)?)|((unit)?test(ing)?)))
WORD			[a-zA-Z_][a-zA-Z0-9_]*
NUMBER			[0-9]+(\.[0-9]*)?
FILE			[a-zA-Z0-9_:./\\+=-]+
OSNAME			(?i:lin(ux)?|mac(osx)?|win(dows)?)

%s CONFIG
%s QUOTED_STRING
%s TARGET
%s TARGET_TOOL
%s TOOL

%%
	{
		BEGIN Parser_getState();
	}

#.+[\r\n]						{ Parser_prompt(); }

<<EOF>>							{ return T_EXIT; }
(?i:exit)/{WS}					{ return T_EXIT; }

(?i:target(s)?)/{WS}			{ return T_TARGET; }
(?i:config)/{WS}				{ return T_CONFIG; }
(?i:tool(s)?)/{WS}				{ return T_TOOL; }

(?i:h(elp)?)/{WS}				{ return T_HELP; }
<CONFIG>(?i:list|show)/{WS}		{ return T_CONFIG_LIST; }
(?i:list|show)/{WS}				{ return T_LIST; }

(?i:add)/{WS}					{ return T_ADD; }
(?i:edit)/{WS}					{ return T_EDIT; }
(?i:(rm|remove))/{WS}			{ return T_RM; }
(?i:set)/{WS}					{ return T_SET; }
(?i:reset)/{WS}					{ return T_RESET; }

(?i:path)/{WS}					{ return T_PATH; }

(?i:debug)/{WS}					{ return T_DEBUG; }
(?i:verbose)/{WS}				{ return T_VERBOSE; }
(?i:opti(mization)?)/{WS}		{ return T_OPTIMIZATION; }

<CONFIG>(?i:end|quit)/{WS}		{
		Parser_popState();
		return T_CONFIG_END;
	}
<TARGET>(?i:end|quit)/{WS}		{
		Parser_popState();
		return T_TARGET_END;
	}
<TARGET_TOOL>(?i:end|quit)/{WS}	{
		Parser_popState();
		return T_TARGET_TOOL_END;
	}
<TOOL>(?i:end|quit)/{WS}		{
		Parser_popState();
		return T_TOOL_END;
	}

<TOOL>{OSNAME}/{WS}				{
		strcpy(yylval.String, yytext);
		strtolower(yytext);
		return T_OS;
	}

<TOOL>(?i:flag(s)?)/{WS}		{ return T_FLAG; }
<TOOL>(?i:file)/{WS}			{ return T_FILE; }
<TOOL>(?i:pattern(s)?)/{WS}		{ return T_PATTERN; }
<TOOL>(?i:mode)/{WS}			{ return T_MODE; }
<TARGET_TOOL>(?i:mode)/{WS}		{ return T_MODE; }

<TARGET>(?i:dep(endency)?)/{WS}	{ return T_DEPENDENCY; }

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

(?i:library|include)/{WS}		{
		strcpy(yylval.String, yytext);
		strtolower(yytext);
		return T_CONFIG_PARAM;
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
		return T_FILENAME;
	}

[\r\n]							{ return '\n'; }
[ \t]+							{ /* ignore whitespace */ }

%%

