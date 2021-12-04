#ifndef DOWNLOADREMOTEWIDGET_H
#define DOWNLOADREMOTEWIDGET_H

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

#include "downloadabstractmovewidget.h"

/*! @brief The class of the desktop remote widget base.
 * @author Greedysky <greedysky@163.com>
 */
class TTK_MODULE_EXPORT DownloadRemoteWidget : public DownloadAbstractMoveWidget
{
    Q_OBJECT
    TTK_DECLARE_MODULE(DownloadRemoteWidget)
public:
    /*!
     * Object contsructor.
     */
    explicit DownloadRemoteWidget(QWidget *parent = nullptr);
    ~DownloadRemoteWidget();

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
