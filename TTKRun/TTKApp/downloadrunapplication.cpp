#include "downloadrunapplication.h"
#include "downloadlocalpeer.h"

#include <QWidget>

class DownloadRunApplicationPrivate : public DownloadPrivate<DownloadRunApplication>
{
public:
    DownloadRunApplicationPrivate();
    ~DownloadRunApplicationPrivate();

    DownloadLocalPeer *m_peer;
    QWidget *m_activeWindow;
};

DownloadRunApplicationPrivate::DownloadRunApplicationPrivate()
{
    m_peer = nullptr;
    m_activeWindow = nullptr;
}

DownloadRunApplicationPrivate::~DownloadRunApplicationPrivate()
{
    delete m_peer;
}

//////////////////////////////////////////////////////
//////////////////////////////////////////////////////
///
///

DownloadRunApplication::DownloadRunApplication(int &argc, char **argv, bool GUIenabled)
    : QApplication(argc, argv, GUIenabled)
{
    DOWNLOAD_INIT_PRIVATE;
    sysInit();
}

DownloadRunApplication::DownloadRunApplication(const QString &appId, int &argc, char **argv)
    : QApplication(argc, argv)
{
    DOWNLOAD_INIT_PRIVATE;
    sysInit(appId);
}

#if QT_VERSION < 0x050000
DownloadRunApplication::DownloadRunApplication(int &argc, char **argv, Type type)
    : QApplication(argc, argv, type)
{
    DOWNLOAD_INIT_PRIVATE;
    sysInit();
}

#  if defined(Q_WS_X11)
DownloadRunApplication::DownloadRunApplication(Display* dpy, Qt::HANDLE visual, Qt::HANDLE cmap)
    : QApplication(dpy, visual, cmap)
{
    DOWNLOAD_INIT_PRIVATE;
    sysInit();
}

DownloadRunApplication::DownloadRunApplication(Display *dpy, int &argc, char **argv, Qt::HANDLE visual, Qt::HANDLE cmap)
    : QApplication(dpy, argc, argv, visual, cmap)
{
    DOWNLOAD_INIT_PRIVATE;
    sysInit();
}

DownloadRunApplication::DownloadRunApplication(Display* dpy, const QString &appId, int argc, char **argv, Qt::HANDLE visual, Qt::HANDLE cmap)
    : QApplication(dpy, argc, argv, visual, cmap)
{
    DOWNLOAD_INIT_PRIVATE;
    sysInit(appId);
}
#  endif
#endif

void DownloadRunApplication::initialize(bool dummy)
{
    Q_UNUSED(dummy);
    isRunning();
}

bool DownloadRunApplication::isRunning() const
{
    DOWNLOAD_D(DownloadRunApplication);
    return d->m_peer->isClient();
}

QString DownloadRunApplication::id() const
{
    DOWNLOAD_D(DownloadRunApplication);
    return d->m_peer->applicationId();
}

void DownloadRunApplication::setActivationWindow(QWidget* aw, bool activateOnMessage)
{
    DOWNLOAD_D(DownloadRunApplication);
    d->m_activeWindow = aw;

    if(activateOnMessage)
    {
        connect(d->m_peer, SIGNAL(messageReceived(QString)), this, SLOT(activateWindow()));
    }
    else
    {
        disconnect(d->m_peer, SIGNAL(messageReceived(QString)), this, SLOT(activateWindow()));
    }
}

QWidget* DownloadRunApplication::activationWindow() const
{
    DOWNLOAD_D(DownloadRunApplication);
    return d->m_activeWindow;
}

bool DownloadRunApplication::sendMessage(const QString &message, int timeout)
{
    DOWNLOAD_D(DownloadRunApplication);
    return d->m_peer->sendMessage(message, timeout);
}

void DownloadRunApplication::activateWindow()
{
    DOWNLOAD_D(DownloadRunApplication);
    if(d->m_activeWindow)
    {
        d->m_activeWindow->setWindowState(d->m_activeWindow->windowState() & ~Qt::WindowMinimized);
        d->m_activeWindow->raise();
        d->m_activeWindow->activateWindow();
    }
}

void DownloadRunApplication::sysInit(const QString &appId)
{
    DOWNLOAD_D(DownloadRunApplication);
    d->m_peer = new DownloadLocalPeer(this, appId);
    connect(d->m_peer, SIGNAL(messageReceived(QString)), SIGNAL(messageReceived(QString)));
}
