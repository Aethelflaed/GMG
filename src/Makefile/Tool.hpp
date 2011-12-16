#ifndef MAKEFILE_TOOL_HPP
#define MAKEFILE_TOOL_HPP

#include <ostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <map>

#include "Config.hpp"

namespace Makefile
{
	enum class ToolType : int
	{
		OTHER = -1,
		C = 0,
		CXX,
		LEX,
		YACC,
		TEX
	};

	class Tool
	{
	public:
		Tool(const std::string& typeName, const std::string& typeFlagName);
		explicit Tool(ToolType type);
		explicit Tool(int type);
		~Tool() = default;

		int getTypeId() const;
		ToolType getType() const;

		const std::string& getName() const;
		void setName(const std::string& name);

		const std::string& getPath() const;
		void setPath(const std::string& path);

		const std::vector<std::string>& getFlags() const;
		void addFlag(const std::string& flag);
		void removeFlag(const std::string& flag) throw (std::out_of_range);

		bool isDebugMode() const;
		void setDebugMode(bool debugMode);

		bool isVerboseMode() const;
		void setVerboseMode(bool verboseMode);

		std::vector<std::string>&& getAllFlags() const;

	private:
		static std::map<int, std::string> typeNames;
		static std::map<int, std::string> typeFlagNames;
		static std::map<int, std::vector<std::string>> debugFlags;
		static std::map<int, std::string> verboseFlags;
		static std::map<int, std::vector<std::string>> defaultFilePatterns;
		static std::map<int, std::map<OperatingSystem, std::string>> paths;

		ToolType type;
		int typeId;

		std::string name;
		std::string path;

		std::vector<std::string> filePatterns;

		std::vector<std::string> flags;
		bool debugMode;
		bool verboseMode;
		bool optimizationMode = false;
	};
}

#endif /* MAKEFILE_TOOL_HPP */

