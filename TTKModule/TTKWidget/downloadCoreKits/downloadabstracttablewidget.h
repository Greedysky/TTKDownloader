#ifndef DOWNLOADABSTRACTTABLEWIDGET_H
#define DOWNLOADABSTRACTTABLEWIDGET_H

/***************************************************************************
 * This file is part of the TTK Downloader project
 * Copyright (C) 2015 - 2023 Greedysky Studio

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

#include "downloaduiobject.h"
#include "ttkabstracttablewidget.h"

/*! @brief The class of the table widget base.
 * @author Greedysky <greedysky@163.com>
 */
class TTK_MODULE_EXPORT DownloadAbstractTableWidget : public TTKAbstractTableWidget
{
    Q_OBJECT
    TTK_DECLARE_MODULE(DownloadAbstractTableWidget)
public:
    /*!
     * Object constructor.
     */
    explicit DownloadAbstractTableWidget(QWidget *parent = nullptr);

};

#endif // DOWNLOADABSTRACTTABLEWIDGET_H
