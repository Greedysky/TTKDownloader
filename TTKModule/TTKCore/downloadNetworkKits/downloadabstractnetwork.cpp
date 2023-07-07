#include "downloadabstractnetwork.h"

DownloadAbstractNetwork::DownloadAbstractNetwork(QObject *parent)
    : QObject(parent),
      m_stateCode(TTK::NetworkCode::Query),
      m_reply(nullptr)
{
#ifndef QT_NO_SSL
    connect(&m_manager, SIGNAL(sslErrors(QNetworkReply*,QList<QSslError>)), SLOT(sslErrors(QNetworkReply*,QList<QSslError>)));
#endif
}

DownloadAbstractNetwork::~DownloadAbstractNetwork()
{
    m_stateCode = TTK::NetworkCode::Error;
    deleteAll();
}

void DownloadAbstractNetwork::deleteAll()
{
    if(m_reply)
    {
        m_reply->deleteLater();
        m_reply = nullptr;
    }
}

void DownloadAbstractNetwork::replyError(QNetworkReply::NetworkError)
{
    TTK_ERROR_STREAM("Abnormal network connection");
    Q_EMIT downLoadDataChanged(QString());
    deleteAll();
}

#ifndef QT_NO_SSL
void DownloadAbstractNetwork::sslErrors(QNetworkReply* reply, const QList<QSslError> &errors)
{
    sslErrorsString(reply, errors);
    Q_EMIT downLoadDataChanged(QString());
    deleteAll();
}

void DownloadAbstractNetwork::sslErrorsString(QNetworkReply *reply, const QList<QSslError> &errors)
{
    QString errorString;
    for(const QSslError &error : qAsConst(errors))
    {
        if(!errorString.isEmpty())
        {
            errorString += ", ";
        }
        errorString += error.errorString();
    }

    TTK_ERROR_STREAM(QString("sslErrors: %1").arg(errorString));
    reply->ignoreSslErrors();
}
#endif

namespace TTK
{
void setSslConfiguration(QNetworkRequest *request, QSslSocket::PeerVerifyMode mode)
{
#ifndef QT_NO_SSL
    QSslConfiguration sslConfig = request->sslConfiguration();
    sslConfig.setPeerVerifyMode(mode);
    request->setSslConfiguration(sslConfig);
#else
    Q_UNUSED(request);
    Q_UNUSED(mode);
#endif
}
}
