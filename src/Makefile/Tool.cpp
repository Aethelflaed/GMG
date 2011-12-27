#include "Tool.hpp"

#include <algorithm>

using namespace Makefile;

std::unordered_set<std::shared_ptr<Tool>> Tool::tools {
	Tool::addInitializedTool(
		"C",
		"CFLAGS",
		{
		},
		{
			"-g3",
			"-gdwarf-2",
			"-W",
			"-Wall"
		},
		"-v",
		"-O3",
		{
			".c"
		},
		{
			"/usr/bin/gcc",
			"/usr/bin/gcc",
			"C:\\"
		}
	),
	Tool::addInitializedTool(
		"CXX",
		"CXXFLAGS",
		{
		},
		{
			"-g3",
			"-gdwarf-2",
			"-W",
			"-Wall"
		},
		"-v",
		"-O3",
		{
			".cpp",
			".cxx"
		},
		{
			"/usr/bin/g++",
			"/usr/bin/g++",
			"C:\\"
		}
	),
	Tool::addInitializedTool(
		"LEX",
		"LFLAGS",
		{
		},
		{
		},
		"-c",
		"",
		{
			".l",
			".lex"
		},
		{
			"/usr/bin/flex",
			"/usr/bin/flex",
			"C:\\"
		}
	),
	Tool::addInitializedTool(
		"YACC",
		"YFLAGS",
		{
			"-d"
		},
		{
			"--debug"
		},
		"-v",
		"",
		{
			".y",
			".ypp"
		},
		{
			"/usr/bin/bison",
			"/usr/bin/bison",
			"C:\\"
		}
	),
	Tool::addInitializedTool(
		"TEX",
		"TEXFLAGS",
		{
		},
		{
		},
		"",
		"",
		{
			".tex"
		},
		{
			"/",
			"/",
			"C:\\"
		}
	)
};

Tool::Tool(const std::string& name, const std::string& flagName)
	:name{name}, flagName{flagName}
{
}

Tool::Tool(const std::string& name,
	const std::string& flagName,
	std::initializer_list<std::string> flags,
	std::initializer_list<std::string> debugFlags,
	const std::string& verboseFlag,
	const std::string& optimizationFlag,
	std::initializer_list<std::string> filePatterns,
	std::initializer_list<std::string> paths)

	:name{name}, flagName{flagName},
	 flags{flags},
	 debugFlags{debugFlags}, verboseFlag{verboseFlag},
	 optimizationFlag{optimizationFlag},
	 filePatterns{filePatterns}
{
	const std::string* path = paths.begin();
	for (std::initializer_list<int>::size_type i = 0;
		 i < paths.size(); i++, path++)
	{
		this->paths[i] = *path;
	}
}

std::shared_ptr<Tool> Tool::addInitializedTool(
		const std::string& name,
		const std::string& flagName,
		std::initializer_list<std::string> flags,
		std::initializer_list<std::string> debugFlags,
		const std::string& verboseFlag,
		const std::string& optimizationFlag,
		std::initializer_list<std::string> filePatterns,
		std::initializer_list<std::string> paths
	)
{
	std::shared_ptr<Tool> tool{new Tool{name, flagName, flags, debugFlags, verboseFlag,
		optimizationFlag, filePatterns, paths}};
	return *(Tool::tools.insert(tool).first);
}

Tool& Tool::addTool(const std::string& name, const std::string& flagName)
{
	return **(Tool::tools.insert(std::shared_ptr<Tool>(new Tool(name, flagName))).first);
}

void Tool::removeTool(const std::string& name)
{
	auto it = std::find(Tool::tools.begin(), Tool::tools.end(), name);

	if (it == Tool::tools.end())
	{
		throw std::invalid_argument("No such tool.");
	}

	Tool::tools.erase(*it);
}

Tool& Tool::getTool(const std::string& name)
{
	if (name == "")
	{
		throw std::invalid_argument{"No such tool"};
	}

	auto it = std::find(Tool::tools.begin(), Tool::tools.end(), name);
	if (it == Tool::tools.end())
	{
		throw std::invalid_argument{"No such tool"};
	}

	return **it;
}

const std::string& Tool::getName() const
{
	return this->name;
}

const std::string& Tool::getFlagName() const
{
	return this->flagName;
}

void Tool::addFlag(const std::string& flag)
{
	this->flags.insert(flag);
}
void Tool::removeFlag(const std::string& flag)
{
	this->flags.erase(flag);
}
void Tool::resetFlags()
{
	this->flags.clear();
}
const std::unordered_set<std::string>& Tool::getFlags() const
{
	return this->flags;
}

void Tool::addDebugFlag(const std::string& flag)
{
	this->debugFlags.insert(flag);
}
void Tool::removeDebugFlag(const std::string& flag)
{
	this->debugFlags.erase(flag);
}
void Tool::resetDebugFlags()
{
	this->debugFlags.clear();
}
const std::unordered_set<std::string>& Tool::getDebugFlags() const
{
	return this->debugFlags;
}

void Tool::setVerboseFlag(const std::string& flag)
{
	this->verboseFlag = flag;
}
const std::string& Tool::getVerboseFlag() const
{
	return this->verboseFlag;
}

void Tool::setOptimizationFlag(const std::string& flag)
{
	this->optimizationFlag = flag;
}
const std::string& Tool::getOptimizationFlag() const
{
	return this->optimizationFlag;
}

void Tool::addFilePattern(const std::string& pattern)
{
	this->filePatterns.insert(pattern);
}
void Tool::removeFilePattern(const std::string& pattern)
{
	this->filePatterns.erase(pattern);
}
void Tool::resetFilePatterns()
{
	this->filePatterns.clear();
}
const std::unordered_set<std::string>& Tool::getFilePatterns() const
{
	return this->filePatterns;
}

void Tool::setPathForOS(OperatingSystem OS, const std::string& path)
{
	this->paths[(unsigned short) OS] = path;
}
const std::string& Tool::getPathForOS(OperatingSystem OS) const
{
	return this->paths[(unsigned short) OS];
}

std::unordered_set<std::string>&& Tool::getAllFlags(bool debugMode,
		bool verboseMode, bool optimizationMode) const
{
	std::unordered_set<std::string> flags = this->flags;

	if (debugMode)
	{
		flags.insert(this->debugFlags.begin(), this->debugFlags.end());
	}
	if (verboseMode)
	{
		flags.insert(this->verboseFlag);
	}
	if (optimizationMode)
	{
		flags.insert(this->optimizationFlag);
	}

	return std::move(flags);
}

