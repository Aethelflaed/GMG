#include "Target.hpp"

using namespace Makefile;

Target::Target()
	:name{}
{
}

Target::Target(const std::string& name)
	:name{name}
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

