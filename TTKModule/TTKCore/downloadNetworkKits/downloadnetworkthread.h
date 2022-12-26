#ifndef DOWNLOADNETWORKTHREAD_H
#define DOWNLOADNETWORKTHREAD_H

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

#include <QTimer>
#include "ttksingleton.h"
#include "ttkglobaldefine.h"

#define G_NETWORK_PTR (TTKSingleton<DownloadNetworkThread>::createInstance())

/*! @brief The class of the thread to check current network.
 * @author Greedysky <greedysky@163.com>
 */
class TTK_MODULE_EXPORT DownloadNetworkThread : public QObject
{
    Q_OBJECT
    TTK_DECLARE_MODULE(DownloadNetworkThread)
public:
    /*!
     * Strat thread now.
     */
    void start();
    /*!
     * Set flag wheather to block current network.
     */
    void setBlockNetWork(int block);
    /*!
     * Set current network state.
     */
    inline void setNetWorkState(bool state) { m_networkState = state; }
    /*!
     * Check current network is on.
     */
    inline bool isOnline() const { return m_networkState; }

Q_SIGNALS:
    /*!
     * Network connection state changed.
     * default status is true, means connected network.
     */
    void networkConnectionStateChanged(bool state);

public Q_SLOTS:
    /*!
     * Network connection state changed.
     */
    void networkStateChanged();

private:
    /*!
     * Object contsructor.
     */
    DownloadNetworkThread();
    ~DownloadNetworkThread();

    QTimer m_timer;
    bool m_networkState;

    TTK_DECLARE_SINGLETON_CLASS(DownloadNetworkThread)

};

#endif // DOWNLOADNETWORKTHREAD_H
