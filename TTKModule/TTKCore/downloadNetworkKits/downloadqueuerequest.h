#ifndef DOWNLOADQUEUEREQUEST_H
#define DOWNLOADQUEUEREQUEST_H

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

#include "downloadabstractrequest.h"

/*! @brief The class of the download queue data.
 * @author Greedysky <greedysky@163.com>
 */
struct TTK_MODULE_EXPORT DownloadQueueData
{
    QString m_url;    ///*download url*/
    QString m_path;   ///*save local path*/
};
TTK_DECLARE_LIST(DownloadQueueData);


/*! @brief The class of the download data from queue request.
 * @author Greedysky <greedysky@163.com>
 */
class TTK_MODULE_EXPORT DownloadQueueRequest : public DownLoadAbstractRequest
{
    Q_OBJECT
public:
    /*!
     * Object constructor.
     */
    explicit DownloadQueueRequest(QObject *parent = nullptr);
    DownloadQueueRequest(const DownloadQueueData &data, QObject *parent = nullptr);
    DownloadQueueRequest(const DownloadQueueDataList &datas, QObject *parent = nullptr);
    /*!
     * Object destructor.
     */
    ~DownloadQueueRequest();

    /*!
     * Add download url and save path to download queue.
     */
    void addQueue(const DownloadQueueDataList &datas);
    /*!
     * Start to download data.
     */
    virtual void startToRequest() override final;

    /*!
     * Abort current download thread.
     */
    void abort();
    /*!
     * Clear image download url queue.
     */
    void clear();

public Q_SLOTS:
    /*!
     * Download data from net finished.
     */
    virtual void downLoadFinished() override final;
    /*!
     * Download received data ready.
     */
    void handleReadyRead();
    /*!
     * Download reply error.
     */
    void handleError(QNetworkReply::NetworkError code);

private:
    /*!
     * Start to download data from url.
     */
    void startDownload(const QString &url);
    /*!
     * Start to download data in order.
     */
    void startOrderQueue();

    bool m_isDownload, m_isAbort;
    DownloadQueueDataList m_queue;
    QNetworkRequest *m_request;

};

#endif // DOWNLOADQUEUEREQUEST_H
