#ifndef DOWNLOADQUEUECACHE_H
#define DOWNLOADQUEUECACHE_H

/* =================================================
 * This file is part of the TTK Downloader project
 * Copyright (c) 2016 - 2017 Greedysky Studio
 * All rights reserved!
 * Redistribution and use of the source code or any derivative
 * works are strictly forbiden.
   =================================================*/

#include "downloadthreadabstract.h"

/*! @brief The class of the download queue data.
 * @author Greedysky <greedysky@163.com>
 */
typedef struct DOWNLOAD_NETWORK_EXPORT DownloadQueueData
{
    QString m_url;        ///*download url*/
    QString m_savePath;   ///*save local path*/
}DownloadQueueData;
DOWNLOAD_DECLARE_LISTS(DownloadQueueData)

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
