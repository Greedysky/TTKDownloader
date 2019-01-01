#ifndef DOWNLOADLICENSECORE_H
#define DOWNLOADLICENSECORE_H

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

#include <QObject>
#include "downloadglobaldefine.h"

/*! @brief The class of the license core module.
 * @author Greedysky <greedysky@163.com>
 */
class DOWNLOAD_CORE_EXPORT DownloadLicenseCore : public QObject
{
    Q_OBJECT
public:
    /*!
     * Object contsructor.
     */
    explicit DownloadLicenseCore(QObject *parent = 0);

    /*!
     * Check license string.
     */
    bool checkLicense(const QString &str);
    /*!
     * Get characteristic string.
     */
    QString getCharacteristicString();
    /*!
     * Get characteristic normal string.
     */
    QString getCharacteristicStringNormal();
    /*!
     * Get encode key.
     */
    QString getEncodeKey(const QString &key);

private:
    /*!
     * Get characteristic strings.
     */
    QStringList getCharacteristicStrings();
    /*!
     * Get hmac in sha1.
     */
    QByteArray hmacSha1(const QByteArray &data, const QByteArray &key);
    /*!
     * Split hmac string.
     */
    QString splitString(const QByteArray &data, const QByteArray &key);

};

#endif // DOWNLOADLICENSECORE_H
