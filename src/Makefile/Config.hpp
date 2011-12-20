#ifndef MAKEFILE_CONFIG_HPP
#define MAKEFILE_CONFIG_HPP

#include "../GP/OSDetection.h"

#include <vector>
#include <ostream>
#include <string>
#include <memory>

namespace Makefile
{
	enum class OperatingSystem : unsigned short int
	{
		/* Don't change ordering, to enable values count */
		Linux = 0,
		MacOSX,
		Windows,

		/* Keep that value in the end */
		_trailing
	};

	class Config
	{
	public:
		Config();
		Config(const Config& config, bool dependency = false);
		~Config() = default;

		static std::string getOSName(OperatingSystem OS);
		static OperatingSystem getOSValue(std::string OS);
		static OperatingSystem getCurrentOS();

		OperatingSystem getTargetOS() const;
		bool isTargetOSModified() const;
		void setTargetOS(OperatingSystem os);

		bool isDebug() const;
		bool isDebugModified() const;
		void setDebug(bool debug);

		bool isVerbose() const;
		bool isVerboseModified() const;
		void setVerbose(bool verbose);

		const std::vector<std::string>& getIncludePaths() const;
		bool isIncludePathsModified() const;
		void addIncludePath(std::string includePath);

		const std::vector<std::string>& getLibraryPaths() const;
		bool isLibraryPathsModified() const;
		void addLibraryPath(std::string libraryPath);

		const std::vector<std::string>& getLibraries() const;
		bool isLibrariesModified() const;
		void addLibrary(std::string library);

		friend std::ostream& operator<< (std::ostream& stream, Config& config)
		{
			stream << "Configuration: (Field marked * are inherited)" << std::endl;
			stream << "\tDebug" << (config.isDebugModified() ? "" : "*") << ": " << (config.isDebug() ? "Yes" : "No") << std::endl;
			stream << "\tVerbose" << (config.isVerboseModified() ? "" : "*") << ": " << (config.isVerbose()  ? "Yes" : "No") << std::endl;

			stream << "\tInclude paths" << (config.isIncludePathsModified() ? "" : "*" ) << ":" << std::endl;
			for (const std::string& name : config.getIncludePaths())
			{
				stream << "\t\t" << name << std::endl;
			}
			stream << "\tLibrary paths" << (config.isLibraryPathsModified() ? "" : "*" ) << ":" << std::endl;
			for (const std::string& name : config.getLibraryPaths())
			{
				stream << "\t\t" << name << std::endl;
			}
			stream << "\tLibraries" << (config.isLibrariesModified() ? "" : "*" ) << ":" << std::endl;
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

