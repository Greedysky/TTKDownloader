#ifndef DOWNLOADTHREAD_H
#define DOWNLOADTHREAD_H

/* =================================================
 * This file is part of the TTK Downloader project
 * Copyright (c) 2016 - 2017 Greedysky Studio
 * All rights reserved!
 * Redistribution and use of the source code or any derivative
 * works are strictly forbiden.
   =================================================*/

#include <QNetworkReply>
#include "downloadglobaldefine.h"

class QFile;
class QNetworkAccessManager;

/*! @brief The class of download thread.
 * @author Greedysky <greedysky@163.com>
 */
class DOWNLOAD_NETWORK_EXPORT DownloadThread : public QObject
{
    Q_OBJECT
public:
    enum DownloadState
    {
        D_Waiting = 0,   /*!< Download waiting state */
        D_Download,      /*!< Download download state */
        D_Pause,         /*!< Download pause state */
        D_Stop,          /*!< Download stop state */
        D_Finished       /*!< Download finished state */
    };

    /*!
     * Object contsructor.
     */
    explicit DownloadThread(QObject *parent = 0);

    ~DownloadThread();

    /*!
     * Get class object name.
     */
    static QString getClassName();
    /*!
     * Start to download.
     */
    void startDownload(int index, const QString &url, QFile *file,
                       qint64 startPoint, qint64 endPoint,
                       qint64 readySize = 0);
    /*!
     * Get ready size.
     */
    inline qint64 getReadySize() const { return m_readySize; }

Q_SIGNALS:
    /*!
     * Download finished.
     */
    void finished(int index);
    /*!
     * Show error code index and string.
     */
    void errorCode(int index, const QString &errorString);
    /*!
     * Download state changed.
     */
    void downloadChanged();

public Q_SLOTS:
    /*!
     * Stop to download.
     */
    void stop();
    /*!
     * Restart to download.
     */
    void restart();

private Q_SLOTS:
    /*!
     * Network download finished.
     */
    void finishedSlot();
    /*!
     * Download received data ready.
     */
    void readyReadSlot();
    /*!
     * Download reply error.
     */
    void errorSlot(QNetworkReply::NetworkError code);

private:
    int m_index;
    QString m_url;
    qint64 m_startPoint, m_endPoint, m_readySize;
    QFile *m_file;
    QNetworkAccessManager *m_manager;
    QNetworkReply *m_reply;
    DownloadState m_state;

};

#endif // DOWNLOADTHREAD_H
