#ifndef DOWNLOADINITOBJECT_H
#define DOWNLOADINITOBJECT_H

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

#include <QDebug>
#include "downloadobject.h"
#include "downloadversion.h"
#include "downloadrunglobaldefine.h"

#define S_APPDATA_DIR_FULL        DownloadObject::getAppDir() + APPDATA_DIR
#define S_DOWNLOADS_DIR_FULL      DownloadObject::getAppDir() + DOWNLOADS_DIR

#define S_TEMPORARY_DIR_FULL      S_DOWNLOADS_DIR_FULL + TEMPORARY_DIR
#define S_CACHE_DIR_FULL          S_DOWNLOADS_DIR_FULL + CACHE_DIR
#define S_UPDATE_DIR_FULL         S_DOWNLOADS_DIR_FULL + UPDATE_DIR

#define S_COFIGPATH_FULL          S_APPDATA_DIR_FULL + COFIGPATH
#define S_LISTPATH_FULL           S_APPDATA_DIR_FULL + LISTPATH
#define S_HISTORYPATH_FULL        S_APPDATA_DIR_FULL + HISTORYPATH
#define S_AVATAR_DIR_FULL         S_APPDATA_DIR_FULL + AVATAR_DIR
#define S_USER_THEME_DIR_FULL     S_APPDATA_DIR_FULL + USER_THEME_DIR
#define S_MAKENETS_FULL           S_APPDATA_DIR_FULL + MAKENETS

#define S_THEME_DIR_FULL          DownloadObject::getAppDir() + DOWNLOAD_VERSION_STR + "/" + THEME_DIR
#define S_LANGUAGE_DIR_FULL       DownloadObject::getAppDir() + DOWNLOAD_VERSION_STR + "/" + LANGUAGE_DIR

#ifdef Q_OS_WIN
#define S_TTKSERVICE_FULL         DownloadObject::getAppDir() + DOWNLOAD_VERSION_STR + "/TTKService.exe"
#else
#define S_TTKDD_FULL              DownloadObject::getAppDir() + DOWNLOAD_VERSION_STR + "/TTKLDD.sh"
#define S_TTKSERVICE_FULL         DownloadObject::getAppDir() + DOWNLOAD_VERSION_STR + "/TTKService.sh"
#endif


/*! @brief The class of the download init object.
 * @author Greedysky <greedysky@163.com>
 */
class DOWNLOAD_RUN_EXPORT DownloadInitObject : public QObject
{
    Q_OBJECT
public:
    /*!
     * Object contsructor.
     */
    explicit DownloadInitObject(QObject *parent = 0);

    /*!
     * Check current setting file's validation.
     */
    void checkValid();

    /*!
     * Init all parameter.
     */
    void init();
    /*!
     * Check current dir is exist, no, just create it.
     */
    void dirIsExist(const QString &name);
    /*!
     * Check the related dir is exist.
     */
    void checkTheDirectoryExist();
    /*!
     * Check the related file is exist.
     */
    void checkTheFileNeededExist();
    /*!
     * Copy file by overwrite.
     */
    void copyFileOverwrite(const QString &origin, const QString &des);
    /*!
     * Copy file.
     */
    void copyFile(const QString &origin, const QString &des);

};

#endif // DOWNLOADINITOBJECT_H
