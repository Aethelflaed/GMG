#include "Tool.hpp"
#include "Config.hpp"

#include "Util/Output.hpp"
#include "Util/Indent.hpp"

#include "GP/ObjectVisibility.h"

#include <ios>

using namespace Makefile;

namespace __private
{
	struct Tool_output
	{
		static void save(std::ostream& stream, const Tool& tool) VISIBILITY_LOCAL;
		static void list(std::ostream& stream, const Tool& tool) VISIBILITY_LOCAL;

		static ::Makefile::Util::Indent indent VISIBILITY_LOCAL;
	};
}

::Makefile::Util::Indent __private::Tool_output::indent{0};

void Tool::output(std::ostream& stream, Util::OutputType outputType, unsigned short indentLevel) const
{
	__private::Tool_output::indent = indentLevel;

	switch(outputType)
	{
		case Util::OutputType::Command:
			__private::Tool_output::save(stream, *this);
			break;
		case Util::OutputType::List:
			__private::Tool_output::list(stream, *this);
			break;
		case Util::OutputType::Makefile:
			break;
		default:
			break;
	}
}

void __private::Tool_output::save(std::ostream& stream, const Tool& tool)
{
	stream << indent << "add tool \"" << tool.getName()
		<< "\" \"" << tool.getFlagName() << "\"\n";

	++ indent;

	stream << "\n" << indent << "reset flags\n";
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
}

void __private::Tool_output::list(std::ostream& stream, const Tool& tool)
{
	stream << indent << "Tool \"" << tool.getName() << "\"\n";

	++ indent;
	stream << indent << "Flag name : \"" << tool.getFlagName() << "\"\n";

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

