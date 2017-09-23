#include "downloadlocalpeer.h"
#include "downloadlockedfile.h"

#include <QCoreApplication>
#include <QDataStream>
#include <QTime>
#include <QLocalServer>
#include <QLocalSocket>
#include <QDir>

#if defined(Q_OS_WIN)
#include <QLibrary>
#include <qt_windows.h>
typedef BOOL(WINAPI*PProcessIdToSessionId)(DWORD,DWORD*);
static PProcessIdToSessionId pProcessIdToSessionId = 0;
#endif
#if defined(Q_OS_UNIX)
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#endif

namespace DownloadLockedPrivate {
#include "downloadlockedfile.cpp"
#if defined(Q_OS_WIN)
#include "downloadlockedfile_win.cpp"
#else
#include "downloadlockedfile_unix.cpp"
#endif
}

class DownloadLocalPeerPrivate : public DownloadPrivate<DownloadLocalPeer>
{
public:
    DownloadLocalPeerPrivate();
    ~DownloadLocalPeerPrivate();

    QString m_id;
    QString m_socketName;
    QLocalServer *m_server;
    DownloadLockedPrivate::DownloadLockedFile m_lockFile;
    static const char *m_ack;
};
const char *DownloadLocalPeerPrivate::m_ack = "ack";

DownloadLocalPeerPrivate::DownloadLocalPeerPrivate()
{
    m_server = nullptr;
}

DownloadLocalPeerPrivate::~DownloadLocalPeerPrivate()
{
    delete m_server;
}

//////////////////////////////////////////////////////
//////////////////////////////////////////////////////
///
///

DownloadLocalPeer::DownloadLocalPeer(QObject *parent, const QString &appId)
    : QObject(parent)
{
    DOWNLOAD_INIT_PRIVATE;
    DOWNLOAD_D(DownloadLocalPeer);

    QString prefix = d->m_id = appId;
    if(prefix.isEmpty())
    {
        d->m_id = QCoreApplication::applicationFilePath();
#if defined(Q_OS_WIN)
        d->m_id = d->m_id.toLower();
#endif
        prefix = d->m_id.section(QLatin1Char('/'), -1);
    }
    prefix.remove(QRegExp("[^a-zA-Z]"));
    prefix.truncate(6);

    QByteArray idc = d->m_id.toUtf8();
    quint16 idNum = qChecksum(idc.constData(), idc.size());
    d->m_socketName = QLatin1String("qtsingleapp-") + prefix +
                      QLatin1Char('-') + QString::number(idNum, 16);

#if defined(Q_OS_WIN)
    if(!pProcessIdToSessionId)
    {
        QLibrary lib("kernel32");
        pProcessIdToSessionId = (PProcessIdToSessionId)lib.resolve("ProcessIdToSessionId");
    }
    if(pProcessIdToSessionId)
    {
        DWORD sessionId = 0;
        pProcessIdToSessionId(GetCurrentProcessId(), &sessionId);
        d->m_socketName += QLatin1Char('-') + QString::number(sessionId, 16);
    }
#else
    d->m_socketName += QLatin1Char('-') + QString::number(::getuid(), 16);
#endif

    d->m_server = new QLocalServer(this);
    QString lockName = QDir(QDir::tempPath()).absolutePath()
                       + QLatin1Char('/') + d->m_socketName
                       + QLatin1String("-lockfile");
    d->m_lockFile.setFileName(lockName);
    d->m_lockFile.open(QIODevice::ReadWrite);
}

bool DownloadLocalPeer::isClient()
{
    DOWNLOAD_D(DownloadLocalPeer);
    if(d->m_lockFile.isLocked())
    {
        return false;
    }

    if(!d->m_lockFile.lock(DownloadLockedPrivate::DownloadLockedFile::WriteLock, false))
    {
        return true;
    }

    bool res = d->m_server->listen(d->m_socketName);
#if defined(Q_OS_UNIX) && (QT_VERSION >= QT_VERSION_CHECK(4,5,0))
    // ### Workaround
    if(!res && d->m_server->serverError() == QAbstractSocket::AddressInUseError)
    {
        QFile::remove(QDir::cleanPath(QDir::tempPath()) + QLatin1Char('/') + d->m_socketName);
        res = d->m_server->listen(d->m_socketName);
    }
#endif
    if(!res)
    {
        qWarning("Application: listen on local socket failed, %s", qPrintable(d->m_server->errorString()));
    }

    connect(d->m_server, SIGNAL(newConnection()), SLOT(receiveConnection()));
    return false;
}

bool DownloadLocalPeer::sendMessage(const QString &message, int timeout)
{
    DOWNLOAD_D(DownloadLocalPeer);
    if(!isClient())
    {
        return false;
    }

    QLocalSocket socket;
    bool connOk = false;
    for(int i=0; i<2; i++)
    {
        // Try twice, in case the other instance is just starting up
        socket.connectToServer(d->m_socketName);
        connOk = socket.waitForConnected(timeout/2);
        if(connOk || i)
        {
            break;
        }
        int ms = 250;
#if defined(Q_OS_WIN)
        Sleep(DWORD(ms));
#else
        struct timespec ts = { ms / 1000, (ms % 1000) * 1000 * 1000 };
        nanosleep(&ts, NULL);
#endif
    }
    if(!connOk)
    {
        return false;
    }

    QByteArray uMsg(message.toUtf8());
    QDataStream ds(&socket);
    ds.writeBytes(uMsg.constData(), uMsg.size());

    bool res = socket.waitForBytesWritten(timeout);
    if(res)
    {
        res &= socket.waitForReadyRead(timeout);   // wait for ack
        if(res)
        {
            res &= (socket.read(qstrlen(d->m_ack)) == d->m_ack);
        }
    }
    return res;
}

QString DownloadLocalPeer::applicationId() const
{
    DOWNLOAD_D(DownloadLocalPeer);
    return d->m_id;
}

void DownloadLocalPeer::receiveConnection()
{
    DOWNLOAD_D(DownloadLocalPeer);
    QLocalSocket *socket = d->m_server->nextPendingConnection();
    if(!socket)
    {
        return;
    }

    while(true)
    {
        if(socket->state() == QLocalSocket::UnconnectedState)
        {
            qWarning("QtLocalPeer: Peer disconnected");
            delete socket;
            return;
        }
        
        if(socket->bytesAvailable() >= qint64(sizeof(quint32)))
        {
            break;
        }
        socket->waitForReadyRead();
    }

    QDataStream ds(socket);
    QByteArray uMsg;
    quint32 remaining;
    ds >> remaining;
    uMsg.resize(remaining);

    int got = 0;
    char *uMsgBuf = uMsg.data();
    do
    {
        got = ds.readRawData(uMsgBuf, remaining);
        remaining -= got;
        uMsgBuf += got;
    }while(remaining && got >= 0 && socket->waitForReadyRead(2000));
    if(got < 0)
    {
        qWarning("DownloadtLocalPeer: Message reception failed %s", socket->errorString().toLatin1().constData());
        delete socket;
        return;
    }

    QString message(QString::fromUtf8(uMsg));
    socket->write(d->m_ack, qstrlen(d->m_ack));
    socket->waitForBytesWritten(1000);
    socket->waitForDisconnected(1000); // make sure client reads ack
    delete socket;

    emit messageReceived(message); //### (might take a long time to return)
}
