#include "downloadthreadmanager.h"
#include "downloadobject.h"
#include "downloadbreakpointconfigmanager.h"
#include "downloadcoreutils.h"
#include "downloadurlencoder.h"

#include <QDebug>
#include <QFileInfo>
#include <QEventLoop>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QNetworkAccessManager>

DownloadThreadManager::DownloadThreadManager(QObject *parent)
    : QObject(parent)
{
    m_file = nullptr;
    m_state = DownloadThread::D_Stop;
}

DownloadThreadManager::~DownloadThreadManager()
{
    delete m_file;
    qDeleteAll(m_threads);
}

QString DownloadThreadManager::getClassName()
{
    return staticMetaObject.className();
}

qint64 DownloadThreadManager::getFileSize(const QString &url, int tryTimes)
{
    qint64 size = -1;
    while(tryTimes--)
    {
        QNetworkAccessManager manager;
        QEventLoop loop;
        QNetworkRequest request;
        request.setUrl(url);
    #ifndef QT_NO_SSL
        QSslConfiguration sslConfig = request.sslConfiguration();
        sslConfig.setPeerVerifyMode(QSslSocket::VerifyNone);
        request.setSslConfiguration(sslConfig);
    #endif
        QNetworkReply *reply = manager.head(request);
        if(!reply)
        {
            continue;
        }
        connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
        loop.exec();

        if(reply->error() != QNetworkReply::NoError)
        {
            continue;
        }

        size = reply->header(QNetworkRequest::ContentLengthHeader).toLongLong();
        reply->deleteLater();
        break;
    }
    return size;
}

QString DownloadThreadManager::getDownloadedPath() const
{
    return m_file ? m_file->fileName() : QString();
}

bool DownloadThreadManager::downloadFile(const QString &url, const QString &name)
{
    emit stateChanged(tr("D_Waiting"));

    if(m_state == DownloadThread::D_Download)
    {
        qDebug() << "Current is downloading a file";
        return false;
    }

    m_state = DownloadThread::D_Waiting;
    if(THREADCOUNT < 1 || THREADCOUNT > 15)
    {
        qDebug() << "Download thread count error";
        return false;
    }

    QString durl(DownloadUrlEncoder().decoder(url));
    if((m_totalSize = getFileSize(durl)) == -1)
    {
        qDebug() << "Download file size error";
        return false;
    }

#ifdef DOWNLOAD_WINEXTRAS
    QString fileName = QUrl(durl).fileName();
#else
    const QString ourPath = QUrl(durl).path();
    const int slash = ourPath.lastIndexOf(QLatin1Char('/'));
    QString fileName = (slash == -1) ? ourPath : ourPath.mid(slash + 1);
#endif
    ////////////////////////////////////////////////
    if(name.isEmpty())
    {
        QDir dir(DownloadUtils::Core::downloadPrefix());
        QString idFileName = fileName;
        for(int i=1; i<99; ++i)
        {
            if(!dir.entryList().contains(idFileName))
            {
                break;
            }
            const int slash = fileName.lastIndexOf(QLatin1Char('.'));
            idFileName = (slash == -1) ? fileName : fileName.left(slash);
            QString sufix = (slash == -1) ? fileName : fileName.mid(slash);
            if(idFileName == sufix)
            {
                sufix.clear();
            }
            idFileName = QString("%1(%2)%3").arg(idFileName).arg(i).arg(sufix);
        }
        fileName = idFileName;
    }
    else
    {
        fileName = name;
    }
    ////////////////////////////////////////////////
    emit updateFileInfoChanged(fileName, m_totalSize);

    fileName = DownloadUtils::Core::downloadPrefix() + fileName;

    DownloadBreakPointConfigManager manager;
    DownloadBreakPointItems records;
    if(manager.readConfig(fileName + SET_FILE))
    {
        manager.readBreakPointConfig(records);
    }

    m_readySize = 0;
    m_file = new QFile(fileName, this);
    if(!m_file->open(QFile::WriteOnly))
    {
        m_file->close();
        qDebug() << "Can not open file : " + m_file->errorString();
        delete m_file;
        m_file = nullptr;
        return false;
    }

    m_file->resize(m_totalSize);
    qDeleteAll(m_threads);
    m_threads.clear();

    for(int i=0; i<THREADCOUNT; ++i)
    {
        qint64 startPoint = m_totalSize * i / THREADCOUNT;
        qint64 endPoint = m_totalSize * (i + 1) / THREADCOUNT;
        qint64 readySize = 0;

        if(!records.isEmpty())
        {
            DownloadBreakPointItem item = records[i];
            startPoint = !item.isEmpty() ? item.m_start : startPoint;
            endPoint = !item.isEmpty() ? item.m_end : endPoint;
            readySize = !item.isEmpty() ? item.m_ready : readySize;
        }

        DownloadThread *thread = new DownloadThread(this);
        connect(thread, SIGNAL(finished(int)), SLOT(finishedSlot(int)));
        connect(thread, SIGNAL(downloadChanged()), SLOT(progressChangedSlot()));
        connect(thread, SIGNAL(errorCode(int,QString)), SLOT(errorSlot(int,QString)));
        thread->startDownload(i, durl, m_file, startPoint, endPoint, readySize);
        m_threads.append(thread);
    }

    m_state = DownloadThread::D_Download;
    emit stateChanged(tr("D_Download"));
    m_runningCount = THREADCOUNT;

    return true;
}

void DownloadThreadManager::downloadingFinish()
{
    QString fileName = m_file->fileName();
    m_file->flush();
    m_file->close();
    delete m_file;
    m_file = nullptr;
    m_state = DownloadThread::D_Finished;

    QFile::remove(fileName + SET_FILE);

    qDeleteAll(m_threads);
    m_threads.clear();

    emit stateChanged(tr("D_Finished"));
    emit downloadingFinished(fileName);
}

void DownloadThreadManager::pause()
{
    if(m_state != DownloadThread::D_Download && m_state != DownloadThread::D_Waiting)
    {
        qDebug() << "Current is not downloading";
        return;
    }

    m_state = DownloadThread::D_Pause;
    emit stateChanged(tr("D_Pause"));

    DownloadBreakPointItems records;
    foreach(DownloadThread *thread, m_threads)
    {
        thread->pause();

        DownloadBreakPointItem item;
        item.m_url = thread->getUrl();
        item.m_start = thread->getStartPoint();
        item.m_end = thread->getEndPoint();
        item.m_ready = thread->getReadySize();
        records << item;
    }

    if(m_file)
    {
        DownloadBreakPointConfigManager manager;
        if(manager.writeConfig(m_file->fileName() + SET_FILE))
        {
            manager.writeBreakPointConfig(records);
        }
    }
}

void DownloadThreadManager::restart()
{
    if(m_state != DownloadThread::D_Pause)
    {
        qDebug() << "Current is not paused";
        return;
    }

    m_state = DownloadThread::D_Download;
    emit stateChanged(tr("D_Download"));

    foreach(DownloadThread *thread, m_threads)
    {
        thread->restart();
    }
}

void DownloadThreadManager::finishedSlot(int index)
{
    m_runningCount--;
    qDebug() << "Download index of " << index << " finished";

    if(m_runningCount == 0 && m_state == DownloadThread::D_Download)
    {
        downloadingFinish();
    }
}

void DownloadThreadManager::progressChangedSlot()
{
    m_readySize = 0;
    foreach(DownloadThread *thread, m_threads)
    {
        m_readySize += thread->getReadySize();
    }

    emit progressChanged(m_readySize, m_totalSize);
}

void DownloadThreadManager::errorSlot(int index, const QString &errorString)
{
    if(index < 0 || index >= m_threads.count())
    {
        return;
    }

    m_threads[index]->pause();
    qDebug() << "Download index of " << index << " error: " << errorString;
}
