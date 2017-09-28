#ifndef DOWNLOADREMOTEWIDGET_H
#define DOWNLOADREMOTEWIDGET_H

/* =================================================
 * This file is part of the TTK Downloader project
 * Copyright (c) 2016 - 2017 Greedysky Studio
 * All rights reserved!
 * Redistribution and use of the source code or any derivative
 * works are strictly forbiden.
   =================================================*/

#include "downloadabstractmovewidget.h"

/*! @brief The class of the desktop remote widget base.
 * @author Greedysky <greedysky@163.com>
 */
class DOWNLOAD_REMOTE_EXPORT DownloadRemoteWidget : public DownloadAbstractMoveWidget
{
    Q_OBJECT
public:
    /*!
     * Object contsructor.
     */
    explicit DownloadRemoteWidget(QWidget *parent = 0);

    virtual ~DownloadRemoteWidget();

    /*!
     * Get class object name.
     */
    static QString getClassName();

public Q_SLOTS:
    /*!
     * Set value.
     */
    void setValue(int value);
    /*!
     * Override show function.
     */
    void show();

protected:
    /*!
     * Adjust the widget postion.
     */
    void adjustPostion(QWidget *w);
    /*!
     * Override the widget event.
     */
    virtual void contextMenuEvent(QContextMenuEvent *event) override;
    virtual void paintEvent(QPaintEvent *event) override;

    int m_value;

};

#endif // DOWNLOADREMOTEWIDGET_H
