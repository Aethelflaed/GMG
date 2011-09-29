#include "Config.hpp"

using namespace Makefile;

Config::Config()
	:targetOS{Config::currentOS}, includePaths{}, libraryPaths{}, libraries{}
{
}

