#ifndef MAKEFILE_TARGET_HPP
#define MAKEFILE_TARGET_HPP

#include <ostream>
#include <string>
#include <vector>
#include <stdexcept>

namespace Makefile
{
	class Target
	{
	public:
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

		friend std::ostream& operator<< (std::ostream& stream, Target& target)
		{
			stream << "Target \"" << target.getName()
				   << "\" version \"" << target.getVersion()
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
	};
}

#endif /* MAKEFILE_TARGET_HPP */

