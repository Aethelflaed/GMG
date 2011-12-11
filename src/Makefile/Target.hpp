#ifndef MAKEFILE_TARGET_HPP
#define MAKEFILE_TARGET_HPP

#include <ostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <memory>

#include "define.hpp"
#include "Config.hpp"
#include "Generator.hpp"
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
		typedef std::weak_ptr<Target> dependency_type;
		typedef std::vector<dependency_type> dependencies_vector;

		Target(Generator& generator, const std::string& name);
		~Target() = default;

		void clean();

		const std::string& getName() const;
		void setName(const std::string& name);

		const std::string& getVersion() const;
		void setVersion(const std::string& version);

		const std::vector<std::string>& getModules() const;
		void addModule(const std::string& module);
		void removeModule(const std::string& module) throw (std::out_of_range);

		TargetType getType() const;
		void setType(TargetType type);

		Config& getConfig();
		void setConfig(const Config& config);

		const dependencies_vector& getDependencies() const;
		void addDependency(const std::string& name) throw (std::out_of_range);
		void removeDependency(const std::string& name) throw (std::out_of_range);

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

			stream << "Target: \"" << target.getName() << "\"" << std::endl
				   << "\tVersion: \"" << target.getVersion() << "\"" << std::endl
				   << "\tType: \"" << type << "\"" << std::endl
				   << "\tModules:" << std::endl;
			auto modules = target.getModules();
			for (size_t i = 0; i < modules.size(); i++)
			{
				stream << "\t  " << modules[i] << "\n";
			}
			return stream;
		}

	private:
		std::string name;
		std::string version;
		std::vector<std::string> modules;

		Generator& generator;
		TargetType type;
		Config config;

		std::vector<Tool> tool;
		dependencies_vector dependencies;
	};
}

#endif /* MAKEFILE_TARGET_HPP */

