#include "downloadthreadabstract.h"
#include "downloadsettingmanager.h"

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QThread>
#if defined Q_OS_UNIX || defined Q_CC_MINGW
#  include <unistd.h>
#endif
#include <QSslError>

DownLoadThreadAbstract::DownLoadThreadAbstract(const QString &url, const QString &save, QObject *parent)
    : DownloadNetworkAbstract(parent)
{
    m_url = url;
    m_savePathName = save;
    m_hasReceived = 0;
    m_currentReceived = 0;

    if(QFile::exists(save))
    {
        QFile::remove(save);
    }
    m_file = new QFile(save, this);

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
    TTK_LOGGER_ERROR("Abnormal network connection");
    emit downLoadDataChanged("The file create failed");
    deleteAll();
}

#ifndef QT_NO_SSL
void DownLoadThreadAbstract::sslErrors(QNetworkReply* reply, const QList<QSslError> &errors)
{
    sslErrorsString(reply, errors);
    emit downLoadDataChanged("The file create failed");
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
    int delta = m_currentReceived - m_hasReceived;
    //////////////////////////////////////
    ///limit speed
    if(G_SETTING_PTR->value(DownloadSettingManager::DownloadLimitChoiced).toInt() == 0)
    {
        int limitValue = G_SETTING_PTR->value(DownloadSettingManager::DownloadDLoadLimitChoiced).toInt();
        if(limitValue != 0 && delta > limitValue*MH_KB)
        {
#if defined Q_OS_WIN && TTK_QT_VERSION_CHECK(5,0,0)
            QThread::msleep(MT_S2MS - limitValue*MH_KB*MT_S2MS/delta);
#else
            usleep((MT_S2MS - limitValue*MH_KB*MT_S2MS/delta)*MT_S2MS);
#endif
            delta = limitValue*MH_KB;
        }
    }
    //////////////////////////////////////
    m_hasReceived = m_currentReceived;
}
