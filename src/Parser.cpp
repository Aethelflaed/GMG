#include "Parser.h"
#include "grammar.hpp"

#include <iostream>

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
			case CONFIG:
				std::cout << "config";
				break;
			case QUOTED_STRING:
				std::cout << "dbquote";
				break;
			case TARGET:
				std::cout << "target:" << this->target->getName();
				break;
			case TARGET_TOOL:
				std::cout << "target_tool";
				break;
			case TOOL:
				std::cout << "tool";
				break;
			default:
				break;
		}
		std::cout << ">";
	}
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

