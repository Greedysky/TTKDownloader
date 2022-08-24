#include "downloadnetworkabstract.h"

DownloadNetworkAbstract::DownloadNetworkAbstract(QObject *parent)
    : QObject(parent)
{
    m_stateCode = StateCode::Init;
    m_reply = nullptr;
    m_manager = nullptr;
}

DownloadNetworkAbstract::~DownloadNetworkAbstract()
{
    m_stateCode = StateCode::Success;
    deleteAll();
}

void DownloadNetworkAbstract::deleteAll()
{
    if(m_manager)
    {
        m_manager->deleteLater();
        m_manager = nullptr;
    }

    if(m_reply)
    {
        m_reply->deleteLater();
        m_reply = nullptr;
    }
}

void DownloadNetworkAbstract::replyError(QNetworkReply::NetworkError)
{
    TTK_LOGGER_ERROR("Abnormal network connection");
    emit downLoadDataChanged(QString());
    deleteAll();
}

#ifndef QT_NO_SSL
void DownloadNetworkAbstract::sslErrors(QNetworkReply* reply, const QList<QSslError> &errors)
{
    sslErrorsString(reply, errors);
    emit downLoadDataChanged(QString());
    deleteAll();
}

void DownloadNetworkAbstract::sslErrorsString(QNetworkReply *reply, const QList<QSslError> &errors)
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

    TTK_LOGGER_ERROR(QString("sslErrors: %1").arg(errorString));
    reply->ignoreSslErrors();
}
#endif
