#include "Config.hpp"

using namespace Makefile;

Config::Config()
	:targetOS{Config::getCurrentOS()}, includePaths{}, libraryPaths{}, libraries{}
{
}

Config::Config(const Config& config)
	:targetOS{config.targetOS}, includePaths{config.includePaths},
	 libraryPaths{config.libraryPaths}, libraries{libraries}
{
}

auto Config::getCurrentOS() -> OperatingSystem
{
#if defined MACOSX
	return OperatingSystem::MacOSX;
#elif defined LINUX
	return OperatingSystem::Linux;
#elif defined WINDOWS
	return OperatingSystem::Windows;
#endif
}

auto Config::getTargetOS() const -> OperatingSystem
{
	return this->targetOS;
}
void Config::setTargetOS(OperatingSystem system)
{
	this->targetOS = system;
}

const std::vector<std::string>& Config::getIncludePaths() const
{
	return this->includePaths;
}
std::vector<std::string>& Config::getIncludePaths()
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
std::vector<std::string>& Config::getLibraryPaths()
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
std::vector<std::string>& Config::getLibraries()
{
	return this->libraries;
}
void Config::addLibrary(std::string library)
{
	this->libraries.push_back(library);
}

