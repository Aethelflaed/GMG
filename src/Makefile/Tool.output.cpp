#include "Tool.hpp"
#include "Config.hpp"

#include "Util/Output.hpp"

#include "GP/ObjectVisibility.h"

using namespace Makefile;

namespace __private
{
	struct Tool_global_output
	{
		VISIBILITY_LOCAL static void outputTool(std::ostream& stream,
				unsigned short typeId,
				const Tool::Type& type,
				Util::OutputType outputType);

		VISIBILITY_LOCAL static void outputToolCommand(std::ostream& stream,
				unsigned short typeId,
				const Tool::Type& type);

		VISIBILITY_LOCAL static void outputToolFlags_command(std::ostream& stream,
				const Tool::Type& type);
		VISIBILITY_LOCAL static void outputToolFlags_list(std::ostream& stream,
				const Tool::Type& type);

		VISIBILITY_LOCAL static void outputToolFilePattern_command(std::ostream& stream,
				const Tool::Type& type);
		VISIBILITY_LOCAL static void outputToolFilePattern_list(std::ostream& stream,
				const Tool::Type& type);

		VISIBILITY_LOCAL static void outputToolPaths_command(std::ostream& stream,
				const Tool::Type& type);
		VISIBILITY_LOCAL static void outputToolPaths_list(std::ostream& stream,
				const Tool::Type& type);
	};

	struct Tool_output
	{
		VISIBILITY_LOCAL static void outputTool(std::ostream& stream,
				const Tool& tool,
				Util::OutputType outputType);

		VISIBILITY_LOCAL static void outputToolMode_command(std::ostream& stream,
				const Tool& tool);
		VISIBILITY_LOCAL static void outputToolMode_list(std::ostream& stream,
				const Tool& tool);
	};
}

void Tool::outputGlobal(std::ostream& stream, Util::OutputType outputType)
{
	for (unsigned short typeId = 0; typeId < Tool::index; typeId++)
	{
		Tool::Type& type = Tool::types[typeId];
		__private::Tool_global_output::outputTool(stream, typeId, type, outputType);
	}
}

void Tool::output(std::ostream& stream, Util::OutputType outputType)
{
	__private::Tool_output::outputTool(stream, *this, outputType);
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
	__private::Tool_global_output::outputToolFilePattern_list(stream, type);
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

void __private::Tool_output::outputTool(std::ostream& stream,
		const Tool& tool,
		Util::OutputType outputType)
{
	if (outputType == Util::OutputType::Command)
	{
		stream << "add tool \"" << tool.getName() << "\"" << std::endl;
		__private::Tool_output::outputToolMode_command(stream, tool);
	}
	else
	{
		stream << "Tool #" << tool.getTypeId() << " \"" << tool.getName() << "\"" << std::endl;
		__private::Tool_output::outputToolMode_list(stream, tool);
	}
}

void __private::Tool_output::outputToolMode_command(std::ostream& stream,
		const Tool& tool)
{
	stream << "\tset debug mode " << (tool.isDebugMode() ? "on" : "off") << std::endl;
	stream << "\tset verbose mode " << (tool.isVerboseMode() ? "on" : "off") << std::endl;
	stream << "\tset optimization mode " << (tool.isOptimizationMode() ? "on" : "off") << std::endl;
}

void __private::Tool_output::outputToolMode_list(std::ostream& stream,
		const Tool& tool)
{
	stream << "\tDebug mode: " << (tool.isDebugMode() ? "on" : "off") << std::endl;
	stream << "\tVerbose mode: " << (tool.isVerboseMode() ? "on" : "off") << std::endl;
	stream << "\tOptimization mode: " << (tool.isOptimizationMode() ? "on" : "off") << std::endl;
}

