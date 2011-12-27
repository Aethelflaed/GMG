#include "TargetTool.hpp"

#include "Util/Output.hpp"
#include "Util/Indent.hpp"

#include "GP/ObjectVisibility.h"

#include <string>

using namespace Makefile;

namespace __private
{
	struct TargetTool_output
	{
		static void save(std::ostream& stream, const TargetTool& targetTool) VISIBILITY_LOCAL;
		static void list(std::ostream& stream, const TargetTool& targetTool) VISIBILITY_LOCAL;

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

::Makefile::Util::Indent __private::TargetTool_output::indent{0};

void TargetTool::output(std::ostream& stream, Util::OutputType outputType, unsigned short indentLevel) const
{
	__private::TargetTool_output::indent = indentLevel;

	switch(outputType)
	{
		case Util::OutputType::Command:
			__private::TargetTool_output::save(stream, *this);
			break;
		case Util::OutputType::List:
			__private::TargetTool_output::list(stream, *this);
			break;
		case Util::OutputType::Makefile:
			break;
		default:
			break;
	}
}

void __private::TargetTool_output::save(std::ostream& stream, const TargetTool& targetTool)
{
	stream << indent << "add tool \"" << targetTool.getName() << "\"\n";
	++ indent;
	stream << indent << "set debug mode " << bool_value(targetTool.isDebugMode()) << "\n";
	stream << indent << "set verbose mode " << bool_value(targetTool.isVerboseMode()) << "\n";
	stream << indent << "set optimization mode " << bool_value(targetTool.isOptimizationMode()) << "\n";
	-- indent;
	stream << indent << "end\n";
}

void __private::TargetTool_output::list(std::ostream& stream, const TargetTool& targetTool)
{
	stream << indent << "Tool \"" << targetTool.getName() << "\"\n";
	++ indent;
	stream << indent << "Debug mode: " << bool_name(targetTool.isDebugMode()) << "\n";
	stream << indent << "Verbose mode: " << bool_name(targetTool.isVerboseMode()) << "\n";
	stream << indent << "Optimization mode: " << bool_name(targetTool.isOptimizationMode()) << "\n";
	-- indent;
}

