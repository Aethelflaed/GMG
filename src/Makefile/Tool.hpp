#ifndef MAKEFILE_TOOL_HPP
#define MAKEFILE_TOOL_HPP

#include <ostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <map>

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
		static std::map<int, std::string> typeNames;
		static std::map<int, std::string> typeFlagNames;
		static std::map<int, std::vector<std::string>> debugFlags;
		static std::map<int, std::string> verboseFlags;

		Tool(const std::string& typeName, const std::string& typeFlagName);
		explicit Tool(ToolType type);
		explicit Tool(int type);
		~Tool() = default;

		int getCustomTypeId() const;

		ToolType getType() const;
		void setType(ToolType type);

		const std::string& getName() const;
		void setString(const std::string& name);

		const std::string& getPath() const;
		void setPath(const std::string& path);

		const std::vector<std::string>& getFlags() const;
		void addFlag(const std::string& flag);
		void removeFlag(const std::string& flag) throw (std::out_of_range);
		void removeFlag(int index) throw (std::out_of_range);

		void addDebugFlag();
		void addVerboseFlag();
	private:
		ToolType type;
		int customType;
		std::string name;
		std::string path;
		std::vector<std::string> flags;
	};
}

#endif /* MAKEFILE_TOOL_HPP */

