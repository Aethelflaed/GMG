#include <iostream>
#include "grammar.hpp"

extern "C"
{
	int yyparse();
}

int main(int argc, const char** argv)
{
	yyparse();
}

