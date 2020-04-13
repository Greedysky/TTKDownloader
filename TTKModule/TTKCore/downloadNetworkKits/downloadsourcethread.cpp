#include "downloadsourcethread.h"

DownloadSourceThread::DownloadSourceThread(QObject *parent)
    : DownloadNetworkAbstract(parent)
{

}

DownloadSourceThread::~DownloadSourceThread()
{
    deleteAll();
}

QString DownloadSourceThread::getClassName()
{
    return staticMetaObject.className();
}

void DownloadSourceThread::startToDownload(const QString &url)
{
    m_manager = new QNetworkAccessManager(this);

    QNetworkRequest request;
    request.setUrl(url);
#ifndef QT_NO_SSL
    connect(m_manager, SIGNAL(sslErrors(QNetworkReply*,QList<QSslError>)),
                       SLOT(sslErrors(QNetworkReply*,QList<QSslError>)));
    TTK_LOGGER_INFO(QString("%1 Support ssl: %2").arg(getClassName()).arg(QSslSocket::supportsSsl()));

    QSslConfiguration sslConfig = request.sslConfiguration();
    sslConfig.setPeerVerifyMode(QSslSocket::VerifyNone);
    request.setSslConfiguration(sslConfig);
#endif

    m_reply = m_manager->get(request);
    connect(m_reply, SIGNAL(finished()), SLOT(downLoadFinished()));
}

void DownloadSourceThread::downLoadFinished()
{
    if(m_reply && m_reply->error() == QNetworkReply::NoError)
    {
        if(m_reply->attribute(QNetworkRequest::RedirectionTargetAttribute).isValid())
        {
            QString newUrl = m_reply->attribute(QNetworkRequest::RedirectionTargetAttribute).toString();
            deleteAll();
            startToDownload(newUrl); ///redirection target url
        }
        else
        {
            emit downLoadByteDataChanged(m_reply->readAll());
            deleteAll();
        }
    }
    else
    {
        TTK_LOGGER_ERROR("Download source data error");
        emit downLoadByteDataChanged(QByteArray());
        deleteAll();
    }
}

void DownloadSourceThread::replyError(QNetworkReply::NetworkError)
{
    TTK_LOGGER_ERROR("Abnormal network connection");
    emit downLoadByteDataChanged(QByteArray());
    deleteAll();
}

#ifndef QT_NO_SSL
void DownloadSourceThread::sslErrors(QNetworkReply* reply, const QList<QSslError> &errors)
{
    sslErrorsString(reply, errors);
    emit downLoadByteDataChanged(QByteArray());
    deleteAll();
}
#endif
