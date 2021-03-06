#include <fstream>

#include "Generator.hpp"
#include "Target.hpp"
#include "Tool.hpp"

using namespace Makefile;

namespace _private
{
	struct Generator_output
	{
		static void make_tools();
	};
}

void Generator::generate()
{
	for (targets_map::value_type& target_pair : this->targets)
	{
		target_pair.second->clean();
	}
	this->save();
	_private::Generator_output::make_tools();
}

void Generator::save()
{
	std::ofstream file("maker.gmg");

	file << "# Global configuration\n";
	this->config.save(file);
	file << "\n";

	file << "# Tools configuration\n";
	file << "reset tools\n\n";
	for (const auto& tool : Tool::getTools())
	{
		tool->save(file);
		file << "\n";
	}

	file << "# Targets\n";
	for (const auto& target_pair : this->targets)
	{
		const target_type& target = target_pair.second;
		target->save(file);
		file << "\n";
	}

	file.close();
}

void _private::Generator_output::make_tools()
{
	std::ofstream stream {"Makefile.tools", std::ios_base::out | std::ios_base::trunc};

	stream << "# Makefile tools\n"
		   << "#\n"
		   << "# This file has been generated by GMG.\n"
		   << "# If you edit this file, note that it will be regenerated by\n"
		   << "# GMG if you run it again.\n"
		   << "\n"
		   << "\n"
		   << "# Include configuration\n"
		   << "include Makefile.conf\n"
		   << "\n"
		   << "#	Commands\n"
		   << "# Set the various commands used in the makefile.\n"
		   << "# No customization is supported at this time, but you can still\n"
		   << "# update the file yourself.\n"
		   << "\n"
		   << "RM := @rm -vrf\n"
		   << "COPY := @cp -vr\n"
		   << "CP := @cp -r\n"
		   << "ECHO := @echo\n"
		   << "MKDIR := mkdir -p\n"
		   << "\n"
		   << "# Specialization for ms-dos command line.\n"
		   << "ifeq ($(CONFIG_OS_TYPE), windows)\n"
		   << "	# Not yet supported. Needs testing\n"
		   << "	MKDIR := mkdir\n"
		   << "	COPY := copy\n"
		   << "	CP := copy\n"
		   << "	RM := rmdir /S /Q\n"
		   << "	SHELL := cmd\n"
		   << "endif\n\n";

	for (const auto& tool : Tool::getTools())
	{
		tool->make(stream);
	}
}

