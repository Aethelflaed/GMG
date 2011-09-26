#ifndef MAKEFILE_TARGET_HPP
#define MAKEFILE_TARGET_HPP

#include <ostream>
#include <string>

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

		friend std::ostream& operator<< (std::ostream& stream, Target& target)
		{
			stream << "Target \"" << target.getName() << "\"" << std::endl;
			return stream;
		}

	private:
		std::string name;
	};
}

#endif /* MAKEFILE_TARGET_HPP */

