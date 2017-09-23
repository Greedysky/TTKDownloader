#ifndef DOWNLOADAPPLICATIONOBJECT_H
#define DOWNLOADAPPLICATIONOBJECT_H

/* =================================================
 * This file is part of the TTK Downloader project
 * Copyright (c) 2016 - 2017 Greedysky Studio
 * All rights reserved!
 * Redistribution and use of the source code or any derivative
 * works are strictly forbiden.
   =================================================*/

#include "downloadobject.h"
#include "downloadglobaldefine.h"

/*! @brief The class of the app object widget.
 * @author Greedysky <greedysky@163.com>
 */
class DOWNLOAD_GUI_EXPORT DownloadApplicationObject : public QObject
{
    Q_OBJECT
public:
    /*!
     * Object contsructor.
     */
    explicit DownloadApplicationObject(QObject *parent = 0);

    virtual ~DownloadApplicationObject();

    /*!
     * Get class object name.
     */
    static QString getClassName();

    /*!
     * Get class object instance.
     */
    static DownloadApplicationObject *instance();

private:
    /*!
     * Something temp clean up.
     */
    void cleanUp();

    static DownloadApplicationObject *m_instance;
};

#endif // DOWNLOADAPPLICATIONOBJECT_H
