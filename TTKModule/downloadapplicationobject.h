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

class QPropertyAnimation;

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

public Q_SLOTS:
    /*!
     * Window close animation.
     */
    void windowCloseAnimation();
    /*!
     * Show about us widget.
     */
    void appAboutUs();
    /*!
     * Show version update widget.
     */
    void appVersionUpdate();
    /*!
     * Reset current window geometry.
     */
    void appResetWindow();

private:
    /*!
     * Something temp clean up.
     */
    void cleanUp();

    QPropertyAnimation *m_animation;

    static DownloadApplicationObject *m_instance;
};

#endif // DOWNLOADAPPLICATIONOBJECT_H
