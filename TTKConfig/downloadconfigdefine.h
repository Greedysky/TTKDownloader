#ifndef DOWNLOADCONFIGDEFINE_H
#define DOWNLOADCONFIGDEFINE_H

/***************************************************************************
 * This file is part of the TTK Downloader project
 * Copyright (C) 2015 - 2023 Greedysky Studio

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

#include "downloadobject.h"
#include "ttkmoduleexport.h"

//
#define TTK_MAKE_NET_PATH_FULL   MAKE_NET_PATH_FULL
#define TTK_LIST_PATH_FULL       LIST_PATH_FULL
#define TTK_COFIG_PATH_FULL      COFIG_PATH_FULL
#define TTK_HISTORY_PATH_FULL    HISTORY_PATH_FULL
#define TTK_USER_THEME_DIR_FULL  USER_THEME_DIR_FULL
//
#define TTK_THEME_DIR_FULL       TTK::applicationPath() + THEME_DIR
#define TTK_LANGUAGE_DIR_FULL    TTK::applicationPath() + LANGUAGE_DIR

#ifdef Q_OS_WIN
#  define TTK_SERVICE_FULL       TTK::applicationPath() + SERVICE_EXE_NAME
#else
#  define TTK_ROUTINE_FULL       TTK::applicationPath() + TTK_PDIR + "TTKRoutine.sh"
#  define TTK_DOWNLOADER_FULL    TTK::applicationPath() + TTK_PDIR + APP_SHL_NAME
#  define TTK_CONSOLE_FULL       TTK::applicationPath() + "TTKConsole.sh"
#  define TTK_INIT_FULL          TTK::applicationPath() + "TTKInit.sh"
#  define TTK_SERVICE_FULL       TTK::applicationPath() + SERVICE_SHL_NAME
#  define TTK_ROUTINECOPY_FULL   TTK::applicationPath() + "TTKRoutineCopy.sh"
#endif

#endif // DOWNLOADCONFIGDEFINE_H
