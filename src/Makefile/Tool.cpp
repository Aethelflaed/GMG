#include "Tool.hpp"

#include <algorithm>

using namespace Makefile;

std::mutex Tool::classMutex{};
std::atomic<unsigned short> Tool::index(std::move(((unsigned short)ToolType::_trailing) - 1));

std::vector<Tool> Tool::tools {
	{
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
	},
	{
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
	},
	{
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
	},
	{
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
	},
	{
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
	}
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

	:Tool{name, flagName}
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

void Tool::removeType(const std::string& typeName)
{
	if (typeName == "")
	{
		throw NoSuchItemException();
	}

	std::lock_guard<std::mutex> lock(Tool::classMutex);
	std::vector<Type>::iterator it = Tool::types.begin();
	for (; it != Tool::types.end(); it++)
	{
		if (*it == typeName)
		{
			Tool::types.erase(it);
			return;
		}
	}

	throw NoSuchItemException();
}

unsigned short Tool::getTypeId(const std::string& typeName)
{
	if (typeName == "")
	{
		throw NoSuchItemException();
	}

	for (unsigned short i = 0; i < index; i++)
	{
		std::lock_guard<std::mutex> lock(Tool::classMutex);
		if (Tool::types[i] == typeName)
		{
			return i;
		}
	}

	throw NoSuchItemException();

	/* Prevent compiler warning */
	return 0;
}

void Tool::addFlag(const std::string& flag)
{
	if (typeId >= Tool::index)
	{
		throw Tool::TypeIdException{};
	}
	std::lock_guard<std::mutex> lock(Tool::classMutex);
	Tool::Type& type = Tool::types[typeId];
	if (type.name == "")
	{
		throw Tool::TypeIdException{};
	}
	type.flags.insert(flag);
}
void Tool::removeFlag(const std::string& flag)
{
	if (typeId >= Tool::index)
	{
		throw Tool::TypeIdException{};
	}
	std::lock_guard<std::mutex> lock(Tool::classMutex);
	Tool::Type& type = Tool::types[typeId];
	if (type.name == "")
	{
		throw Tool::TypeIdException{};
	}
	std::unordered_set<std::string>::iterator it = type.flags.find(flag);
	if (it == type.flags.end())
	{
		throw Tool::NoSuchItemException{};
	}
	type.flags.erase(it);
}
void Tool::resetFlags()
{
	if (typeId >= Tool::index)
	{
		throw Tool::TypeIdException{};
	}
	std::lock_guard<std::mutex> lock{Tool::classMutex};
	Tool::Type& type = Tool::types[typeId];
	if (type.name == "")
	{
		throw Tool::TypeIdException{};
	}
	type.flags.clear();
}
const std::unordered_set<std::string>& Tool::getFlags()
{
	if (typeId >= Tool::index)
	{
		throw Tool::TypeIdException{};
	}
	std::lock_guard<std::mutex> lock(Tool::classMutex);
	const Tool::Type& type = Tool::types[typeId];
	if (type.name == "")
	{
		throw Tool::TypeIdException{};
	}
	return type.flags;
}

void Tool::addDebugFlag(const std::string& flag)
{
	if (typeId >= Tool::index)
	{
		throw Tool::TypeIdException{};
	}
	std::lock_guard<std::mutex> lock(Tool::classMutex);
	Tool::Type& type = Tool::types[typeId];
	if (type.name == "")
	{
		throw Tool::TypeIdException{};
	}
	type.debugFlags.insert(flag);
}
void Tool::removeDebugFlag(const std::string& flag)
{
	if (typeId >= Tool::index)
	{
		throw Tool::TypeIdException{};
	}
	std::lock_guard<std::mutex> lock(Tool::classMutex);
	Tool::Type& type = Tool::types[typeId];
	if (type.name == "")
	{
		throw Tool::TypeIdException{};
	}
	std::unordered_set<std::string>::iterator it = type.debugFlags.find(flag);
	if (it == type.debugFlags.end())
	{
		throw Tool::NoSuchItemException{};
	}
	type.debugFlags.erase(it);
}
void Tool::resetDebugFlags()
{
	if (typeId >= Tool::index)
	{
		throw Tool::TypeIdException{};
	}
	std::lock_guard<std::mutex> lock{Tool::classMutex};
	Tool::Type& type = Tool::types[typeId];
	if (type.name == "")
	{
		throw Tool::TypeIdException{};
	}
	type.debugFlags.clear();
}
const std::unordered_set<std::string>& Tool::getDebugFlags()
{
	if (typeId >= Tool::index)
	{
		throw Tool::TypeIdException{};
	}
	std::lock_guard<std::mutex> lock(Tool::classMutex);
	const Tool::Type& type = Tool::types[typeId];
	if (type.name == "")
	{
		throw Tool::TypeIdException{};
	}
	return type.debugFlags;
}

void Tool::setVerboseFlag(const std::string& flag)
{
	if (typeId >= Tool::index)
	{
		throw Tool::TypeIdException{};
	}
	std::lock_guard<std::mutex> lock(Tool::classMutex);
	Tool::Type& type = Tool::types[typeId];
	if (type.name == "")
	{
		throw Tool::TypeIdException{};
	}
	type.verboseFlag = flag;
}
const std::string& Tool::getVerboseFlag()
{
	if (typeId >= Tool::index)
	{
		throw Tool::TypeIdException{};
	}
	std::lock_guard<std::mutex> lock(Tool::classMutex);
	const Tool::Type& type = Tool::types[typeId];
	if (type.name == "")
	{
		throw Tool::TypeIdException{};
	}
	return type.verboseFlag;
}

void Tool::setOptimizationFlag(const std::string& flag)
{
	if (typeId >= Tool::index)
	{
		throw Tool::TypeIdException{};
	}
	std::lock_guard<std::mutex> lock(Tool::classMutex);
	Tool::Type& type = Tool::types[typeId];
	if (type.name == "")
	{
		throw Tool::TypeIdException{};
	}
	type.optimizationFlag = flag;
}
const std::string& Tool::getOptimizationFlag()
{
	if (typeId >= Tool::index)
	{
		throw Tool::TypeIdException{};
	}
	std::lock_guard<std::mutex> lock(Tool::classMutex);
	const Tool::Type& type = Tool::types[typeId];
	if (type.name == "")
	{
		throw Tool::TypeIdException{};
	}
	return type.optimizationFlag;
}

void Tool::addFilePattern(const std::string& pattern)
{
	if (typeId >= Tool::index)
	{
		throw Tool::TypeIdException{};
	}
	std::lock_guard<std::mutex> lock(Tool::classMutex);
	Tool::Type& type = Tool::types[typeId];
	if (type.name == "")
	{
		throw Tool::TypeIdException{};
	}
	type.filePatterns.insert(pattern);
}
void Tool::removeFilePattern(const std::string& pattern)
{
	if (typeId >= Tool::index)
	{
		throw Tool::TypeIdException{};
	}
	std::lock_guard<std::mutex> lock(Tool::classMutex);
	Tool::Type& type = Tool::types[typeId];
	if (type.name == "")
	{
		throw Tool::TypeIdException{};
	}
	std::unordered_set<std::string>::iterator it = type.filePatterns.find(pattern);
	if (it == type.filePatterns.end())
	{
		throw Tool::NoSuchItemException{};
	}
	type.filePatterns.erase(it);
}
void Tool::resetFilePatterns()
{
	if (typeId >= Tool::index)
	{
		throw Tool::TypeIdException{};
	}
	std::lock_guard<std::mutex> lock{Tool::classMutex};
	Tool::Type& type = Tool::types[typeId];
	if (type.name == "")
	{
		throw Tool::TypeIdException{};
	}
	type.filePatterns.clear();
}
const std::unordered_set<std::string>& Tool::getFilePatterns()
{
	if (typeId >= Tool::index)
	{
		throw Tool::TypeIdException{};
	}
	std::lock_guard<std::mutex> lock(Tool::classMutex);
	const Tool::Type& type = Tool::types[typeId];
	if (type.name == "")
	{
		throw Tool::TypeIdException{};
	}
	return type.filePatterns;
}

void Tool::setPathForOS(OperatingSystem OS, const std::string& path)
{
	if (typeId >= Tool::index)
	{
		throw Tool::TypeIdException{};
	}
	std::lock_guard<std::mutex> lock(Tool::classMutex);
	Tool::Type& type = Tool::types[typeId];
	if (type.name == "")
	{
		throw Tool::TypeIdException{};
	}
	type.paths[(unsigned short) OS] = path;
}
const std::string& Tool::getPathForOS(OperatingSystem OS)
{
	if (typeId >= Tool::index)
	{
		throw Tool::TypeIdException{};
	}
	std::lock_guard<std::mutex> lock(Tool::classMutex);
	const Tool::Type& type = Tool::types[typeId];
	if (type.name == "")
	{
		throw Tool::TypeIdException{};
	}
	return type.paths[(unsigned short) OS];
}

