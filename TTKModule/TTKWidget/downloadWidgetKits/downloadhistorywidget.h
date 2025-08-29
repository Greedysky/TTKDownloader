#ifndef DOWNLOADHISTORYWIDGET_H
#define DOWNLOADHISTORYWIDGET_H

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

#include "downloadabstracttablewidget.h"
#include "downloadrecordconfigmanager.h"

/*! @brief The class of the download history widget.
 * @author Greedysky <greedysky@163.com>
 */
class TTK_MODULE_EXPORT DownloadHistoryWidget : public DownloadAbstractTableWidget
{
    Q_OBJECT
public:
    /*!
     * Object constructor.
     */
    explicit DownloadHistoryWidget(QWidget *parent = nullptr);
    /*!
     * Object destructor.
     */
    ~DownloadHistoryWidget();

    /*!
     * Init widget.
     */
    void initialize();
    /*!
     * Resize window bound by widgte resize called.
     */
    void resizeWindow();

    /*!
     * Remove all items.
     */
    virtual void removeItems() override final;

public Q_SLOTS:
    /*!
     * Unselect all items.
     */
    void unselectAll();
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

private:
    /*!
     * Override the widget event.
     */
    virtual void contextMenuEvent(QContextMenuEvent *event) override final;
    /*!
     * Create item by index and name and size and time.
     */
    void addCellItem(int index, const DownloadRecord &record);

    DownloadRecordList m_records;
    int m_loadRecordCount;

};

#endif // DOWNLOADHISTORYWIDGET_H
