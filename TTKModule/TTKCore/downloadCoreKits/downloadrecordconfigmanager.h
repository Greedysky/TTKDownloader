#ifndef DOWNLOADRECORDCONFIGMANAGER_H
#define DOWNLOADRECORDCONFIGMANAGER_H

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

#include "downloadobject.h"
#include "ttkabstractxml.h"

/*! @brief The class of the local download record item.
 * @author Greedysky <greedysky@163.com>
 */
struct TTK_MODULE_EXPORT DownloadRecord
{
    QString m_time;
    QString m_path;
    QString m_size;
    QString m_url;
};
TTK_DECLARE_LIST(DownloadRecord);

/*! @brief The class of the download record manager.
 * @author Greedysky <greedysky@163.com>
 */
class TTK_MODULE_EXPORT DownloadRecordConfigManager : public TTKXmlDocument, public TTKAbstractReadWriteInterface<DownloadRecordList>
{
    Q_OBJECT
    TTK_DECLARE_MODULE(DownloadRecordConfigManager)
public:
    /*!
     * Object constructor.
     */
    explicit DownloadRecordConfigManager(QObject *parent = nullptr);

    /*!
     * Read datas from buffer.
     */
    virtual bool readBuffer(DownloadRecordList &items) override final;
    /*!
     * Write datas into buffer.
     */
    virtual bool writeBuffer(const DownloadRecordList &items) override final;

};

#endif // DOWNLOADRECORDCONFIGMANAGER_H
