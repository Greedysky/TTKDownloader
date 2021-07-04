#ifndef DOWNLOADABSTRACTTABLEWIDGET_H
#define DOWNLOADABSTRACTTABLEWIDGET_H

/* =================================================
 * This file is part of the TTK Downloader project
 * Copyright (C) 2015 - 2021 Greedysky Studio

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

#include <QTableWidget>
#include <QHeaderView>

#include "downloaduiobject.h"
#include "ttkglobaldefine.h"

/*! @brief The class of the table widget base.
 * @author Greedysky <greedysky@163.com>
 */
class TTK_MODULE_EXPORT DownloadAbstractTableWidget : public QTableWidget
{
    Q_OBJECT
    TTK_DECLARE_MODULE(DownloadAbstractTableWidget)
public:
    /*!
     * Object contsructor.
     */
    explicit DownloadAbstractTableWidget(QWidget *parent = nullptr);
    virtual ~DownloadAbstractTableWidget();

    /*!
     * Clear current items.
     */
    void clear();

public Q_SLOTS:
    /*!
     * Table widget list cell enter.
     */
    virtual void listCellEntered(int row, int column);
    /*!
     * Table widget list cell click.
     * Subclass should implement this function.
     */
    virtual void listCellClicked(int row, int column) = 0;

protected:
    /*!
     * Set selected item row color.
     */
    void setRowColor(int row, const QColor &color) const;

    QColor m_defaultBkColor;
    int m_previousColorRow;
    int m_previousClickRow;

};

#endif // DOWNLOADABSTRACTTABLEWIDGET_H
