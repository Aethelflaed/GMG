#include "Parser.h"

#include <iostream>

Parser* Parser::parser = nullptr;

Parser::Parser()
	:state{INITIAL}, makefile{new Makefile::Builder{}},
	 target{nullptr}, interactive{true}
{
}

Parser& Parser::getParser()
{
	if (parser == nullptr)
	{
		parser = new Parser{};
	}
	return *parser;
}

void Parser::prompt()
{
	if (this->interactive == true)
	{
		if (this->state == TARGET)
		{
			std::cout << "target:" << this->target->getName();
		}
		std::cout << ">";
	}
}

ParserState Parser::getState() const
{
	return this->state;
}
void Parser::setState(ParserState state)
{
	this->state = state;
}

Makefile::Target& Parser::getTarget()
{
	return *this->target;
}
void Parser::setTarget(Makefile::Target* target)
{
	this->target = target;
}

Makefile::Builder& Parser::getMakefile()
{
	return *this->makefile;
}

bool Parser::isInteractive() const
{
	return this->interactive;
}
void Parser::setInteractive(bool interactive)
{
	this->interactive = interactive;
}

extern "C"
{
	ParserState Parser_getState()
	{
		return Parser::getParser().getState();
	}

	void Parser_setState(ParserState state)
	{
		Parser::getParser().setState(state);
	}

	void Parser_prompt()
	{
		Parser::getParser().prompt();
	}
}

