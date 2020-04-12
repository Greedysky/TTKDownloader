#ifndef DOWNLOADGLOBALDEFINE_H
#define DOWNLOADGLOBALDEFINE_H

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

#include "downloadglobal.h"

//////////////////////////////////////
#ifdef TTK_LIBRARY
#  define DOWNLOAD_NETWORK
#  define DOWNLOAD_CORE
#  define DOWNLOAD_WIDGET
#  define DOWNLOAD_GUI
#  define DOWNLOAD_UTILS
#  define DOWNLOAD_REMOTE
#endif

//////////////////////////////////////
///exoprt
///
///
#define DOWNLOAD_EXPORT

#ifdef DOWNLOAD_NETWORK
#  ifdef DOWNLOAD_EXPORT
#    define DOWNLOAD_NETWORK_EXPORT Q_DECL_EXPORT
#  else
#    define DOWNLOAD_NETWORK_IMPORT Q_DECL_IMPORT
#  endif
#endif

#ifdef DOWNLOAD_CORE
#  ifdef DOWNLOAD_EXPORT
#    define DOWNLOAD_CORE_EXPORT Q_DECL_EXPORT
#  else
#    define DOWNLOAD_CORE_IMPORT Q_DECL_IMPORT
#  endif
#endif

#ifdef DOWNLOAD_WIDGET
#  ifdef DOWNLOAD_EXPORT
#    define DOWNLOAD_WIDGET_EXPORT Q_DECL_EXPORT
#  else
#    define DOWNLOAD_WIDGET_IMPORT Q_DECL_IMPORT
#  endif
#endif

#ifdef DOWNLOAD_GUI
#  ifdef DOWNLOAD_EXPORT
#    define DOWNLOAD_GUI_EXPORT Q_DECL_EXPORT
#  else
#    define DOWNLOAD_GUI_IMPORT Q_DECL_IMPORT
#  endif
#endif

#ifdef DOWNLOAD_UTILS
#  ifdef DOWNLOAD_EXPORT
#    define DOWNLOAD_UTILS_EXPORT Q_DECL_EXPORT
#  else
#    define DOWNLOAD_UTILS_IMPORT Q_DECL_IMPORT
#  endif
#endif

#ifdef DOWNLOAD_REMOTE
#  ifdef DOWNLOAD_EXPORT
#    define DOWNLOAD_REMOTE_EXPORT Q_DECL_EXPORT
#  else
#    define DOWNLOAD_REMOTE_IMPORT Q_DECL_IMPORT
#  endif
#endif

#endif // DOWNLOADGLOBALDEFINE_H
