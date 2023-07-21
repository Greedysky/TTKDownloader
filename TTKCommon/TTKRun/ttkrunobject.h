#ifndef TTKRUNOBJECT_H
#define TTKRUNOBJECT_H

/***************************************************************************
 * This file is part of the TTK Library Module project
 * Copyright (C) 2015 - 2023 Greedysky Studio

 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License along
 * with this program; If not, see <http://www.gnu.org/licenses/>.
 ***************************************************************************/

#include "ttkglobal.h"

#ifdef _MSC_VER
#  pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")
#endif

/*! @brief The class of the ttk run object.
 * @author Greedysky <greedysky@163.com>
 */
class TTKRunObject
{
public:
    TTKRunObject() = default;

    /*!
     * To run main window.
     */
    void run(int argc, char **argv) const;

};

#endif // TTKRUNOBJECT_H
