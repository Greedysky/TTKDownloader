#ifndef DOWNLOADUNITS_H
#define DOWNLOADUNITS_H

/* =================================================
 * This file is part of the TTK Downloader project
 * Copyright (c) 2016 - 2017 Greedysky Studio
 * All rights reserved!
 * Redistribution and use of the source code or any derivative
 * works are strictly forbiden.
   =================================================*/

#include "downloadglobaldefine.h"

class DownloadThreadManager;
class DownloadListItemWidget;

/*! @brief The class of download thread manager.
 * @author Greedysky <greedysky@163.com>
 */
class DOWNLOAD_NETWORK_EXPORT DownloadUnits : public QObject
{
    Q_OBJECT
public:
    /*!
     * Object contsructor.
     */
    explicit DownloadUnits(const QString &url, QObject *parent = 0);

    ~DownloadUnits();

    /*!
     * Get class object name.
     */
    static QString getClassName();
    /*!
     * Get download list item widget.
     */
    DownloadListItemWidget* getDownloadItemWidget();

    /*!
     * Pause to download.
     */
    void pause();
    /*!
     * Start to download.
     */
    void start();

    /*!
     * Get download state.
     */
    int getState() const;
    /*!
     * Get download url.
     */
    inline QString getUrl() const { return m_url; }
    /*!
     * Set download state changed.
     */
    void setStateChanged(const QString &state);

Q_SIGNALS:
    /*!
     * Remove current item widget.
     */
    void removeItemWidget(DownloadUnits *unit);

private Q_SLOTS:
    /*!
     * Download finished.
     */
    void downloadingFinished();

protected:
    QString m_url;
    bool m_pause;
    DownloadListItemWidget* m_downloadItem;
    DownloadThreadManager* m_downloadThread;

};

#endif // DOWNLOADUNITS_H
