#include <fstream>

#include "Generator.hpp"
#include "Target.hpp"
#include "../GP/Strings/case.h"

using namespace Makefile;

std::unordered_set<std::string> Generator::reservedWords {
	"all",
	"install",
	"clean",
	"mrproper",
	"debug",
	"release"
};

Generator::Generator()
	:targets()
{
}

const Generator::targets_map& Generator::getTargets() const
{
	return this->targets;
}
Target& Generator::getTarget(const std::string& name)
{
	return *(this->getTargetPointer(name).get());
}
Generator::target_type Generator::getTargetPointer(const std::string& name)
{
	std::string nameToLower = GP::Strings::stringToLower(name);
	try
	{
		return this->targets.at(nameToLower);
	}
	catch(std::out_of_range ex)
	{
		throw std::out_of_range("No such target");
	}
}
Target& Generator::addTarget(const std::string& name)
{
	std::string nameToLower = GP::Strings::stringToLower(name);
	if (Generator::reservedWords.find(nameToLower) != Generator::reservedWords.end())
	{
		throw std::invalid_argument(std::string("Invalid use of reserved name : ") + name);
	}

	target_type& target = this->targets[nameToLower];
	if (target.get() != nullptr)
	{
		throw std::invalid_argument("Target already exists");
	}
	target = target_type(new Target(*this, nameToLower));

	return *(target.get());
}
void Generator::removeTarget(const std::string& name)
{
	std::string nameToLower = GP::Strings::stringToLower(name);

	target_type target = this->targets[nameToLower];
	if (target.get() == nullptr)
	{
		throw std::out_of_range("No such target");
	}
	this->targets.erase(nameToLower);
}

Config& Generator::getConfig()
{
	return this->config;
}

