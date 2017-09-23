#ifndef DOWNLOADRUNOBJECT_H
#define DOWNLOADRUNOBJECT_H

/* =================================================
 * This file is part of the TTK Downloader project
 * Copyright (c) 2016 - 2017 Greedysky Studio
 * All rights reserved!
 * Redistribution and use of the source code or any derivative
 * works are strictly forbiden.
   =================================================*/

#include <QDebug>
#include "downloadprivate.h"
#include "downloadrunglobaldefine.h"

class DownloadRunObjectPrivate;

/*! @brief The class of the download run object.
 * @author Greedysky <greedysky@163.com>
 */
class DOWNLOAD_RUN_EXPORT DownloadRunObject : public QObject
{
    Q_OBJECT
public:
    /*!
     * Object contsructor.
     */
    explicit DownloadRunObject(QObject *parent = 0);

    /*!
     * Check current setting file's validation.
     */
    void checkValid();
    /*!
     * To run main window.
     */
    void run(int argc, char **argv);

private Q_SLOTS:
    /*!
     * Run finished.
     */
    void finished(int code);

private:
   DOWNLOAD_DECLARE_PRIVATE(DownloadRunObject)

};

#endif // DOWNLOADRUNOBJECT_H
