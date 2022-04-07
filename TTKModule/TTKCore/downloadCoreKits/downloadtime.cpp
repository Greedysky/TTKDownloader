#include "downloadtime.h"

#include <QDateTime>

DownloadTime::DownloadTime()
{
    m_defaultType = All_Msec;
    m_greedyMode = false;
    initialize();
}

DownloadTime::DownloadTime(const DownloadTime &other)
{
    copyToThis(other);
}

DownloadTime::DownloadTime(qint64 value, Type type)
    : DownloadTime()
{
    m_defaultType = type;
    fromTimeStamp(value, type == All_Sec ? MT_S : MT_S2MS);
}

DownloadTime::DownloadTime(int day, int hour, int min, int sec, int msec)
    : DownloadTime()
{
    m_defaultType = All_Msec;
    setHMSM(day, hour, min, sec, msec);
}

void DownloadTime::setHMSM(int day, int hour, int min, int sec, int msec)
{
    initialize();

    int delta = 0;
    delta = msec >= MT_S2MS ? msec / MT_S2MS : 0;
    m_msec = msec % MT_S2MS;

    sec += delta;
    delta = sec >= MT_M2S ? sec / MT_M2S : 0;
    m_sec = sec % MT_M2S;

    min += delta;
    delta = min >= MT_H2M ? min / MT_H2M : 0;
    m_min = min % MT_H2M;

    hour += delta;
    m_day = hour >= MT_D2H ? hour / MT_D2H : 0;
    m_hour = hour % MT_D2H;

    m_day += day;
}

bool DownloadTime::isNull() const
{
    return (m_hour == 0 && m_min == 0 && m_sec == 0 && m_msec == 0);
}

bool DownloadTime::isValid() const
{
    return !isNull();
}

DownloadTime DownloadTime::fromString(const QString &s, const QString &format)
{
    DownloadTime time;
    QTime t = QTime::fromString(s, format);
    time.setHMSM(0, t.hour(), t.minute(), t.second(), t.msec());
    return time;
}

QString DownloadTime::toString(qint64 value, Type type, const QString &format)
{
    return DownloadTime(value, type).toString(format);
}

QString DownloadTime::toString(const QString &format) const
{
    return QTime(m_hour, m_min, m_sec, m_msec).toString(format);
}

qint64 DownloadTime::timeStamp(Type type) const
{
    qint64 delta = (type == All_Sec) ? MT_S : MT_S2MS;
           delta = (m_day*MT_D2S + m_hour*MT_H2S + m_min*MT_M2S + m_sec)*delta;
    return (type == All_Sec) ? delta : (delta + m_msec);
}

qint64 DownloadTime::timeStamp(bool ms)
{
    qint64 t = QDateTime::currentMSecsSinceEpoch();
    return ms ? t : t / 1000;
}

QString DownloadTime::msecTime2LabelJustified() const
{
    if(!m_greedyMode)
    {
        return toString("mm:ss");
    }
    else
    {
        int min = m_day*MT_H2S + MT_H*m_hour + m_min;
        return QString::number(min).rightJustified(2, '0') + ":" +
               QString::number(m_sec).rightJustified(2, '0');
    }
}

QString DownloadTime::msecTime2LabelJustified(qint64 time, bool greedy)
{
    const DownloadTime t(time, DownloadTime::All_Msec);
    if(!greedy || time < MT_H2S * MT_S2MS)
    {
        return t.toString("mm:ss");
    }
    else
    {
        int min = t.day() * MT_H2S + MT_H * t.hour() + t.minute();
        return QString::number(min).rightJustified(2, '0') + ":" +
               QString::number(t.second()).rightJustified(2, '0');
    }
}

QString DownloadTime::normalTime2Label() const
{
    if(m_day == 0 && m_hour == 0 && m_min == 0)
    {
        return QString::number(m_sec) + QObject::tr("ss");
    }
    else if(m_day == 0 && m_hour == 0 && m_min != 0)
    {
        return QString::number(m_min) + QObject::tr("mm");
    }
    else if(m_day == 0 && m_hour != 0)
    {
        return QString::number(m_hour) + QObject::tr("hh");
    }
    else if(m_day != 0)
    {
        return QString::number(m_day) + QObject::tr("day");
    }
    else
    {
        return QString();
    }
}

QString DownloadTime::normalTime2Label(qint64 time)
{
    if(time < MT_M2S)
    {
        return QString::number(time) + QObject::tr("ss");
    }
    else if(MT_M2S <= time && time < MT_H2S)
    {
        return QString::number(time/MT_M2S) + QObject::tr("mm");
    }
    else if(MT_H2S <= time && time < MT_D2S)
    {
        return QString::number(time/MT_H2S) + QObject::tr("hh");
    }
    else
    {
        return QString::number(time/MT_D2S) + QObject::tr("day");
    }
}

DownloadTime& DownloadTime::operator= (const DownloadTime &other)
{
    copyToThis(other);
    return *this;
}

DownloadTime& DownloadTime::operator+= (const DownloadTime &other)
{
    qint64 t = timeStamp(All_Msec) + other.timeStamp(All_Msec);
    fromTimeStamp(t, m_defaultType == All_Sec ? MT_S : MT_S2MS);
    return *this;
}

DownloadTime& DownloadTime::operator+= (const int other)
{
    qint64 t = timeStamp(All_Msec) + other;
    fromTimeStamp(t, m_defaultType == All_Sec ? MT_S : MT_S2MS);
    return *this;
}

DownloadTime& DownloadTime::operator-= (const DownloadTime &other)
{
    qint64 t = timeStamp(All_Msec) - other.timeStamp(All_Msec);
    fromTimeStamp(t, m_defaultType == All_Sec ? MT_S : MT_S2MS);
    return *this;
}

DownloadTime& DownloadTime::operator-= (const int other)
{
    qint64 t = timeStamp(All_Msec) - other;
    fromTimeStamp(t, m_defaultType == All_Sec ? MT_S : MT_S2MS);
    return *this;
}

DownloadTime& DownloadTime::operator*= (const int other)
{
    qint64 t = timeStamp(All_Msec) * other;
    fromTimeStamp(t, m_defaultType == All_Sec ? MT_S : MT_S2MS);
    return *this;
}

DownloadTime& DownloadTime::operator/= (const int other)
{
    qint64 t = timeStamp(All_Msec) / other;
    fromTimeStamp(t, m_defaultType == All_Sec ? MT_S : MT_S2MS);
    return *this;
}

DownloadTime DownloadTime::operator+ (const DownloadTime &other)
{
    qint64 t = timeStamp(All_Msec) + other.timeStamp(All_Msec);
    return DownloadTime(t, m_defaultType);
}

DownloadTime DownloadTime::operator+ (const int other)
{
    qint64 t = timeStamp(All_Msec) + other;
    return DownloadTime(t, m_defaultType);
}

DownloadTime DownloadTime::operator- (const DownloadTime &other)
{
    qint64 t = timeStamp(All_Msec) - other.timeStamp(All_Msec);
    return DownloadTime(t, m_defaultType);
}

DownloadTime DownloadTime::operator- (const int other)
{
    qint64 t = timeStamp(All_Msec) - other;
    return DownloadTime(t, m_defaultType);
}

DownloadTime DownloadTime::operator* (const int other)
{
    qint64 t = timeStamp(All_Msec) * other;
    return DownloadTime(t, m_defaultType);
}

DownloadTime DownloadTime::operator/ (const int other)
{
    qint64 t = timeStamp(All_Msec) / other;
    return DownloadTime(t, m_defaultType);
}

bool DownloadTime::operator== (const DownloadTime &other) const
{
    return timeStamp(All_Msec) == other.timeStamp(All_Msec);
}

bool DownloadTime::operator!= (const DownloadTime &other) const
{
    return timeStamp(All_Msec) != other.timeStamp(All_Msec);
}

void DownloadTime::initialize()
{
    m_day = 0;
    m_hour = 0;
    m_min = 0;
    m_sec = 0;
    m_msec = 0;
}

void DownloadTime::copyToThis(const DownloadTime &other)
{
    m_greedyMode = other.m_greedyMode;
    m_defaultType = other.m_defaultType;
    m_day = other.m_day;
    m_hour = other.m_hour;
    m_min = other.m_min;
    m_sec = other.m_sec;
    m_msec = other.m_msec;
}

void DownloadTime::fromTimeStamp(qint64 value, int delta)
{
    if(value < 0)
    {
        initialize();
        return;
    }

    m_day = value/MT_D2S/delta;
    value -= m_day*MT_D2S*delta;

    m_hour = value/MT_H2S/delta;
    value -= m_hour*MT_H2S*delta;

    m_min = value/MT_M2S/delta;
    value -= m_min*MT_M2S*delta;

    m_sec = value/delta;
    if(delta == MT_S2MS)
    {
        value -= (m_sec*delta);
        m_msec = value;
    }
}
