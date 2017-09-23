#include "downloadwindowextras.h"
#include "downloadapplication.h"

#include <QStyle>
#if defined Q_OS_WIN && defined DOWNLOAD_WINEXTRAS
#   include <QtWinExtras/QtWinExtras>
#endif

DownloadWindowExtras::DownloadWindowExtras(QObject *parent)
    : QObject(parent)
{
#if defined Q_OS_WIN && defined DOWNLOAD_WINEXTRAS
    m_taskbarProgress = nullptr;
    m_taskbarButton = nullptr;
    m_superClass = MStatic_cast(DownloadApplication*, parent);
    disableBlurBehindWindow( QtWin::isCompositionEnabled() );
#  ifdef DOWNLOAD_DEBUG
    createJumpList();
    createTaskbar();
#  endif

#else
    m_disableBlurBehindWindow = true;
#endif
}

DownloadWindowExtras::~DownloadWindowExtras()
{
#if defined Q_OS_WIN && defined DOWNLOAD_WINEXTRAS
    delete m_taskbarProgress;
    delete m_taskbarButton;
#endif
}

QString DownloadWindowExtras::getClassName()
{
    return staticMetaObject.className();
}

void DownloadWindowExtras::disableBlurBehindWindow(bool enable)
{
    m_disableBlurBehindWindow = enable;
#if defined Q_OS_WIN && defined DOWNLOAD_WINEXTRAS
    QtWin::enableBlurBehindWindow(m_superClass);
    QtWin::disableBlurBehindWindow(m_superClass);
#endif
}

#if defined Q_OS_WIN && defined DOWNLOAD_WINEXTRAS
void DownloadWindowExtras::showPlayStatus(bool status) const
{
    if(!status)
    {
#ifdef DOWNLOAD_DEBUG
        m_taskbarButton->setOverlayIcon(m_superClass->style()->standardIcon(QStyle::SP_MediaPause));
        m_taskbarProgress->show();
        m_taskbarProgress->resume();
#endif
    }
    else
    {
#ifdef DOWNLOAD_DEBUG
        m_taskbarButton->setOverlayIcon(m_superClass->style()->standardIcon(QStyle::SP_MediaPlay));
        m_taskbarProgress->show();
        m_taskbarProgress->pause();
#endif
    }
}

void DownloadWindowExtras::setValue(int value) const
{
    m_taskbarProgress->setValue(value);
}

void DownloadWindowExtras::setRange(int start, int end) const
{
    m_taskbarProgress->setRange(start, end);
}

void DownloadWindowExtras::createJumpList() const
{
    QWinJumpList().recent()->setVisible(true);
}

void DownloadWindowExtras::createTaskbar()
{
    m_taskbarButton = new QWinTaskbarButton(this);
    m_taskbarButton->setWindow(m_superClass->windowHandle());
    m_taskbarProgress = m_taskbarButton->progress();
}

#endif
