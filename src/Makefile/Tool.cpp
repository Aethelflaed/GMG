#include "Tool.hpp"

#include <algorithm>

using namespace Makefile;

std::mutex Tool::classMutex{};
std::atomic<unsigned short> Tool::index{};

std::vector<Tool::Type> Tool::types {
	Tool::Type {
		"C",
		"CFLAGS",
		"-g3 -gdwarf-2 -W -Wall",
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
	}
};

Tool::Type::Type(const std::string& name, const std::string& flagName)
	:name{name}, flagName{flagName}
{
}

Tool::Type::Type(const std::string& name,
	const std::string& flagName,
	const std::string& debugFlag,
	const std::string& verboseFlag,
	const std::string& optimizationFlag,
	std::initializer_list<std::string> filePatterns,
	std::initializer_list<std::string> paths)

	:name{name}, flagName{flagName},
	 debugFlag{debugFlag}, verboseFlag{verboseFlag},
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

void Tool::setTypeDebugFlag(unsigned short typeId, const std::string& flag)
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
	type.debugFlag = flag;
}
const std::string& Tool::getTypeDebugFlag(unsigned short typeId)
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
	return type.debugFlag;
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
	type.filePatterns.erase(pattern);
}
const std::set<std::string>& Tool::getTypeFilePatterns(unsigned short typeId)
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

Tool::Tool(ToolType type)
	:type(type), typeId((unsigned short) type)
{
	{
		std::lock_guard<std::mutex> lock(Tool::classMutex);
		const Tool::Type& baseType = Tool::types[(unsigned short) type];
		this->name = baseType.name;
		this->filePatterns = baseType.filePatterns;
		this->path = baseType.paths[(unsigned short) Config::getCurrentOS()];
	}
	switch (this->type)
	{
		case ToolType::YACC:
			this->flags.insert("-d");
			break;
		default:
			break;
	}
}

Tool::Tool(unsigned short type)
	:type(ToolType::_trailing), typeId(type)
{
	if (typeId >= Tool::index)
	{
		throw Tool::TypeIdException{};
	}
	if (typeId >= Tool::index)
	{
		std::lock_guard<std::mutex> lock(Tool::classMutex);
		const Tool::Type& baseType = Tool::types[(unsigned short) type];
		if (baseType.name == "")
		{
			throw Tool::TypeIdException{};
		}

		this->name = baseType.name;
		this->filePatterns = baseType.filePatterns;
		this->path = baseType.paths[(unsigned short) Config::getCurrentOS()];
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

const std::set<std::string>& Tool::getFlags() const
{
	return this->flags;
}
void Tool::addFlag(const std::string& flag)
{
	this->flags.insert(flag);
}
void Tool::removeFlag(const std::string& flag)
{
	this->flags.erase(flag);
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

std::set<std::string>&& Tool::getAllFlags() const
{
	std::set<std::string> flags = this->flags;

	/*if (this->debugMode)
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
	}*/

	return std::move(flags);
}

