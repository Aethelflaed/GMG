#include "Config.hpp"

using namespace Makefile;

Config::Config()
	:dependency(nullptr), targetOS(new OperatingSystem(Config::getCurrentOS())),
	 debug(new bool(false)), verbose(new bool(false)),
	 includePaths(new std::vector<std::string>()),
	 libraryPaths(new std::vector<std::string>()),
	 libraries(new std::vector<std::string>())
{
}

Config::Config(const Config& config, bool dependency)
	:dependency(&config), targetOS(), debug(), verbose(),
	 includePaths(), libraryPaths(), libraries()
{
	if (dependency == false)
	{
		this->dependency = nullptr;
		this->targetOS = std::shared_ptr<OperatingSystem> (new OperatingSystem(config.getTargetOS()));
		this->debug = std::shared_ptr<bool> (new bool(config.isDebug()));
		this->verbose = std::shared_ptr<bool> (new bool(config.isVerbose()));
		this->includePaths = std::shared_ptr<std::vector<std::string>> (new std::vector<std::string>(config.getIncludePaths()));
		this->libraryPaths = std::shared_ptr<std::vector<std::string>> (new std::vector<std::string>(config.getLibraryPaths()));
		this->libraries = std::shared_ptr<std::vector<std::string>> (new std::vector<std::string>(config.getLibraries()));
	}
}

OperatingSystem Config::getCurrentOS()
{
#if defined MACOSX
	return OperatingSystem::MacOSX;
#elif defined LINUX
	return OperatingSystem::Linux;
#elif defined WINDOWS
	return OperatingSystem::Windows;
#endif
}

OperatingSystem Config::getTargetOS() const
{
	if (this->targetOS.get() == nullptr)
	{
		return this->dependency->getTargetOS();
	}
	return *(this->targetOS);
}
bool Config::isTargetOSModified() const
{
	return this->targetOS.get() != nullptr;
}
void Config::setTargetOS(OperatingSystem os)
{
	this->targetOS = std::shared_ptr<OperatingSystem> (new OperatingSystem(os));
}

bool Config::isDebug() const
{
	if (this->debug.get() == nullptr)
	{
		return this->dependency->isDebug();
	}
	return *(this->debug);
}
bool Config::isDebugModified() const
{
	return this->debug.get() != nullptr;
}
void Config::setDebug(bool debug)
{
	this->debug = std::shared_ptr<bool> (new bool(debug));
}

bool Config::isVerbose() const
{
	if (this->verbose.get() == nullptr)
	{
		return this->dependency->isVerbose();
	}
	return *(this->verbose);
}
bool Config::isVerboseModified() const
{
	return this->verbose.get() != nullptr;
}
void Config::setVerbose(bool verbose)
{
	this->verbose = std::shared_ptr<bool> (new bool(verbose));
}

const std::vector<std::string>& Config::getIncludePaths() const
{
	if (this->includePaths.get() == nullptr)
	{
		return this->dependency->getIncludePaths();
	}
	return *(this->includePaths);
}
bool Config::isIncludePathsModified() const
{
	return this->includePaths.get() != nullptr;
}
void Config::addIncludePath(std::string includePath)
{
	if (this->includePaths.get() == nullptr)
	{
		this->includePaths = std::shared_ptr<std::vector<std::string>> (new std::vector<std::string>());
	}
	this->includePaths->push_back(includePath);
}

const std::vector<std::string>& Config::getLibraryPaths() const
{
	if (this->libraryPaths.get() == nullptr)
	{
		return this->dependency->getLibraryPaths();
	}
	return *(this->libraryPaths);
}
bool Config::isLibraryPathsModified() const
{
	return this->libraryPaths.get() != nullptr;
}
void Config::addLibraryPath(std::string libraryPath)
{
	if (this->libraryPaths.get() == nullptr)
	{
		this->libraryPaths = std::shared_ptr<std::vector<std::string>> (new std::vector<std::string>());
	}
	this->libraryPaths->push_back(libraryPath);
}

const std::vector<std::string>& Config::getLibraries() const
{
	if (this->libraries.get() == nullptr)
	{
		return this->dependency->getLibraries();
	}
	return *(this->libraries);
}
bool Config::isLibrariesModified() const
{
	return this->libraries.get() != nullptr;
}
void Config::addLibrary(std::string library)
{
	if (this->libraries.get() == nullptr)
	{
		this->libraries = std::shared_ptr<std::vector<std::string>> (new std::vector<std::string>());
	}
	this->libraries->push_back(library);
}

