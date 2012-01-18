/**
 * This file is part of "Geoffroy PLANQUART's Library" hereafter referred
 * as "GP's Library"
 *
 * "GP's Library" is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * "GP's Library" is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with "GP's Library".  If not, see <http://www.gnu.org/licenses/>.
 */

#include "case.h"
#include <boost/algorithm/string.hpp>
#include <memory>

::std::string GP::Strings::stringToLower(::std::string& string)
{
	::boost::algorithm::to_lower(string);
	return string;
}

::std::string GP::Strings::stringToUpper(::std::string& string)
{
	::boost::algorithm::to_upper(string);
	return string;
}

::std::string&& GP::Strings::stringToLower(const ::std::string& string)
{
	std::string newString {string};
	::boost::algorithm::to_lower(newString);
	return ::std::move(newString);
}

::std::string&& GP::Strings::stringToUpper(const ::std::string& string)
{
	std::string newString {string};
	::boost::algorithm::to_upper(newString);
	return ::std::move(newString);
}

