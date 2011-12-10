#ifndef MAKEFILE_CONFIG_HPP
#define MAKEFILE_CONFIG_HPP

#include "../GP/OSDetection.h"

#include <vector>
#include <ostream>
#include <string>

namespace Makefile
{
	enum class OperatingSystem : unsigned int
	{
		MacOSX = 0,
		Linux = 1,
		Windows = 2
	};

	class Config
	{
	public:

		Config();
		Config(const Config& config);
		~Config() = default;

		static OperatingSystem getCurrentOS();

		OperatingSystem getTargetOS() const;
		void setTargetOS(OperatingSystem os);

		bool isDebug() const;
		void setDebug(bool debug);

		bool isVerbose() const;
		void setVerbose(bool verbose);

		const std::vector<std::string>& getIncludePaths() const;
		void addIncludePath(std::string includePath);

		const std::vector<std::string>& getLibraryPaths() const;
		void addLibraryPath(std::string libraryPath);

		const std::vector<std::string>& getLibraries() const;
		void addLibrary(std::string library);

		friend std::ostream& operator<< (std::ostream& stream, Config& config)
		{
			stream << "Configuration:" << std::endl;
			stream << "\tDebug:   " << (config.debug ? "Yes" : " No") << std::endl;
			stream << "\tVerbose: " << (config.debug ? "Yes" : " No") << std::endl;

			stream << "\tInclude paths :" << std::endl;
			for (std::string& name : config.includePaths)
			{
				stream << "\t\t" << name << std::endl;
			}
			stream << "\tLibrary paths :" << std::endl;
			for (std::string& name : config.libraryPaths)
			{
				stream << "\t\t" << name << std::endl;
			}
			stream << "\tLibraries :" << std::endl;
			for (std::string& name : config.libraries)
			{
				stream << "\t\t" << name << std::endl;
			}

			return stream;
		}

	private:
		OperatingSystem targetOS;

		bool debug;
		bool verbose;

		std::vector<std::string> includePaths;
		std::vector<std::string> libraryPaths;
		std::vector<std::string> libraries;
	};
}

#endif /* MAKEFILE_CONFIG_HPP */

