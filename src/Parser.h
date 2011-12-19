#ifndef PARSER_H
#define PARSER_H

/*
 * Define the enum for both C and C++
 */
typedef
	enum
	{
		INITIAL,
		TARGET
	}
	ParserState;

#ifndef __cplusplus
/*
 * Define C accessors for Parser object
 */

extern void Parser_prompt();
extern void Parser_pushState(ParserState state);
extern ParserState Parser_popState();
extern ParserState Parser_getState();

#else
/*
 * Define the Parser class, only in C++ files
 */

#include <stack>

#include "Makefile/Generator.hpp"
#include "Makefile/Target.hpp"

class Parser
{
public:
	static Parser& getParser();

	void prompt() const;
	void help(int command) const;

	void pushState(ParserState state);
	ParserState popState();
	ParserState getState() const;

	Makefile::Target& getTarget();
	void setTarget(Makefile::Target* target);

	Makefile::Generator& getMakefileGenerator();
	Makefile::Config& getCurrentConfig();

	bool isInteractive() const;
	void setInteractive(bool interactive);

private:
	Parser();
	~Parser();

	void help_state_chooser() const;
	void help_global() const;
	void help_target() const;
	void help_target_mode() const;
	void help_config() const;

	static Parser* parser;

	std::stack<ParserState> states {};
	Makefile::Generator* generator {new Makefile::Generator()};
	Makefile::Target* target {nullptr};
	bool interactive {true};
};

#endif /* __cplusplus */

#endif /* PARSER_H */

