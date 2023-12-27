#ifndef DOWNLOADTHREAD_H
#define DOWNLOADTHREAD_H

/***************************************************************************
 * This file is part of the TTK Downloader project
 * Copyright (C) 2015 - 2024 Greedysky Studio

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

#include <QNetworkReply>
#include "ttkmoduleexport.h"

class QFile;

/*! @brief The class of the download thread.
 * @author Greedysky <greedysky@163.com>
 */
class TTK_MODULE_EXPORT DownloadThread : public QObject
{
    Q_OBJECT
    TTK_DECLARE_MODULE(DownloadThread)
public:
    enum class State
    {
        Waiting = 0,   /*!< Download waiting state */
        Download,      /*!< Download download state */
        Pause,         /*!< Download pause state */
        Stop,          /*!< Download stop state */
        Finished       /*!< Download finished state */
    };

    /*!
     * Object constructor.
     */
    explicit DownloadThread(QObject *parent = nullptr);
    /*!
     * Object destructor.
     */
    ~DownloadThread();

    /*!
     * Start to download.
     */
    void startDownload(int index, const QString &url, QFile *file,
                       qint64 startPoint, qint64 endPoint,
                       qint64 readySize = 0);
    /*!
     * Get download url.
     */
    inline QString url() const { return m_url; }
    /*!
     * Get ready size.
     */
    inline qint64 readySize() const { return m_readySize; }
    /*!
     * Get start point(.
     */
    inline qint64 startPoint() const { return m_startPoint; }
    /*!
     * Get end point.
     */
    inline qint64 endPoint() const { return m_endPoint; }

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
    void downLoadFinished();
    /*!
     * Download received data ready.
     */
    void handleReadyRead();
    /*!
     * Download reply error.
     */
    void handleError(QNetworkReply::NetworkError code);

private:
    int m_index;
    QString m_url;
    qint64 m_startPoint, m_endPoint, m_readySize;
    QFile *m_file;
    QNetworkAccessManager *m_manager;
    QNetworkReply *m_reply;
    State m_state;

};

#endif // DOWNLOADTHREAD_H
