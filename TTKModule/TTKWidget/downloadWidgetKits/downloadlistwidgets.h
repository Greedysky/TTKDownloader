#ifndef DOWNLOADLISTWIDGETS_H
#define DOWNLOADLISTWIDGETS_H

/* =================================================
 * This file is part of the TTK Downloader project
 * Copyright (c) 2016 - 2017 Greedysky Studio
 * All rights reserved!
 * Redistribution and use of the source code or any derivative
 * works are strictly forbiden.
   =================================================*/

#include "downloadabstracttablewidget.h"

class DownloadUnits;

/*! @brief The class of the download list widget.
 * @author Greedysky <greedysky@163.com>
 */
class DOWNLOAD_WIDGET_EXPORT DownloadListWidgets : public DownloadAbstractTableWidget
{
    Q_OBJECT
public:
    /*!
     * Object contsructor.
     */
    explicit DownloadListWidgets(QWidget *parent = 0);

    virtual ~DownloadListWidgets();

    /*!
     * Init widget.
     */
    void init();
    /*!
     * Get class object name.
     */
    static QString getClassName();
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
     * Table widget list cell click.
     */
    virtual void listCellClicked(int row, int column) override;
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

protected:
    /*!
     * Override the widget event.
     */
    virtual void contextMenuEvent(QContextMenuEvent *event) override;
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
    void start(int row, const QString &name = QString());
    /*!
     * Pause to download.
     */
    void pause(int row);
    /*!
     * Get top url to download.
     */
    void getTopUrlToDownload();
    /*!
     * Find url if it exists.
     */
    bool findUrl(const QString &path) const;

    int m_maxDownloadCount;
    QList<DownloadUnits*> m_itemList;

};

#endif // DOWNLOADLISTWIDGETS_H
