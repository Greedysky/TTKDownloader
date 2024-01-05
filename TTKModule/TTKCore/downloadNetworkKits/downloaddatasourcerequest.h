#ifndef DOWNLOADDATASOURCEREQUEST_H
#define DOWNLOADDATASOURCEREQUEST_H

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

#include "downloadabstractnetwork.h"

/*! @brief The class of the data source download request.
 * @author Greedysky <greedysky@163.com>
 */
class TTK_MODULE_EXPORT DownloadDataSourceRequest : public DownloadAbstractNetwork
{
    Q_OBJECT
    TTK_DECLARE_MODULE(DownloadDataSourceRequest)
public:
    /*!
     * Object constructor.
     */
    explicit DownloadDataSourceRequest(QObject *parent = nullptr);

    /*!
     * Release the network object.
     */
    virtual void deleteAll() override final;

    /*!
     * Start to download data.
     */
    void startToRequest(const QString &url);

public Q_SLOTS:
    /*!
     * Download data from net finished.
     */
    virtual void downLoadFinished() override final;

};

#endif // DOWNLOADDATASOURCEREQUEST_H
