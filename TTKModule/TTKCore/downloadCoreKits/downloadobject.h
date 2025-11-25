#ifndef DOWNLOADOBJECT_H
#define DOWNLOADOBJECT_H

/***************************************************************************
 * This file is part of the TTK Downloader project
 * Copyright (C) 2015 - 2025 Greedysky Studio

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

#include <QDir>

#include "ttkqtglobal.h"
#include "ttkqtobject.h"

#define TKF_FILE_SUFFIX         "tkf"
#define TKX_FILE_SUFFIX         "tkx"
#define TKM_FILE_SUFFIX         "tkm"
#define TKB_FILE_SUFFIX         "tkb"
//
#define SKN_FILE_SUFFIX         "skn"
#define JPG_FILE_SUFFIX         "jpg"
#define XML_FILE_SUFFIX         "xml"
#define STK_FILE_SUFFIX         "stk"
// playlist ext
#define TPL_FILE_SUFFIX         "tkpl"


#define TKF_FILE                TTK_STR_CAT(TTK_DOT, TKF_FILE_SUFFIX)
#define TKX_FILE                TTK_STR_CAT(TTK_DOT, TKX_FILE_SUFFIX)
#define TKM_FILE                TTK_STR_CAT(TTK_DOT, TKM_FILE_SUFFIX)
#define TKB_FILE                TTK_STR_CAT(TTK_DOT, TKB_FILE_SUFFIX)
//
#define SKN_FILE                TTK_STR_CAT(TTK_DOT, SKN_FILE_SUFFIX)
#define JPG_FILE                TTK_STR_CAT(TTK_DOT, JPG_FILE_SUFFIX)
#define XML_FILE                TTK_STR_CAT(TTK_DOT, XML_FILE_SUFFIX)
#define STK_FILE                TTK_STR_CAT(TTK_DOT, STK_FILE_SUFFIX)
#define TPL_FILE                TTK_STR_CAT(TTK_DOT, TPL_FILE_SUFFIX)


#define APPDATA_DIR             TTK_STR_CAT("AppData", TTK_SEPARATOR)
#define APPCACHE_DIR            TTK_STR_CAT("AppCache", TTK_SEPARATOR)
//
#define LANGUAGE_DIR            TTK_STR_CAT("GLanguage", TTK_SEPARATOR)
#define THEME_DIR               TTK_STR_CAT("GTheme", TTK_SEPARATOR)
//
#define TDDOWNLOAD_DIR          TTK_STR_CAT("TDDOWNLOAD", TTK_SEPARATOR)
#define USER_THEME_DIR          TTK_STR_CAT("theme", TTK_SEPARATOR)


#define TRAFFIC_PATH            "avnets"
#define LIST_PATH               TTK_STR_CAT("list", TPL_FILE)
#define COFIG_PATH              TTK_STR_CAT("config", XML_FILE)
#define HISTORY_PATH            TTK_STR_CAT("history", TKF_FILE)
#define RECYCLE_PATH            TTK_STR_CAT("recycle", TKF_FILE)


#define MAIN_DIR_FULL           TTK::applicationPath() + TTK_PARENT_DIR
//
#ifdef Q_OS_WIN
#  define TDDOWNLOAD_DIR_FULL   MAIN_DIR_FULL + TDDOWNLOAD_DIR
#else
#  define TDDOWNLOAD_DIR_FULL   QDir::homePath() + TTK_STR_CAT("/.cache/", TTK_APP_NAME, TTK_SEPARATOR) + TDDOWNLOAD_DIR
#endif
#define APPDATA_DIR_FULL        TTK::configPath() + APPDATA_DIR
#define APPCACHE_DIR_FULL       TTK::configPath() + APPCACHE_DIR


#define TRAFFIC_PATH_FULL       APPDATA_DIR_FULL + TRAFFIC_PATH
#define LIST_PATH_FULL          APPDATA_DIR_FULL + LIST_PATH
#define COFIG_PATH_FULL         APPDATA_DIR_FULL + COFIG_PATH
#define HISTORY_PATH_FULL       APPDATA_DIR_FULL + HISTORY_PATH
#define RECYCLE_PATH_FULL       APPDATA_DIR_FULL + RECYCLE_PATH
#define USER_THEME_DIR_FULL     APPDATA_DIR_FULL + USER_THEME_DIR

#define THEME_DIR_FULL          TTK::applicationPath() + THEME_DIR
#define LANGUAGE_DIR_FULL       TTK::applicationPath() + LANGUAGE_DIR


#define WINDOW_WIDTH_MIN        1000
#define WINDOW_HEIGHT_MIN       690


/*! @brief The namespace of the application object.
 * @author Greedysky <greedysky@163.com>
 */
namespace TTK
{
    enum class DownloadState
    {
        Queue = 0, /*!< Download queue state */
        Wait,      /*!< Download wait state */
        Download,  /*!< Download download state */
        Pause,     /*!< Download pause state */
        Stop,      /*!< Download stop state */
        Finish,    /*!< Download finish state */
        Error      /*!< Download error state */
    };

    /*!
     * Get application config dir.
     */
    inline static QString configPath()
    {
#ifdef Q_OS_WIN
        return QString::fromLocal8Bit(qgetenv("APPDATA")) + "/ttkdl/";
#else
        return QDir::homePath() + "/.config/ttkdl/";
#endif
    }
}

#endif // DOWNLOADOBJECT_H
