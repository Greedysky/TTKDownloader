#ifndef DOWNLOADBACKGROUNDCONFIGMANAGER_H
#define DOWNLOADBACKGROUNDCONFIGMANAGER_H

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

#include <QPixmap>
#include "downloadobject.h"
#include "ttkabstractxml.h"

/*! @brief The class of the skin config item.
 * @author Greedysky <greedysky@163.com>
 */
struct TTK_MODULE_EXPORT DownloadSkinConfigItem
{
    QString m_name;
    int m_useCount;

    DownloadSkinConfigItem() noexcept
        : m_name("Greedysky"),
          m_useCount(8888)
    {

    }

    inline bool isValid() const noexcept
    {
        return !(m_name.isEmpty() && m_useCount == 0);
    }
};

/*! @brief The class of the skin backgroud image item.
 * @author Greedysky <greedysky@163.com>
 */
struct TTK_MODULE_EXPORT DownloadBackgroundImage
{
    QPixmap m_pix;
    DownloadSkinConfigItem m_item;

    inline bool isValid() const noexcept
    {
        return !m_pix.isNull() && m_item.isValid();
    }
};


/*! @brief The class of the skin XML Config Manager.
 * @author Greedysky <greedysky@163.com>
 */
class TTK_MODULE_EXPORT DownloadSkinConfigManager : public TTKAbstractXml, public TTKAbstractReadWriteInterface<DownloadSkinConfigItem>
{
    TTK_DECLARE_MODULE(DownloadSkinConfigManager)
public:
    /*!
     * Object constructor.
     */
    DownloadSkinConfigManager();

    /*!
     * Read datas from buffer.
     */
    virtual bool readBuffer(DownloadSkinConfigItem &items) override final;
    /*!
     * Write datas into buffer.
     */
    virtual bool writeBuffer(const DownloadSkinConfigItem &items) override final;

};

#endif // DOWNLOADBACKGROUNDCONFIGMANAGER_H
