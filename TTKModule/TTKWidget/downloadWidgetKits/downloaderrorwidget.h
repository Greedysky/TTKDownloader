#ifndef DOWNLOADERRORWIDGET_H
#define DOWNLOADERRORWIDGET_H

/***************************************************************************
 * This file is part of the TTK Downloader project
 * Copyright (C) 2015 - 2025 Greedysky Studio

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

#include "downloadbasewidget.h"

/*! @brief The class of the download error widget.
 * @author Greedysky <greedysky@163.com>
 */
class TTK_MODULE_EXPORT DownloadErrorWidget : public DownloadBaseWidget
{
    Q_OBJECT
public:
    /*!
     * Object constructor.
     */
    explicit DownloadErrorWidget(QWidget *parent = nullptr);

private:
    /*!
     * Override the widget event.
     */
    virtual void contextMenuEvent(QContextMenuEvent *event) override final;

};

#endif // DOWNLOADERRORWIDGET_H
