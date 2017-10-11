#ifndef DOWNLOADEXTRACTWRAP_H
#define DOWNLOADEXTRACTWRAP_H

/* =================================================
 * This file is part of the TTK Downloader project
 * Copyright (c) 2016 - 2017 Greedysky Studio
 * All rights reserved!
 * Redistribution and use of the source code or any derivative
 * works are strictly forbiden.
   =================================================*/

#include "downloadglobaldefine.h"

struct DownloadBackgroundImage;

/*! @brief The class of the extract data wrap.
 * @author Greedysky <greedysky@163.com>
 */
class DOWNLOAD_CORE_EXPORT DownloadExtractWrap
{
public:
    /*!
     * Get class object name.
     */
    static QString getClassName();

    /*!
     * Transfer file to image data.
     */
    static bool outputThunderSkin(QPixmap &image, const QString &path);

    /*!
     * Transfer file to image data.
     */
    static bool outputSkin(DownloadBackgroundImage *image, const QString &path);
    /*!
     * Transfer image data to file.
     */
    static bool inputSkin(DownloadBackgroundImage *image, const QString &path);

    /*!
     * Transfer file to data.
     */
    static bool outputText(QByteArray &data, const QString &path);
    /*!
     * Transfer data to file.
     */
    static bool inputText(const QByteArray &data, const QString &path);

};

#endif // DOWNLOADEXTRACTWRAP_H
