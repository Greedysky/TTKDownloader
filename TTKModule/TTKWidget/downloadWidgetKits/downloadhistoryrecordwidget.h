#ifndef DOWNLOADHISTORYRECORDWIDGET_H
#define DOWNLOADHISTORYRECORDWIDGET_H

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

#include "downloadabstracttablewidget.h"
#include "downloadrecordconfigmanager.h"

/*! @brief The class of the download record widget.
 * @author Greedysky <greedysky@163.com>
 */
class TTK_MODULE_EXPORT DownloadHistoryRecordWidget : public DownloadAbstractTableWidget
{
    Q_OBJECT
    TTK_DECLARE_MODULE(DownloadHistoryRecordWidget)
public:
    explicit DownloadHistoryRecordWidget(QWidget *parent = nullptr);
    ~DownloadHistoryRecordWidget();

    /*!
     * Init widget.
     */
    void init();
    /*!
     * Clear All Items.
     */
    void clearAllItems();
    /*!
     * Resize window bound by widgte resize called.
     */
    void resizeWindow();

public Q_SLOTS:
    /*!
     * Reverse select.
     */
    void reverseSelect();
    /*!
     * Table widget list cell click.
     */
    void listCellClicked(int row, int column);
    /*!
     * Create download item from download path.
     */
    void createDownloadItem(const QString &path, const QString &url);
    /*!
     * Delete selected item from list.
     */
    void deleteItemFromList();
    /*!
     * Delete selected item from list.
     */
    void deleteItemFromList(bool file);
    /*!
     * Delete selected item from list with file.
     */
    void deleteItemFromListWithFile();
    /*!
     * Open the local path.
     */
    void openFileDir();
    /*!
     * Copy url context.
     */
    void copyUrlClicked();

protected:
    /*!
     * Override the widget event.
     */
    virtual void contextMenuEvent(QContextMenuEvent *event) override final;
    /*!
     * Create item by index and name and size and time.
     */
    void createItem(int index, const DownloadRecord &record);

    DownloadRecordList m_records;
    int m_loadRecordCount;

};

#endif // DOWNLOADHISTORYRECORDWIDGET_H
