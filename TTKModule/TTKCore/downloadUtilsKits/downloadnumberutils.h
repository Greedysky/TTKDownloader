#ifndef DOWNLOADNUMBERUTILS_H
#define DOWNLOADNUMBERUTILS_H

/* =================================================
 * This file is part of the TTK Downloader project
 * Copyright (C) 2015 - 2020 Greedysky Studio

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
 ================================================= */

#include "downloadnumberdefine.h"
#include "downloadglobaldefine.h"

/*! @brief The class of the utils number object namespace.
 * @author Greedysky <greedysky@163.com>
 */
namespace DownloadUtils
{
    namespace Number
    {
        /*!
         * Transform value to cp float value.
         */
        DOWNLOAD_UTILS_EXPORT QString size2Number(qint64 size);
        /*!
         * Transform value to cp int value.
         */
        DOWNLOAD_UTILS_EXPORT QString size2NumberInt(qint64 size);
        /*!
         * Transform value to cp value.
         */
        DOWNLOAD_UTILS_EXPORT QString size2Label(qint64 size);
        /*!
         * Transform value to speed float value.
         */
        DOWNLOAD_UTILS_EXPORT QString speed2Label(qint64 size);
        /*!
         * Transform value to speed int value.
         */
        DOWNLOAD_UTILS_EXPORT QString speed2LabelInt(qint64 size);

        /*!
         * Transform value to kb entity.
         */
        DOWNLOAD_UTILS_EXPORT qreal sizeByte2KByte(qint64 size);
        /*!
         * Transform value to mb entity.
         */
        DOWNLOAD_UTILS_EXPORT qreal sizeByte2MByte(qint64 size);
        /*!
         * Transform value to tb entity.
         */
        DOWNLOAD_UTILS_EXPORT qreal sizeByte2TByte(qint64 size);

        /*!
         * Transform value to speed value base.
         */
        DOWNLOAD_UTILS_EXPORT QString speed2LabelFromLabel(qint64 size, const QString &label);

    }
}

#endif // DOWNLOADNUMBERUTILS_H
