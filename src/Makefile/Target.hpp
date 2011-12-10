#ifndef MAKEFILE_TARGET_HPP
#define MAKEFILE_TARGET_HPP

#include <ostream>
#include <string>
#include <vector>
#include <stdexcept>

#include "define.hpp"
#include "Config.hpp"
#include "Tool.hpp"

namespace Makefile
{
	enum class TargetType : unsigned int
	{
		Application = 0,
		Library = 1,
		UnitTest = 2
	};

	class Target
	{
	public:
		explicit Target(Builder& builder);
		Target(Builder& builder, const std::string& name);
		~Target() = default;

		const std::string& getName() const;
		void setName(const std::string& name);

		const std::string& getVersion() const;
		void setVersion(const std::string& version);

		const std::vector<std::string>& getModules() const;
		std::vector<std::string>& getModules();
		void addModule(const std::string& module);
		void removeModule(const std::string& module) throw (std::out_of_range);
		void removeModule(int index) throw (std::out_of_range);

		TargetType getType() const;
		void setType(TargetType type);

		const Config& getConfig() const;
		Config& getConfig();
		void setConfig(const Config& config);

		friend std::ostream& operator<< (std::ostream& stream, Target& target)
		{
			std::string type;
			switch(target.getType())
			{
				case TargetType::Application:
					type = "Application";
					break;
				case TargetType::Library:
					type = "Library";
					break;
				case TargetType::UnitTest:
					type = "UnitTest";
					break;
				default:
					type = "Unknow";
					break;
			}
			stream << "Target \"" << target.getName()
				   << "\", version \"" << target.getVersion()
				   << "\", type \"" << type
				   << "\"\n  Modules :\n";
			auto modules = target.getModules();
			for (size_t i = 0; i < modules.size(); i++)
			{
				stream << "\t" << i << "\t: " << modules[i] << "\n";
			}
			return stream;
		}

	private:
		Builder& builder;
		std::string name;
		std::string version;
		std::vector<std::string> modules;
		TargetType type;
		Config config;
		std::vector<Tool> tool;
	};
}

#endif /* MAKEFILE_TARGET_HPP */

