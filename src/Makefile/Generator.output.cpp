#include <fstream>

#include "Generator.hpp"
#include "Target.hpp"

using namespace Makefile;

void Generator::save()
{
	std::ofstream file("maker.gmg");

	file << "# Global configuration\n";
	this->config.save(file);
	file << "\n";

	file << "# Tools configuration\n";
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

