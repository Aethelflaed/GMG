#include "TargetTool.hpp"

#include <algorithm>

using namespace Makefile;

TargetTool::TargetTool(const std::string& name)
	:tool(Tool::getTool(name))
{
}

Tool& TargetTool::getTool()
{
	return this->tool;
}

const std::string& TargetTool::getName() const
{
	return this->name;
}

bool TargetTool::isDebugMode() const
{
	return this->debugMode;
}
void TargetTool::setDebugMode(bool debugMode)
{
	this->debugMode = debugMode;
}

bool TargetTool::isVerboseMode() const
{
	return this->verboseMode;
}
void TargetTool::setVerboseMode(bool verboseMode)
{
	this->verboseMode = verboseMode;
}

bool TargetTool::isOptimizationMode() const
{
	return this->optimizationMode;
}
void TargetTool::setOptimizationMode(bool optimizationMode)
{
	this->optimizationMode = optimizationMode;
}

std::unordered_set<std::string>&& TargetTool::getAllFlags() const
{
	return std::move(this->tool.getAllFlags(this->debugMode,
		this->verboseMode,
		this->optimizationMode));
}

