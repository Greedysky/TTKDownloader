#include "downloadthread.h"

#include <QFile>
#include <QSslConfiguration>
#include <QNetworkRequest>
#include <QNetworkAccessManager>

DownloadThread::DownloadThread(QObject *parent)
    : QObject(parent)
{
    m_state = Stop;
    m_manager = new QNetworkAccessManager(this);
}

DownloadThread::~DownloadThread()
{
    delete m_manager;
}

void DownloadThread::startDownload(int index, const QString &url, QFile *file,
                                   qint64 startPoint, qint64 endPoint,
                                   qint64 readySize)
{
    if(m_state == Download)
    {
        emit errorCode(m_index, "is downloading a file");
        return;
    }

    m_index = index;
    m_url = url;
    m_file = file;
    m_startPoint = startPoint;
    m_endPoint = endPoint;
    m_readySize = readySize;

    QNetworkRequest request;
    request.setUrl(m_url);
    QString range = QString("bytes=%0-%1").arg(m_startPoint + m_readySize).arg(m_endPoint);
    request.setRawHeader("Range", range.toUtf8());
#ifndef QT_NO_SSL
    QSslConfiguration sslConfig = request.sslConfiguration();
    sslConfig.setPeerVerifyMode(QSslSocket::VerifyNone);
    request.setSslConfiguration(sslConfig);
#endif

    m_reply = m_manager->get(request);
    connect(m_reply, SIGNAL(finished()), SLOT(finishedSlot()));
    connect(m_reply, SIGNAL(readyRead()), SLOT(readyReadSlot()));
#if TTK_QT_VERSION_CHECK(5,15,0)
    connect(m_reply, SIGNAL(errorOccurred(QNetworkReply::NetworkError)), SLOT(errorSlot(QNetworkReply::NetworkError)));
#else
    connect(m_reply, SIGNAL(error(QNetworkReply::NetworkError)), SLOT(errorSlot(QNetworkReply::NetworkError)));
#endif

    m_state = Download;
    emit downloadChanged();
}

void DownloadThread::pause()
{
    if(m_state != Download)
    {
        emit errorCode(m_index, "is not downloading");
        return;
    }

    m_state = Pause;
    m_reply->abort();
    m_file->flush();
    m_reply->deleteLater();
}

void DownloadThread::restart()
{
    if(m_state != Pause)
    {
        emit errorCode(m_index, "is not stoped");
        return;
    }

    startDownload(m_index, m_url, m_file, m_startPoint, m_endPoint, m_readySize);
}

void DownloadThread::finishedSlot()
{
    if(m_state != Download)
    {
        return;
    }

    m_file->flush();
    m_reply->deleteLater();
    m_state = Finished;

    emit finished(m_index);
}

void DownloadThread::readyReadSlot()
{
    const QByteArray &buffer = m_reply->readAll();
    m_file->seek(m_startPoint + m_readySize);
    m_file->write(buffer);
    m_readySize += buffer.length();

    emit downloadChanged();
}

void DownloadThread::errorSlot(QNetworkReply::NetworkError code)
{
    if(m_state != Download)
    {
        return;
    }
    emit errorCode(m_index, "QNetworkReply::NetworkError : " +
                            QString::number((int)code) + " \n" +
                            m_reply->errorString());
    m_state = Stop;
    m_reply->abort();
    m_file->flush();
    m_reply->deleteLater();
}
