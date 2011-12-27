#include "Tool.hpp"
#include "Config.hpp"

#include "Util/Output.hpp"
#include "Util/Indent.hpp"

#include "GP/ObjectVisibility.h"

using namespace Makefile;

namespace __private
{
	struct Tool_global_output
	{
		static void outputTool(std::ostream& stream,
				unsigned short typeId,
				const Tool::Type& type,
				Util::OutputType outputType) VISIBILITY_LOCAL;

		static void outputToolCommand(std::ostream& stream,
				unsigned short typeId,
				const Tool::Type& type) VISIBILITY_LOCAL;

		static void outputToolFlags_command(std::ostream& stream,
				const Tool::Type& type) VISIBILITY_LOCAL;
		static void outputToolFlags_list(std::ostream& stream,
				const Tool::Type& type) VISIBILITY_LOCAL;

		static void outputToolFilePattern_command(std::ostream& stream,
				const Tool::Type& type) VISIBILITY_LOCAL;
		static void outputToolFilePattern_list(std::ostream& stream,
				const Tool::Type& type) VISIBILITY_LOCAL;

		static void outputToolPaths_command(std::ostream& stream,
				const Tool::Type& type) VISIBILITY_LOCAL;
		static void outputToolPaths_list(std::ostream& stream,
				const Tool::Type& type) VISIBILITY_LOCAL;

		static ::Makefile::Util::Indent indent VISIBILITY_LOCAL;
	};
}

::Makefile::Util::Indent __private::Tool_global_output::indent{0};

void Tool::outputGlobal(std::ostream& stream, Util::OutputType outputType, unsigned short indentLevel)
{
	__private::Tool_global_output::indent = indentLevel;

	for (unsigned short typeId = 0; typeId < Tool::index; typeId++)
	{
		Tool::Type& type = Tool::types[typeId];
		__private::Tool_global_output::outputTool(stream, typeId, type, outputType);
	}
}

void __private::Tool_global_output::outputTool(std::ostream& stream,
		unsigned short typeId,
		const Tool::Type& type,
		Util::OutputType outputType)
{
	if (outputType == Util::OutputType::Command)
	{
		__private::Tool_global_output::outputToolCommand(stream, typeId, type);
	}
	else
	{
		stream << "Tool #" << typeId << " \"" << type.name << "\"" << std::endl;
		stream << "\tFlag name: \"" << type.flagName << "\"" << std::endl;
		__private::Tool_global_output::outputToolFlags_list(stream, type);
		__private::Tool_global_output::outputToolFilePattern_list(stream, type);
		__private::Tool_global_output::outputToolPaths_list(stream, type);
	}

}

void __private::Tool_global_output::outputToolCommand(std::ostream& stream,
		unsigned short typeId,
		const Tool::Type& type)
{
	if (typeId < (unsigned short) ToolType::_trailing)
	{
		stream << "tool edit \"" << type.name << "\"" << std::endl;
		stream << "\tset flag name \"" << type.flagName << "\"" << std::endl;
	}
	else
	{
		stream << "tool add \"" << type.name << "\" \"" << type.flagName << "\"" << std::endl;
	}

	__private::Tool_global_output::outputToolFlags_command(stream, type);
	__private::Tool_global_output::outputToolFilePattern_command(stream, type);
	__private::Tool_global_output::outputToolPaths_command(stream, type);
}

void __private::Tool_global_output::outputToolFlags_command(std::ostream& stream,
		const Tool::Type& type)
{
	stream << "\treset flags" << std::endl;
	for (const std::string& flag : type.flags)
	{
		stream << "\tadd flag \"" << flag << "\"" << std::endl;
	}
	stream << "\treset debug flags" << std::endl;
	for (const std::string& flag : type.debugFlags)
	{
		stream << "\tadd debug flag \"" << flag << "\"" << std::endl;
	}
	stream << "\tset verbose flag \"" << type.verboseFlag << "\"" << std::endl;
	stream << "\tset optimization  flag \"" << type.optimizationFlag << "\"" << std::endl;

}

void __private::Tool_global_output::outputToolFlags_list(std::ostream& stream,
		const Tool::Type& type)
{
	stream << "\tFlags:" << std::endl;
	for (const std::string& flag : type.flags)
	{
		stream << "\t\t" << flag << std::endl;
	}
	stream << "\tDebug flags:" << std::endl;
	for (const std::string& flag : type.debugFlags)
	{
		stream << "\t\t" << flag << std::endl;
	}
	stream << "\tVerbose flag:" << type.verboseFlag << std::endl;
	stream << "\tOptimization flag:" << type.optimizationFlag << std::endl;

}

void __private::Tool_global_output::outputToolFilePattern_command(std::ostream& stream,
		const Tool::Type& type)
{
	stream << "\treset file patterns" << std::endl;
	for (const std::string& pattern : type.filePatterns)
	{
		stream << "\tadd file pattern \"" << pattern << "\"" << std::endl;
	}

}

void __private::Tool_global_output::outputToolFilePattern_list(std::ostream& stream,
		const Tool::Type& type)
{
	stream << "\tMatching file patterns:" << std::endl;
	for (const std::string& pattern : type.filePatterns)
	{
		stream << "\t\t\"" << pattern << "\"" << std::endl;
	}

}

void __private::Tool_global_output::outputToolPaths_command(std::ostream& stream,
		const Tool::Type& type)
{
	for (unsigned short i = 0; i < (unsigned short) ToolType::_trailing; i++)
	{
		stream << "\tset " << Config::getOSName(OperatingSystem(i)) << " path \"" << type.paths[i] << "\"" << std::endl;
	}
}

void __private::Tool_global_output::outputToolPaths_list(std::ostream& stream,
		const Tool::Type& type)
{
	stream << "\tTools paths:" << std::endl;
	for (unsigned short i = 0; i < (unsigned short) ToolType::_trailing; i++)
	{
		stream << "\t\t" << Config::getOSName(OperatingSystem(i)) << ": " << type.paths[i] << std::endl;
	}
}

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
	stream << indent << "add tool \"" << tool.getName() << "\"\n";
	++ indent;
	stream << indent << "set debug mode " << (tool.isDebugMode() ? "on" : "off") << "\n";
	stream << indent << "set verbose mode " << (tool.isVerboseMode() ? "on" : "off") << "\n";
	stream << indent << "set optimization mode " << (tool.isOptimizationMode() ? "on" : "off") << "\n";
	-- indent;
}

void __private::Tool_output::list(std::ostream& stream, const Tool& tool)
{
	stream << indent << "Tool #" << tool.getTypeId() << " \"" << tool.getName() << "\"\n";
	++ indent;
	stream << indent << "Debug mode: " << (tool.isDebugMode() ? "on" : "off") << "\n";
	stream << indent << "Verbose mode: " << (tool.isVerboseMode() ? "on" : "off") << "\n";
	stream << indent << "Optimization mode: " << (tool.isOptimizationMode() ? "on" : "off") << "\n";
	-- indent;
}

