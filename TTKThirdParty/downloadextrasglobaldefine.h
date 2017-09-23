#ifndef DOWNLOADEXTRASGLOBALDEFINE_H
#define DOWNLOADEXTRASGLOBALDEFINE_H

/* =================================================
 * This file is part of the TTK Downloader project
 * Copyright (c) 2016 - 2017 Greedysky Studio
 * All rights reserved!
 * Redistribution and use of the source code or any derivative
 * works are strictly forbiden.
   =================================================*/

#include "downloadglobal.h"

//////////////////////////////////////
///exoprt
///
///
#define DOWNLOAD_EXPORT

#ifdef DOWNLOAD_EXPORT
#  define DOWNLOAD_EXTRAS_EXPORT Q_DECL_EXPORT
#else
#  define DOWNLOAD_EXTRAS_IMPORT Q_DECL_IMPORT
#endif

#endif // DOWNLOADEXTRASGLOBALDEFINE_H
