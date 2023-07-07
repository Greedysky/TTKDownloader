#include "downloadqueuerequest.h"
#include "downloadnetworkthread.h"

#include <QStringList>

DownloadQueueRequest::DownloadQueueRequest(QObject *parent)
    : DownloadQueueRequest(DownloadQueueData(), parent)
{

}

DownloadQueueRequest::DownloadQueueRequest(const DownloadQueueData &data, QObject *parent)
    : DownLoadAbstractRequest(data.m_url, data.m_path, parent),
      m_isDownload(false),
      m_isAbort(false)
{
    m_request = new QNetworkRequest;
    TTK::setSslConfiguration(m_request);
}

DownloadQueueRequest::DownloadQueueRequest(const DownloadQueueDataList &datas, QObject *parent)
    : DownloadQueueRequest(DownloadQueueData(), parent)
{
    addImageQueue(datas);
}

DownloadQueueRequest::~DownloadQueueRequest()
{
    delete m_request;
    m_request = nullptr;
    deleteAll();
}

void DownloadQueueRequest::startRequest()
{
    if(!m_imageQueue.isEmpty())
    {
        startOrderImageQueue();
    }
}

void DownloadQueueRequest::abort()
{
    clear();
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

void DownloadQueueRequest::clear()
{
    m_imageQueue.clear();
}

void DownloadQueueRequest::addImageQueue(const DownloadQueueDataList &datas)
{
    m_imageQueue = datas;
}

void DownloadQueueRequest::startOrderImageQueue()
{
    if(!m_imageQueue.isEmpty())
    {
        if(QFile::exists(m_imageQueue.front().m_path))
        {
            Q_EMIT downLoadDataChanged(m_imageQueue.takeFirst().m_path);
            startOrderImageQueue();
        }
        else if(G_NETWORK_PTR->isOnline())
        {
            startDownload(m_imageQueue.front().m_url);
        }
    }
}

void DownloadQueueRequest::startDownload(const QString &url)
{
    m_isDownload = true;
    delete m_file;
    m_file = new QFile(m_imageQueue.front().m_path, this);
    if(!m_file->open(QIODevice::WriteOnly))
    {
        m_file->close();
        delete m_file;
        m_file = nullptr;
        return;
    }

    if(!m_request)
    {
        return;
    }

    m_speedTimer.start();
    m_request->setUrl(url);
    m_reply = m_manager.get(*m_request);
    connect(m_reply, SIGNAL(finished()), SLOT(downLoadFinished()));
    connect(m_reply, SIGNAL(readyRead()), SLOT(handleReadyRead()));
    QtNetworkErrorConnect(m_reply, this, handleError);
}

void DownloadQueueRequest::downLoadFinished()
{
    if(m_isAbort || !m_request || !m_reply || !m_file)
    {
        return;
    }

    DownLoadAbstractRequest::downLoadFinished();
    m_file->flush();
    m_file->close();
    m_isDownload = false;
    DownloadAbstractNetwork::deleteAll();
    Q_EMIT downLoadDataChanged(m_imageQueue.takeFirst().m_path);

    startOrderImageQueue();
}

void DownloadQueueRequest::handleReadyRead()
{
    if(!m_file || !m_reply)
    {
        return;
    }

    m_file->write(m_reply->readAll());
    m_file->flush();
}

void DownloadQueueRequest::handleError(QNetworkReply::NetworkError code)
{
    if(!m_file || !m_reply)
    {
        return;
    }

#ifndef TTK_DEBUG
    Q_UNUSED(code);
#endif
    TTK_ERROR_STREAM(QString("QNetworkReply::NetworkError : %1 %2").arg(code).arg(m_reply->errorString()));
    m_file->flush();
    if(!m_isAbort)
    {
        DownloadAbstractNetwork::deleteAll();
    }

    startRequest();
}
