#ifndef DOWNLOADTHREADABSTRACT_H
#define DOWNLOADTHREADABSTRACT_H

/* =================================================
 * This file is part of the TTK Downloader project
 * Copyright (C) 2015 - 2021 Greedysky Studio

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

#include <QFile>
#include <QTimer>
#include "downloadobject.h"
#include "downloadnetworkabstract.h"
#include "downloadnumberdefine.h"

/*! @brief The class of abstract downloading data.
 * @author Greedysky <greedysky@163.com>
 */
class TTK_MODULE_EXPORT DownLoadThreadAbstract : public DownloadNetworkAbstract
{
    Q_OBJECT
    TTK_DECLARE_MODULE(DownLoadThreadAbstract)
public:
    /*!
     * Object contsructor provide download URL\ save local path and download type.
     */
    DownLoadThreadAbstract(const QString &url, const QString &save, QObject *parent = nullptr);

    virtual ~DownLoadThreadAbstract();

    /*!
     * Release the network object.
     */
    virtual void deleteAll() override;

    /*!
     * Start to download data.
     * Subclass should implement this function.
     */
    virtual void startToDownload() = 0;

public Q_SLOTS:
    /*!
     * Get download received and total data.
     */
    virtual void downloadProgress(qint64 bytesReceived, qint64 bytesTotal);
    /*!
     * Download reply error.
     */
    virtual void replyError(QNetworkReply::NetworkError error) override;
#ifndef QT_NO_SSL
    /*!
     * Download ssl reply error.
     */
    virtual void sslErrors(QNetworkReply *reply, const QList<QSslError> &errors) override;
#endif
    /*!
     * Updata download speed due the user mod the net speed limited.
     */
    virtual void updateDownloadSpeed();

protected:
    QFile *m_file;
    QString m_url, m_savePathName;
    qint64 m_hasReceived, m_currentReceived, m_totalSize;
    QTimer m_timer;

};

#endif // DOWNLOADTHREADABSTRACT_H
