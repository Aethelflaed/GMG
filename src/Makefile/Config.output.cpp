#include "Config.hpp"
#include "Util/Output.hpp"
#include "Util/Indent.hpp"

#include "GP/ObjectVisibility.h"

#include <ostream>

#define IS_MODIFIED(x) \
	((char*) (x) ? "" : "*")
#define BOOL_VALUE(x) \
	((char*) ((x) ? "on" : "off"))
#define BOOL_NAME(x) \
	((char*) ((x) ? "Yes" : "No"))

using namespace Makefile;

namespace __private
{
	struct Config_output
	{
		static void save(std::ostream& stream, const Config& config) VISIBILITY_LOCAL;
		static void list(std::ostream& stream, const Config& config) VISIBILITY_LOCAL;
		static void generate(std::ostream& stream, const Config& config) VISIBILITY_LOCAL;

		static ::Makefile::Util::Indent indent VISIBILITY_LOCAL;
	};
}

::Makefile::Util::Indent __private::Config_output::indent{0};

void Config::output(std::ostream& stream, Util::OutputType outputType, unsigned short indentLevel) const
{
	__private::Config_output::indent = indentLevel;

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
	stream << indent << "config\n";
	++ indent;

	bool firstOutput = true;
	if (config.isDebugModified())
	{
		firstOutput = false;
		stream << indent << "set debug " << BOOL_VALUE(config.isDebug()) << "\n";
	}

	if (config.isVerboseModified())
	{
		firstOutput = false;
		stream << indent << "set verbose " << BOOL_VALUE(config.isVerbose()) << "\n";
	}

	if (firstOutput == false)
	{
		stream << "\n";
	}
	if (config.areIncludePathsModified())
	{
		for (const std::string& name : config.getIncludePaths())
		{
			stream << indent << "add include path \"" << name << "\"\n";
		}
	}

	if (config.areLibraryPathsModified())
	{
		for (const std::string& name : config.getLibraryPaths())
		{
			stream << indent << "add library path \"" << name << "\"\n";
		}
	}

	if (config.areLibrariesModified())
	{
		for (const std::string& name : config.getLibraries())
		{
			stream << indent << "add library \"" << name << "\"\n";
		}
	}

	--indent;
	stream << indent << "end\n";
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

