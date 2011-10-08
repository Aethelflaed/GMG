#include "Target.hpp"

#include <algorithm>

using namespace Makefile;

Target::Target(Builder& builder)
	:builder{builder}, name{}, version{"1.0"},
	 modules{}, type{Type::Application}, config{}
{
}

Target::Target(Builder& builder, const std::string& name)
	:builder{builder}, name{name}, version{"1.0"},
	 modules{}, type{Type::Application}, config{}
{
}

const std::string& Target::getName() const
{
	return this->name;
}
void Target::setName(const std::string& name)
{
	this->name = name;
}

const std::string& Target::getVersion() const
{
	return this->version;
}
void Target::setVersion(const std::string& version)
{
	this->version = version;
}

const std::vector<std::string>& Target::getModules() const
{
	return this->modules;
}
std::vector<std::string>& Target::getModules()
{
	return this->modules;
}
void Target::addModule(const std::string& module)
{
	this->modules.push_back(module);
}
void Target::removeModule(const std::string& module)
	throw (std::out_of_range)
{
	auto iterator = std::find(this->modules.begin(),
		this->modules.end(),
		module);
	if (iterator == this->modules.end())
	{
		throw std::out_of_range("No such module");
	}

	this->modules.erase(iterator);
}
void Target::removeModule(int index)
	throw (std::out_of_range)
{
	std::string module;
	try
	{
		module = this->modules.at(index);
	}
	catch (const std::out_of_range& ex)
	{
		throw std::out_of_range("No such module");
	}

	this->removeModule(module);
}

auto Target::getType() const -> Type
{
	return this->type;
}
void Target::setType(Type type)
{
	this->type = type;
}

const Config& Target::getConfig() const
{
	return this->config;
}
Config& Target::getConfig()
{
	return this->config;
}
void Target::setConfig(const Config& config)
{
	this->config = Config{config};
}

