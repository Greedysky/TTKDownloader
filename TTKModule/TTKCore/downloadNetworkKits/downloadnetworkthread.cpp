#include "downloadnetworkthread.h"
#include "downloadsettingmanager.h"
#include "downloadobject.h"

#include <QHostInfo>
#if TTK_QT_VERSION_CHECK(5,0,0)
#  include <QtConcurrent/QtConcurrent>
#else
#  include <QtConcurrentRun>
#endif

#define NETWORK_DETECT_INTERVAL     5000             // second
#define NETWORK_REQUEST_ADDRESS     "www.baidu.com"  // ip

DownloadNetworkThread::DownloadNetworkThread()
    : QObject(nullptr), m_networkState(true)
{
    connect(&m_timer, SIGNAL(timeout()), SLOT(networkStateChanged()));
}

DownloadNetworkThread::~DownloadNetworkThread()
{
    m_timer.stop();
}

void DownloadNetworkThread::start()
{
    TTK_LOGGER_INFO("Load NetworkThread");
    m_timer.start(NETWORK_DETECT_INTERVAL);
}

void DownloadNetworkThread::setBlockNetWork(int block)
{
    G_SETTING_PTR->setValue(DownloadSettingManager::Config::CloseNetWorkChoiced, block);
}

void DownloadNetworkThread::networkStateChanged()
{
    const auto status = QtConcurrent::run([&]()
    {
        bool block = G_SETTING_PTR->value(DownloadSettingManager::Config::CloseNetWorkChoiced).toBool();
        QHostInfo info = QHostInfo::fromName(NETWORK_REQUEST_ADDRESS);
        m_networkState = !info.addresses().isEmpty();
        m_networkState = block ? false : m_networkState;
        emit networkConnectionStateChanged(m_networkState);
    });
    Q_UNUSED(status);
}
