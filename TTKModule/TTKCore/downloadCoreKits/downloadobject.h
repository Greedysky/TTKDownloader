#ifndef DOWNLOADOBJECT_H
#define DOWNLOADOBJECT_H

/* =================================================
 * This file is part of the TTK Downloader project
 * Copyright (C) 2015 - 2021 Greedysky Studio

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

#include <QDir>
#include <QCoreApplication>
#include "ttkglobal.h"

//
#define TTS_FILE_PREFIX         "ttks"
#define SKN_FILE_PREFIX         "skn"
#define JPG_FILE_PREFIX         "jpg"
#define CFG_FILE_PREFIX         "ttk"
#define LST_FILE_PREFIX         "tkpl"
#define EXE_FILE_PREFIX         "exe"
#define XML_FILE_PREFIX         "xml"
#define SET_FILE_PREFIX         "stk"
#define COM_FILE_PREFIX         "com"

#define TTS_FILE                TTK_STRCAT(TTK_DOT, TTS_FILE_PREFIX)
#define SKN_FILE                TTK_STRCAT(TTK_DOT, SKN_FILE_PREFIX)
#define JPG_FILE                TTK_STRCAT(TTK_DOT, JPG_FILE_PREFIX)
#define EXE_FILE                TTK_STRCAT(TTK_DOT, EXE_FILE_PREFIX)
#define XML_FILE                TTK_STRCAT(TTK_DOT, XML_FILE_PREFIX)
#define SET_FILE                TTK_STRCAT(TTK_DOT, SET_FILE_PREFIX)
#define COM_FILE                TTK_STRCAT(TTK_DOT, COM_FILE_PREFIX)


#define APP_NAME                "TTKDownloader"
#define APP_DOT_NAME            TTK_STRCAT(APP_NAME, TTK_DOT)
#define APP_COME_NAME           TTK_STRCAT(APP_NAME, COM_FILE)
#define APP_EXE_NAME            TTK_STRCAT(APP_NAME, EXE_FILE)


#define APPDATA_DIR             TTK_STRCAT("AppData", TTK_SEPARATOR)
#define APPCACHE_DIR            TTK_STRCAT("AppCache", TTK_SEPARATOR)

#define THEME_DIR               TTK_STRCAT("GTheme", TTK_SEPARATOR)
#define LANGUAGE_DIR            TTK_STRCAT("GLanguage", TTK_SEPARATOR)

#define TDDOWNLOAD_DIR          TTK_STRCAT("TDDOWNLOAD", TTK_SEPARATOR)

#define USER_THEME_DIR          TTK_STRCAT("theme", TTK_SEPARATOR)


#define MAKE_NETS               "avnets.sh"
#define LIST_PATH               "list.tkpl"
#define COFIG_PATH              "config.xml"
#define HISTORY_PATH            "history.ttk"


#define MAIN_DIR_FULL           DownloadObject::getAppDir() + TTK_PDIR
#define APPDATA_DIR_FULL        DownloadObject::getConfigDir() + APPDATA_DIR
#define APPCACHE_DIR_FULL       DownloadObject::getConfigDir() + APPCACHE_DIR
#define TDDOWNLOAD_DIR_FULL     MAIN_DIR_FULL + TDDOWNLOAD_DIR


#define MAKE_NETS_FULL          APPDATA_DIR_FULL + MAKE_NETS
#define LIST_PATH_FULL          APPDATA_DIR_FULL + LIST_PATH
#define COFIG_PATH_FULL         APPDATA_DIR_FULL + COFIG_PATH
#define HISTORY_PATH_FULL       APPDATA_DIR_FULL + HISTORY_PATH
#define USER_THEME_DIR_FULL     APPDATA_DIR_FULL + USER_THEME_DIR

#define THEME_DIR_FULL          DownloadObject::getAppDir() + THEME_DIR
#define LANGUAGE_DIR_FULL       DownloadObject::getAppDir() + LANGUAGE_DIR


#define WINDOW_WIDTH_MIN        1000
#define WINDOW_HEIGHT_MIN       690
//
#define DEFAULT_INDEX_LEVEL0    -1
#define DEFAULT_INDEX_LEVEL1    -999
#define DEFAULT_INDEX_LEVEL2    -888
#define DEFAULT_INDEX_LEVEL3    -777
#define DEFAULT_INDEX_LEVEL4    -666
#define DEFAULT_INDEX_LEVEL5    -555


/*! @brief The namespace of the application object.
 * @author Greedysky <greedysky@163.com>
 */
namespace DownloadObject
{
    /*!
     * Get application work dir.
     */
    static QString getAppDir()
    {
        return QCoreApplication::applicationDirPath() + TTK_SEPARATOR;
    }

    /*!
     * Get application config dir.
     */
    static QString getConfigDir()
    {
#ifdef Q_OS_WIN
        return QString::fromLocal8Bit(getenv("APPDATA")) + "/ttkdl/";
#else
        return QDir::homePath() + "/.config/ttkdl/";
#endif
    }
}

#endif // DOWNLOADOBJECT_H
