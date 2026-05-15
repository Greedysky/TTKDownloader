#ifndef TTKMODULEEXPORT_H
#define TTKMODULEEXPORT_H

/***************************************************************************
 * This file is part of the TTK Library Module project
 * Copyright (C) 2015 - 2026 Greedysky Studio

 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.

 * You should have received a copy of the GNU Lesser General Public License along
 * with this program; If not, see <http://www.gnu.org/licenses/>.
 ***************************************************************************/

#include "ttkqtcompat.h"

#ifdef TTK_LIBRARY
// Force use of visibility("default") to fix GCC 16 + Qt6 compatibility issues
#  define TTK_MODULE_EXPORT __attribute__((visibility("default")))
#else
#  define TTK_MODULE_EXPORT __attribute__((visibility("default")))
#endif

#endif // TTKMODULEEXPORT_H
