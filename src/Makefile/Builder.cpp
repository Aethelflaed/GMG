#include "Builder.hpp"

using namespace Makefile;

Builder::Builder()
	:targets{}, options{}
{
}

const Options& Builder::getOptions() const
{
	return this->options;
}
Options& Builder::getOptions()
{
	return this->options;
}

const Builder::targets_map& Builder::getTargets() const
{
	return this->targets;
}
Target& Builder::addTarget(const std::string& name)
	throw (std::invalid_argument)
{
	typedef targets_map::value_type target_type;

	auto result = this->targets.insert(target_type{name, Target{name}});

	if (result.second == false)
	{
		throw std::invalid_argument{"Target already exists"};
	}

	return result.first->second;
}
Target& Builder::getTarget(const std::string& name)
	throw (std::out_of_range)
{
	try
	{
		return this->targets.at(name);
	}
	catch(std::out_of_range ex)
	{
		throw std::out_of_range{"No such target"};
	}
}
void Builder::removeTarget(const std::string& name)
	throw (std::out_of_range)
{
	targets_map::size_type count = this->targets.erase(name);
	if (count < 1)
	{
		throw std::out_of_range{"No such target"};
	}
}

