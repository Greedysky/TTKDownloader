#ifndef DOWNLOADLISTWIDGET_H
#define DOWNLOADLISTWIDGET_H

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

#include <QTimer>
#include "downloadabstracttablewidget.h"

class DownloadUnits;

/*! @brief The class of the download list widget.
 * @author Greedysky <greedysky@163.com>
 */
class TTK_MODULE_EXPORT DownloadListWidget : public DownloadAbstractTableWidget
{
    Q_OBJECT
public:
    /*!
     * Object constructor.
     */
    explicit DownloadListWidget(QWidget *parent = nullptr);
    /*!
     * Object destructor.
     */
    ~DownloadListWidget();

    /*!
     * Init widget and parameter.
     */
    void initialize();

    /*!
     * Resize window bound by widgte resize called.
     */
    void resizeWindow();

Q_SIGNALS:
    /*!
     * Download state changed.
     */
    void downloadStateChanged(bool);
    /*!
     * Download finished.
     */
    void downloadFinished(const QString &path, const QString &url);
    /*!
     * Deleted file to list finished.
     */
    void deleteFinished(const QString &path, const QString &url);

public Q_SLOTS:
    /*!
     * Unselect all items.
     */
    void unselectAll();
    /*!
     * Pause to download.
     */
    void pause();
    /*!
     * Start to download.
     */
    void start();
    /*!
     * Add downlaod url to item list.
     */
    void addItemToList(const QStringList &urls);
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
     * Remove current item widget.
     */
    void removeItemWidget(DownloadUnits *unit);
    /*!
     * Table widget item cell click.
     */
    virtual void itemCellClicked(int row, int column) override final;
    /*!
     * Open the local path.
     */
    void openFileDir();
    /*!
     * Start to download context.
     */
    void startClicked();
    /*!
     * Pause to download context.
     */
    void pauseClicked();
    /*!
     * Copy url context.
     */
    void copyUrlClicked();

private Q_SLOTS:
    /*!
     * Update total speed label.
     */
    void updateTotalSpeedLabel();
    /*!
     * Item double clicked.
     */
    void itemLeftDoublePressed();

private:
    /*!
     * Override the widget event.
     */
    virtual void contextMenuEvent(QContextMenuEvent *event) override final;
    /*!
     * Add downlaod url to item list.
     */
    void addItemToCacheList(const QString &url, const QString &name);
    /*!
     * Add downlaod url to item list and start.
     */
    void addItemToStartList(const QString &url);
    /*!
     * Clear download item.
     */
    void clearItems();
    /*!
     * Set donwload state.
     */
    void setDownloadState(int row);
    /*!
     * Start to download.
     */
    void start(int row);
    /*!
     * Pause to download.
     */
    void pause(int row);
    /*!
     * Get next url to download.
     */
    void nextUrlToDownload();
    /*!
     * Find url if it exists.
     */
    bool findUrl(const QString &url) const;

    QTimer m_speedTimer;
    int m_maxDownloadCount;
    QList<DownloadUnits*> m_items;

};

#endif // DOWNLOADLISTWIDGET_H
