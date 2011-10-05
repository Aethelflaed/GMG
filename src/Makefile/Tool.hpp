#ifndef MAKEFILE_TOOL_HPP
#define MAKEFILE_TOOL_HPP

#include <ostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <map>

namespace Makefile
{
	class Tool
	{
	public:
		enum class Type : int
		{
			OTHER = -1,
			C = 0,
			CXX,
			LEX,
			YACC,
			TEX
		};

		static std::map<int, std::string> typeNames;
		static std::map<int, std::string> typeFlagNames;
		static std::map<int, std::vector<std::string>> debugFlags;
		static std::map<int, std::string> verboseFlags;

		Tool(const std::string& typeName, const std::string& typeFlagName);
		explicit Tool(Type type);
		explicit Tool(int type);
		~Tool() = default;

		int getCustomTypeId() const;

		Type getType() const;
		void setType(Type type);

		const std::string& getName() const;
		std::string& getName();
		void setString(const std::string& name);

		const std::string& getPath() const;
		std::string& getPath();
		void setPath(const std::string& path);

		const std::vector<std::string>& getFlags() const;
		std::vector<std::string>& getFlags();
		void addFlag(const std::string& flag);
		void removeFlag(const std::string& flag) throw (std::out_of_range);
		void removeFlag(int index) throw (std::out_of_range);

		void addDebugFlag();
		void addVerboseFlag();
	private:
		Type type;
		int customType;
		std::string name;
		std::string path;
		std::vector<std::string> flags;
	};
}

#endif /* MAKEFILE_TOOL_HPP */

