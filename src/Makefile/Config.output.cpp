#include "Config.hpp"
#include "Util/Output.hpp"

#include "GP/ObjectVisibility.h"

#include <ostream>

#define IS_MODIFIED(x) \
	((char*) (x) ? "" : "*")
#define BOOL_VALUE(x) \
	((char*) (x) ? "on" : "off")
#define BOOL_NAME(x) \
	((char*) (x) ? "Yes" : "No")

using namespace Makefile;

namespace __private
{
	struct Config_output
	{
		static void save(std::ostream& stream, const Config& config) VISIBILITY_LOCAL;
		static void list(std::ostream& stream, const Config& config) VISIBILITY_LOCAL;
		static void generate(std::ostream& stream, const Config& config) VISIBILITY_LOCAL;
	};
}

void Config::output(std::ostream& stream, Util::OutputType outputType)
{
	switch(outputType)
	{
		case Util::OutputType::Command:
			__private::Config_output::save(stream, *this);
			break;
		case Util::OutputType::List:
			__private::Config_output::list(stream, *this);
			break;
		case Util::OutputType::Makefile:
			__private::Config_output::generate(stream, *this);
			break;
		default:
			break;
	}
}

void __private::Config_output::save(std::ostream& stream, const Config& config)
{
	stream << "config\n";
	if (config.isDebugModified())
	{
		stream << "\tset debug " << BOOL_VALUE(config.isDebug()) << "\n";
	}

	if (config.isVerboseModified())
	{
		stream << "\tset verbose " << BOOL_VALUE(config.isDebug()) << "\n";
	}

	if (config.areIncludePathsModified())
	{
		for (const std::string& name : config.getIncludePaths())
		{
			stream << "\tadd include path \"" << name << "\"\n";
		}
	}

	if (config.areLibraryPathsModified())
	{
		for (const std::string& name : config.getLibraryPaths())
		{
			stream << "\tadd library path \"" << name << "\"\n";
		}
	}

	if (config.areLibrariesModified())
	{
		for (const std::string& name : config.getLibraries())
		{
			stream << "\tadd library \"" << name << "\"\n";
		}
	}
}

void __private::Config_output::list(std::ostream& stream, const Config& config)
{
	stream << "Configuration\n";
	stream << "\tFileds marked * are inherited.\n\n";
	stream << "\tDebug" << IS_MODIFIED(config.isDebugModified()) << ": " <<
		BOOL_NAME(config.isDebug()) << "\n";
	stream << "\tVerbose" << IS_MODIFIED(config.isVerboseModified()) << ": " <<
		BOOL_NAME(config.isVerbose()) << "\n";

	stream << "\tInclude paths" << IS_MODIFIED(config.areIncludePathsModified()) << ":\n";
	for (const std::string& name : config.getIncludePaths())
	{
		stream << "\t\t" << name << "\n";
	}
	stream << "\tLibrary paths" << IS_MODIFIED(config.areLibraryPathsModified()) << ":\n";
	for (const std::string& name : config.getLibraryPaths())
	{
		stream << "\t\t" << name << "\n";
	}
	stream << "\tLibraries" << IS_MODIFIED(config.areLibrariesModified()) << ":\n";
	for (const std::string& name : config.getLibraries())
	{
		stream << "\t\t" << name << "\n";
	}
}

void __private::Config_output::generate(std::ostream& stream, const Config& config)
{
}

