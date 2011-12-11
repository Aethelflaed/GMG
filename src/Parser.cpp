#include "Parser.h"
#include "grammar.hpp"

#include <iostream>

#define HELP_SEE(name)	"Type `help " << name << "' for more details."

Parser* Parser::parser = nullptr;

Parser::Parser()
	:state(INITIAL), generator(new Makefile::Generator()),
	 target(nullptr), interactive(true)
{
}

Parser& Parser::getParser()
{
	if (parser == nullptr)
	{
		parser = new Parser();
	}
	return *parser;
}

void Parser::prompt() const
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

void Parser::help(int command) const
{
	if (this->interactive == true)
	{
		switch(command)
		{
			case 0:
				std::cout << "Global help" << std::endl;
				std::cout << "\t\"target\"\tConfigure targets. " << HELP_SEE("target") << std::endl;
				std::cout << "\t\"config\"\tSpecify global configuration options. " << HELP_SEE("config") << std::endl;
				std::cout << "\t\"exit\"\tExit configuration and build makefile." << std::endl;
				break;
			case T_TARGET:
				break;
			case T_CONFIG:
				break;
		}
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

Makefile::Generator& Parser::getMakefileGenerator()
{
	return *this->generator;
}

Makefile::Config& Parser::getCurrentConfig()
{
	if (this->target != nullptr)
	{
		return this->target->getConfig();
	}
	return this->generator->getConfig();
}

bool Parser::isInteractive() const
{
	return this->interactive;
}
void Parser::setInteractive(bool interactive)
{
	this->interactive = interactive;
}

/*
 * Implement the C accessors
 */
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

