#include "downloadalgorithmutils.h"
#include "ttkcryptographichash.h"

#include <QCryptographicHash>

static constexpr const char *URL_KEY = "GREEDYSKY";

QByteArray TTK::Algorithm::sha1(const QByteArray &data)
{
    return QCryptographicHash::hash(data, QCryptographicHash::Sha1);
}

QString TTK::Algorithm::mdII(const QString &data, bool encode)
{
    TTKCryptographicHash hash;
    return encode ? hash.encrypt(data, URL_KEY) : hash.decrypt(data, URL_KEY);
}

QString TTK::Algorithm::mdII(const QString &data, const QString &key, bool encode)
{
    TTKCryptographicHash hash;
    return encode ? hash.encrypt(data, key) : hash.decrypt(data, key);
}
