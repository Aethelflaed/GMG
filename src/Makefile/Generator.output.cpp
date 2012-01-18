#include <fstream>

#include "Generator.hpp"
#include "Target.hpp"

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
}

