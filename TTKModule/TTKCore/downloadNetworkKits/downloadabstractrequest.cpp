#include "downloadabstractrequest.h"
#include "downloadsettingmanager.h"
#ifdef Q_CC_MSVC
#  include <qt_windows.h>
#elif defined Q_OS_UNIX || defined Q_CC_MINGW
#  include <unistd.h>
#endif

DownLoadAbstractRequest::DownLoadAbstractRequest(const QString &url, const QString &path, QObject *parent)
    : DownloadAbstractNetwork(parent),
      m_url(url),
      m_hasReceived(0),
      m_currentReceived(0)
{
    if(QFile::exists(path))
    {
        QFile::remove(path);
    }
    m_file = new QFile(path, this);

    m_speedTimer.setInterval(MT_S2MS);
    connect(&m_speedTimer, SIGNAL(timeout()), SLOT(updateDownloadSpeed()));
}

DownLoadAbstractRequest::~DownLoadAbstractRequest()
{
    if(m_speedTimer.isActive())
    {
        m_speedTimer.stop();
    }
}

void DownLoadAbstractRequest::deleteAll()
{
    DownloadAbstractNetwork::deleteAll();
    delete m_file;
    m_file = nullptr;
    deleteLater();
}

void DownLoadAbstractRequest::downLoadFinished()
{
    m_speedTimer.stop();
}

void DownLoadAbstractRequest::downloadProgress(qint64 bytesReceived, qint64 bytesTotal)
{
    m_currentReceived = bytesReceived;
    m_totalSize = bytesTotal;
}

void DownLoadAbstractRequest::updateDownloadSpeed()
{
    const int delta = m_currentReceived - m_hasReceived;
    ///limit speed
    if(G_SETTING_PTR->value(DownloadSettingManager::DownloadLimit).toBool())
    {
        const int limitValue = G_SETTING_PTR->value(DownloadSettingManager::DownloadDLoadLimit).toInt();
        if(limitValue != 0 && delta > limitValue * MH_KB)
        {
#ifdef Q_CC_MSVC
            ::Sleep(MT_S2MS - limitValue * MH_KB * MT_S2MS / delta);
#elif defined Q_OS_UNIX || defined Q_CC_MINGW
            usleep((MT_S2MS - limitValue * MH_KB * MT_S2MS / delta) * MT_MS2US);
#endif
        }
    }
    m_hasReceived = m_currentReceived;
}
