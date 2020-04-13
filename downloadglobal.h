#ifndef DOWNLOADGLOBAL_H
#define DOWNLOADGLOBAL_H

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

#include "ttkglobal.h"

///
#ifndef DOWNLOAD_NAMESPACE
#define DOWNLOAD_NAMESPACE DOWNLOAD
#endif //DOWNLOAD_NAMESPACE

#if !TTK_QT_VERSION_CHECK(4,5,0)
#define DOWNLOAD_NO_NAMESPACE_SUPPORT
#endif

#ifndef DOWNLOAD_NO_NAMESPACE_SUPPORT
#define DOWNLOAD_BEGIN_NAMESPACE namespace DOWNLOAD_NAMESPACE {
#define DOWNLOAD_END_NAMESPACE }
#define DOWNLOAD_USE_NAMESPACE using namespace ::DOWNLOAD_NAMESPACE;
#else
#define DOWNLOAD_BEGIN_NAMESPACE
#define DOWNLOAD_END_NAMESPACE
#define DOWNLOAD_USE_NAMESPACE
#endif //DOWNLOAD_NAMESPACE_SUPPORT

#endif // DOWNLOADGLOBAL_H
