#ifndef DOWNLOADSOURCETHREAD_H
#define DOWNLOADSOURCETHREAD_H

/* =================================================
 * This file is part of the TTK Downloader project
 * Copyright (C) 2015 - 2020 Greedysky Studio

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

#include "downloadnetworkabstract.h"

/*! @brief The class of source data download thread.
 * @author Greedysky <greedysky@163.com>
 */
class DOWNLOAD_NETWORK_EXPORT DownloadSourceThread : public DownloadNetworkAbstract
{
    Q_OBJECT
public:
    /*!
     * Object contsructor.
     */
    explicit DownloadSourceThread(QObject *parent = 0);

    ~DownloadSourceThread();

    /*!
     * Get class object name.
     */
    static QString getClassName();
    /*!
     * Start to download data.
     */
    void startToDownload(const QString &url);

Q_SIGNALS:
    /*!
     * Send download byte data from net.
     */
    void downLoadByteDataChanged(const QByteArray &data);

public Q_SLOTS:
    /*!
     * Download data from net finished.
     */
    virtual void downLoadFinished() override;
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

};

#endif // DOWNLOADSOURCETHREAD_H
