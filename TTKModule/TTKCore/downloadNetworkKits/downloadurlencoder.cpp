#include "downloadurlencoder.h"

static const QString THUNDER = "thunder://";
static const QString FLASHGET = "Flashget://";
static const QString QQDL = "qqdl://";

QString DownloadUrlEncoder::decoder(const QString &url)
{
    QString turl = url;
    if(url.left(THUNDER.length()).contains(THUNDER, Qt::CaseInsensitive))
    {
        QByteArray byte = QByteArray::fromBase64(turl.mid(THUNDER.length()).toUtf8());
        byte.remove(0, 2); //remove AA
        byte.chop(2); //remove ZZ
        return byte;
    }
    else if(url.left(FLASHGET.length()).contains(FLASHGET, Qt::CaseInsensitive))
    {
        const int d = turl.lastIndexOf('&');
        turl = (d == -1) ? turl : turl.left(d);
        QByteArray byte = QByteArray::fromBase64(turl.mid(FLASHGET.length()).toUtf8());
        byte.remove(0, 10); //remove [FLASHGET]
        byte.chop(10); //remove  [FLASHGET]
        return byte;
    }
    else if(url.left(QQDL.length()).contains(QQDL, Qt::CaseInsensitive))
    {
        return QByteArray::fromBase64(turl.mid(QQDL.length()).toUtf8());
    }
    else
    {
        return url;
    }
}
