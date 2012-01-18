#ifndef MAKEFILE_TOOL_HPP
#define MAKEFILE_TOOL_HPP

#include <iostream>
#include <ostream>
#include <string>
#include <stdexcept>
#include <unordered_set>
#include <array>
#include <memory>

#include "Util/Output.hpp"

#include "Config.hpp"

namespace Makefile
{
	enum class ToolType : unsigned short int
	{
		/* Don't change ordering, to enable values count */
		C = 0,
		CXX,
		LEX,
		YACC,
		TEX,

		/* Keep that value in the end */
		_trailing
	};

	class Tool : public Util::Output
	{
	private:
		Tool(const std::string& name, const std::string& flagName);
		Tool(const std::string& name,
				const std::string& flagName,
				std::initializer_list<std::string> flags,
				std::initializer_list<std::string> debugFlags,
				const std::string& verboseFlag,
				const std::string& optimizationFlag,
				std::initializer_list<std::string> filePatterns,
				std::initializer_list<std::string> paths);

	public:
		static Tool& addTool(const std::string& name, const std::string& flagName);
		static void removeTool(const std::string& name);
		static Tool& getTool(const std::string& name);
		static const std::unordered_set<std::shared_ptr<Tool>>& getTools();
		static void resetTools();

		const std::string& getName() const;
		const std::string& getFlagName() const;

		void addFlag(const std::string& flag);
		void removeFlag(const std::string& flag);
		void resetFlags();
		const std::unordered_set<std::string>& getFlags() const;

		void addDebugFlag(const std::string& flag);
		void removeDebugFlag(const std::string& flag);
		void resetDebugFlags();
		const std::unordered_set<std::string>& getDebugFlags() const;

		void setVerboseFlag(const std::string& flag);
		const std::string& getVerboseFlag() const;

		void setOptimizationFlag(const std::string& flag);
		const std::string& getOptimizationFlag() const;

		void addFilePattern(const std::string& pattern);
		void removeFilePattern(const std::string& pattern);
		void resetFilePatterns();
		const std::unordered_set<std::string>& getFilePatterns() const;

		void setPathForOS(OperatingSystem OS, const std::string& path);
		const std::string& getPathForOS(OperatingSystem OS) const;

		std::unordered_set<std::string>&& getAllFlags(bool debugMode,
				bool verboseMode, bool optimizationMode) const;

		void output(std::ostream& stream, Util::OutputType outputType, unsigned short indentLevel = 0) const override;
		static void help(std::ostream& stream, int command = 0);

	private:
		static std::unordered_set<std::shared_ptr<Tool>> tools;

		unsigned short toolId;
		std::string name;
		std::string flagName;
		std::unordered_set<std::string> flags;
		std::unordered_set<std::string> debugFlags;
		std::string verboseFlag;
		std::string optimizationFlag;
		std::unordered_set<std::string> filePatterns;
		std::array<std::string, (unsigned short) OperatingSystem::_trailing> paths;
	};
}

#endif /* MAKEFILE_TOOL_HPP */

