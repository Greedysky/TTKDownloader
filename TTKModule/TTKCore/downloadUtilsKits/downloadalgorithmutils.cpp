#include "downloadalgorithmutils.h"
#include "downloadcryptographichash.h"

#include <QCryptographicHash>

QByteArray DownloadUtils::Algorithm::md5(const QByteArray &data)
{
    return QCryptographicHash::hash(data, QCryptographicHash::Md5);
}

QByteArray DownloadUtils::Algorithm::sha1(const QByteArray &data)
{
    return QCryptographicHash::hash(data, QCryptographicHash::Sha1);
}

QString DownloadUtils::Algorithm::mdII(const QString &data, bool encode)
{
    DownloadCryptographicHash hash;
    return encode ? hash.encrypt(data, ALG_URL_KEY) : hash.decrypt(data, ALG_URL_KEY);
}

QString DownloadUtils::Algorithm::mdII(const QString &data, const QString &key, bool encode)
{
    DownloadCryptographicHash hash;
    return encode ? hash.encrypt(data, key) : hash.decrypt(data, key);
}
