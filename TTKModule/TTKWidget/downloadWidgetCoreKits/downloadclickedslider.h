#ifndef DOWNLOADCLICKEDSLIDER_H
#define DOWNLOADCLICKEDSLIDER_H

/* =================================================
 * This file is part of the TTK Downloader project
 * Copyright (c) 2016 - 2017 Greedysky Studio
 * All rights reserved!
 * Redistribution and use of the source code or any derivative
 * works are strictly forbiden.
   =================================================*/

#include <QSlider>
#include "downloadglobaldefine.h"

/*! @brief The class of the slider that can clicked any position.
 * @author Greedysky <greedysky@163.com>
 */
class DOWNLOAD_WIDGET_EXPORT DownloadClickedSlider : public QSlider
{
    Q_OBJECT
public:
    /*!
     * Object contsructor.
     */
    explicit DownloadClickedSlider(QWidget *parent = 0);
    explicit DownloadClickedSlider(Qt::Orientation orientation, QWidget *parent = 0);

    /*!
     * Get class object name.
     */
    static QString getClassName();

protected:
    /*!
     * Override the widget event.
     */
    virtual bool event(QEvent *event) override;
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;

protected:
    int m_value;
    bool m_mousePress;

};

#endif // DOWNLOADCLICKEDSLIDER_H
