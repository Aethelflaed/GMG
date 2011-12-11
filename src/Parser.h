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

extern ParserState Parser_getState();
extern void Parser_setState(ParserState state);
extern void Parser_prompt();

#else
/*
 * Define the Parser class, only in C++ files
 */

#include "Makefile/Generator.hpp"
#include "Makefile/Target.hpp"

class Parser
{
public:
	static Parser& getParser();

	void prompt() const;
	void help(int command) const;

	ParserState getState() const;
	void setState(ParserState state);

	Makefile::Target& getTarget();
	void setTarget(Makefile::Target* target);

	Makefile::Generator& getMakefileGenerator();
	Makefile::Config& getCurrentConfig();

	bool isInteractive() const;
	void setInteractive(bool interactive);

private:
	Parser();

	static Parser* parser;

	ParserState state;
	Makefile::Generator* generator;
	Makefile::Target* target;
	bool interactive;
};

#endif /* __cplusplus */

#endif /* PARSER_H */

