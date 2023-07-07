#include "downloaddatasourcerequest.h"

DownloadDataSourceRequest::DownloadDataSourceRequest(QObject *parent)
    : DownloadAbstractNetwork(parent)
{

}

void DownloadDataSourceRequest::deleteAll()
{
    DownloadAbstractNetwork::deleteAll();
    deleteLater();
}

void DownloadDataSourceRequest::startRequest(const QString &url)
{
    QNetworkRequest request;
    request.setUrl(url);
    TTK::setSslConfiguration(&request);

    m_reply = m_manager.get(request);
    connect(m_reply, SIGNAL(finished()), SLOT(downLoadFinished()));
    QtNetworkErrorConnect(m_reply, this, replyError);
}

void DownloadDataSourceRequest::downLoadFinished()
{
    if(m_reply && m_reply->error() == QNetworkReply::NoError)
    {
        const QVariant &redirection = m_reply->attribute(QNetworkRequest::RedirectionTargetAttribute);
        if(redirection.isValid())
        {
            const QString &url = redirection.toString();
            DownloadAbstractNetwork::deleteAll();
            startRequest(url);
        }
        else
        {
            Q_EMIT downLoadRawDataChanged(m_reply->readAll());
            deleteAll();
        }
    }
    else
    {
        TTK_ERROR_STREAM("Download source data error");
        Q_EMIT downLoadRawDataChanged(QByteArray());
        deleteAll();
    }
}
