#ifndef DOWNLOADCOREUTILS_H
#define DOWNLOADCOREUTILS_H

/* =================================================
 * This file is part of the TTK Downloader project
 * Copyright (c) 2016 - 2017 Greedysky Studio
 * All rights reserved!
 * Redistribution and use of the source code or any derivative
 * works are strictly forbiden.
   =================================================*/

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
         * Open file from local by path or net url.
         */
        DOWNLOAD_UTILS_EXPORT bool openUrl(const QString &path, bool local = true);

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

        /*!
         * Version check.
         */
        DOWNLOAD_UTILS_EXPORT bool versionCheck(const QStringList &ol, const QStringList &dl, int depth);
        /*!
         * Version check.
         */
        DOWNLOAD_UTILS_EXPORT bool versionCheck(const QString &o, const QString &d);

    }
}

#endif // DOWNLOADCOREUTILS_H
