#ifndef MAKEFILE_TARGET_HPP
#define MAKEFILE_TARGET_HPP

#include <ostream>
#include <string>
#include <vector>
#include <stdexcept>

#include "Config.hpp"

namespace Makefile
{
	class Target
	{
	public:
		enum class Type : unsigned int
		{
			Application = 0,
			Library = 1,
			UnitTest = 2
		};

		Target();
		explicit Target(const std::string& name);
		~Target() = default;

		const std::string& getName() const;
		void setName(const std::string& name);

		const std::string& getVersion() const;
		void setVersion(const std::string& version);

		const std::vector<std::string>& getModules() const;
		std::vector<std::string>& getModules();
		void addModule(const std::string& module);
		void removeModule(const std::string& module) throw (std::out_of_range);

		Type getType() const;
		void setType(Type type);

		const Config& getConfig() const;
		Config& getConfig();

		friend std::ostream& operator<< (std::ostream& stream, Target& target)
		{
			std::string type;
			switch(target.getType())
			{
				case Type::Application:
					type = "Application";
					break;
				case Type::Library:
					type = "Library";
					break;
				case Type::UnitTest:
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
			for (std::string module : target.getModules())
			{
				stream << "\t" << module << "\n";
			}
			return stream;
		}

	private:
		std::string name;
		std::string version;
		std::vector<std::string> modules;
		Type type;
		Config config;
	};
}

#endif /* MAKEFILE_TARGET_HPP */

