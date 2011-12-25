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

#ifndef GP_OBJECTVISIBILITY_H
#define GP_OBJECTVISIBILITY_H

#include "OSDetection.h"

#if defined WINDOWS

#	if defined EXPORT_SYMBOLS

#		define VISIBILITY_PUBLIC __declspec(dllexport)
#		define VISIBILITY_LOCAL

#	else

#		define VISIBILITY_PUBLIC __declspec(dllimport)
#		define VISIBILITY_LOCAL

#	endif

#else /* WINDOWS */
#	if defined __GNUC__ && __GNUC__ >= 4

#		define VISIBILITY_PUBLIC	__attribute__ ((visibility ("default")))
#		define VISIBILITY_LOCAL		__attribute__ ((visibility ("hidden")))

#	else

#		define VISIBILITY_PUBLIC
#		define VISIBILITY_LOCAL
#		warning Visibility attributes unknow for current compiler.

#	endif /* __GNUC__ */
#endif /* WINDOWS */

#endif /* GP_OBJECTVISIBILITY_H */

