#ifndef MAKEFILE_TOOL_HPP
#define MAKEFILE_TOOL_HPP

#include <ostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <unordered_map>
#include <mutex>
#include <atomic>
#include <array>
#include <set>

#include "../GP/Exceptions/LockAcquisitionException.hpp"

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

	class Tool
	{
	public:
		static unsigned short addType(const std::string& typeName,
				const std::string& typeFlagName);

		static void addTypeDebugFlag(unsigned short typeId, const std::string& flag);
		static void removeTypeDebugFlag(unsigned short typeId, const std::string& flag);
		static const std::set<std::string>& getTypeDebugFlags(unsigned short typeId);

		static void setTypeVerboseFlag(unsigned short typeId, const std::string& flag);
		static const std::string& getTypeVerboseFlag(unsigned short typeId);

		static void setTypeOptimizationFlag(unsigned short typeId, const std::string& flag);
		static const std::string& getTypeOptimizationFlag(unsigned short type);

		static void addTypeFilePattern(unsigned short typeId, const std::string& pattern);
		static void removeTypeFilePattern(unsigned short typeId, const std::string& pattern);
		static const std::set<std::string>& getTypeFilePatterns(unsigned short type);

		static void setTypePathForOS(unsigned short typeId, OperatingSystem OS, const std::string& path);
		static const std::string& getTypePathForOS(unsigned short typeId, OperatingSystem OS);

		explicit Tool(ToolType type);
		explicit Tool(unsigned short type);
		~Tool() = default;

		int getTypeId() const;
		ToolType getType() const;

		const std::string& getName() const;
		void setName(const std::string& name);

		const std::string& getPath() const;
		void setPath(const std::string& path);

		const std::set<std::string>& getFlags() const;
		void addFlag(const std::string& flag);
		void removeFlag(const std::string& flag);

		bool isDebugMode() const;
		void setDebugMode(bool debugMode);

		bool isVerboseMode() const;
		void setVerboseMode(bool verboseMode);

		bool isOptimizationMode() const;
		void setOptimizationMode(bool optimizationMode);

		std::set<std::string>&& getAllFlags() const;

	private:
		struct Type
		{
			Type(const std::string& name, const std::string& flagName);
			Type(const std::string& name,
				 const std::string& flagName,
				 std::initializer_list<std::string> debugFlags,
				 const std::string& verboseFlag,
				 const std::string& optimizationFlag,
				 std::initializer_list<std::string> filePatterns,
				 std::initializer_list<std::string> paths);

			std::string name;
			std::string flagName;
			std::set<std::string> debugFlags;
			std::string verboseFlag;
			std::string optimizationFlag;
			std::set<std::string> filePatterns;
			std::array<std::string, (int) ToolType::_trailing - 1> paths;
		};

		static std::mutex classMutex;
		static std::atomic<unsigned short> index;
		static std::vector<Type> types;

		ToolType type;
		unsigned short typeId;

		std::string name {};
		std::string path {};

		std::set<std::string> filePatterns {};
		std::set<std::string> flags {};

		std::atomic<bool> debugMode {false};
		std::atomic<bool> verboseMode {false};
		std::atomic<bool> optimizationMode {false};

		/* Exceptions thrown by this class, just a short-hand to centralize `what' arg */
		class TypeIdException : public std::invalid_argument
		{
		public:
			TypeIdException()
				:std::invalid_argument{"No type matching this typeId."}
			{
			}
		};
		class NoSuchItemException : public std::invalid_argument
		{
		public:
			NoSuchItemException()
				:std::invalid_argument{"No such item."}
			{
			}
		};
	};
}

#endif /* MAKEFILE_TOOL_HPP */

