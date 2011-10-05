#include "Tool.hpp"

#include <algorithm>

using namespace Makefile;

std::map<int, std::string> Tool::typeNames {
	std::pair<int, std::string>{(int) Type::C, "C"},
	std::pair<int, std::string>{(int) Type::CXX, "CXX"},
	std::pair<int, std::string>{(int) Type::LEX, "LEX"},
	std::pair<int, std::string>{(int) Type::YACC, "YACC"},
	std::pair<int, std::string>{(int) Type::TEX, "TEX"}
};

std::map<int, std::string> Tool::typeFlagNames {
	std::pair<int, std::string>{(int) Type::C, "CFLAGS"},
	std::pair<int, std::string>{(int) Type::CXX, "CXXFLAGS"},
	std::pair<int, std::string>{(int) Type::LEX, "LEXFLAGS"},
	std::pair<int, std::string>{(int) Type::YACC, "YFLAGS"},
	std::pair<int, std::string>{(int) Type::TEX, "TEXFLAGS"}
};

std::map<int, std::vector<std::string>> Tool::debugFlags {
	std::pair<int, std::vector<std::string>>{(int) Type::C,
		std::vector<std::string> {
			"-g3",
			"-gdwarf-2",
			"-W",
			"-Wall"
		}
	},
	std::pair<int, std::vector<std::string>>{(int) Type::CXX,
		std::vector<std::string> {
			"-g3",
			"-gdwarf-2",
			"-W",
			"-Wall"
		}
	},
	std::pair<int, std::vector<std::string>>{(int) Type::LEX,
		std::vector<std::string> {}
	},
	std::pair<int, std::vector<std::string>>{(int) Type::YACC,
		std::vector<std::string> { "--debug" }
	},
	std::pair<int, std::vector<std::string>>{(int) Type::TEX,
		std::vector<std::string> { "" }
	}
};

std::map<int, std::string> Tool::verboseFlags {
	std::pair<int, std::string>{(int) Type::C,    "-v"},
	std::pair<int, std::string>{(int) Type::CXX,  "-v"},
	std::pair<int, std::string>{(int) Type::LEX,  "-v"},
	std::pair<int, std::string>{(int) Type::YACC, "-v"},
	std::pair<int, std::string>{(int) Type::TEX,  ""}
};

Tool::Tool(const std::string& typeName, const std::string& typeFlagName)
	:type{Type::OTHER}, customType{-1}, name{}, path{}, flags{}
{
	int typeId = typeNames.size();
	typeNames[typeId] = typeName;
	typeFlagNames[typeId] = typeFlagName;
}

Tool::Tool(Type type)
	:type{type}, customType{-1}, name{}, path{}, flags{}
{
	if (this->type == Type::YACC)
	{
		this->flags.push_back("-d");
	}
}

Tool::Tool(int type)
	:type{Type::OTHER}, customType{type}, name{}, path{}, flags{}
{
}

int Tool::getCustomTypeId() const
{
	return this->customType;
}

auto Tool::getType() const -> Type
{
	return this->type;
}

void Tool::setType(Type type)
{
	this->type = type;
}

const std::string& Tool::getName() const
{
	return this->name;
}
std::string& Tool::getName()
{
	return this->name;
}
void Tool::setString(const std::string& name)
{
	this->name = name;
}

const std::string& Tool::getPath() const
{
	return this->path;
}
std::string& Tool::getPath()
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
std::vector<std::string>& Tool::getFlags()
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

void Tool::removeFlag(int index) throw (std::out_of_range)
{
	std::string flag;
	try
	{
		flag = this->flags.at(index);
	}
	catch(const std::out_of_range& ex)
	{
		throw std::out_of_range("No such flag");
	}

	this->removeFlag(flag);
}

