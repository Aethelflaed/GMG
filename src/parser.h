#ifndef PARSER_H
#define PARSER_H

typedef
	enum
	{
		INITIAL,
		TARGET
	}
	ParserState;

#ifndef __cplusplus

extern ParserState Parser_getState();
extern void Parser_setState(ParserState state);
extern void Parser_prompt();

#else

#include "Makefile/Builder.hpp"

class Parser
{
public:
	static Parser& getParser();

	void prompt();

	ParserState getState() const;
	void setState(ParserState state);

	Makefile::Target& getTarget();
	void setTarget(Makefile::Target* target);

	Makefile::Builder& getMakefile();

	bool isInteractive() const;
	void setInteractive(bool interactive);

private:
	Parser();

	static Parser* parser;

	ParserState state;
	Makefile::Builder* makefile;
	Makefile::Target* target;
	bool interactive;
};

#endif /* __cplusplus */

#endif /* PARSER_H */

