#include "Generator.hpp"
#include "Target.hpp"

using namespace Makefile;

Generator::Generator()
	:targets()
{
}

void Generator::generate()
{
	for (targets_map::value_type& target_pair : this->targets)
	{
		target_pair.second->clean();
	}
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
		return *(this->targets.at(name).get());
	}
	catch(std::out_of_range ex)
	{
		throw std::out_of_range("No such target");
	}
}
Generator::target_type Generator::getTargetPointer(const std::string& name)
	throw (std::out_of_range)
{
	try
	{
		return this->targets.at(name);
	}
	catch(std::out_of_range ex)
	{
		throw std::out_of_range("No such target");
	}
}
Target& Generator::addTarget(const std::string& name)
	throw (std::invalid_argument)
{
	if (name == "all" ||
		name == "install" ||
		name == "clean" ||
		name == "mrproper" ||
		name == "debug" ||
		name == "release")
	{
		throw std::invalid_argument(std::string("Invalid use of reserved name : ") + name);
	}

	target_type& target = this->targets[name];
	if (target.get() != nullptr)
	{
		throw std::invalid_argument("Target already exists");
	}
	target = target_type(new Target(*this, name));

	return *(target.get());
}
void Generator::removeTarget(const std::string& name)
	throw (std::out_of_range)
{
	target_type target = this->targets[name];
	if (target.get() == nullptr)
	{
		throw std::out_of_range("No such target");
	}
	this->targets.erase(name);
}

Config& Generator::getConfig()
{
	return this->config;
}

