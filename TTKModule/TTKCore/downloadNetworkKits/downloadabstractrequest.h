#ifndef DOWNLOADABSTRACTREQUEST_H
#define DOWNLOADABSTRACTREQUEST_H

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

#include <QFile>
#include <QTimer>

#include "downloadobject.h"
#include "downloadabstractnetwork.h"
#include "ttknumberdefine.h"

/*! @brief The class of the abstract downloading data.
 * @author Greedysky <greedysky@163.com>
 */
class TTK_MODULE_EXPORT DownLoadAbstractRequest : public DownloadAbstractNetwork
{
    Q_OBJECT
    TTK_DECLARE_MODULE(DownLoadAbstractRequest)
public:
    /*!
     * Object constructor.
     */
    DownLoadAbstractRequest(const QString &url, const QString &path, QObject *parent = nullptr);
    /*!
     * Object destructor.
     */
    ~DownLoadAbstractRequest();

    /*!
     * Release the network object.
     */
    virtual void deleteAll() override final;

    /*!
     * Start to download data.
     * Subclass should implement this function.
     */
    virtual void startRequest() = 0;

public Q_SLOTS:
    /*!
     * Download data from net finished.
     */
    virtual void downLoadFinished() override;
    /*!
     * Get download received and total data.
     */
    virtual void downloadProgress(qint64 bytesReceived, qint64 bytesTotal);
    /*!
     * Updata download speed due the user mod the net speed limited.
     */
    virtual void updateDownloadSpeed();

protected:
    QFile *m_file;
    QString m_url;
    qint64 m_hasReceived, m_currentReceived, m_totalSize;
    QTimer m_speedTimer;

};

#endif // DOWNLOADABSTRACTREQUEST_H
