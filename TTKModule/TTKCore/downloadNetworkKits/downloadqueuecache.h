#ifndef DOWNLOADQUEUECACHE_H
#define DOWNLOADQUEUECACHE_H

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

#include "downloadthreadabstract.h"

/*! @brief The class of the download queue data.
 * @author Greedysky <greedysky@163.com>
 */
typedef struct DOWNLOAD_NETWORK_EXPORT DownloadQueueData
{
    QString m_url;        ///*download url*/
    QString m_savePath;   ///*save local path*/
}DownloadQueueData;
TTK_DECLARE_LISTS(DownloadQueueData)

/*! @brief The class to download data from cache queue.
 * @author Greedysky <greedysky@163.com>
 */
class DOWNLOAD_NETWORK_EXPORT DownloadQueueCache : public DownLoadThreadAbstract
{
    Q_OBJECT
public:
    /*!
     * Object contsructor.
     */
    explicit DownloadQueueCache(Download_Type type, QObject *parent = 0);

    /*!
     * Object contsructor.
     */
    DownloadQueueCache(const DownloadQueueData &data,
                            Download_Type type, QObject *parent = 0);
    /*!
     * Object contsructor.
     */
    DownloadQueueCache(const DownloadQueueDatas &datas,
                            Download_Type type, QObject *parent = 0);

    ~DownloadQueueCache();

    /*!
     * Get class object name.
     */
    static QString getClassName();

    /*!
     * Add image download url and save path to download queue.
     */
    void addImageQueue(const DownloadQueueDatas &datas);
    /*!
     * Start to download data.
     */
    virtual void startToDownload() override;
    /*!
     * Abort current download thread.
     */
    void abort();

public Q_SLOTS:
    /*!
     * Download data from net finished.
     */
    virtual void downLoadFinished() override;
    /*!
     * Download received data ready.
     */
    void readyReadSlot();
    /*!
     * Download reply error.
     */
    void errorSlot(QNetworkReply::NetworkError code);

protected:
    /*!
     * Start to download data from url.
     */
    void startDownload(const QString &url);
    /*!
     * Start to download data in order.
     */
    void startOrderImageQueue();

    bool m_isDownload, m_isAbort;
    QList<DownloadQueueData> m_imageQueue;
    QNetworkRequest *m_request;

};

#endif // DOWNLOADQUEUECACHE_H
