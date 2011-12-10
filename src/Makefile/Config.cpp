#include "Config.hpp"

using namespace Makefile;

Config::Config()
	:targetOS(Config::getCurrentOS()), includePaths(), libraryPaths(), libraries()
{
}

Config::Config(const Config& config)
	:targetOS(config.targetOS), includePaths(config.includePaths),
	 libraryPaths(config.libraryPaths), libraries(libraries)
{
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
	return this->targetOS;
}
void Config::setTargetOS(OperatingSystem os)
{
	this->targetOS = os;
}

bool Config::isDebug() const
{
	return this->debug;
}
void Config::setDebug(bool debug)
{
	this->debug = debug;
}

bool Config::isVerbose() const
{
	return this->verbose;
}
void Config::setVerbose(bool verbose)
{
	this->verbose = verbose;
}

const std::vector<std::string>& Config::getIncludePaths() const
{
	return this->includePaths;
}
void Config::addIncludePath(std::string includePath)
{
	this->includePaths.push_back(includePath);
}

const std::vector<std::string>& Config::getLibraryPaths() const
{
	return this->libraryPaths;
}
void Config::addLibraryPath(std::string libraryPath)
{
	this->libraryPaths.push_back(libraryPath);
}

const std::vector<std::string>& Config::getLibraries() const
{
	return this->libraries;
}
void Config::addLibrary(std::string library)
{
	this->libraries.push_back(library);
}

