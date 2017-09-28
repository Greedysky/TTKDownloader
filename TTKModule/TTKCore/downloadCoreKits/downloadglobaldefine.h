#ifndef DOWNLOADGLOBALDEFINE_H
#define DOWNLOADGLOBALDEFINE_H

/* =================================================
 * This file is part of the TTK Downloader project
 * Copyright (c) 2016 - 2017 Greedysky Studio
 * All rights reserved!
 * Redistribution and use of the source code or any derivative
 * works are strictly forbiden.
   =================================================*/

#include <QtCore/qglobal.h>

//////////////////////////////////////
#ifdef DOWNLOAD_LIBRARY
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

//////////////////////////////////////
///load logger
#include "downloadlogger.h"

#endif // DOWNLOADGLOBALDEFINE_H
