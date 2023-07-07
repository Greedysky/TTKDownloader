#ifndef DOWNLOADABSTRACTNETWORK_H
#define DOWNLOADABSTRACTNETWORK_H

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

#include <QNetworkReply>
#include <QSslConfiguration>

#include "downloadnetworkdefines.h"
#include "downloadalgorithmutils.h"

/*! @brief The class of the abstract downloading data.
 * @author Greedysky <greedysky@163.com>
 */
class TTK_MODULE_EXPORT DownloadAbstractNetwork : public QObject
{
    Q_OBJECT
    TTK_DECLARE_MODULE(DownloadAbstractNetwork)
public:
    /*!
     * Object contsructor.
     */
    explicit DownloadAbstractNetwork(QObject *parent = nullptr);
    ~DownloadAbstractNetwork();

    /*!
     * Release the network object.
     */
    virtual void deleteAll();

    /*!
     * Set the current raw data.
     */
    inline void setHeader(const QString &key, const QVariant &value) { m_rawData[key] = value; }
    /*!
     * Get the current raw data.
     */
    inline const QVariant header(const QString &key) const { return m_rawData[key]; }

Q_SIGNALS:
    /*!
     * Send download data from net.
     */
    void downLoadDataChanged(const QString &bytes);
    /*!
     * Send download raw data changed.
     */
    void downLoadRawDataChanged(const QByteArray &bytes);

public Q_SLOTS:
    /*!
     * Download data from net finished.
     * Subclass should implement this function.
     */
    virtual void downLoadFinished() = 0;
    /*!
     * Download reply error.
     */
    virtual void replyError(QNetworkReply::NetworkError error);
#ifndef QT_NO_SSL
    /*!
     * Download ssl reply error.
     */
    virtual void sslErrors(QNetworkReply *reply, const QList<QSslError> &errors);
    /*!
     * Download ssl reply error strings.
     */
    void sslErrorsString(QNetworkReply *reply, const QList<QSslError> &errors);
#endif

protected:
    QVariantMap m_rawData;
    volatile TTK::NetworkCode m_stateCode;
    QNetworkReply *m_reply;
    QNetworkAccessManager m_manager;

};

/*! @brief The namespace of the application object.
 * @author Greedysky <greedysky@163.com>
 */
namespace TTK
{
    /*!
     * Set request ssl configuration.
     */
    TTK_MODULE_EXPORT void setSslConfiguration(QNetworkRequest *request, QSslSocket::PeerVerifyMode mode = QSslSocket::VerifyNone);

}

#endif // DOWNLOADABSTRACTNETWORK_H
