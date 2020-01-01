#ifndef DOWNLOADCODECUTILS_H
#define DOWNLOADCODECUTILS_H

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

#include "downloadglobaldefine.h"

/*! @brief The class of the utils core object namespace.
 * @author Greedysky <greedysky@163.com>
 */
namespace DownloadUtils
{
    namespace Codec
    {
        /*!
         * Set string to unicode string by format.
         */
        DOWNLOAD_UTILS_EXPORT QString toUnicode(const char *chars, const char *format = "GBK");
        /*!
         * Set string to unicode string by format.
         */
        DOWNLOAD_UTILS_EXPORT QString toUnicode(const QByteArray &chars, const char *format = "GBK");
        /*!
         * Set string from unicode string by format.
         */
        DOWNLOAD_UTILS_EXPORT QByteArray fromUnicode(const QString &chars, const char *format = "GBK");
        /*!
         * Set local codec by format.
         */
        DOWNLOAD_UTILS_EXPORT void setLocalCodec(const char *format = "utf-8");
        /*!
         * Trasform string to local 8bit char.
         */
        DOWNLOAD_UTILS_EXPORT const char *toLocal8Bit(const QString &str);
        /*!
         * Trasform string to utf8 char.
         */
        DOWNLOAD_UTILS_EXPORT const char *toUtf8(const QString &str);

    }
}

#endif // DOWNLOADCODECUTILS_H
