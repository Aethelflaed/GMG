#include "Target.hpp"
#include "Util/Output.hpp"
#include "Util/Indent.hpp"

#include "GP/ObjectVisibility.h"

#include <ostream>

using namespace Makefile;

namespace __private
{
	struct Target_output
	{
		static void save(std::ostream& stream, const Target& target) VISIBILITY_LOCAL;
		static void list(std::ostream& stream, const Target& target) VISIBILITY_LOCAL;
		static void generate(std::ostream& stream, const Target& target) VISIBILITY_LOCAL;

		static ::Makefile::Util::Indent indent VISIBILITY_LOCAL;
	};
}

::Makefile::Util::Indent __private::Target_output::indent{0};

void Target::output(std::ostream& stream, Util::OutputType outputType, unsigned short indentLevel) const
{
	__private::Target_output::indent = indentLevel;
	switch(outputType)
	{
		case Util::OutputType::Command:
			__private::Target_output::save(stream, *this);
			break;
		case Util::OutputType::List:
			__private::Target_output::list(stream, *this);
			break;
		case Util::OutputType::Makefile:
			__private::Target_output::generate(stream, *this);
			break;
		default:
			break;
	}
}

void __private::Target_output::save(std::ostream& stream, const Target& target)
{
	std::string type;
	switch(target.getType())
	{
		case TargetType::Application:
			type = "Application";
			break;
		case TargetType::Library:
			type = "Library";
			break;
		case TargetType::UnitTest:
			type = "UnitTesting";
			break;
		default:
			type = "Unknow";
			break;
	}

	stream << indent << "target add \"" << target.getName() << "\"\n";
	++ indent;
	stream << indent << "set version " << target.getVersion() << "\n";
	stream << indent << "set type " << type << "\n";

	stream << "\n" << indent << "# Modules\n";
	for (auto module : target.getModules())
	{
		stream << indent << "add module \"" << module << "\"\n";
	}

	stream << "\n" << indent << "# Dependencies\n";
	for (auto dep : target.getDependencies())
	{
		if (dep.expired() == false)
		{
			stream << indent << "add dependency \"" << dep.lock()->getName() << "\"\n";
		}
	}

	stream << "\n" << indent << "# Tools\n";
	for (auto tool : target.getTools())
	{
		tool->output(stream, Util::OutputType::Command, indent);
	}

	stream << "\n" << indent << "# Specific Configuration\n";
	target.getConfig().output(stream, Util::OutputType::Command, indent);

	-- indent;
	stream << indent << "end\n";
}

void __private::Target_output::list(std::ostream& stream, const Target& target)
{
	std::string type;
	switch(target.getType())
	{
		case TargetType::Application:
			type = "Application";
			break;
		case TargetType::Library:
			type = "Library";
			break;
		case TargetType::UnitTest:
			type = "UnitTest";
			break;
		default:
			type = "Unknow";
			break;
	}

	stream << "Target: \"" << target.getName() << "\"\n"
		<< "\tVersion: \"" << target.getVersion() << "\"\n"
		<< "\tType: \"" << type << "\"\n"
		<< "\tModules:\n";

	auto modules = target.getModules();
	for (const std::string& module : modules)
	{
		stream << "\t  " << module << "\n";
	}
	stream << "\tDependencies:\n";
	for (auto dep : target.getDependencies())
	{
		if (dep.expired())
		{
			stream << "\t  <<expired target>>\n";
		}
		else
		{
			stream << "\t  " << dep.lock()->getName() << "\n";
		}
	}

	stream << "Target's ";
	target.getConfig().list(stream);
}

void __private::Target_output::generate(std::ostream& stream, const Target& target)
{
}

