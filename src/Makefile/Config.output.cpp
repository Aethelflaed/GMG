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

namespace _private
{
	struct Config_output
	{
		static void save(std::ostream& stream, const Config& config) VISIBILITY_LOCAL;
		static void list(std::ostream& stream, const Config& config) VISIBILITY_LOCAL;
		static void make(std::ostream& stream, const Config& config) VISIBILITY_LOCAL;

		static void help_global(std::ostream& stream) VISIBILITY_LOCAL;

		static ::Makefile::Util::Indent indent VISIBILITY_LOCAL;
	};
}

::Makefile::Util::Indent _private::Config_output::indent{0};

void Config::output(std::ostream& stream, Util::OutputType outputType, unsigned short indentLevel) const
{
	_private::Config_output::indent = indentLevel;

	switch(outputType)
	{
		case Util::OutputType::Command:
			_private::Config_output::save(stream, *this);
			break;
		case Util::OutputType::List:
			_private::Config_output::list(stream, *this);
			break;
		case Util::OutputType::Makefile:
			_private::Config_output::make(stream, *this);
			break;
		default:
			break;
	}
}

void Config::help(std::ostream& stream, int command)
{
	_private::Config_output::indent = 0;

	switch(command)
	{
		default:
			_private::Config_output::help_global(stream);
	}
}

void _private::Config_output::save(std::ostream& stream, const Config& config)
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

	bool newLineInserted = false;
	if (config.areIncludePathsModified())
	{
		for (const std::string& name : config.getIncludePaths())
		{
			if (firstOutput == false && newLineInserted == false)
			{
				newLineInserted = true;
				stream << "\n";
			}
			stream << indent << "add include path \"" << name << "\"\n";
		}
	}

	if (config.areLibraryPathsModified())
	{
		for (const std::string& name : config.getLibraryPaths())
		{
			if (firstOutput == false && newLineInserted == false)
			{
				newLineInserted = true;
				stream << "\n";
			}
			stream << indent << "add library path \"" << name << "\"\n";
		}
	}

	if (config.areLibrariesModified())
	{
		for (const std::string& name : config.getLibraries())
		{
			if (firstOutput == false && newLineInserted == false)
			{
				newLineInserted = true;
				stream << "\n";
			}
			stream << indent << "add library \"" << name << "\"\n";
		}
	}

	--indent;
	stream << indent << "end\n";
}

void _private::Config_output::list(std::ostream& stream, const Config& config)
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

void _private::Config_output::make(std::ostream& stream, const Config& config)
{
}

void _private::Config_output::help_global(std::ostream& stream)
{
}

