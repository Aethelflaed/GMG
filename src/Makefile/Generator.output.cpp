#include <fstream>

#include "Generator.hpp"
#include "Target.hpp"

using namespace Makefile;

void Generator::save()
{
	std::ofstream file("maker.gmg");

	file << "# Global configuration\n";
	this->config.save(file);

	file << "\n\n# Targets" << std::endl;
	for (auto& target_pair : this->targets)
	{
		target_type& target = target_pair.second;

		file << "target add \"" << target->getName() << "\"\n";

		const Config& config = target->getConfig();
		bool shouldSkipLine = false;
		if (config.isDebugModified())
		{
			shouldSkipLine = true;
			file << "\tconfig set debug " << (config.isDebug() ? "true" : "false" ) << "\n";
		}
		if (config.isVerboseModified())
		{
			shouldSkipLine = true;
			file << "\tconfig set verbose " << (config.isVerbose() ? "true" : "false" ) << "\n";
		}

		if (shouldSkipLine)
		{
			shouldSkipLine = false;
			file << std::endl;
		}

		if (config.areIncludePathsModified())
		{
			shouldSkipLine = true;
			for (const std::string& name : config.getIncludePaths())
			{
				file << "\tconfig add include path \"" << name << "\"\n";
			}
		}
		if (config.areLibraryPathsModified())
		{
			shouldSkipLine = true;
			for (const std::string& name : config.getLibraryPaths())
			{
				file << "\tconfig add library path \"" << name << "\"\n";
			}
		}
		if (config.areLibrariesModified())
		{
			shouldSkipLine = true;
			for (const std::string& name : config.getLibraries())
			{
				file << "\tconfig add library \"" << name << "\"\n";
			}
		}

		if (shouldSkipLine)
		{
			shouldSkipLine = false;
			file << std::endl;
		}

		for (const std::string& module : target->getModules())
		{
			shouldSkipLine = true;
			file << "\tadd module \"" << module << "\"\n";
		}

		if (shouldSkipLine)
		{
			shouldSkipLine = false;
			file << std::endl;
		}

		for (const std::weak_ptr<Target>& dependency : target->getDependencies())
		{
			if (dependency.expired() == false)
			{
				file << "\tadd dependency \"" << dependency.lock()->getName() << "\"\n";
			}
		}

		file << "\n\n";
	}

	file.close();
}

