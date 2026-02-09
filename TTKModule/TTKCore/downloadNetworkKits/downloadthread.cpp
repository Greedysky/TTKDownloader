#include "downloadthread.h"
#include "downloadabstractnetwork.h"

#include <QFile>

DownloadThread::DownloadThread(QObject *parent)
    : QObject(parent),
      m_state(TTK::DownloadState::Stop)
{
    m_manager = new QNetworkAccessManager(this);
}

DownloadThread::~DownloadThread()
{
    delete m_manager;
}

void DownloadThread::startDownload(const Data &data)
{
    if(m_state == TTK::DownloadState::Download)
    {
        Q_EMIT errorOccurred(data.m_index, "is downloading a file");
        return;
    }

    m_data = data;

    QNetworkRequest request;
    request.setUrl(data.m_url);
    const QString &range = QString("bytes=%0-%1").arg(data.m_startPoint + data.m_readySize).arg(data.m_endPoint);
    request.setRawHeader("Range", range.toUtf8());
    TTK::setSslConfiguration(&request);

    m_reply = m_manager->get(request);
    connect(m_reply, SIGNAL(finished()), SLOT(downloadFinished()));
    connect(m_reply, SIGNAL(readyRead()), SLOT(handleReadyRead()));
    QtNetworkErrorConnect(m_reply, this, handleError, TTK_SLOT);

    m_state = TTK::DownloadState::Download;
    Q_EMIT downloadChanged();
}

void DownloadThread::pause()
{
    if(m_state != TTK::DownloadState::Download)
    {
        Q_EMIT errorOccurred(m_data.m_index, "is not downloading");
        return;
    }

    m_state = TTK::DownloadState::Pause;
    m_reply->abort();
    m_data.m_file->flush();
    m_reply->deleteLater();
}

void DownloadThread::restart()
{
    if(m_state != TTK::DownloadState::Pause)
    {
        Q_EMIT errorOccurred(m_data.m_index, "is not stoped");
        return;
    }

    startDownload(m_data);
}

void DownloadThread::downloadFinished()
{
    if(m_state != TTK::DownloadState::Download)
    {
        return;
    }

    m_data.m_file->flush();
    m_reply->deleteLater();
    m_state = TTK::DownloadState::Finish;

    Q_EMIT finished(m_data.m_index);
}

void DownloadThread::handleReadyRead()
{
    const QByteArray &buffer = m_reply->readAll();
    m_data.m_file->seek(m_data.m_startPoint + m_data.m_readySize);
    m_data.m_file->write(buffer);
    m_data.m_readySize += buffer.length();

    Q_EMIT downloadChanged();
}

void DownloadThread::handleError(QNetworkReply::NetworkError code)
{
    if(m_state != TTK::DownloadState::Download)
    {
        return;
    }

    Q_EMIT errorOccurred(m_data.m_index, "QNetworkReply::NetworkError : " + QString::number(TTKStaticCast(int, code)) + " \n" + m_reply->errorString());

    m_state = TTK::DownloadState::Error;
    m_reply->abort();
    m_data.m_file->flush();
    m_reply->deleteLater();
}
