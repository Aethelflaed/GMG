#include "Options.hpp"

using namespace Makefile;

Options::Options()
	: debug{false}, verbose{false}
{
}

bool Options::getDebug() const
{
	return this->debug;
}
void Options::setDebug(bool debug)
{
	this->debug = debug;
}

bool Options::getVerbose() const
{
	return this->verbose;
}
void Options::setVerbose(bool verbose)
{
	this->verbose = verbose;
}

