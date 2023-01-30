#include "downloadthreadabstract.h"
#include "downloadsettingmanager.h"
#if defined Q_OS_UNIX || defined Q_CC_MINGW
#  include <unistd.h>
#endif
#include <QSslError>

DownLoadThreadAbstract::DownLoadThreadAbstract(const QString &url, const QString &path, QObject *parent)
    : DownloadNetworkAbstract(parent),
      m_url(url),
      m_hasReceived(0),
      m_currentReceived(0)
{
    if(QFile::exists(path))
    {
        QFile::remove(path);
    }
    m_file = new QFile(path, this);

    m_timer.setInterval(MT_S2MS);
    connect(&m_timer, SIGNAL(timeout()), SLOT(updateDownloadSpeed()));
}

void DownLoadThreadAbstract::deleteAll()
{
    DownloadNetworkAbstract::deleteAll();
    if(m_file)
    {
        delete m_file;
        m_file = nullptr;
    }
    deleteLater();
}

void DownLoadThreadAbstract::replyError(QNetworkReply::NetworkError)
{
    TTK_ERROR_STREAM("Abnormal network connection");
    Q_EMIT downLoadDataChanged("The file create failed");
    deleteAll();
}

#ifndef QT_NO_SSL
void DownLoadThreadAbstract::sslErrors(QNetworkReply* reply, const QList<QSslError> &errors)
{
    sslErrorsString(reply, errors);
    Q_EMIT downLoadDataChanged("The file create failed");
    deleteAll();
}
#endif

void DownLoadThreadAbstract::downloadProgress(qint64 bytesReceived, qint64 bytesTotal)
{
    m_currentReceived = bytesReceived;
    m_totalSize = bytesTotal;
}

void DownLoadThreadAbstract::updateDownloadSpeed()
{
    const int delta = m_currentReceived - m_hasReceived;
    ///limit speed
    if(G_SETTING_PTR->value(DownloadSettingManager::DownloadLimitChoiced).toInt() == 0)
    {
        const int limitValue = G_SETTING_PTR->value(DownloadSettingManager::DownloadDLoadLimitChoiced).toInt();
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
