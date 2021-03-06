#include <iostream>
#include <stdio.h>

#include "Parser.h"
#include "grammar.hpp"
#include "Makefile/Generator.hpp"

extern "C"
{
	int yyparse();

	extern FILE* yyin;
}

int main(int argc, const char** argv)
{
	FILE* input = nullptr;
	if (argc > 1)
	{
		input = fopen(argv[1], "r");
		if (input != nullptr)
		{
			yyin = input;
			Parser::getParser().setInteractive(false);
		}
	}

	Parser::getParser().prompt();
	yyparse();

	if (input != nullptr)
	{
		fclose(input);
	}

	return 0;
}

