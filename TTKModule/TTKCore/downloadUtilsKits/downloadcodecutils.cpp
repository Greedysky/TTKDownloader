#include "downloadcodecutils.h"
#include "downloadobject.h"

#include <QTextCodec>

QString DownloadUtils::Codec::toUnicode(const char *chars, const char *format)
{
    QTextCodec *codec = QTextCodec::codecForName(format);
    return codec->toUnicode(chars);
}

QString DownloadUtils::Codec::toUnicode(const QByteArray &chars, const char *format)
{
    QTextCodec *codec = QTextCodec::codecForName(format);
    return codec->toUnicode(chars);
}

QByteArray DownloadUtils::Codec::fromUnicode(const QString &chars, const char *format)
{
    QTextCodec *codec = QTextCodec::codecForName(format);
    return codec->fromUnicode(chars);
}

void DownloadUtils::Codec::setLocalCodec(const char *format)
{
    QTextCodec *codec = QTextCodec::codecForName(format);
    QTextCodec::setCodecForLocale(codec);
#if !TTK_QT_VERSION_CHECK(5,0,0)
    QTextCodec::setCodecForCStrings(codec);
    QTextCodec::setCodecForTr(codec);
#endif
}

const char* DownloadUtils::Codec::toLocal8Bit(const QString &str)
{
    return str.toLocal8Bit().constData();
}

const char* DownloadUtils::Codec::toUtf8(const QString &str)
{
    return str.toUtf8().constData();
}
