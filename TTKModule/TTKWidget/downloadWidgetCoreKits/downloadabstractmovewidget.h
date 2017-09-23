#ifndef DOWNLOADABSTRACTMOVEWIDGET_H
#define DOWNLOADABSTRACTMOVEWIDGET_H

/* =================================================
 * This file is part of the TTK Downloader project
 * Copyright (c) 2016 - 2017 Greedysky Studio
 * All rights reserved!
 * Redistribution and use of the source code or any derivative
 * works are strictly forbiden.
   =================================================*/

#include <QLabel>
#include <QMouseEvent>
#include "downloadglobaldefine.h"

/*! @brief The class of the moving widget base.
 * @author Greedysky <greedysky@163.com>
 */
class DOWNLOAD_WIDGET_EXPORT DownloadAbstractMoveWidget : public QWidget
{
    Q_OBJECT
public:
    /*!
     * Object contsructor.
     */
    explicit DownloadAbstractMoveWidget(QWidget *parent = 0);
    /*!
     * Object contsructor.
     */
    explicit DownloadAbstractMoveWidget(bool transparent, QWidget *parent = 0);

    virtual ~DownloadAbstractMoveWidget();

    /*!
     * Get class object name.
     */
    static QString getClassName();
    /*!
     * Set or not draw window bound shadow.
     */
    inline void drawWindowShadow(bool show) { m_showShadow = show;}
    /*!
     * Set or not block widget moving.
     */
    inline void blockMoveOption(bool block) { m_moveOption = block;}

public Q_SLOTS:
    /*!
     * Background image changed.
     */
    void backgroundChanged();

protected:
    /*!
     * Override the widget event.
     */
    virtual void paintEvent(QPaintEvent *event) override;
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;
    /*!
     * Set background pixmap.
     */
    void setBackgroundPixmap(QLabel *label, const QSize &size);
    /*!
     * Set background pixmap.
     */
    void setBackgroundPixmap(const QSize &size);

    QPoint m_pressAt;
    bool m_moveOption, m_showShadow;
    bool m_leftButtonPress;
    QWidget *m_background;

};


/*! @brief The class of the moving widget single without ui widget.
 * @author Greedysky <greedysky@163.com>
 */
class DOWNLOAD_WIDGET_EXPORT DownloadAbstractMoveSingleWidget : public DownloadAbstractMoveWidget
{
    Q_OBJECT
public:
    /*!
     * Object contsructor.
     */
    explicit DownloadAbstractMoveSingleWidget(QWidget *parent = 0);
    /*!
     * Object contsructor.
     */
    explicit DownloadAbstractMoveSingleWidget(bool transparent, QWidget *parent = 0);

    virtual ~DownloadAbstractMoveSingleWidget();

    /*!
     * Get class object name.
     */
    static QString getClassName();

protected:
    QWidget *m_container;

};

#endif // DOWNLOADABSTRACTMOVEWIDGET_H
