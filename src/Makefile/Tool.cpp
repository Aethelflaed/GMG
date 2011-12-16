#include "Tool.hpp"

#include <algorithm>

using namespace Makefile;

std::map<int, std::string> Tool::typeNames {
	{(int) ToolType::C, "C"},
	{(int) ToolType::CXX, "CXX"},
	{(int) ToolType::LEX, "LEX"},
	{(int) ToolType::YACC, "YACC"},
	{(int) ToolType::TEX, "TEX"}
};

std::map<int, std::string> Tool::typeFlagNames {
	{(int) ToolType::C, "CFLAGS"},
	{(int) ToolType::CXX, "CXXFLAGS"},
	{(int) ToolType::LEX, "LEXFLAGS"},
	{(int) ToolType::YACC, "YFLAGS"},
	{(int) ToolType::TEX, "TEXFLAGS"}
};

std::map<int, std::vector<std::string>> Tool::debugFlags {
	{(int) ToolType::C, {
			"-g3",
			"-gdwarf-2",
			"-W",
			"-Wall"
		}
	},
	{(int) ToolType::CXX, {
			"-g3",
			"-gdwarf-2",
			"-W",
			"-Wall"
		}
	},
	{(int) ToolType::LEX, {
		}
	},
	{(int) ToolType::YACC, {
			"--debug"
		}
	},
	{(int) ToolType::TEX, {
			""
		}
	}
};

std::map<int, std::string> Tool::verboseFlags {
	{(int) ToolType::C,		"-v"},
	{(int) ToolType::CXX,	"-v"},
	{(int) ToolType::LEX,	"-v"},
	{(int) ToolType::YACC,	"-v"},
	{(int) ToolType::TEX,	""}
};

std::map<int, std::string> Tool::optimizationFlags {
	{(int) ToolType::C,		"-0s"},
	{(int) ToolType::CXX,	"-0s"},
	{(int) ToolType::LEX,	""},
	{(int) ToolType::YACC,	""},
	{(int) ToolType::TEX,	""}
};

std::map<int, std::vector<std::string>> Tool::defaultFilePatterns {
	{(int) ToolType::C, {
			".c"
		}
	},
	{(int) ToolType::CXX, {
			".cpp",
			".cxx"
		}
	},
	{(int) ToolType::LEX, {
			".l",
			".lex"
		}
	},
	{(int) ToolType::YACC, {
			".y",
			".ypp"
		}
	},
	{(int) ToolType::TEX, {
			".tex"
		}
	}
};

std::map<int, std::map<OperatingSystem, std::string>> Tool::paths {
	{(int) ToolType::C,		{{OperatingSystem::Linux,	"/usr/bin/gcc"}}},
	{(int) ToolType::C,		{{OperatingSystem::MacOSX,	"/usr/bin/gcc"}}},
	{(int) ToolType::C,		{{OperatingSystem::Windows,	"C:\\"}}},

	{(int) ToolType::CXX,	{{OperatingSystem::Linux,	"/usr/bin/g++"}}},
	{(int) ToolType::CXX,	{{OperatingSystem::MacOSX,	"/usr/bin/g++"}}},
	{(int) ToolType::CXX,	{{OperatingSystem::Windows,	"C:\\"}}},

	{(int) ToolType::LEX,	{{OperatingSystem::Linux,	"/usr/bin/flex"}}},
	{(int) ToolType::LEX,	{{OperatingSystem::MacOSX,	"/usr/bin/flex"}}},
	{(int) ToolType::LEX,	{{OperatingSystem::Windows,	"C:\\"}}},

	{(int) ToolType::YACC,	{{OperatingSystem::Linux,	"/usr/bin/bison"}}},
	{(int) ToolType::YACC,	{{OperatingSystem::MacOSX,	"/usr/bin/bison"}}},
	{(int) ToolType::YACC,	{{OperatingSystem::Windows,	"C:\\"}}},

	{(int) ToolType::CXX,	{{OperatingSystem::Linux,	"/"}}},
	{(int) ToolType::CXX,	{{OperatingSystem::MacOSX,	"/"}}},
	{(int) ToolType::CXX,	{{OperatingSystem::Windows,	"C:\\"}}}
};

Tool::Tool(ToolType type)
	:type(type), typeId((int) type),
	 name(Tool::typeNames[(int) type]),
	 path(Tool::paths[(int) type][Config::getCurrentOS()]),
	 filePatterns(Tool::defaultFilePatterns[(int) type])
{
	switch (this->type)
	{
		case ToolType::YACC:
			this->flags.push_back("-d");
			break;
		default:
			break;
	}
}

Tool::Tool(int type)
	:type(ToolType::OTHER), typeId(type),
	 name(Tool::typeNames[type]),
	 path(Tool::paths[type][Config::getCurrentOS()]),
	 filePatterns(Tool::defaultFilePatterns[(int) type])
{
}

int Tool::getTypeId() const
{
	return this->typeId;
}
ToolType Tool::getType() const
{
	return this->type;
}

const std::string& Tool::getName() const
{
	return this->name;
}
void Tool::setName(const std::string& name)
{
	this->name = name;
}

const std::string& Tool::getPath() const
{
	return this->path;
}
void Tool::setPath(const std::string& path)
{
	this->path = path;
}

const std::vector<std::string>& Tool::getFlags() const
{
	return this->flags;
}
void Tool::addFlag(const std::string& flag)
{
	this->flags.push_back(flag);
}
void Tool::removeFlag(const std::string& flag) throw (std::out_of_range)
{
	auto iterator =  std::find(this->flags.begin(),
		this->flags.end(),
		flag);
	if (iterator == this->flags.end())
	{
		throw std::out_of_range("No such flag");
	}

	this->flags.erase(iterator);
}

bool Tool::isDebugMode() const
{
	return this->debugMode;
}
void Tool::setDebugMode(bool debugMode)
{
	this->debugMode = debugMode;
}

bool Tool::isVerboseMode() const
{
	return this->verboseMode;
}
void Tool::setVerboseMode(bool verboseMode)
{
	this->verboseMode = verboseMode;
}

bool Tool::isOptimizationMode() const
{
	return this->optimizationMode;
}
void Tool::setOptimizationMode(bool optimizationMode)
{
	this->optimizationMode = optimizationMode;
}

std::vector<std::string>&& Tool::getAllFlags() const
{
	std::vector<std::string> flags = this->flags;

	if (this->debugMode)
	{
		for (const std::string& flag : Tool::debugFlags[this->typeId])
		{
			flags.push_back(flag);
		}
	}

	if (this->verboseMode)
	{
		flags.push_back(Tool::verboseFlags[this->typeId]);
	}

	if (this->optimizationMode)
	{
		flags.push_back(Tool::optimizationFlags[this->typeId]);
	}

	return std::move(flags);
}

