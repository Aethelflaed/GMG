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
		~Config() = default;

		OperatingSystem getTargetOS() const;
		void setTargetOS(OperatingSystem OS);
	private:
#if defined MACOSX
		static const OperatingSystem currentOS = OperatingSystem::MacOSX;
#elif defined LINUX
		static const OperatingSystem currentOS = OperatingSystem::Linux;
#elif defined WINDOWS
		static const OperatingSystem currentOS = OperatingSystem::Windows;
#endif

		OperatingSystem targetOS;
		std::vector<std::string> includePaths;
		std::vector<std::string> libraryPaths;
		std::vector<std::string> libraries;
	};
}

#endif /* MAKEFILE_CONFIG_HPP */

