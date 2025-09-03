#include "downloadunits.h"
#include "downloadlistitemwidget.h"
#include "downloadthreadmanager.h"

DownloadUnits::DownloadUnits(const QString &url, QObject *parent)
    : DownloadUnits(url, {}, parent)
{
}

DownloadUnits::DownloadUnits(const QString &url, const QString &name, QObject *parent)
    : QObject(parent),
      m_pause(false),
      m_url(url),
      m_name(name)
{
    m_item = new DownloadListItemWidget;
    m_manager = new DownloadThreadManager(this);

    connect(m_item, SIGNAL(itemLeftDoublePressed()), parent, SLOT(itemLeftDoublePressed()));
    connect(m_manager, SIGNAL(progressChanged(qint64,qint64)), m_item, SLOT(progressChanged(qint64,qint64)));
    connect(m_manager, SIGNAL(updateFileInfoChanged(QString,qint64)), m_item, SLOT(updateFileInfoChanged(QString,qint64)));
    connect(m_manager, SIGNAL(stateChanged(QString)), m_item, SLOT(stateChanged(QString)));
    connect(m_manager, SIGNAL(downloadFinished(QString)), SLOT(downloadFinished(QString)));
}

DownloadUnits::~DownloadUnits()
{
    pause();
    delete m_item;
    delete m_manager;
}

DownloadListItemWidget* DownloadUnits::widget() const noexcept
{
    return m_item;
}

void DownloadUnits::start()
{
    if(m_pause)
    {
        m_manager->restart();
    }
    else
    {
        m_manager->download(m_url, m_name);
        m_path = m_manager->path();

        if(m_name.isEmpty())
        {
            m_name = QFileInfo(m_path).fileName();
        }
    }
}

void DownloadUnits::pause()
{
    m_pause = true;
    m_manager->pause();
}

void DownloadUnits::queue()
{
    m_manager->queue();
}

TTK::DownloadState DownloadUnits::state() const noexcept
{
    return m_manager->state();
}

bool DownloadUnits::isRunning() const noexcept
{
    const TTK::DownloadState state = m_manager->state();
    return state == TTK::DownloadState::Download || state == TTK::DownloadState::Wait;
}

void DownloadUnits::downloadFinished(const QString &path)
{
    if(path.isEmpty())
    {
        Q_EMIT removeItemWidget(nullptr);
    }
    else
    {
        m_path = path;
        Q_EMIT removeItemWidget(this);
    }
}
