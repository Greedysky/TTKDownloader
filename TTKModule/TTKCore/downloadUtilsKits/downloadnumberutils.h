#ifndef DOWNLOADNUMBERUTILS_H
#define DOWNLOADNUMBERUTILS_H

/***************************************************************************
 * This file is part of the TTK Downloader project
 * Copyright (C) 2015 - 2024 Greedysky Studio

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

#include "ttkmoduleexport.h"

/*! @brief The namespace of the utils number.
 * @author Greedysky <greedysky@163.com>
 */
namespace TTK
{
    namespace Number
    {
        /*!
         * Transform value to cp float value.
         */
        TTK_MODULE_EXPORT QString sizeByteToLabel(qint64 size);
        /*!
         * Transform value to speed float value.
         */
        TTK_MODULE_EXPORT QString speedByteToLabel(qint64 size);

    }
}

#endif // DOWNLOADNUMBERUTILS_H
