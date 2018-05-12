#ifndef DOWNLOADCOREUTILS_H
#define DOWNLOADCOREUTILS_H

/* =================================================
 * This file is part of the TTK Downloader project
 * Copyright (C) 2015 - 2018 Greedysky Studio

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

#include "downloadobject.h"
#include "downloadnumberdefine.h"
#include "downloadglobaldefine.h"

/*! @brief The class of the utils core object namespace.
 * @author Greedysky <greedysky@163.com>
 */
namespace DownloadUtils
{
    namespace Core
    {
        /*!
         * Get download dir path.
         */
        DOWNLOAD_UTILS_EXPORT QString downloadPrefix();
        /*!
         * Get file suffix path.
         */
        DOWNLOAD_UTILS_EXPORT QString fileSuffix(const QString &name);

        /*!
         * Get given dir size.
         */
        DOWNLOAD_UTILS_EXPORT quint64 dirSize(const QString &dirName);
        /*!
         * Check given dir size is bigger than given size.
         */
        DOWNLOAD_UTILS_EXPORT void checkCacheSize(quint64 cacheSize, bool disabled, const QString &path);
        /*!
         * To find file by dir path.
         */
        DOWNLOAD_UTILS_EXPORT QFileInfoList findFile(const QString &path, const QStringList &filter);

        /*!
         * Get Language Name by given index.
         */
        DOWNLOAD_UTILS_EXPORT QString getLanguageName(int index);

        /*!
         * Dir remove recursively.
         */
        DOWNLOAD_UTILS_EXPORT bool removeRecursively(const QString &dir);

        /*!
         * App version check.
         */
        DOWNLOAD_UTILS_EXPORT bool appVersionCheck(const QStringList &ol, const QStringList &dl, int depth);
        /*!
         * App version check.
         */
        DOWNLOAD_UTILS_EXPORT bool appVersionCheck(const QString &o, const QString &d);

    }
}

#endif // DOWNLOADCOREUTILS_H
