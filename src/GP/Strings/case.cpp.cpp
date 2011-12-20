#include "case.h"
#include <boost/algorithm/string.hpp>

::std::string GP::Strings::stringToLower(::std::string& string)
{
	::boost::algorithm::to_lower(string);
	return string;
}

::std::string GP::Strings::stringToUppder(::std::string& string)
{
	::boost::algorithm::to_upper(string);
	return string;
}

