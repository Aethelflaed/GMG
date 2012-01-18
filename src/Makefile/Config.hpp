#ifndef MAKEFILE_CONFIG_HPP
#define MAKEFILE_CONFIG_HPP

#include "GP/OSDetection.h"

#include "Util/Output.hpp"

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

	class Config : public Util::Output
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
		bool areIncludePathsModified() const;
		void addIncludePath(std::string includePath);

		const std::vector<std::string>& getLibraryPaths() const;
		bool areLibraryPathsModified() const;
		void addLibraryPath(std::string libraryPath);

		const std::vector<std::string>& getLibraries() const;
		bool areLibrariesModified() const;
		void addLibrary(std::string library);

		void output(std::ostream& stream, Util::OutputType outputType, unsigned short indentLevel = 0) const override;
		static void help(std::ostream& stream, int command = 0);

		friend std::ostream& operator<< (std::ostream& stream, Config& config)
		{
			config.list(stream);
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

