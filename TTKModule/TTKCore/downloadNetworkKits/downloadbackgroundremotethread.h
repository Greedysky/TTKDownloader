#ifndef DOWNLOADBACKGROUNDREMOTETHREAD_H
#define DOWNLOADBACKGROUNDREMOTETHREAD_H

/* =================================================
 * This file is part of the TTK Downloader project
 * Copyright (C) 2015 - 2019 Greedysky Studio

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

#include "downloadabstractxml.h"

/*! @brief The class of the remote skin item.
 * @author Greedysky <greedysky@163.com>
 */
typedef struct DOWNLOAD_NETWORK_EXPORT DownloadSkinRemoteItem
{
    QString m_name;
    QString m_url;
    int m_useCount;

    DownloadSkinRemoteItem()
    {
        m_name = "Greedysky";
        m_useCount = 8888;
    }

    bool isValid() const
    {
        return !(m_name.isEmpty() && m_useCount == 0);
    }

}DownloadSkinRemoteItem;
DOWNLOAD_DECLARE_LISTS(DownloadSkinRemoteItem)

/*! @brief The class of the remote skin item group.
 * @author Greedysky <greedysky@163.com>
 */
typedef struct DOWNLOAD_NETWORK_EXPORT DownloadSkinRemoteGroup
{
    QString m_group;
    DownloadSkinRemoteItems m_items;

    bool isValid() const
    {
        return !(m_group.isEmpty() && m_items.isEmpty());
    }

}DownloadSkinRemoteGroup;
DOWNLOAD_DECLARE_LISTS(DownloadSkinRemoteGroup)


/*! @brief The class of the remote skin XML Config Manager.
 * @author Greedysky <greedysky@163.com>
 */
class DOWNLOAD_NETWORK_EXPORT DownloadSkinRemoteConfigManager : public DownloadAbstractXml
{
    Q_OBJECT
public:
    /*!
     * Object contsructor.
     */
    explicit DownloadSkinRemoteConfigManager(QObject *parent = 0);

    /*!
     * Get class object name.
     */
    static QString getClassName();

    /*!
     * Read datas into xml file.
     */
    void readSkinRemoteXMLConfig(DownloadSkinRemoteGroups &items);

};


/*! @brief The class of download skin remote background.
 * @author Greedysky <greedysky@163.com>
 */
class DOWNLOAD_NETWORK_EXPORT DownloadBackgroundRemoteThread : public QObject
{
    Q_OBJECT
public:
    /*!
     * Object contsructor.
     */
    explicit DownloadBackgroundRemoteThread(QObject *parent = 0);

    /*!
     * Get class object name.
     */
    static QString getClassName();

    /*!
     * Start to download data from net.
     */
    void startToDownload();

Q_SIGNALS:
    /*!
     * Send download data from net.
     */
    void downLoadDataChanged(const DownloadSkinRemoteGroups &data);

public Q_SLOTS:
    /*!
     * Download data from net finished.
     */
    void downLoadDataFinished(const QByteArray &bytes);

};

#endif // DOWNLOADBACKGROUNDREMOTETHREAD_H
