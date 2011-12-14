#include "Tool.hpp"

#include <algorithm>

using namespace Makefile;

std::map<int, std::string> Tool::typeNames {
	std::pair<int, std::string>((int) ToolType::C, "C"),
	std::pair<int, std::string>((int) ToolType::CXX, "CXX"),
	std::pair<int, std::string>((int) ToolType::LEX, "LEX"),
	std::pair<int, std::string>((int) ToolType::YACC, "YACC"),
	std::pair<int, std::string>((int) ToolType::TEX, "TEX")
};

std::map<int, std::string> Tool::typeFlagNames {
	std::pair<int, std::string>((int) ToolType::C, "CFLAGS"),
	std::pair<int, std::string>((int) ToolType::CXX, "CXXFLAGS"),
	std::pair<int, std::string>((int) ToolType::LEX, "LEXFLAGS"),
	std::pair<int, std::string>((int) ToolType::YACC, "YFLAGS"),
	std::pair<int, std::string>((int) ToolType::TEX, "TEXFLAGS")
};

std::map<int, std::vector<std::string>> Tool::debugFlags {
	std::pair<int, std::vector<std::string>>{(int) ToolType::C,
		std::vector<std::string> {
			"-g3",
			"-gdwarf-2",
			"-W",
			"-Wall"
		}
	},
	std::pair<int, std::vector<std::string>>{(int) ToolType::CXX,
		std::vector<std::string> {
			"-g3",
			"-gdwarf-2",
			"-W",
			"-Wall"
		}
	},
	std::pair<int, std::vector<std::string>>{(int) ToolType::LEX,
		std::vector<std::string> ()
	},
	std::pair<int, std::vector<std::string>>{(int) ToolType::YACC,
		std::vector<std::string> { "--debug" }
	},
	std::pair<int, std::vector<std::string>>{(int) ToolType::TEX,
		std::vector<std::string> { "" }
	}
};

std::map<int, std::string> Tool::verboseFlags {
	std::pair<int, std::string>((int) ToolType::C,    "-v"),
	std::pair<int, std::string>((int) ToolType::CXX,  "-v"),
	std::pair<int, std::string>((int) ToolType::LEX,  "-v"),
	std::pair<int, std::string>((int) ToolType::YACC, "-v"),
	std::pair<int, std::string>((int) ToolType::TEX,  "")
};

std::map<int, std::vector<std::string>> Tool::defaultFilePatterns {
	{(int) ToolType::C, {
			".c"
		}
	}
};

Tool::Tool(const std::string& typeName, const std::string& typeFlagName)
	:type(ToolType::OTHER), typeId(-1), name(), path(), flags(),
	 debugMode(false), verboseMode(false)
{
	int typeId = Tool::typeNames.size();
	Tool::typeNames[typeId] = typeName;
	Tool::typeFlagNames[typeId] = typeFlagName;

	this->typeId = typeId;
}

Tool::Tool(ToolType type)
	:type(type), typeId((int) type), name(), path(), flags(),
	 debugMode(false), verboseMode(false)
{
	if (this->type == ToolType::YACC)
	{
		this->flags.push_back("-d");
	}
}

Tool::Tool(int type)
	:type(ToolType::OTHER), typeId(type), name(), path(), flags(),
	 debugMode(false), verboseMode(false)
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

	return std::move(flags);
}

