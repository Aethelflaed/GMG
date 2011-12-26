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
		virtual void output(std::ostream& stream, OutputType type) = 0;

		void generate(std::ostream& stream)
		{
			this->output(stream, OutputType::Makefile);
		}
		void list(std::ostream& stream)
		{
			this->output(stream, OutputType::List);
		}
		void save(std::ostream& stream)
		{
			this->output(stream, OutputType::Command);
		}
	};
}
}

#endif /* MAKEFILE_UTIL_OUTPUT_HPP */

