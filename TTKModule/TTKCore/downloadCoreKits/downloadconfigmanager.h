#ifndef DOWNLOADCONFIGMANAGER_H
#define DOWNLOADCONFIGMANAGER_H

/***************************************************************************
 * This file is part of the TTK Downloader project
 * Copyright (C) 2015 - 2024 Greedysky Studio

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

/*! @brief The class of the xml config manager.
 * @author Greedysky <greedysky@163.com>
 */
class TTK_MODULE_EXPORT DownloadConfigManager : public TTKAbstractXml, public TTKAbstractReadWriteInterface<int>
{
    TTK_DECLARE_MODULE(DownloadConfigManager)
public:
    /*!
     * Object constructor.
     */
    DownloadConfigManager();

    /*!
     * Read datas from buffer.
     */
    bool readBuffer();
    /*!
     * Write datas into buffer.
     */
    bool writeBuffer();

    /*!
     * Read window widget Geometry Config.
     */
    QRect readWindowGeometry() const;

private:
    /*!
     * Read datas from buffer.
     */
    virtual bool readBuffer(int &items) override final;
    /*!
     * Write datas into buffer.
     */
    virtual bool writeBuffer(const int &items) override final;

};

#endif // DOWNLOADCONFIGMANAGER_H
