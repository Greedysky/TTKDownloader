#ifndef DOWNLOADBACKGROUNDREMOTETHREAD_H
#define DOWNLOADBACKGROUNDREMOTETHREAD_H

/***************************************************************************
 * This file is part of the TTK Downloader project
 * Copyright (C) 2015 - 2026 Greedysky Studio

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

#include "ttkabstractxml.h"

/*! @brief The class of the remote skin item.
 * @author Greedysky <greedysky@163.com>
 */
struct TTK_MODULE_EXPORT DownloadSkinRemoteItem
{
    QString m_name;
    QString m_url;
    int m_useCount;

    DownloadSkinRemoteItem() noexcept
        : m_name("Greedysky"),
          m_useCount(8888)
    {

    }

    inline bool isValid() const noexcept
    {
        return !(m_name.isEmpty() && m_useCount == 0);
    }
};
TTK_DECLARE_LIST(DownloadSkinRemoteItem);

/*! @brief The class of the remote skin item group.
 * @author Greedysky <greedysky@163.com>
 */
struct TTK_MODULE_EXPORT DownloadSkinRemoteGroup
{
    QString m_group;
    DownloadSkinRemoteItemList m_items;

    inline bool isValid() const noexcept
    {
        return !(m_group.isEmpty() && m_items.isEmpty());
    }
};
TTK_DECLARE_LIST(DownloadSkinRemoteGroup);


/*! @brief The class of the thunder skin XML Config Manager.
 * @author Greedysky <greedysky@163.com>
 */
class TTK_MODULE_EXPORT DownloadThunderSkinConfigManager : public TTKAbstractXml, public TTKAbstractReadInterface<DownloadSkinRemoteGroupList>
{
public:
    /*!
     * Object constructor.
     */
    DownloadThunderSkinConfigManager();

    /*!
     * Read datas from buffer.
     */
    virtual bool readBuffer(DownloadSkinRemoteGroupList &items) override final;

};


/*! @brief The class of the download thunder skin background.
 * @author Greedysky <greedysky@163.com>
 */
class TTK_MODULE_EXPORT DownloadThunderSkinRequest : public QObject
{
    Q_OBJECT
public:
    /*!
     * Object constructor.
     */
    explicit DownloadThunderSkinRequest(QObject *parent = nullptr);

    /*!
     * Start to download data from net.
     */
    void startToRequest();

Q_SIGNALS:
    /*!
     * Send download data from net.
     */
    void downLoadDataChanged(const DownloadSkinRemoteGroupList &bytes);

public Q_SLOTS:
    /*!
     * Download data from net finished.
     */
    void downLoadFinished(const QByteArray &bytes);

};

#endif // DOWNLOADBACKGROUNDREMOTETHREAD_H
