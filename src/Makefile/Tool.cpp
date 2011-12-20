#include "Tool.hpp"

#include <algorithm>

using namespace Makefile;

std::mutex Tool::classMutex{};
std::atomic<unsigned short> Tool::index(std::move(((unsigned short)ToolType::_trailing) - 1));

std::vector<Tool::Type> Tool::types {
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

Tool::Type::Type(const std::string& name, const std::string& flagName)
	:name{name}, flagName{flagName}
{
}

Tool::Type::Type(const std::string& name,
	const std::string& flagName,
	std::initializer_list<std::string> flags,
	std::initializer_list<std::string> debugFlags,
	const std::string& verboseFlag,
	const std::string& optimizationFlag,
	std::initializer_list<std::string> filePatterns,
	std::initializer_list<std::string> paths)

	:name{name}, flagName{flagName}, flags{flags},
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

unsigned short Tool::addType(const std::string& typeName,
		const std::string& typeFlagName)
{
	unsigned short typeId;

	Tool::Type type {typeName, typeFlagName};

	{
		std::lock_guard<std::mutex> lock(Tool::classMutex);
		typeId = Tool::index++;
		types.push_back(type);
	}

	return typeId;
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

void Tool::addTypeFlag(unsigned short typeId, const std::string& flag)
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
void Tool::removeTypeFlag(unsigned short typeId, const std::string& flag)
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
const std::unordered_set<std::string>& Tool::getTypeFlags(unsigned short typeId)
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

void Tool::addTypeDebugFlag(unsigned short typeId, const std::string& flag)
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
void Tool::removeTypeDebugFlag(unsigned short typeId, const std::string& flag)
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
const std::unordered_set<std::string>& Tool::getTypeDebugFlags(unsigned short typeId)
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

void Tool::setTypeVerboseFlag(unsigned short typeId, const std::string& flag)
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
const std::string& Tool::getTypeVerboseFlag(unsigned short typeId)
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

void Tool::setTypeOptimizationFlag(unsigned short typeId, const std::string& flag)
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
const std::string& Tool::getTypeOptimizationFlag(unsigned short typeId)
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

void Tool::addTypeFilePattern(unsigned short typeId, const std::string& pattern)
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
void Tool::removeTypeFilePattern(unsigned short typeId, const std::string& pattern)
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
const std::unordered_set<std::string>& Tool::getTypeFilePatterns(unsigned short typeId)
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

void Tool::setTypePathForOS(unsigned short typeId, OperatingSystem OS, const std::string& path)
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
const std::string& Tool::getTypePathForOS(unsigned short typeId, OperatingSystem OS)
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

Tool::Tool(const std::string& name)
	:Tool(Tool::getTypeId(name))
{
}

Tool::Tool(ToolType type)
	:Tool((unsigned short)type)
{
}

Tool::Tool(unsigned short type)
	:type(ToolType::_trailing), typeId(type)
{
	if (typeId >= Tool::index)
	{
		throw Tool::TypeIdException{};
	}
	std::lock_guard<std::mutex> lock(Tool::classMutex);
	const Tool::Type& baseType = Tool::types[(unsigned short) type];
	if (baseType.name == "")
	{
		throw Tool::TypeIdException{};
	}
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
	std::lock_guard<std::mutex> lock{Tool::classMutex};
	const Tool::Type& baseType = Tool::types[(unsigned short) type];
	if (baseType.name == "")
	{
		throw Tool::TypeIdException{};
	}
	return baseType.name;
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

std::unordered_set<std::string>&& Tool::getAllFlags() const
{
	std::lock_guard<std::mutex> lock(Tool::classMutex);
	Tool::Type& baseType = Tool::types[this->typeId];

	std::unordered_set<std::string> flags = baseType.flags;

	if (this->debugMode)
	{
		flags.insert(baseType.debugFlags.begin(),
				baseType.debugFlags.end());
	}

	if (this->verboseMode)
	{
		flags.insert(baseType.verboseFlag);
	}

	if (this->optimizationMode)
	{
		flags.insert(baseType.optimizationFlag);
	}

	return std::move(flags);
}

