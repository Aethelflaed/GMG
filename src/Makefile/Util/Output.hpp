#ifndef MAKEFILE_UTIL_OUTPUT_HPP
#define MAKEFILE_UTIL_OUTPUT_HPP

#include <ostream>

namespace Makefile
{
namespace Util
{
	enum class OutputType : unsigned short
	{
		Command,
		List,
		Makefile
	};

	class Output
	{
	public:
		virtual void output(std::ostream& stream, OutputType type, unsigned short indentLevel = 0) const = 0;

		void make(std::ostream& stream) const
		{
			this->output(stream, OutputType::Makefile);
		}
		void list(std::ostream& stream) const
		{
			this->output(stream, OutputType::List);
		}
		void save(std::ostream& stream) const
		{
			this->output(stream, OutputType::Command);
		}
	};
}
}

#endif /* MAKEFILE_UTIL_OUTPUT_HPP */

