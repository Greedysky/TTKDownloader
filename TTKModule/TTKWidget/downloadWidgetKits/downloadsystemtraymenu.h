#ifndef DOWNLOADSYSTEMTRAYMENU_H
#define DOWNLOADSYSTEMTRAYMENU_H

/* =================================================
 * This file is part of the TTK Downloader project
 * Copyright (c) 2016 - 2017 Greedysky Studio
 * All rights reserved!
 * Redistribution and use of the source code or any derivative
 * works are strictly forbiden.
   =================================================*/

#include <QMenu>
#include "downloadglobaldefine.h"

/*! @brief The class of the system tray menu widget.
 * @author Greedysky <greedysky@163.com>
 */
class DOWNLOAD_WIDGET_EXPORT DownloadSystemTrayMenu : public QMenu
{
    Q_OBJECT
public:
    /*!
     * Object contsructor.
     */
    explicit DownloadSystemTrayMenu(QWidget *parent = 0);

    ~DownloadSystemTrayMenu();

    /*!
     * Get class object name.
     */
    static QString getClassName();

protected:
    /*!
     * Override the widget event.
     */
    virtual void showEvent(QShowEvent *event) override;

    QMenu *m_floatMenu;

};

#endif // DOWNLOADSYSTEMTRAYMENU_H
