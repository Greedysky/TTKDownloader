#include "downloadnetworkthread.h"
#include "downloadsettingmanager.h"
#include "downloadobject.h"

#include <QHostInfo>
#ifdef TTK_GREATER_NEW
#  include <QtConcurrent/QtConcurrent>
#else
#  include <QtConcurrentRun>
#endif

DownloadNetworkThread::DownloadNetworkThread()
    : QObject(nullptr), m_networkState(true)
{
    connect(&m_timer, SIGNAL(timeout()), SLOT(networkStateChanged()));
}

DownloadNetworkThread::~DownloadNetworkThread()
{
    m_timer.stop();
}

QString DownloadNetworkThread::getClassName()
{
    return staticMetaObject.className();
}

void DownloadNetworkThread::start()
{
    TTK_LOGGER_INFO("Load NetworkThread");
    m_timer.start(NETWORK_DETECT_INTERVAL);
}

void DownloadNetworkThread::setBlockNetWork(int block)
{
    M_SETTING_PTR->setValue(DownloadSettingManager::CloseNetWorkChoiced, block);
}

void DownloadNetworkThread::networkStateChanged()
{
    QtConcurrent::run([&]
    {
        bool block = M_SETTING_PTR->value(DownloadSettingManager::CloseNetWorkChoiced).toBool();
        QHostInfo info = QHostInfo::fromName(NETWORK_REQUEST_ADDRESS);
        m_networkState = !info.addresses().isEmpty();
        m_networkState = block ? false : m_networkState;
        emit networkConnectionStateChanged(m_networkState);
    });
}
