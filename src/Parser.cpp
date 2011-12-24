#include "Parser.h"
#include "grammar.hpp"

#include <iostream>

#define HELP_SEE(name)	"Type `help " << name << "' for more details."

extern "C"
{
#ifndef YY_HEADER_EXPORT_START_CONDITIONS
#define YY_HEADER_EXPORT_START_CONDITIONS
#endif

#include "lexer.c.h"
}

Parser* Parser::parser = nullptr;

Parser::Parser()
{
	this->states.push_back(INITIAL);
}

Parser::~Parser()
{
	delete this->generator;
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
		switch(this->states.back())
		{
			case TARGET:
				std::cout << "target:" << this->target->getName();
				break;
			case TOOL:
				std::cout << "tool";
				break;
			case TARGET_TOOL:
				std::cout << "target_tool";
				break;
			case QUOTED_STRING:
				std::cout << "dbquote";
			default:
				break;
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
	switch(this->states.back())
	{
		case INITIAL:
			this->help_global();
			break;
		case TARGET:
			this->help_target_mode();
			break;
		default:
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
	std::cout << "\t`target add \"NAME\"'  add a new target." << std::endl;
	std::cout << "\t`target edit \"NAME\"' update an existing target." << std::endl;
	std::cout << "\t`target rm \"NAME\"'   remove a target." << std::endl;
	std::cout << "\t`target list'        list all targets." << std::endl;
}
void Parser::help_target_mode() const
{
	std::cout << "Configure a specific target" << std::endl;
	std::cout << "\t`set version X.Y'            Set the version X.Y of the target." << std::endl;
	std::cout << "\t`set type (app|lib|test)'    Set the type  of the target." << std::endl;
	std::cout << "\t`config'                     Set target specific configuration. " << HELP_SEE("config") << std::endl;
	std::cout << "\t`(add|rm) module \"NAME\"'     Add / remove a module, i.e. a source folder." << std::endl;
	std::cout << "\t`(add|rm) dependency \"NAME\"' Add / remove a dependency target, specified by its name." << std::endl;
}
void Parser::help_config() const
{
	std::cout << "Specify global configuration options." << std::endl;
	std::cout << "All other configuration inherit from this one, and if no parameter is changed they keep the global value." << std::endl;
	std::cout << "\t`config set debug (true|false)'             Specify global debug value" << std::endl;
	std::cout << "\t`config set verbose (true|false)'           Specify global debug value" << std::endl;
	std::cout << "\t`config add (include|library) path {FILE}'  Add the specified include / library path" << std::endl;
	std::cout << "\t`config add library {NAME}'                 Add the specified library to be linked" << std::endl;
	std::cout << "\t`config (show|list)'                        Show configuration" << std::endl;
}

#if defined DEBUG || defined DEBUG_STACK
std::string Parser::getStateName(int state)
{
	switch (state)
	{
		case INITIAL:
			return "INITIAL";
		case TARGET:
			return "TARGET";
		case TOOL:
			return "TOOL";
		case QUOTED_STRING:
			return "QUOTED_STRING";
		case TARGET_TOOL:
			return "TARGET_TOOL";
	}
	return "";
}
#endif

void Parser::pushState(int state)
{
	this->states.push_back(state);
}
int Parser::popState()
{
	int state = this->states.back();
	this->states.pop_back();
	return state;
}
int Parser::getState() const
{
	return this->states.back();
}
const std::deque<int>& Parser::getStates() const
{
	return this->states;
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

void Parser::setToolId(unsigned short toolId)
{
	this->toolId = toolId;
}
unsigned short Parser::getToolId()
{
	return this->toolId;
}

void Parser::setTool(Makefile::Tool* tool)
{
	this->tool = tool;
}
Makefile::Tool& Parser::getTool()
{
	if (this->tool == nullptr)
	{
		throw std::invalid_argument{"No current tool"};
	}
	return *this->tool;
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
	void Parser_prompt()
	{
		Parser::getParser().prompt();
	}

	void Parser_pushState(int state)
	{
		Parser::getParser().pushState(state);
	}

	int Parser_popState()
	{
		return Parser::getParser().popState();
	}

	int Parser_getState()
	{
		return Parser::getParser().getState();
	}
}

