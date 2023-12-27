#ifndef DOWNLOADNETWORKSPEEDTHREAD_H
#define DOWNLOADNETWORKSPEEDTHREAD_H

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

#include <QThread>
#include <QStringList>
#include "ttkabstractthread.h"

class QProcess;

/*! @brief The class of the network speed thread.
 * @author Greedysky <greedysky@163.com>
 */
class TTK_MODULE_EXPORT DownloadNetworkSpeedThread : public TTKAbstractThread
{
    Q_OBJECT
    TTK_DECLARE_MODULE(DownloadNetworkSpeedThread)
public:
    /*!
     * Object constructor.
     */
    explicit DownloadNetworkSpeedThread(QObject *parent = nullptr);
    /*!
     * Object destructor.
     */
    ~DownloadNetworkSpeedThread();

    /*!
     * Set available newtwork names.
     */
    void setAvailableNewtworkNames(const QStringList &names);
    /*!
     * Get available newtwork names.
     */
    QStringList availableNewtworkNames() const;
    /*!
     * Get newtwork names.
     */
    QStringList newtworkNames() const;

Q_SIGNALS:
    /*!
     * Send current upload and download speed data.
     */
    void networkData(ulong upload, ulong download);

public Q_SLOTS:
    /*!
     * Thread run now.
     */
    virtual void run() override final;

private Q_SLOTS:
    /*!
     * Get output recieved data on linux network.
     */
    void outputRecieved();

private:
    QStringList m_names;
    QProcess *m_process ;

};

#endif // DOWNLOADNETWORKSPEEDTHREAD_H
