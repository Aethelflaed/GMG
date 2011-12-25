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

#ifndef GP_STRINGS_CASE_H
#define GP_STRINGS_CASE_H

#ifdef __cplusplus
extern "C"
{
#endif

char* strtolower(char* string);

char* strtoupper(char* string);

#ifdef __cplusplus
} /* extern "C" */

#include <string>

namespace GP
{
namespace Strings
{
	::std::string stringToLower(::std::string& string);
	::std::string stringToUppder(::std::string& string);
}
}
#endif /* __cplusplus */

#endif /* GP_STRINGS_CASE_H */

