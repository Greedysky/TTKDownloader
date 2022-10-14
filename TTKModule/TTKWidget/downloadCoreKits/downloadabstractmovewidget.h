#ifndef DOWNLOADABSTRACTMOVEWIDGET_H
#define DOWNLOADABSTRACTMOVEWIDGET_H

/***************************************************************************
 * This file is part of the TTK Downloader project
 * Copyright (C) 2015 - 2022 Greedysky Studio

 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License along
 * with this program; If not, see <http://www.gnu.org/licenses/>.
 ***************************************************************************/

#include <QLabel>
#include <QMouseEvent>
#include "ttkglobaldefine.h"

/*! @brief The class of the moving widget base.
 * @author Greedysky <greedysky@163.com>
 */
class TTK_MODULE_EXPORT DownloadAbstractMoveWidget : public QWidget
{
    Q_OBJECT
    TTK_DECLARE_MODULE(DownloadAbstractMoveWidget)
public:
    /*!
     * Object contsructor.
     */
    explicit DownloadAbstractMoveWidget(QWidget *parent = nullptr);
    /*!
     * Object contsructor.
     */
    explicit DownloadAbstractMoveWidget(bool transparent, QWidget *parent = nullptr);
    ~DownloadAbstractMoveWidget();

    /*!
     * Set or not draw window bound shadow.
     */
    inline void drawWindowShadow(bool show) { m_showShadow = show;}
    /*!
     * Set or not block widget moving.
     */
    inline void blockMoveOption(bool block) { m_moveOption = block;}
    /*!
     * Set background label.
     */
    inline void setBackgroundLabel(QLabel *label) { m_background = label; }

public Q_SLOTS:
    /*!
     * Background image changed.
     */
    void backgroundChanged();
    /*!
     * Override show function.
     */
    void show();

protected:
    /*!
     * Override the widget event.
     */
    virtual void paintEvent(QPaintEvent *event) override;
    virtual void mousePressEvent(QMouseEvent *event) override final;
    virtual void mouseMoveEvent(QMouseEvent *event) override final;
    virtual void mouseReleaseEvent(QMouseEvent *event) override final;
    /*!
     * Set background pixmap.
     */
    void setBackgroundPixmap(const QSize &size);

    QPoint m_pressAt;
    bool m_moveOption, m_showShadow;
    bool m_leftButtonPress;
    QLabel *m_background;

};


/*! @brief The class of the moving widget single without ui widget.
 * @author Greedysky <greedysky@163.com>
 */
class TTK_MODULE_EXPORT DownloadAbstractMoveSingleWidget : public DownloadAbstractMoveWidget
{
    Q_OBJECT
    TTK_DECLARE_MODULE(DownloadAbstractMoveSingleWidget)
public:
    /*!
     * Object contsructor.
     */
    explicit DownloadAbstractMoveSingleWidget(QWidget *parent = nullptr);
    /*!
     * Object contsructor.
     */
    explicit DownloadAbstractMoveSingleWidget(bool transparent, QWidget *parent = nullptr);
    ~DownloadAbstractMoveSingleWidget();

protected:
    QWidget *m_container;

};

#endif // DOWNLOADABSTRACTMOVEWIDGET_H
