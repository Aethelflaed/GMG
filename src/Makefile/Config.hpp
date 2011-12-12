#ifndef MAKEFILE_CONFIG_HPP
#define MAKEFILE_CONFIG_HPP

#include "../GP/OSDetection.h"

#include <vector>
#include <ostream>
#include <string>
#include <memory>

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
		Config(const Config& config, bool dependency = false);
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
			stream << "\tDebug:   " << (config.isDebug() ? "Yes" : " No") << std::endl;
			stream << "\tVerbose: " << (config.isVerbose()  ? "Yes" : " No") << std::endl;

			stream << "\tInclude paths :" << std::endl;
			for (const std::string& name : config.getIncludePaths())
			{
				stream << "\t\t" << name << std::endl;
			}
			stream << "\tLibrary paths :" << std::endl;
			for (const std::string& name : config.getLibraryPaths())
			{
				stream << "\t\t" << name << std::endl;
			}
			stream << "\tLibraries :" << std::endl;
			for (const std::string& name : config.getLibraries())
			{
				stream << "\t\t" << name << std::endl;
			}

			return stream;
		}

	private:
		const Config* dependency;

		std::shared_ptr<OperatingSystem> targetOS;

		std::shared_ptr<bool> debug;
		std::shared_ptr<bool> verbose;

		std::shared_ptr<std::vector<std::string>> includePaths;
		std::shared_ptr<std::vector<std::string>> libraryPaths;
		std::shared_ptr<std::vector<std::string>> libraries;
	};
}

#endif /* MAKEFILE_CONFIG_HPP */

