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

#define DOT                     "."

///////////////////////////////////////
#define APPNAME                 "TTKDownloader"
#define APPDOT                  "TTKDownloader."
#define APPCOME                 "TTKDownloader.com"
///////////////////////////////////////

#define APPDATA_DIR             "AppData/"
#define DOWNLOADS_DIR           "Downloads/"

#define THEME_DIR               "MTheme/"
#define CACHE_DIR               "MCached/"
#define UPDATE_DIR              "MUpdate/"
#define TDDOWNLOAD_DIR          "TDDOWNLOAD/"
#define AVATAR_DIR              "avatar/"
#define USER_THEME_DIR          "theme/"
#define LANGUAGE_DIR            "MLanguage/"
#define TEMPORARY_DIR           "temporary"

#define TTS_FILE_PREFIX         "ttks"
#define SKN_FILE_PREFIX         "skn"
#define JPG_FILE_PREFIX         "jpg"
#define BMP_FILE_PREFIX         "bmp"
#define PNG_FILE_PREFIX         "png"
#define LRC_FILE_PREFIX         "lrc"
#define KRC_FILE_PREFIX         "krc"
#define MP3_FILE_PREFIX         "mp3"
#define CFG_FILE_PREFIX         "ttk"
#define LST_FILE_PREFIX         "tkpl"
#define EXE_FILE_PREFIX         "exe"
#define XML_FILE_PREFIX         "xml"
#define SET_FILE_PREFIX         "stk"

#define TTS_FILE                TTK_STRCAT(DOT, TTS_FILE_PREFIX)
#define SKN_FILE                TTK_STRCAT(DOT, SKN_FILE_PREFIX)
#define JPG_FILE                TTK_STRCAT(DOT, JPG_FILE_PREFIX)
#define BMP_FILE                TTK_STRCAT(DOT, BMP_FILE_PREFIX)
#define PNG_FILE                TTK_STRCAT(DOT, PNG_FILE_PREFIX)
#define LRC_FILE                TTK_STRCAT(DOT, LRC_FILE_PREFIX)
#define KRC_FILE                TTK_STRCAT(DOT, KRC_FILE_PREFIX)
#define MP3_FILE                TTK_STRCAT(DOT, MP3_FILE_PREFIX)
#define CFG_FILE                TTK_STRCAT(DOT, CFG_FILE_PREFIX)
#define LST_FILE                TTK_STRCAT(DOT, LST_FILE_PREFIX)
#define EXE_FILE                TTK_STRCAT(DOT, EXE_FILE_PREFIX)
#define XML_FILE                TTK_STRCAT(DOT, XML_FILE_PREFIX)
#define SET_FILE                TTK_STRCAT(DOT, SET_FILE_PREFIX)

#define MAKENETS                "avnets.sh"
#define LISTPATH                "download.tkpl"
#define COFIGPATH               "downloadconfig.xml"
#define HISTORYPATH             "downloadhistory.ttk"

///////////////////////////////////////
#define APPDATA_DIR_FULL        DownloadObject::getAppDir() + QString("../") + APPDATA_DIR
#define DOWNLOADS_DIR_FULL      DownloadObject::getAppDir() + QString("../") + DOWNLOADS_DIR

#define TEMPORARY_DIR_FULL      DOWNLOADS_DIR_FULL + TEMPORARY_DIR
#define CACHE_DIR_FULL          DOWNLOADS_DIR_FULL + CACHE_DIR
#define UPDATE_DIR_FULL         DOWNLOADS_DIR_FULL + UPDATE_DIR
#define TDDOWNLOAD_DIR_FULL     DOWNLOADS_DIR_FULL + TDDOWNLOAD_DIR

#define MAKENETS_FULL           APPDATA_DIR_FULL + MAKENETS
#define LISTPATH_FULL           APPDATA_DIR_FULL + LISTPATH
#define COFIGPATH_FULL          APPDATA_DIR_FULL + COFIGPATH
#define HISTORYPATH_FULL        APPDATA_DIR_FULL + HISTORYPATH
#define AVATAR_DIR_FULL         APPDATA_DIR_FULL + AVATAR_DIR
#define USER_THEME_DIR_FULL     APPDATA_DIR_FULL + USER_THEME_DIR

#define THEME_DIR_FULL          DownloadObject::getAppDir() + THEME_DIR
#define LANGUAGE_DIR_FULL       DownloadObject::getAppDir() + LANGUAGE_DIR

///////////////////////////////////////
#define WINDOW_WIDTH_MIN        1000
#define WINDOW_HEIGHT_MIN       690
///////////////////////////////////////
#define DEFAULT_INDEX_LEVEL0    -1
#define DEFAULT_INDEX_LEVEL1    -999
#define DEFAULT_INDEX_LEVEL2    -888
#define DEFAULT_INDEX_LEVEL3    -777
#define DEFAULT_INDEX_LEVEL4    -666
#define DEFAULT_INDEX_LEVEL5    -555
///////////////////////////////////////
#define STRING_SPLITER          "*|||*"
///////////////////////////////////////

/*! @brief The namespace of the application object.
 * @author Greedysky <greedysky@163.com>
 */
namespace DownloadObject
{
    /*!
     * Get application dir.
     */
    static QString getAppDir()
    {
        return QCoreApplication::applicationDirPath() + "/";
    }

}

#endif // DOWNLOADOBJECT_H
