#ifndef MAKEFILE_CONFIG_HPP
#define MAKEFILE_CONFIG_HPP

#include "../GP/OSDetection.h"

#include <vector>
#include <string>

namespace Makefile
{
	class Config
	{
	public:
		enum class OperatingSystem : unsigned int
		{
			MacOSX = 0,
			Linux = 1,
			Windows = 2
		};

		Config();
		Config(const Config& config);
		~Config() = default;

		static OperatingSystem getCurrentOS();

		OperatingSystem getTargetOS() const;
		void setTargetOS(OperatingSystem system);

		const std::vector<std::string>& getIncludePaths() const;
		std::vector<std::string>& getIncludePaths();
		void addIncludePath(std::string includePath);

		const std::vector<std::string>& getLibraryPaths() const;
		std::vector<std::string>& getLibraryPaths();
		void addLibraryPath(std::string libraryPath);

		const std::vector<std::string>& getLibraries() const;
		std::vector<std::string>& getLibraries();
		void addLibrary(std::string library);

	private:
		OperatingSystem targetOS;
		std::vector<std::string> includePaths;
		std::vector<std::string> libraryPaths;
		std::vector<std::string> libraries;
	};
}

#endif /* MAKEFILE_CONFIG_HPP */

