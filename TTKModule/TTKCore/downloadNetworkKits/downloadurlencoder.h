#ifndef DOWNLOADURLENCODER_H
#define DOWNLOADURLENCODER_H

/* =================================================
 * This file is part of the TTK Music Player project
 * Copyright (c) 2015 - 2017 Greedysky Studio
 * All rights reserved!
 * Redistribution and use of the source code or any derivative
 * works are strictly forbiden.
   =================================================*/

#include "downloadglobaldefine.h"

class QProcess;

/*! @brief The class of the network url encoder and decoder.
 * @author Greedysky <greedysky@163.com>
 */
class DOWNLOAD_NETWORK_EXPORT DownloadUrlEncoder : public QObject
{
    Q_OBJECT
public:
    /*!
     * Object contsructor.
     */
    explicit DownloadUrlEncoder(QObject *parent = 0);

    /*!
     * Get class object name.
     */
    static QString getClassName();
    /*!
     * Decode url.
     */
    QString decoder(const QString &url);

};

#endif // DOWNLOADURLENCODER_H
