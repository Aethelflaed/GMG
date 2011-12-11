#include "Generator.hpp"

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

	auto result = this->targets.insert(target_type(name, Target(name)));

	if (result.second == false)
	{
		throw std::invalid_argument("Target already exists");
	}

	return result.first->second;
}
void Generator::removeTarget(const std::string& name)
	throw (std::out_of_range)
{
	targets_map::size_type count = this->targets.erase(name);
	if (count < 1)
	{
		throw std::out_of_range("No such target");
	}
}

Config& Generator::getConfig()
{
	return this->config;
}

