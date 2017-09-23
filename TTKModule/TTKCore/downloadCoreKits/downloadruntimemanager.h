#ifndef DOWNLOADRUNTIMEMANAGER_H
#define DOWNLOADRUNTIMEMANAGER_H

/* =================================================
 * This file is part of the TTK Downloader project
 * Copyright (c) 2016 - 2017 Greedysky Studio
 * All rights reserved!
 * Redistribution and use of the source code or any derivative
 * works are strictly forbiden.
   =================================================*/

#include "downloadglobaldefine.h"

/*! @brief The class of the app run time needed.
 * @author Greedysky <greedysky@163.com>
 */
class DOWNLOAD_CORE_EXPORT DownloadRunTimeManager
{
public:
    /*!
     * Object contsructor.
     */
    DownloadRunTimeManager();

    /*!
     * Get class object name.
     */
    static QString getClassName();

    /*!
     * Run.
     */
    void run() const;

    /*!
     * Get translator path.
     */
    QString translator() const;

};

#endif // DOWNLOADRUNTIMEMANAGER_H
