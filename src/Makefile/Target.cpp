#include "Target.hpp"

#include <algorithm>

using namespace Makefile;

Target::Target(Generator& generator, const std::string& name)
	:name(name), version("1.0"),
	 modules(), generator(generator), type(TargetType::Application), config()
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

	for (dependencies_vector::iterator& iterator : deprecated_iterators)
	{
		this->dependencies.erase(iterator);
	}

	throw std::out_of_range("No such dependencies");
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

TargetType Target::getType() const
{
	return this->type;
}
void Target::setType(TargetType type)
{
	this->type = type;
}

Config& Target::getConfig()
{
	return this->config;
}
void Target::setConfig(const Config& config)
{
	this->config = Config(config);
}

const Target::dependencies_vector& Target::getDependencies() const
{
	return this->dependencies;
}
void Target::addDependency(const std::string& name) throw (std::out_of_range)
{
	this->dependencies.push_back(this->generator.getTargetPointer(name));
}
void Target::removeDependency(const std::string& name) throw (std::out_of_range)
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

	for (dependencies_vector::iterator& iterator : deprecated_iterators)
	{
		this->dependencies.erase(iterator);
	}

	throw std::out_of_range("No such dependencies");
}

