#ifndef DOWNLOADURLENCODER_H
#define DOWNLOADURLENCODER_H

/* =================================================
 * This file is part of the TTK Downloader project
 * Copyright (C) 2015 - 2019 Greedysky Studio

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

#include "downloadglobaldefine.h"

class QProcess;

/*! @brief The class of the network url encoder and decoder.
 * @author Greedysky <greedysky@163.com>
 */
class DOWNLOAD_NETWORK_EXPORT DownloadUrlEncoder : public QObject
{
    Q_OBJECT
public:
    /*!
     * Object contsructor.
     */
    explicit DownloadUrlEncoder(QObject *parent = 0);

    /*!
     * Get class object name.
     */
    static QString getClassName();
    /*!
     * Decode url.
     */
    QString decoder(const QString &url);

};

#endif // DOWNLOADURLENCODER_H
