#include "downloadunits.h"
#include "downloadlistitemwidget.h"
#include "downloadthreadmanager.h"
#include <QDebug>

DownloadUnits::DownloadUnits(const QString &url, QObject *parent)
    : QObject(parent), m_url(url)
{
    m_downloadItem = new DownloadListItemWidget(nullptr);
    m_downloadThread = new DownloadThreadManager(this);

    connect(m_downloadThread, SIGNAL(progressChanged(qint64,qint64)),
            m_downloadItem, SLOT(progressChanged(qint64,qint64)));
    connect(m_downloadThread, SIGNAL(updateFileInfoChanged(QString,qint64)),
            m_downloadItem, SLOT(updateFileInfoChanged(QString,qint64)));
    connect(m_downloadThread, SIGNAL(stateChanged(QString)),
            m_downloadItem, SLOT(stateChanged(QString)));
    connect(m_downloadThread, SIGNAL(downloadingFinished()), SLOT(downloadingFinished()));

    m_pause = false;
}

DownloadUnits::~DownloadUnits()
{
    pause();
    delete m_downloadItem;
    delete m_downloadThread;
}

QString DownloadUnits::getClassName()
{
    return staticMetaObject.className();
}

DownloadListItemWidget* DownloadUnits::getDownloadItemWidget()
{
    return m_downloadItem;
}

void DownloadUnits::pause()
{
    m_pause = true;
    m_downloadThread->pause();
}

void DownloadUnits::start()
{
    if(!m_pause)
    {
        m_downloadThread->downloadFile(m_url);
    }
    else
    {
        m_downloadThread->restart();
    }
}

int DownloadUnits::getState() const
{
    return m_downloadThread->getState();
}

void DownloadUnits::setStateChanged(const QString &state)
{
    m_downloadItem->stateChanged(state);
}

void DownloadUnits::downloadingFinished()
{
    emit removeItemWidget(this);
}
