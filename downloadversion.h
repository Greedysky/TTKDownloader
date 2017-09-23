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
 * Copyright (c) 2016 - 2017 Greedysky Studio
 * All rights reserved!
 * Redistribution and use of the source code or any derivative
 * works are strictly forbiden.
   =================================================*/

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

