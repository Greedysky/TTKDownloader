#ifndef DOWNLOADLISTWIDGETS_H
#define DOWNLOADLISTWIDGETS_H

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

#include <QTimer>
#include "downloadabstracttablewidget.h"

class DownloadUnits;

/*! @brief The class of the download list widget.
 * @author Greedysky <greedysky@163.com>
 */
class TTK_MODULE_EXPORT DownloadListWidgets : public DownloadAbstractTableWidget
{
    Q_OBJECT
    TTK_DECLARE_MODULE(DownloadListWidgets)
public:
    /*!
     * Object constructor.
     */
    explicit DownloadListWidgets(QWidget *parent = nullptr);
    /*!
     * Object destructor.
     */
    ~DownloadListWidgets();

    /*!
     * Init widget.
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
    void downloadingFinished(const QString &path, const QString &url);

public Q_SLOTS:
    /*!
     * Reverse select.
     */
    void reverseSelect();
    /*!
     * Pause to download.
     */
    void pause();
    /*!
     * Start to download.
     */
    void start();
    /*!
     * Downlaod url changed.
     */
    void addItemToList(const QString &path, const QString &name);
    /*!
     * Downlaod url changed.
     */
    void addItemToList(const QStringList &path);
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

private:
    /*!
     * Override the widget event.
     */
    virtual void contextMenuEvent(QContextMenuEvent *event) override final;
    /*!
     * Clear download item.
     */
    void clearItems();
    /*!
     * Download state changed.
     */
    void stateChanged(int row);
    /*!
     * Start to download.
     */
    void start(int row, const QString &name = {});
    /*!
     * Pause to download.
     */
    void pause(int row);
    /*!
     * Get top url to download.
     */
    void topUrlToDownload();
    /*!
     * Find url if it exists.
     */
    bool findUrl(const QString &path) const;

    QTimer m_speedTimer;
    int m_maxDownloadCount;
    QList<DownloadUnits*> m_itemList;

};

#endif // DOWNLOADLISTWIDGETS_H
