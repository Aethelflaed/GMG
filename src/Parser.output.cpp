#include "Parser.h"
#include "grammar.hpp"

extern "C"
{
#ifndef YY_HEADER_EXPORT_START_CONDITIONS
#define YY_HEADER_EXPORT_START_CONDITIONS
#endif

#include "lexer.c.h"
}

#include <iostream>

#define HELP_SEE(name)	"\n\tType `help " << name << "' for more details."

using namespace std;

namespace _private
{
	struct Parser_output
	{
		static ostream& help_stateChooser(ostream& stream, int state, int command);
		static ostream& help_stateChooser_config(ostream& stream, int command);
		static ostream& help_stateChooser_global(ostream& stream, int command);
		static ostream& help_stateChooser_target(ostream& stream, int command);
		static ostream& help_stateChooser_targetTool(ostream& stream, int command);

		static ostream& help_config(ostream& stream);

		static ostream& help_global(ostream& stream);
		static ostream& help_global_config(ostream& stream);
		static ostream& help_global_exit(ostream& stream);
		static ostream& help_global_target(ostream& stream);

		static ostream& help_target(ostream& stream);
		static ostream& help_target_config(ostream& stream);
		static ostream& help_target_dependency(ostream& stream);
		static ostream& help_target_module(ostream& stream);
		static ostream& help_target_type(ostream& stream);
		static ostream& help_target_version(ostream& stream);

		static ostream& help_targetTool(ostream& stream);
		static ostream& help_targetTool_set(ostream& stream);
	};
}

void Parser::help(int command) const
{
	if (this->interactive == true)
	{
		_private::Parser_output::help_stateChooser(cout, this->states.back(), command);
	}
}

ostream& _private::Parser_output::help_stateChooser(ostream& stream, int state, int command)
{
	switch(state)
	{
		case INITIAL:
			_private::Parser_output::help_stateChooser_global(stream, command);
			break;
		case CONFIG:
			_private::Parser_output::help_stateChooser_config(stream, command);
			break;
		case TARGET:
			_private::Parser_output::help_stateChooser_target(stream, command);
			break;
		case TARGET_TOOL:
			_private::Parser_output::help_stateChooser_targetTool(stream, command);
			break;
		case TOOL:
			Makefile::Tool::help(stream, command);
			break;
		default:
			break;
	}

	return stream;
}

ostream& _private::Parser_output::help_stateChooser_config(ostream& stream, int command)
{
	switch(command)
	{
		default:
			_private::Parser_output::help_config(stream);
			break;
	}
	return stream;
}

ostream& _private::Parser_output::help_stateChooser_global(ostream& stream, int command)
{
	switch(command)
	{
		case T_CONFIG:
			_private::Parser_output::help_global_config(stream);
			break;
		case T_EXIT:
			_private::Parser_output::help_global_exit(stream);
			break;
		case T_TARGET:
			_private::Parser_output::help_global_target(stream);
			break;
		case T_TOOL:
			Makefile::Tool::help(stream);
			break;
		default:
			_private::Parser_output::help_global(stream);
			break;
	}

	return stream;
}

ostream& _private::Parser_output::help_stateChooser_target(ostream& stream, int command)
{
	switch(command)
	{
		case T_CONFIG:
			_private::Parser_output::help_target_config(stream);
			break;
		case T_DEPENDENCY:
			_private::Parser_output::help_target_dependency(stream);
			break;
		case T_MODULE:
			_private::Parser_output::help_target_module(stream);
			break;
		case T_TYPE:
			_private::Parser_output::help_target_type(stream);
			break;
		case T_VERSION:
			_private::Parser_output::help_target_version(stream);
			break;
		default:
			_private::Parser_output::help_target(stream);
			break;
	}

	return stream;
}

ostream& _private::Parser_output::help_stateChooser_targetTool(ostream& stream, int command)
{
	switch(command)
	{
		case T_SET:
			_private::Parser_output::help_targetTool_set(stream);
			break;
		default:
			_private::Parser_output::help_targetTool(stream);
			break;
	}

	return stream;
}

ostream& _private::Parser_output::help_global(ostream& stream)
{
	stream << "Global help" << endl << endl;

	stream << " - `config'   Specify global configuration options."
		<< HELP_SEE("config") << endl;

	stream << " - `exit'     Exit configuration and build makefile."
		<< HELP_SEE("exit") << endl;

	stream << " - `target'   Configure targets."
		<< HELP_SEE("target") << endl;

	stream << " - `tool'     Configure tools."
		<< HELP_SEE("tool") << endl;

	return stream;
}
ostream& _private::Parser_output::help_global_config(ostream& stream)
{
	stream << "Specify global configuration options." << endl;
	stream << "All other configurations inherit from this one." << endl << endl;

	stream << " - `config'   To enter configuration mode." << endl;

	return stream;
}
ostream& _private::Parser_output::help_global_exit(ostream& stream)
{
	stream << " - `exit'" << endl << endl;

	stream << "Exit GMG Makefile Generator." << endl;
	stream << "This command is available in every context." << endl << endl;

	stream << "When exiting the application using `exit', the Makefile is generated." << endl;
	stream << "Additionally the command are saved in `maker.gmg' file." << endl;

	return stream;
}
ostream& _private::Parser_output::help_global_target(ostream& stream)
{
	stream << "Manage targets" << endl << endl;

	stream << " - `target add \"NAME\"'    Add a new target." << endl;

	stream << " - `target edit \"NAME\"'   Update an existing target." << endl;

	stream << " - `target rm \"NAME\"'     Remove a target." << endl;

	stream << " - `targets list'         List all targets." << endl;

	return stream;
}

ostream& _private::Parser_output::help_config(ostream& stream)
{
	stream << "Tune configuration." << endl << endl;

	stream << " - `set debug (true|false)'             Specify debug value" << endl;

	stream << " - `set verbose (true|false)'           Specify debug value" << endl;

	stream << " - `add (include|library) path {FILE}'  Add the specified include / library path" << endl;

	stream << " - `add library {NAME}'                 Add the specified library to be linked" << endl;

	stream << " - `list'                               Show configuration" << endl;

	return stream;
}

ostream& _private::Parser_output::help_target(ostream& stream)
{
	stream << "Configure a specific target" << endl << endl;

	stream << " - `set version X.Y'             Set the version X.Y of the target."
		<< HELP_SEE("version") << endl;

	stream << " - `set type (app|lib|test)'     Set the type  of the target."
		<< HELP_SEE("type") << endl;

	stream << " - `config'                      Set target specific configuration. "
		<< HELP_SEE("config") << endl;

	stream << " - `(add|rm) module \"NAME\"'      Add / remove a module, i.e. a source folder."
		<< HELP_SEE("module") << endl;

	stream << " - `(add|rm) dependency \"NAME\"'  Add / remove a dependency target, specified by its name."
		<< HELP_SEE("dependency") << endl;

	return stream;
}
ostream& _private::Parser_output::help_target_config(ostream& stream)
{
	stream << "Target specific configuration" << endl << endl;

	stream << " - `config'   To enter configuration mode." << endl;

	return stream;
}
ostream& _private::Parser_output::help_target_dependency(ostream& stream)
{
	stream << "Manage target dependencies, i.e. other targets that are required." << endl << endl;

	stream << " - `add dependency \"NAME\"'   Add a the target named \"NAME\" as dependency." << endl;

	stream << " - `rm dependency \"NAME\"'    Remove a dependency." << endl;

	return stream;
}
ostream& _private::Parser_output::help_target_module(ostream& stream)
{
	stream << "Manage target modules, i.e. where to search for sources from src/{target_name} directory" << endl << endl;

	stream << " - `add module \"NAME\"'   Add the module NAME." << endl;

	stream << " - `rm module \"NAME\"'    Remove a module." << endl;

	return stream;
}
ostream& _private::Parser_output::help_target_type(ostream& stream)
{
	stream << "Manage target type. Currently supported values (case-insensitive) are:" << endl << endl;

	stream << " - `Application' OR `app'" << endl;

	stream << " - `Library' OR `lib'" << endl;

	stream << " - `UnitTesting' OR `test' OR `unittest' OR `testing'" << endl;

	return stream;
}
ostream& _private::Parser_output::help_target_version(ostream& stream)
{
	stream << "Set the target version." << endl << endl;

	stream << "The target version must be a positive decimal number and will later be retrievable in the target sources." << endl;
	return stream;
}

ostream& _private::Parser_output::help_targetTool(ostream& stream)
{
	return stream;
}
ostream& _private::Parser_output::help_targetTool_set(ostream& stream)
{
	return stream;
}

