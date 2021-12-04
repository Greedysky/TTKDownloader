#include "downloadunits.h"
#include "downloadlistitemwidget.h"
#include "downloadthreadmanager.h"

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
    connect(m_downloadThread, SIGNAL(downloadingFinished(QString)),
                            SLOT(downloadingFinished(QString)));

    m_pause = false;
}

DownloadUnits::~DownloadUnits()
{
    pause();
    delete m_downloadItem;
    delete m_downloadThread;
}

DownloadListItemWidget* DownloadUnits::downloadItemWidget()
{
    return m_downloadItem;
}

void DownloadUnits::pause()
{
    m_pause = true;
    m_downloadThread->pause();
}

void DownloadUnits::start(const QString &name)
{
    if(!m_pause)
    {
        m_downloadThread->downloadFile(m_url, name);
    }
    else
    {
        m_downloadThread->restart();
    }

    m_path = m_downloadThread->downloadedPath();
}

int DownloadUnits::state() const
{
    return m_downloadThread->state();
}

void DownloadUnits::setStateChanged(const QString &state)
{
    m_downloadItem->stateChanged(state);
}

void DownloadUnits::downloadingFinished(const QString &path)
{
    m_path = path;
    emit removeItemWidget(this);
}
