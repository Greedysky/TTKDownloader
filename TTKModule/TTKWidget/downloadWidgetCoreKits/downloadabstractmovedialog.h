#ifndef DOWNLOADABSTRACTMOVEDIALOG_H
#define DOWNLOADABSTRACTMOVEDIALOG_H

/* =================================================
 * This file is part of the TTK Downloader project
 * Copyright (C) 2015 - 2020 Greedysky Studio

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
 ================================================= */

#include <QLabel>
#include <QDialog>
#include "downloadglobaldefine.h"

/*! @brief The class of the moving dialog base.
 * @author Greedysky <greedysky@163.com>
 */
class DOWNLOAD_WIDGET_EXPORT DownloadAbstractMoveDialog : public QDialog
{
    Q_OBJECT
public:
    /*!
     * Object contsructor.
     */
    explicit DownloadAbstractMoveDialog(QWidget *parent = nullptr);
    /*!
     * Object contsructor.
     */
    explicit DownloadAbstractMoveDialog(bool transparent, QWidget *parent = nullptr);

    virtual ~DownloadAbstractMoveDialog();

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

#endif // DOWNLOADABSTRACTMOVEDIALOG_H
