#ifndef DOWNLOADNETWORKTHREAD_H
#define DOWNLOADNETWORKTHREAD_H

/* =================================================
 * This file is part of the TTK Downloader project
 * Copyright (c) 2016 - 2017 Greedysky Studio
 * All rights reserved!
 * Redistribution and use of the source code or any derivative
 * works are strictly forbiden.
   =================================================*/

#include <QTimer>
#include "downloadsingleton.h"

#define M_NETWORK_PTR (DownloadSingleton<DownloadNetworkThread>::createInstance())
#define NETWORK_DETECT_INTERVAL     5000             // second
#define NETWORK_REQUEST_ADDRESS     "www.baidu.com"  // ip

/*! @brief The class of thread to check current network.
 * @author Greedysky <greedysky@163.com>
 */
class DOWNLOAD_NETWORK_EXPORT DownloadNetworkThread : public QObject
{
    Q_OBJECT
public:
    /*!
     * Get class object name.
     */
    static QString getClassName();

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

    DECLARE_SINGLETON_CLASS(DownloadNetworkThread)
};

#endif // DOWNLOADNETWORKTHREAD_H
