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

#ifndef GP_OSDETECTION_H
#define GP_OSDETECTION_H

#ifndef OS

#if defined linux || defined __linux

    #define LINUX 0
    #define OS LINUX

#elif defined __APPLE__ && defined __MACH__

    #define MACOSX 1
    #define OS MACOSX

#elif defined _WIN32 || defined _WIN64 || defined __WIN32__ || \
    defined __TOS_WIN__ || defined __WINDOWS__

    #define WINDOWS 2
    #define OS WINDOWS

#endif

#endif /* OS */

#endif /* GP_OSDETECTION_H */

