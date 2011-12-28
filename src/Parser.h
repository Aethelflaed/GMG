#ifndef PARSER_H
#define PARSER_H

#include "config.h"

#ifndef __cplusplus
/*
 * Define C accessors for Parser object
 */

extern void Parser_prompt();
extern void Parser_pushState(int state);
extern int Parser_popState();
extern int Parser_getState();

#else
/*
 * Define the Parser class, only in C++ files
 */

#include <deque>

#include "Makefile/Generator.hpp"
#include "Makefile/Target.hpp"
#include "Makefile/TargetTool.hpp"
#include "Makefile/Tool.hpp"

class Parser
{
public:
	static Parser& getParser();

	void prompt() const;
	void help(int command) const;

#if defined DEBUG || defined DEBUG_STACK
	static std::string getStateName(int state);
#endif

	void pushState(int state);
	int popState();
	int getState() const;
	const std::deque<int>& getStates() const;

	Makefile::Target& getTarget();
	void setTarget(Makefile::Target* target);

	Makefile::Generator& getMakefileGenerator();
	Makefile::Config& getCurrentConfig();

	void setTargetTool(Makefile::TargetTool* tool);
	Makefile::TargetTool& getTargetTool();

	void setTool(Makefile::Tool* tool);
	Makefile::Tool& getTool();

	bool isInteractive() const;
	void setInteractive(bool interactive);

private:
	Parser();
	~Parser();

	static Parser* parser;

	std::deque<int> states {};
	Makefile::Generator* generator {new Makefile::Generator()};
	Makefile::Target* target {nullptr};
	Makefile::TargetTool* targetTool {nullptr};
	Makefile::Tool* tool {nullptr};
	bool interactive {true};
};

#endif /* __cplusplus */

#endif /* PARSER_H */

