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
				this->help_state_chooser();
				break;
			case T_TARGET:
				this->help_target();
				break;
			case T_CONFIG:
				this->help_config();
				break;
		}
	}
}
void Parser::help_state_chooser() const
{
	switch(this->state)
	{
		case INITIAL:
			this->help_global();
			break;
		case TARGET:
			this->help_target_mode();
			break;
	}
}
void Parser::help_global() const
{
	std::cout << "Global help" << std::endl;
	std::cout << "\t\"target\"\tConfigure targets. " << HELP_SEE("target") << std::endl;
	std::cout << "\t\"config\"\tSpecify global configuration options. " << HELP_SEE("config") << std::endl;
	std::cout << "\t\"exit\"\tExit configuration and build makefile." << std::endl;
	std::cout << std::endl << "Most commands support `show' (or `list') to show or list specific informations." << std::endl;
}
void Parser::help_target() const
{
	std::cout << "Manage targets" << std::endl;
	std::cout << "\t`target add'  Add a new target." << std::endl;
	std::cout << "\t`target edit' Update an existing target." << std::endl;
	std::cout << "\t`target rm'   Remove a target." << std::endl;
	std::cout << "\t`target list' List all targets." << std::endl;
}
void Parser::help_target_mode() const
{
}
void Parser::help_config() const
{
	std::cout << "Specify global configuration options." << std::endl;
	std::cout << "It is recommended to first tune these settings, because they are then copied to all new target." << std::endl;
	std::cout << "If you edit these settings later, the changes will only be applied to new targets." << std::endl << std::endl;
	std::cout << "\t`config set debug (true|false)'             Specify global debug value" << std::endl;
	std::cout << "\t`config set verbose (true|false)'           Specify global debug value" << std::endl;
	std::cout << "\t`config add (include|library) path {FILE}'  Add the specified include / library path" << std::endl;
	std::cout << "\t`config add library {NAME}'                 Add the specified library to be linked" << std::endl;
	std::cout << "\t`config (show|list)'                        Show configuration" << std::endl;
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

