#ifndef MAKEFILE_UTIL_INDENT_HPP
#define MAKEFILE_UTIL_INDENT_HPP

#include <ostream>

namespace Makefile
{
namespace Util
{
	struct Indent
	{
		Indent(unsigned short level)
			:level{level}
		{
		}

		friend std::ostream& operator<< (std::ostream& stream, const Indent& indent)
		{
			for (unsigned short i = 0; i < indent.level; i++)
			{
				stream << "\t";
			}
			return stream;
		}

		void operator++()
		{
			++ this->level;
		}
		void operator++(int)
		{
			this->level++;
		}

		void operator--()
		{
			-- this->level;
		}
		void operator--(int)
		{
			this->level--;
		}

		operator int()
		{
			return this->level;
		}

		unsigned short level;
	};
}
}

#endif /* MAKEFILE_UTIL_INDENT_HPP */

