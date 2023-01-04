#include "downloadnumberutils.h"
#include "ttknumberdefine.h"

static QString size2Number(qint64 size)
{
    if(size < MH_KB2B)
    {
        return QString::number(size * 1.0, 'f', 1);
    }
    else if(MH_KB2B <= size && size < MH_MB2B)
    {
        return QString::number(size * 1.0 / MH_KB2B, 'f', 1);
    }
    else if(MH_MB2B <= size && size < MH_GB2B)
    {
        return QString::number(size * 1.0 / MH_MB2B, 'f', 1);
    }
    else if(MH_GB2B <= size && size < MH_TB2B)
    {
        return QString::number(size * 1.0 / MH_GB2B, 'f', 1);
    }
    else
    {
        return QString::number(size * 1.0 / MH_TB2B, 'f', 1);
    }
}

QString DownloadUtils::Number::sizeByteToLabel(qint64 size)
{
    if(size < 0)
    {
        return "0.0B";
    }

    const QString &label = size2Number(size);
    if(size < MH_KB2B)
    {
        return QString("%1B").arg(label);
    }
    else if(MH_KB2B <= size && size < MH_MB2B)
    {
        return QString("%1K").arg(label);
    }
    else if(MH_MB2B <= size && size < MH_GB2B)
    {
        return QString("%1M").arg(label);
    }
    else if(MH_GB2B <= size && size < MH_TB2B)
    {
        return QString("%1G").arg(label);
    }
    else
    {
        return QString("%1T").arg(label);
    }
}

QString DownloadUtils::Number::speedByteToLabel(qint64 size)
{
    if(size < 0)
    {
        return "0.0B/s";
    }

    const QString &label = size2Number(size);
    if(size < MH_KB2B)
    {
        return QString("%1B/s").arg(label);
    }
    else if(MH_KB2B <= size && size < MH_MB2B)
    {
        return QString("%1K/s").arg(label);
    }
    else if(MH_MB2B <= size && size < MH_GB2B)
    {
        return QString("%1M/s").arg(label);
    }
    else if(MH_GB2B <= size && size < MH_TB2B)
    {
        return QString("%1G/s").arg(label);
    }
    else
    {
        return QString("%1T/s").arg(label);
    }
}
