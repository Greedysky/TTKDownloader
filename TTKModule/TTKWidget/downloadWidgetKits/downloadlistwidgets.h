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
    void addItemToList(const QString &path);
    /*!
     * Downlaod url changed.
     */
    void addItemToList(const QStringList &path);
    /*!
     * Delete selected item from list.
     */
    void deleteItemFromList();
    /*!
     * Remove current item widget.
     */
    void removeItemWidget(DownloadUnits *unit);
    /*!
     * Table widget list cell click.
     */
    virtual void listCellClicked(int row, int column) override;

protected:
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
    void start(int row);
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
