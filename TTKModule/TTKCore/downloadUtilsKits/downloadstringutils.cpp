#include "downloadstringutils.h"
#include "downloadsettingmanager.h"

#include <QColor>

QString DownloadUtils::String::removeStringBy(const QString &value, const QString &key)
{
    QString s = value;
    s.remove(key);
    if(s.contains(key))
    {
        s = removeStringBy(key);
    }
    return s;
}

QStringList DownloadUtils::String::splitString(const QString &value, const QString &key)
{
    QStringList strings = value.split(QString(" %1 ").arg(key));
    if(strings.isEmpty() || strings.count() == 1)
    {
        strings = value.split(key);
    }
    return strings;
}

QList<QColor> DownloadUtils::String::readColorConfig(const QString &value)
{
    QList<QColor> colors;
#if TTK_QT_VERSION_CHECK(5,15,0)
    const QStringList &rgbs = value.split(";", Qt::SkipEmptyParts);
#else
    const QStringList &rgbs = value.split(";", QString::SkipEmptyParts);
#endif
    for(const QString &rgb : qAsConst(rgbs))
    {
        const QStringList &var = rgb.split(',');
        if(var.count() != 3)
        {
            continue;
        }
        colors << QColor(var[0].toInt(), var[1].toInt(), var[2].toInt());
    }
    return colors;
}

QString DownloadUtils::String::writeColorConfig(const QColor &color)
{
    QString value;
    value.append(QString("%1,%2,%3").arg(color.red()).arg(color.green()).arg(color.blue()));
    return value;
}

QString DownloadUtils::String::writeColorConfig(const QList<QColor> &colors)
{
    QString value;
    for(const QColor &rgb : qAsConst(colors))
    {
        value.append(writeColorConfig(rgb) + ";");
    }
    return value;
}
