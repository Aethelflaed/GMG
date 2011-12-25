#include <fstream>

#include "Generator.hpp"
#include "Target.hpp"

using namespace Makefile;

void Generator::save()
{
	std::ofstream file("maker.gmg");

	file << "# Global configuration\n"
		 << "config set debug " << (this->config.isDebug() ? "true" : "false" ) << std::endl
		 << "config set verbose  " << (this->config.isVerbose() ? "true" : "false" )
		 << std::endl;

	file << "\n# Include paths" << std::endl;
	for (const std::string& includePath : this->config.getIncludePaths())
	{
		file << "config add include path \"" << includePath << "\"\n";
	}

	file << "\n# Library paths" << std::endl;
	for (const std::string& libraryPath : this->config.getLibraryPaths())
	{
		file << "config add library path \"" << libraryPath << "\"\n";
	}

	file << "\n# Libraries" << std::endl;
	for (const std::string& library : this->config.getLibraries())
	{
		file << "config add library \"" << library << "\"\n";
	}

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

		if (config.isIncludePathsModified())
		{
			shouldSkipLine = true;
			for (const std::string& name : config.getIncludePaths())
			{
				file << "\tconfig add include path \"" << name << "\"\n";
			}
		}
		if (config.isLibraryPathsModified())
		{
			shouldSkipLine = true;
			for (const std::string& name : config.getLibraryPaths())
			{
				file << "\tconfig add library path \"" << name << "\"\n";
			}
		}
		if (config.isLibrariesModified())
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

