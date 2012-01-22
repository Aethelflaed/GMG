#include "Tool.hpp"
#include "Config.hpp"

#include "grammar.hpp"

#include "Util/Output.hpp"
#include "Util/Indent.hpp"
#include "Util/StringContainerOutput.hpp"

#include "GP/ObjectVisibility.h"

#include <ios>

using namespace Makefile;

namespace _private
{
	struct Tool_output
	{
		static void save(std::ostream& stream, const Tool& tool) VISIBILITY_LOCAL;
		static void list(std::ostream& stream, const Tool& tool) VISIBILITY_LOCAL;
		static void make(std::ostream& stream, const Tool& tool) VISIBILITY_LOCAL;

		static void help_global(std::ostream& stream) VISIBILITY_LOCAL;
		static void help_add(std::ostream& stream) VISIBILITY_LOCAL;
		static void help_reset(std::ostream& stream) VISIBILITY_LOCAL;
		static void help_remove(std::ostream& stream) VISIBILITY_LOCAL;
		static void help_set(std::ostream& stream) VISIBILITY_LOCAL;

		static ::Makefile::Util::Indent indent VISIBILITY_LOCAL;
	};
}

::Makefile::Util::Indent _private::Tool_output::indent{0};

void Tool::output(std::ostream& stream, Util::OutputType outputType, unsigned short indentLevel) const
{
	_private::Tool_output::indent = indentLevel;

	switch(outputType)
	{
		case Util::OutputType::Command:
			_private::Tool_output::save(stream, *this);
			break;
		case Util::OutputType::List:
			_private::Tool_output::list(stream, *this);
			break;
		case Util::OutputType::Makefile:
			_private::Tool_output::make(stream, *this);
			break;
		default:
			break;
	}
}

void Tool::help(std::ostream& stream, int command)
{
	_private::Tool_output::indent = 0;

	switch(command)
	{
		case T_ADD:
			_private::Tool_output::help_add(stream);
			break;
		case T_RM:
			_private::Tool_output::help_remove(stream);
			break;
		case T_RESET:
			_private::Tool_output::help_reset(stream);
			break;
		case T_SET:
			_private::Tool_output::help_set(stream);
			break;
		default:
			_private::Tool_output::help_global(stream);
	}
}

void _private::Tool_output::save(std::ostream& stream, const Tool& tool)
{
	stream << indent << "tool add \"" << tool.getName() << "\"\n";

	++ indent;

	stream << indent << "reset flags\n";
	for (auto flag : tool.getFlags())
	{
		stream << indent << "add flag \"" << flag << "\"\n";
	}

	stream << "\n" << indent << "reset debug flags\n";
	for (auto flag : tool.getDebugFlags())
	{
		stream << indent << "add debug flag \"" << flag << "\"\n";
	}

	stream << "\n" << indent << "set verbose flag \"" << tool.getVerboseFlag() << "\"\n";
	stream << indent << "set optimization  flag \"" << tool.getOptimizationFlag() << "\"\n";

	stream << "\n" << indent << "reset file patterns\n";
	for (auto pattern : tool.getFilePatterns())
	{
		stream << indent << "add file pattern \"" << pattern << "\"\n";
	}

	stream << "\n";
	for (unsigned short i = 0; i < (unsigned short) OperatingSystem::_trailing; i++)
	{
		OperatingSystem OS = OperatingSystem(i);
		stream << indent << "set " << Config::getOSName(OS) << " path \"" << tool.getPathForOS(OS) << "\"\n";
	}

	-- indent;
	stream << indent << "end\n";
}

void _private::Tool_output::list(std::ostream& stream, const Tool& tool)
{
	stream << indent << "Tool \"" << tool.getName() << "\"\n";

	++ indent;

	stream << "\n" << indent << "Flags:\n";
	++ indent;
	for (auto flag : tool.getFlags())
	{
		stream << indent << " - \"" << flag << "\"\n";
	}
	-- indent;

	stream << "\n" << indent << "Debug flags:\n";
	++ indent;
	for (auto flag : tool.getDebugFlags())
	{
		stream << indent << " - \"" << flag << "\"\n";
	}
	-- indent;

	stream << "\n" << indent << "Verbose flag:      \"" << tool.getVerboseFlag() << "\"\n";
	stream << indent <<			"Optimization flag: \"" << tool.getOptimizationFlag() << "\"\n";

	stream << "\n" << indent << "File patterns:\n";
	++ indent;
	for (auto pattern : tool.getFilePatterns())
	{
		stream << indent << " - \"" << pattern << "\"\n";
	}
	-- indent;

	stream << "\n" << indent << "Tool's path:\n";
	++ indent;
	for (unsigned short i = 0; i < (unsigned short) OperatingSystem::_trailing; i++)
	{
		OperatingSystem OS = OperatingSystem(i);
		stream << indent;

		size_t size = stream.width();
		stream.width(10);
		stream << std::left << Config::getOSName(OS);

		stream.width(size);
		stream << " -> \"" << tool.getPathForOS(OS) << "\"\n";
	}
	-- indent;

	-- indent;
}

void _private::Tool_output::make(std::ostream& stream, const Tool& tool)
{
	stream << tool.getGeneratedName() << " := " << tool.getPathForCurrentOS() << "\n";
	stream << tool.getGeneratedFlagName() << " := ";
	stream << tool.getFlags();

	/*for (const auto& flag : tool.getFlags())
	{
		stream << " " << flag;
	}*/

	stream << "\n\n";
}

void _private::Tool_output::help_global(std::ostream& stream)
{
	stream << "Manage tools\n\n";

	stream << " - `tool add \"NAME\"'               Add a new tool.\n";

	stream << " - `tool edit \"NAME\"'              Edit a tool.\n";

	stream << " - `tool rm \"NAME\"'                Remove a tool.\n";

	stream << " - `tools list'                    List all tools.\n";

	stream << " - `reset tools`                   Remove all tools.\n";
}

void _private::Tool_output::help_add(std::ostream& stream)
{
}

void _private::Tool_output::help_reset(std::ostream& stream)
{
}

void _private::Tool_output::help_remove(std::ostream& stream)
{
}

void _private::Tool_output::help_set(std::ostream& stream)
{
}

