#ifndef DOWNLOADLICENSECORE_H
#define DOWNLOADLICENSECORE_H

/* =================================================
 * This file is part of the TTK Downloader project
 * Copyright (c) 2016 - 2017 Greedysky Studio
 * All rights reserved!
 * Redistribution and use of the source code or any derivative
 * works are strictly forbiden.
   =================================================*/

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
