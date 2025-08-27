#include "downloadnetworkthread.h"
#include "downloadsettingmanager.h"
#include "ttkconcurrent.h"

#include <QHostInfo>

static constexpr int NETWORK_DETECT_INTERVAL = 5000; // second
static constexpr const char *NETWORK_REQUEST_ADDRESS = "www.baidu.com"; // ip

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

void DownloadNetworkThread::networkStateChanged()
{
    TTKConcurrent(
    {
        const QHostInfo &info = QHostInfo::fromName(NETWORK_REQUEST_ADDRESS);
        m_networkState = !info.addresses().isEmpty();
        Q_EMIT networkConnectionStateChanged(m_networkState);
    });
}
