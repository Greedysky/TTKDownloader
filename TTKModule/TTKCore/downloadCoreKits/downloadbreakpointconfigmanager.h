#ifndef DOWNLOADBREAKPOINTCONFIGMANAGER_H
#define DOWNLOADBREAKPOINTCONFIGMANAGER_H

/* =================================================
 * This file is part of the TTK Downloader project
 * Copyright (C) 2015 - 2017 Greedysky Studio

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

/*! @brief The class of the break point item.
 * @author Greedysky <greedysky@163.com>
 */
typedef struct DOWNLOAD_CORE_EXPORT DownloadBreakPointItem
{
    QString m_url;
    qint64 m_start;
    qint64 m_end;
    qint64 m_ready;

    DownloadBreakPointItem()
    {
        m_start = 0;
        m_end = 0;
        m_ready = 0;
    }

    bool isEmpty() const
    {
        return m_start == 0 && m_end == 0 && m_ready == 0;
    }
}DownloadBreakPointItem;
DOWNLOAD_DECLARE_LISTS(DownloadBreakPointItem)

/*! @brief The class of the break point config manager.
 * @author Greedysky <greedysky@163.com>
 */
class DOWNLOAD_CORE_EXPORT DownloadBreakPointConfigManager : public DownloadAbstractXml
{
    Q_OBJECT
public:
    /*!
     * Object contsructor.
     */
    explicit DownloadBreakPointConfigManager(QObject *parent = 0);

    /*!
     * Get class object name.
     */
    static QString getClassName();

    /*!
     * Write datas into xml file.
     */
    void writeBreakPointConfig(const DownloadBreakPointItems &records);
    /*!
     * Read datas into xml file.
     */
    void readBreakPointConfig(DownloadBreakPointItems &records);

};

#endif // DOWNLOADBREAKPOINTCONFIGMANAGER_H
