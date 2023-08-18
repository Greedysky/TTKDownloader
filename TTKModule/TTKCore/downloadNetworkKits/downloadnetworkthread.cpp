#include "downloadnetworkthread.h"
#include "downloadsettingmanager.h"
#include "ttkconcurrent.h"

#include <QHostInfo>

#define NETWORK_DETECT_INTERVAL     5000             // second
#define NETWORK_REQUEST_ADDRESS     "www.baidu.com"  // ip

DownloadNetworkThread::DownloadNetworkThread()
    : QObject(nullptr),
      m_networkState(true)
{
    connect(&m_timer, SIGNAL(timeout()), SLOT(networkStateChanged()));
}

DownloadNetworkThread::~DownloadNetworkThread()
{
    m_timer.stop();
}

void DownloadNetworkThread::start()
{
    TTK_INFO_STREAM("Load NetworkThread");
    m_timer.start(NETWORK_DETECT_INTERVAL);
    networkStateChanged();
}

void DownloadNetworkThread::setBlockNetWork(bool block)
{
    G_SETTING_PTR->setValue(DownloadSettingManager::CloseNetWorkMode, block);
}

void DownloadNetworkThread::networkStateChanged()
{
    TTKConcurrent(
    {
        const bool block = G_SETTING_PTR->value(DownloadSettingManager::CloseNetWorkMode).toBool();
        const QHostInfo info = QHostInfo::fromName(NETWORK_REQUEST_ADDRESS);
        m_networkState = !info.addresses().isEmpty();
        m_networkState = block ? false : m_networkState;
        Q_EMIT networkConnectionStateChanged(m_networkState);
    });
}
