#ifndef DOWNLOADCONSOLEOBJECT_H
#define DOWNLOADCONSOLEOBJECT_H

/***************************************************************************
 * This file is part of the TTK Downloader project
 * Copyright (C) 2015 - 2022 Greedysky Studio

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

#include <QCoreApplication>
#include "downloadobject.h"
#include "ttkglobaldefine.h"

class DownloadThreadManager;

/*! @brief The class of the download console object.
 * @author Greedysky <greedysky@163.com>
 */
class TTK_MODULE_EXPORT DownloadConsoleObject : public QObject
{
    Q_OBJECT
public:
    /*!
     * Object contsructor.
     */
    explicit DownloadConsoleObject(QObject *parent = nullptr);
    ~DownloadConsoleObject();

    /*!
     * Init all parameter.
     */
    bool initialize(const QCoreApplication &app) const;

public Q_SLOTS:
    /*!
     * Download progress changed.
     */
    void progressChanged(qint64 current, qint64 total);

protected:
    DownloadThreadManager *m_manager;

};

#endif // DOWNLOADCONSOLEOBJECT_H
