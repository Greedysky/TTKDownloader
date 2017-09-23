#ifndef DOWNLOADSTRINGUTILS_H
#define DOWNLOADSTRINGUTILS_H

/* =================================================
 * This file is part of the TTK Downloader project
 * Copyright (c) 2016 - 2017 Greedysky Studio
 * All rights reserved!
 * Redistribution and use of the source code or any derivative
 * works are strictly forbiden.
   =================================================*/

#include "downloadnumberdefine.h"
#include "downloadglobaldefine.h"

/*! @brief The class of the utils string object namespace.
 * @author Greedysky <greedysky@163.com>
 */
namespace DownloadUtils
{
    namespace String
    {
        /*!
         * Remove given key in string, default is space.
         */
        DOWNLOAD_UTILS_EXPORT QString removeStringBy(const QString &value, const QString &key = " ");
        /*!
         * Get split string value.
         */
        DOWNLOAD_UTILS_EXPORT QStringList splitString(const QString &value, const QString &key = "-");

        /*!
         * Get song artist name.
         */
        DOWNLOAD_UTILS_EXPORT QString artistName(const QString &value, const QString &key = "-");
        /*!
         * Get song name.
         */
        DOWNLOAD_UTILS_EXPORT QString songName(const QString &value, const QString &key = "-");

        /*!
         * Transform colors string to color list.
         */
        DOWNLOAD_UTILS_EXPORT QList<QColor> readColorConfig(const QString &value);
        /*!
         * Transform color to color string.
         */
        DOWNLOAD_UTILS_EXPORT QString writeColorConfig(const QColor &color);
        /*!
         * Transform color list to colors string.
         */
        DOWNLOAD_UTILS_EXPORT QString writeColorConfig(const QList<QColor> &colors);

    }
}

#endif // DOWNLOADSTRINGUTILS_H
