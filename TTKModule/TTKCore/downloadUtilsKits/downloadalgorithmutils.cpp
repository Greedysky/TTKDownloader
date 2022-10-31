#include "downloadalgorithmutils.h"
#include "ttkcryptographichash.h"

#include <QCryptographicHash>

QByteArray DownloadUtils::Algorithm::sha1(const QByteArray &data)
{
    return QCryptographicHash::hash(data, QCryptographicHash::Sha1);
}

QString DownloadUtils::Algorithm::mdII(const QString &data, bool encode)
{
    TTKCryptographicHash hash;
    return encode ? hash.encrypt(data, "GREEDYSKY") : hash.decrypt(data, "GREEDYSKY");
}
