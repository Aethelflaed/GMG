#ifndef MAKEFILE_UTIL_STRINGCONTAINEROUTPUT_HPP
#define MAKEFILE_UTIL_STRINGCONTAINEROUTPUT_HPP

#include <ostream>
#include <string>
#include <unordered_set>

namespace Makefile
{
namespace Util
{
	enum class OutputForm
	{
		CommaSeparatedValues,
		SpaceSeparatedValues
	};

	struct OutputParameters
	{
		static OutputForm form;

	private:
		OutputParameters()
		{
		}
	};
	OutputForm OutputParameters::form = OutputForm::SpaceSeparatedValues;

	::std::ostream& operator<<(::std::ostream& stream, const OutputForm& form)
	{
		switch(form)
		{
			case OutputForm::CommaSeparatedValues:
				stream << ',';
				break;
			case OutputForm::SpaceSeparatedValues:
				stream << ' ';
				break;
		}
		return stream;
	}

	::std::ostream& operator<<(::std::ostream& stream, const ::std::unordered_set< ::std::string>& set)
	{
		bool first = true;
		for (const ::std::string& string : set)
		{
			if (first == false)
			{
				stream << OutputParameters::form;
			}
			first = false;
			stream << string;
		}

		return stream;
	}
}
}

#endif /* MAKEFILE_UTIL_STRINGCONTAINEROUTPUT_HPP */

