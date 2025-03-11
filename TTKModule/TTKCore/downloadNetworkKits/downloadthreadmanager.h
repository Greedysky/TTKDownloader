#ifndef DOWNLOADTHREADMANAGER_H
#define DOWNLOADTHREADMANAGER_H

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

#include "downloadthread.h"

static constexpr int THREADCOUNT = 1;

/*! @brief The class of the download thread manager.
 * @author Greedysky <greedysky@163.com>
 */
class TTK_MODULE_EXPORT DownloadThreadManager : public QObject
{
    Q_OBJECT
    TTK_DECLARE_MODULE(DownloadThreadManager)
public:
    /*!
     * Object constructor.
     */
    explicit DownloadThreadManager(QObject *parent = nullptr);
    /*!
     * Object destructor.
     */
    ~DownloadThreadManager();

    /*!
     * Download file by url.
     */
    bool downloadFile(const QString &url, const QString &name = {});
    /*!
     * Get download path.
     */
    QString downloadedPath() const;
    /*!
     * Get download state.
     */
    inline DownloadThread::State state() const noexcept { return m_state; }

Q_SIGNALS:
    /*!
     * Download item data from net finished.
     */
    void downloadingFinished(const QString &path);
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
    void finished(int index);
    /*!
     * Show error code index and string.
     */
    void handleError(int index, const QString &errorString);
    /*!
     * Download state changed.
     */
    void progressChanged();

private:
    /*!
     * Download data from net finished.
     */
    void downloadingFinish();
    /*!
     * Get download file size.
     */
    qint64 fileSize(QString &url, int tryTimes = 3);

    int m_runningCount;
    QFile *m_file;
    qint64 m_readySize, m_totalSize;
    DownloadThread::State m_state;
    QList<DownloadThread*> m_threads;

};

#endif // DOWNLOADTHREADMANAGER_H
