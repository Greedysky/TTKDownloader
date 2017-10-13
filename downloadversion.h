#ifndef DOWNLOADVERSION_H
#define DOWNLOADVERSION_H

/**
 * C
 *
 * opyright (c) 2016 - 2017 Greedysky Studio <greedysky@163.com>
 *
 * TTKDownloader that imitation xunlei downloader, based on Qt for windows. 
 */

/** \mainpage
 *
 * \section encoding Attention
 * 
 *
 */
 
/* =================================================
 * This file is part of the TTK Downloader project
 * Copyright (C) 2015 - 2017 Greedysky Studio

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

//update time 2017.09.21
#define DOWNLOAD_VERSION_STR    "1.0.0.0"
#define DOWNLOAD_VERSION_WSTR   L"1.0.0.0"
#define DOWNLOAD_VER_TIME_STR   "(2017/09/21)"

#define DOWNLOAD_MAJOR_VERSION 1
#define DOWNLOAD_MIDLE_VERSION 0
#define DOWNLOAD_MINOR_VERSION 0
#define DOWNLOAD_PATCH_VERSION 0

#define DOWNLOAD_VERSION 0x01000

#define DOWNLOAD_VERSION_CHECK(major, middle, minor, patch) ((major<<12)|(middle<<8)|(minor<<4)|(patch))


#endif // DOWNLOADVERSION_H

