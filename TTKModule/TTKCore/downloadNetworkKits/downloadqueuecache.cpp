#include "downloadqueuecache.h"
#include "downloadnetworkthread.h"

#include <QStringList>

DownloadQueueCache::DownloadQueueCache(QObject *parent)
    : DownloadQueueCache(DownloadQueueData(), parent)
{

}

DownloadQueueCache::DownloadQueueCache(const DownloadQueueData &data, QObject *parent)
    : DownLoadThreadAbstract(data.m_url, data.m_savePath, parent),
      m_isDownload(false),
      m_isAbort(false),
      m_request(nullptr)
{
    m_manager = new QNetworkAccessManager(this);
    m_request = new QNetworkRequest();
#ifndef QT_NO_SSL
    connect(m_manager, SIGNAL(sslErrors(QNetworkReply*,QList<QSslError>)),
                       SLOT(sslErrors(QNetworkReply*,QList<QSslError>)));
    TTK_LOGGER_INFO(QString("%1 Support ssl: %2").arg(className()).arg(QSslSocket::supportsSsl()));

    QSslConfiguration sslConfig = m_request->sslConfiguration();
    sslConfig.setPeerVerifyMode(QSslSocket::VerifyNone);
    m_request->setSslConfiguration(sslConfig);
#endif
}

DownloadQueueCache::DownloadQueueCache(const DownloadQueueDataList &datas, QObject *parent)
    : DownloadQueueCache(DownloadQueueData(), parent)
{
    addImageQueue(datas);
}

DownloadQueueCache::~DownloadQueueCache()
{
    if(m_request)
    {
        delete m_request;
        m_request = nullptr;
    }
    deleteAll();
}

void DownloadQueueCache::startToDownload()
{
    if(!m_imageQueue.isEmpty())
    {
        startOrderImageQueue();
    }
}

void DownloadQueueCache::abort()
{
    if(m_isDownload && m_reply)
    {
        m_isAbort = true;
        m_reply->abort();
        m_file->close();
        m_file->remove();
        delete m_reply;
        m_reply = nullptr;
        m_isAbort = false;
    }
}

void DownloadQueueCache::addImageQueue(const DownloadQueueDataList &datas)
{
    m_imageQueue = datas;
}

void DownloadQueueCache::startOrderImageQueue()
{
    if(!m_imageQueue.isEmpty() && G_NETWORK_PTR->isOnline())
    {
        if(QFile::exists(m_imageQueue.front().m_savePath))
        {
            Q_EMIT downLoadDataChanged(m_imageQueue.takeFirst().m_savePath);
            startOrderImageQueue();
        }
        else
        {
            startDownload(m_imageQueue.front().m_url);
        }
    }
}

void DownloadQueueCache::startDownload(const QString &url)
{
    m_isDownload = true;
    delete m_file;
    m_file = new QFile(m_imageQueue.front().m_savePath, this);
    if(!m_file->open(QFile::WriteOnly))
    {
        m_file->close();
        delete m_file;
        m_file = nullptr;
        return;
    }

    if(!m_request || !m_manager)
    {
        return;
    }

    m_timer.start(MT_S2MS);
    m_request->setUrl(QUrl(url));
    m_reply = m_manager->get(*m_request);
    connect(m_reply, SIGNAL(finished()), SLOT(downLoadFinished()));
    connect(m_reply, SIGNAL(readyRead()), SLOT(readyReadSlot()));
    QtNetworkErrorConnect(m_reply, this, errorSlot);
}

void DownloadQueueCache::downLoadFinished()
{
    if(m_isAbort || !m_request || !m_manager || !m_reply || !m_file)
    {
        return;
    }
    m_timer.stop();

    m_file->flush();
    m_file->close();
    m_reply->deleteLater();
    m_reply = nullptr;
    m_isDownload = false;
    Q_EMIT downLoadDataChanged(m_imageQueue.takeFirst().m_savePath);

    startOrderImageQueue();
}

void DownloadQueueCache::readyReadSlot()
{
    if(!m_file || !m_reply)
    {
        return;
    }

    m_file->write(m_reply->readAll());
    m_file->flush();
}

void DownloadQueueCache::errorSlot(QNetworkReply::NetworkError code)
{
    if(!m_file || !m_reply)
    {
        return;
    }
#ifndef TTK_DEBUG
    Q_UNUSED(code);
#endif
    TTK_LOGGER_ERROR(QString("QNetworkReply::NetworkError : %1 %2").arg(code).arg(m_reply->errorString()));
    m_file->flush();
    if(!m_isAbort)
    {
        m_reply->deleteLater();
        m_reply = nullptr;
    }
}
