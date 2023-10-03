#include "downloadnetworkspeedthread.h"
#include "downloadobject.h"

#include <QProcess>
#ifdef Q_OS_WIN
#  ifdef Q_CC_GNU
#    include <winsock2.h>
#  endif
#  include <qt_windows.h>
#  include <cstdio>
#  include <iphlpapi.h>
#elif defined Q_OS_UNIX
#  include <ifaddrs.h>
#  include <arpa/inet.h>
#endif

DownloadNetworkSpeedThread::DownloadNetworkSpeedThread(QObject *parent)
    : TTKAbstractThread(parent),
      m_process(nullptr)
{
#ifdef Q_OS_UNIX
    setAvailableNewtworkNames(QStringList("eth0"));
#endif
}

DownloadNetworkSpeedThread::~DownloadNetworkSpeedThread()
{
    stop();
    if(m_process)
    {
        m_process->kill();
    }
    delete m_process;
}

void DownloadNetworkSpeedThread::setAvailableNewtworkNames(const QStringList &names)
{
    m_names = names;
#ifdef Q_OS_UNIX
    if(m_names.isEmpty())
    {
        return;
    }

    delete m_process;
    m_process = new QProcess(this);
    m_process->setProcessChannelMode(QProcess::MergedChannels);
    connect(m_process, SIGNAL(readyReadStandardOutput()), SLOT(outputRecieved()));
    m_process->start(MAKE_NET_PATH_FULL, {m_names.front(), "1"});
#endif
}

QStringList DownloadNetworkSpeedThread::availableNewtworkNames() const
{
    return m_names;
}

QStringList DownloadNetworkSpeedThread::newtworkNames() const
{
    QStringList names;
#ifdef Q_OS_WIN
    PMIB_IFTABLE pTable = nullptr;
    DWORD dwAdapters = 0;
    ULONG uRetCode = GetIfTable(pTable, &dwAdapters, TRUE);
    if(uRetCode == ERROR_NOT_SUPPORTED)
    {
        return names;
    }

    if(uRetCode == ERROR_INSUFFICIENT_BUFFER)
    {
        pTable = (PMIB_IFTABLE)new BYTE[65535];
    }

    if(!pTable)
    {
        return {};
    }

    GetIfTable(pTable, &dwAdapters, TRUE);
    for(UINT i = 0; i < pTable->dwNumEntries; ++i)
    {
        MIB_IFROW Row = pTable->table[i];
        TTKString s(TTKReinterpretCast(char const*, Row.bDescr));
        QString qs = QString::fromStdString(s);
        if((Row.dwType == 71 || Row.dwType == 6) && !names.contains(qs))
        {
            names << qs;
        }
    }
    delete[] pTable;
#elif defined Q_OS_UNIX
    struct ifaddrs *ifa = nullptr, *ifList;
    if(getifaddrs(&ifList) < 0)
    {
        return {};
    }

    for(ifa = ifList; ifa != nullptr; ifa = ifa->ifa_next)
    {
        if(ifa->ifa_addr && ifa->ifa_addr->sa_family == AF_INET)
        {
            names << QString(ifa->ifa_name);
        }
    }
    freeifaddrs(ifList);
#endif
    return names;
}

void DownloadNetworkSpeedThread::outputRecieved()
{
#ifdef Q_OS_UNIX
    while(m_process->canReadLine())
    {
        const QByteArray &datas = m_process->readLine();
        const QStringList &list = QString(datas).split("|");
        ulong upload = 0, download = 0;

        if(list.count() == 3)
        {
            download= list[1].trimmed().toULong();
            upload  = list[2].trimmed().toULong();
        }
        Q_EMIT networkData(upload, download);
    }
#endif
}

void DownloadNetworkSpeedThread::run()
{
#ifdef Q_OS_WIN
    PMIB_IFTABLE pTable = nullptr;
    DWORD dwAdapters = 0;
    ULONG uRetCode = GetIfTable(pTable, &dwAdapters, TRUE);

    if(uRetCode == ERROR_NOT_SUPPORTED)
    {
        return;
    }

    if(uRetCode == ERROR_INSUFFICIENT_BUFFER)
    {
        pTable = (PMIB_IFTABLE)new BYTE[65535];
    }

    DWORD dwLastIn = 0, dwLastOut = 0;
    DWORD dwBandIn = 0, dwBandOut = 0;

    while(m_running)
    {
        GetIfTable(pTable, &dwAdapters, TRUE);
        DWORD dwInOctets = 0, dwOutOctets = 0;

        for(UINT i = 0; i < pTable->dwNumEntries; ++i)
        {
            MIB_IFROW Row = pTable->table[i];
            if(Row.dwType <= 23)
            {
                dwInOctets += Row.dwInOctets;
                dwOutOctets += Row.dwOutOctets;
            }
        }

        dwBandIn = dwInOctets - dwLastIn;
        dwBandOut = dwOutOctets - dwLastOut;

        if(dwLastIn <= 0)
        {
            dwBandIn = 0;
        }

        if(dwLastOut <= 0)
        {
            dwBandOut = 0;
        }

        dwLastIn = dwInOctets;
        dwLastOut = dwOutOctets;

        Q_EMIT networkData(dwBandOut, dwBandIn);
        msleep(500);
    }
    delete[] pTable;
#endif
}
