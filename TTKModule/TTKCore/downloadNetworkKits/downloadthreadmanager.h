#ifndef DOWNLOADTHREADMANAGER_H
#define DOWNLOADTHREADMANAGER_H

/* =================================================
 * This file is part of the TTK Downloader project
 * Copyright (c) 2016 - 2017 Greedysky Studio
 * All rights reserved!
 * Redistribution and use of the source code or any derivative
 * works are strictly forbiden.
   =================================================*/

#include "downloadthread.h"

#define THREADCOUNT 3

/*! @brief The class of download thread manager.
 * @author Greedysky <greedysky@163.com>
 */
class DOWNLOAD_NETWORK_EXPORT DownloadThreadManager : public QObject
{
    Q_OBJECT
public:
    /*!
     * Object contsructor.
     */
    explicit DownloadThreadManager(QObject *parent = 0);

    ~DownloadThreadManager();

    /*!
     * Get class object name.
     */
    static QString getClassName();
    /*!
     * Download file by url.
     */
    bool downloadFile(const QString &url);
    /*!
     * Get download state.
     */
    inline DownloadThread::DownloadState getState() const { return m_state; }

Q_SIGNALS:
    /*!
     * Download finished.
     */
    void downloadingFinished();
    /*!
     * Download state changed.
     */
    void stateChanged(const QString &code);
    /*!
     * Download progress changed.
     */
    void progressChanged(qint64 current, qint64 total);
    /*!
     * Update file info changed.
     */
    void updateFileInfoChanged(const QString &name, qint64 size);

public Q_SLOTS:
    /*!
     * Pause to download.
     */
    void pause();
    /*!
     * Restart to download.
     */
    void restart();

private Q_SLOTS:
    /*!
     * Network download finished.
     */
    void finishedSlot(int index);
    /*!
     * Show error code index and string.
     */
    void errorSlot(int index, const QString &errorString);
    /*!
     * Download state changed.
     */
    void progressChangedSlot();

private:
    /*!
     * Download finished.
     */
    void downloadingFinish();
    /*!
     * Get download file size.
     */
    qint64 getFileSize(const QString &url, int tryTimes = 3);

    int m_runningCount;
    QFile *m_file;
    qint64 m_readySize, m_totalSize;
    DownloadThread::DownloadState m_state;
    QList<DownloadThread*> m_threads;

};

#endif // DOWNLOADTHREADMANAGER_H
