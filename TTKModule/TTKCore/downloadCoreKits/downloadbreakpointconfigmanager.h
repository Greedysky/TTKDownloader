#ifndef DOWNLOADBREAKPOINTCONFIGMANAGER_H
#define DOWNLOADBREAKPOINTCONFIGMANAGER_H

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

#include "downloadobject.h"
#include "ttkabstractxml.h"

/*! @brief The class of the break point item.
 * @author Greedysky <greedysky@163.com>
 */
struct TTK_MODULE_EXPORT DownloadBreakPointItem
{
    QString m_url;
    qint64 m_start;
    qint64 m_end;
    qint64 m_ready;

    DownloadBreakPointItem() noexcept
        : m_start(0),
          m_end(0),
          m_ready(0)
    {

    }

    inline bool isEmpty() const noexcept
    {
        return m_start == 0 && m_end == 0 && m_ready == 0;
    }
};
TTK_DECLARE_LIST(DownloadBreakPointItem);

/*! @brief The class of the break point config manager.
 * @author Greedysky <greedysky@163.com>
 */
class TTK_MODULE_EXPORT DownloadBreakPointConfigManager : public TTKAbstractXml, public TTKAbstractReadWriteInterface<DownloadBreakPointItemList>
{
public:
    /*!
     * Object constructor.
     */
    DownloadBreakPointConfigManager();

    /*!
     * Read datas from buffer.
     */
    virtual bool readBuffer(DownloadBreakPointItemList &items) override final;
    /*!
     * Write datas into buffer.
     */
    virtual bool writeBuffer(const DownloadBreakPointItemList &items) override final;

};

#endif // DOWNLOADBREAKPOINTCONFIGMANAGER_H
