#ifndef DOWNLOADHISTORYRECORDWIDGET_H
#define DOWNLOADHISTORYRECORDWIDGET_H

/* =================================================
 * This file is part of the TTK Downloader project
 * Copyright (c) 2016 - 2017 Greedysky Studio
 * All rights reserved!
 * Redistribution and use of the source code or any derivative
 * works are strictly forbiden.
   =================================================*/

#include "downloadabstracttablewidget.h"
#include "downloadrecordconfigmanager.h"

/*! @brief The class of the download record widget.
 * @author Greedysky <greedysky@163.com>
 */
class DOWNLOAD_WIDGET_EXPORT DownloadHistoryRecordWidget : public DownloadAbstractTableWidget
{
    Q_OBJECT
public:
    explicit DownloadHistoryRecordWidget(QWidget *parent = 0);

    virtual ~DownloadHistoryRecordWidget();

    /*!
     * Get class object name.
     */
    static QString getClassName();

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
    virtual void contextMenuEvent(QContextMenuEvent *event) override;
    /*!
     * Create item by index and name and size and time.
     */
    void createItem(int index, const DownloadRecord &record);

    DownloadRecords m_records;
    int m_loadRecordCount;

};

#endif // DOWNLOADHISTORYRECORDWIDGET_H
