#include "Options.hpp"

using namespace Makefile;

Options* Options::instance = nullptr;

Options::Options()
	: debug(false), verbose(false)
{
}

Options& Options::currentOptions()
{
	if (instance == nullptr)
	{
		instance = new Options();
	}
	return *instance;
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

