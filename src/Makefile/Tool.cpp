#include "Tool.hpp"

#include <algorithm>
#include <sstream>

using namespace Makefile;

std::unordered_set<std::shared_ptr<Tool>> Tool::tools {
	std::shared_ptr<Tool>{ new Tool{
		"C",
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
			"C:\\\\"
		}
	}},
	std::shared_ptr<Tool>{ new Tool{
		"CXX",
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
			"C:\\\\"
		}
	}},
	std::shared_ptr<Tool>{ new Tool{
		"LEX",
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
			"C:\\\\"
		}
	}},
	std::shared_ptr<Tool>{ new Tool{
		"YACC",
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
			"C:\\\\"
		}
	}},
	std::shared_ptr<Tool>{ new Tool{
		"TEX",
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
			"C:\\\\"
		}
	}}
};

Tool::Tool(const std::string& name)
	:name{name}
{
}

Tool::Tool(const std::string& name,
	std::initializer_list<std::string> flags,
	std::initializer_list<std::string> debugFlags,
	const std::string& verboseFlag,
	const std::string& optimizationFlag,
	std::initializer_list<std::string> filePatterns,
	std::initializer_list<std::string> paths)

	:name{name},
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

Tool& Tool::addTool(const std::string& name)
{
	for (auto& tool : Tool::tools)
	{
		if (tool->getName() == name)
		{
			return *tool;
		}
	}
	return **(Tool::tools.insert(std::shared_ptr<Tool>(new Tool(name))).first);
}

void Tool::removeTool(const std::string& name)
{
	for (auto tool : Tool::tools)
	{
		if (tool->getName() == name)
		{
			Tool::tools.erase(tool);
			break;
		}
	}

	throw std::invalid_argument("No such tool.");
}

Tool& Tool::getTool(const std::string& name)
{
	if (name == "")
	{
		throw std::invalid_argument{"No such tool"};
	}

	Tool* theTool {nullptr};
	for (auto tool : Tool::tools)
	{
		if (tool->getName() == name)
		{
			theTool = tool.get();
			break;
		}
	}

	if (theTool == nullptr)
	{
		throw std::invalid_argument{"No such tool"};
	}

	return *theTool;
}

const std::unordered_set<std::shared_ptr<Tool>>& Tool::getTools()
{
	return Tool::tools;
}

void Tool::resetTools()
{
	Tool::tools.clear();
}

const std::string& Tool::getName() const
{
	return this->name;
}
std::string Tool::getGeneratedName() const
{
	std::stringstream name;
	name << "TOOL_" << this->name;
	return name.str();
}

std::string Tool::getGeneratedFlagName() const
{
	std::stringstream name;
	name << "TOOL_" << this->name << "FLAGS";
	return name.str();
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
const std::string& Tool::getPathForCurrentOS() const
{
	OperatingSystem OS = Config::getCurrentOS();
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

