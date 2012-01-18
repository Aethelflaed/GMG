#include "TargetTool.hpp"

#include "Util/Output.hpp"
#include "Util/Indent.hpp"

#include "GP/ObjectVisibility.h"

#include <string>

using namespace Makefile;

namespace _private
{
	struct TargetTool_output
	{
		static void save(std::ostream& stream, const TargetTool& targetTool) VISIBILITY_LOCAL;
		static void list(std::ostream& stream, const TargetTool& targetTool) VISIBILITY_LOCAL;
		static void make(std::ostream& stream, const TargetTool& targetTool) VISIBILITY_LOCAL;

		static void help_global(std::ostream& stream) VISIBILITY_LOCAL;

		static ::Makefile::Util::Indent indent VISIBILITY_LOCAL;
	};
}

inline std::string bool_value(bool value) VISIBILITY_LOCAL;
inline std::string bool_value(bool value)
{
	return (value) ? "on" : "off";
}

inline std::string bool_name(bool value) VISIBILITY_LOCAL;
inline std::string bool_name(bool value)
{
	return (value) ? "Yes" : "No";
}

::Makefile::Util::Indent _private::TargetTool_output::indent{0};

void TargetTool::output(std::ostream& stream, Util::OutputType outputType, unsigned short indentLevel) const
{
	_private::TargetTool_output::indent = indentLevel;

	switch(outputType)
	{
		case Util::OutputType::Command:
			_private::TargetTool_output::save(stream, *this);
			break;
		case Util::OutputType::List:
			_private::TargetTool_output::list(stream, *this);
			break;
		case Util::OutputType::Makefile:
			_private::TargetTool_output::make(stream, *this);
			break;
		default:
			break;
	}
}

void TargetTool::help(std::ostream& stream, int command)
{
	_private::TargetTool_output::indent = 0;

	switch(command)
	{
		default:
			_private::TargetTool_output::help_global(stream);
	}
}

void _private::TargetTool_output::save(std::ostream& stream, const TargetTool& targetTool)
{
	stream << indent << "add tool \"" << targetTool.getName() << "\"\n";
	++ indent;
	stream << indent << "set debug mode " << bool_value(targetTool.isDebugMode()) << "\n";
	stream << indent << "set verbose mode " << bool_value(targetTool.isVerboseMode()) << "\n";
	stream << indent << "set optimization mode " << bool_value(targetTool.isOptimizationMode()) << "\n";
	-- indent;
	stream << indent << "end\n";
}

void _private::TargetTool_output::list(std::ostream& stream, const TargetTool& targetTool)
{
	stream << indent << "Tool \"" << targetTool.getName() << "\"\n";
	++ indent;
	stream << indent << "Debug mode: " << bool_name(targetTool.isDebugMode()) << "\n";
	stream << indent << "Verbose mode: " << bool_name(targetTool.isVerboseMode()) << "\n";
	stream << indent << "Optimization mode: " << bool_name(targetTool.isOptimizationMode()) << "\n";
	-- indent;
}

void _private::TargetTool_output::make(std::ostream& stream, const TargetTool& targetTool)
{
}

void _private::TargetTool_output::help_global(std::ostream& stream)
{
}

