#include "Generator.hpp"
#include <iostream>

using namespace Makefile;

Generator::Generator()
	:targets()
{
}

void Generator::generate()
{
}

const Generator::targets_map& Generator::getTargets() const
{
	return this->targets;
}
Target& Generator::getTarget(const std::string& name)
	throw (std::out_of_range)
{
	try
	{
		return *(this->targets.at(name));
	}
	catch(std::out_of_range ex)
	{
		throw std::out_of_range("No such target");
	}
}
Target& Generator::addTarget(const std::string& name)
	throw (std::invalid_argument)
{
	typedef targets_map::value_type target_type;

	if (name == "all" ||
		name == "install" ||
		name == "clean" ||
		name == "mrproper" ||
		name == "debug" ||
		name == "release")
	{
		throw std::invalid_argument(std::string("Invalid use of reserved name : ") + name);
	}

	Target*& target = this->targets[name];
	if (target != nullptr)
	{
		throw std::invalid_argument("Target already exists");
	}
	target = new Target(name);

	return *target;
}
void Generator::removeTarget(const std::string& name)
	throw (std::out_of_range)
{
	Target* target = this->targets[name];
	if (target == nullptr)
	{
		throw std::out_of_range("No such target");
	}
	delete target;
	this->targets.erase(name);
}

Config& Generator::getConfig()
{
	return this->config;
}

