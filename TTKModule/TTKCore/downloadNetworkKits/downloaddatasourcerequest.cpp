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

void DownloadDataSourceRequest::startToRequest(const QString &url)
{
    QNetworkRequest request;
    request.setUrl(url);
    TTK::setSslConfiguration(&request);

    m_reply = m_manager.get(request);
    connect(m_reply, SIGNAL(finished()), SLOT(downloadFinished()));
    QtNetworkErrorConnect(m_reply, this, replyError, TTK_SLOT);
}

void DownloadDataSourceRequest::downloadFinished()
{
    DownloadAbstractNetwork::downloadFinished();
    if(m_reply && m_reply->error() == QNetworkReply::NoError)
    {
        const QVariant &redirection = m_reply->attribute(QNetworkRequest::RedirectionTargetAttribute);
        if(redirection.isValid())
        {
            const QString &url = redirection.toString();
            DownloadAbstractNetwork::deleteAll();
            startToRequest(url);
        }
        else
        {
            Q_EMIT downloadRawDataChanged(m_reply->readAll());
            deleteAll();
        }
    }
    else
    {
        TTK_ERROR_STREAM("Download source data error");
        Q_EMIT downloadRawDataChanged({});
        deleteAll();
    }
}
