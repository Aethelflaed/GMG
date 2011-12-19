#include "Target.hpp"

#include <algorithm>
#include <utility>

using namespace Makefile;

Target::Target(Generator& generator, const std::string& name)
	:name{name}, generator(generator),
	 config{generator.getConfig(), true}
{
}

void Target::clean()
{
	std::vector<dependencies_vector::iterator> deprecated_iterators;

	for (auto iterator = this->dependencies.begin();
		iterator != this->dependencies.end();
		iterator++)
	{
		if (iterator->expired())
		{
			deprecated_iterators.push_back(iterator);
		}
	}

	for (const dependencies_vector::iterator& iterator : deprecated_iterators)
	{
		this->dependencies.erase(iterator);
	}
}

void Target::setName(const std::string& name)
{
	this->name = name;
}
const std::string& Target::getName() const
{
	return this->name;
}

void Target::setVersion(const std::string& version)
{
	this->version = version;
}
const std::string& Target::getVersion() const
{
	return this->version;
}

void Target::addModule(const std::string& module)
{
	this->modules.insert(module);
}
void Target::removeModule(const std::string& module)
{
	auto iterator = this->modules.find(module);
	if (iterator == this->modules.end())
	{
		throw std::out_of_range("No such module");
	}

	this->modules.erase(iterator);
}
const std::unordered_set<std::string>& Target::getModules() const
{
	return this->modules;
}

TargetType Target::getType() const
{
	return this->type;
}
void Target::setType(TargetType type)
{
	this->type = type;
}

void Target::setConfig(const Config& config)
{
	this->config = Config(config);
}
Config& Target::getConfig()
{
	return this->config;
}

void Target::addTool(const std::string& name)
{
	this->tools.insert(std::make_pair<const std::string&, Tool>(name, Tool(Tool::getTypeId(name))));
}
void Target::removeTool(const std::string& name)
{
	this->tools.erase(name);
}
Tool& Target::getTool(const std::string& name)
{
	std::unordered_map<std::string, Tool>::iterator it = this->tools.find(name);
	if (it == this->tools.end())
	{
		throw std::invalid_argument("No such tool.");
	}
	return it->second;
}

void Target::addDependency(const std::string& name)
{
	this->dependencies.push_back(this->generator.getTargetPointer(name));
}
void Target::removeDependency(const std::string& name)
{
	std::vector<dependencies_vector::iterator> deprecated_iterators;

	for (auto iterator = this->dependencies.begin();
		iterator != this->dependencies.end();
		iterator++)
	{
		if (iterator->expired())
		{
			deprecated_iterators.push_back(iterator);
			continue;
		}
		if (iterator->lock()->getName() == name)
		{
			deprecated_iterators.push_back(iterator);
		}
	}

	for (const dependencies_vector::iterator& iterator : deprecated_iterators)
	{
		this->dependencies.erase(iterator);
	}
}
const Target::dependencies_vector& Target::getDependencies() const
{
	return this->dependencies;
}

