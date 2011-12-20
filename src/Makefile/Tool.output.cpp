#include "Tool.hpp"
#include "Config.hpp"

using namespace Makefile;

namespace __private
{
	struct Tool_global_output
	{
		static std::ostream& outputTool(std::ostream& stream,
				unsigned short typeId,
				const Tool::Type& type,
				bool commandStyle = false);

		static std::ostream& outputToolCommand(std::ostream& stream,
				unsigned short typeId,
				const Tool::Type& type);

		static std::ostream& outputToolFlags_command(std::ostream& stream,
				const Tool::Type& type);
		static std::ostream& outputToolFlags_list(std::ostream& stream,
				const Tool::Type& type);

		static std::ostream& outputToolFilePattern_command(std::ostream& stream,
				const Tool::Type& type);
		static std::ostream& outputToolFilePattern_list(std::ostream& stream,
				const Tool::Type& type);

		static std::ostream& outputToolPaths_command(std::ostream& stream,
				const Tool::Type& type);
		static std::ostream& outputToolPaths_list(std::ostream& stream,
				const Tool::Type& type);
	};
}

std::ostream& Tool::listTypes(std::ostream& stream, bool commandStyle)
{
	for (unsigned short typeId = 0; typeId < Tool::index; typeId++)
	{
		Tool::Type& type = Tool::types[typeId];
		__private::Tool_global_output::outputTool(stream, typeId, type, commandStyle);
	}

	return stream;
}

std::ostream& __private::Tool_global_output::outputTool(std::ostream& stream,
		unsigned short typeId,
		const Tool::Type& type,
		bool commandStyle)
{
	if (commandStyle)
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

	return stream;
}

std::ostream& __private::Tool_global_output::outputToolCommand(std::ostream& stream,
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

	return stream;
}

std::ostream& __private::Tool_global_output::outputToolFlags_command(std::ostream& stream,
		const Tool::Type& type)
{
	stream << "\treset debug flags" << std::endl;
	for (const std::string& flag : type.debugFlags)
	{
		stream << "\tadd debug flag \"" << flag << "\"" << std::endl;
	}
	stream << "\tset verbose flag \"" << type.verboseFlag << "\"" << std::endl;
	stream << "\tset optimization  flag \"" << type.optimizationFlag << "\"" << std::endl;

	return stream;
}

std::ostream& __private::Tool_global_output::outputToolFlags_list(std::ostream& stream,
		const Tool::Type& type)
{
	stream << "\tDebug flags:" << std::endl;
	for (const std::string& flag : type.debugFlags)
	{
		stream << "\t\t" << flag << std::endl;
	}
	stream << "\tVerbose flag:" << type.verboseFlag << std::endl;
	stream << "\tOptimization flag:" << type.optimizationFlag << std::endl;

	return stream;
}

std::ostream& __private::Tool_global_output::outputToolFilePattern_command(std::ostream& stream,
		const Tool::Type& type)
{
	stream << "\treset file patterns" << std::endl;
	for (const std::string& pattern : type.filePatterns)
	{
		stream << "\tadd file pattern \"" << pattern << "\"" << std::endl;
	}

	return stream;
}

std::ostream& __private::Tool_global_output::outputToolFilePattern_list(std::ostream& stream,
		const Tool::Type& type)
{
	stream << "\tMatching file patterns:" << std::endl;
	for (const std::string& pattern : type.filePatterns)
	{
		stream << "\t\t\"" << pattern << "\"" << std::endl;
	}

	return stream;
}

std::ostream& __private::Tool_global_output::outputToolPaths_command(std::ostream& stream,
		const Tool::Type& type)
{
	for (unsigned short i = 0; i < (unsigned short) ToolType::_trailing; i++)
	{
		stream << "\tset " << Config::getOSName(OperatingSystem(i)) << " path \"" << type.paths[i] << "\"" << std::endl;
	}
	return stream;
}

std::ostream& __private::Tool_global_output::outputToolPaths_list(std::ostream& stream,
		const Tool::Type& type)
{
	stream << "\tTools paths:" << std::endl;
	for (unsigned short i = 0; i < (unsigned short) ToolType::_trailing; i++)
	{
		stream << "\t\t" << Config::getOSName(OperatingSystem(i)) << ": " << type.paths[i] << std::endl;
	}
	return stream;
}

