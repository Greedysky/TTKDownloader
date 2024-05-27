#include "downloadalgorithmutils.h"
#include "ttkcryptographichash.h"

#include <QCryptographicHash>

static constexpr const char *MDII_URL_KEY = "GREEDYSKY";

QByteArray TTK::Algorithm::sha1(const QByteArray &data)
{
    return QCryptographicHash::hash(data, QCryptographicHash::Sha1);
}

QString TTK::Algorithm::mdII(const QString &data, bool encode)
{
    TTKCryptographicHash hash;
    return encode ? hash.encrypt(data, MDII_URL_KEY) : hash.decrypt(data, MDII_URL_KEY);
}

QString TTK::Algorithm::mdII(const QString &data, const char *key, bool encode)
{
    TTKCryptographicHash hash;
    return encode ? hash.encrypt(data, key) : hash.decrypt(data, key);
}
