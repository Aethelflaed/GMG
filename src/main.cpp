#include <iostream>
#include <stdio.h>

#include "grammar.hpp"
#include "Makefile/Options.hpp"

extern "C"
{
	int yyparse();

	void prompt()
	{
		std::cout << ">";
	}
}

extern FILE* yyin;

int main(int argc, const char** argv)
{
	FILE* input;
	if (argc > 1)
	{
		input = fopen(argv[1], "r");
		if (input != nullptr)
		{
			yyin = input;
		}
	}

	prompt();
	yyparse();

	if (input != nullptr)
	{
		fclose(input);
	}

	return EXIT_SUCCESS;
}

