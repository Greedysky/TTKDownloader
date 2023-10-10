#ifndef DOWNLOADCONFIGMANAGER_H
#define DOWNLOADCONFIGMANAGER_H

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

/*! @brief The class of the xml config manager.
 * @author Greedysky <greedysky@163.com>
 */
class TTK_MODULE_EXPORT DownloadConfigManager : public TTKXmlDocument
{
    Q_OBJECT
    TTK_DECLARE_MODULE(DownloadConfigManager)
public:
    /*!
     * Object constructor.
     */
    explicit DownloadConfigManager(QObject *parent = nullptr);

    /*!
     * Read datas from config file.
     */
    void readBuffer() const;
    /*!
     * Write datas into config file.
     */
    void writeBuffer();

    /*!
     * Read window widget Geometry Config.
     */
    QRect readWindowGeometry() const;

};

#endif // DOWNLOADCONFIGMANAGER_H
