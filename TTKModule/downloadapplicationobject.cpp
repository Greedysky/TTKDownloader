#include "downloadapplicationobject.h"
#include "downloadapplication.h"
#include "downloadsettingmanager.h"
#include "downloadmessageaboutdialog.h"
#include "downloadimageutils.h"
#include "ttknumberdefine.h"
#include "ttkdesktopwrapper.h"

#include <QTimer>
#include <QPropertyAnimation>

DownloadApplicationObject *DownloadApplicationObject::m_instance = nullptr;

DownloadApplicationObject::DownloadApplicationObject(QObject *parent)
    : QObject(parent)
{
    m_instance = this;

    appResetWindow();

    m_animation = new QPropertyAnimation(DownloadApplication::instance(), "windowOpacity", this);
}

DownloadApplicationObject::~DownloadApplicationObject()
{
    Q_CLEANUP_RESOURCE(TTKDownloader);

    delete m_animation;
}

DownloadApplicationObject *DownloadApplicationObject::instance()
{
    return m_instance;
}

void DownloadApplicationObject::quit()
{
    qApp->exit();
}

void DownloadApplicationObject::windowCloseAnimation()
{
    float v = G_SETTING_PTR->value(DownloadSettingManager::BackgroundTransparent).toInt();
    v = TTK::Image::reRenderValue<float>(1.0f, 0.35f, v);
    m_animation->stop();
    m_animation->setDuration(TTK_DN_S2MS / 2);
    m_animation->setStartValue(v);
    m_animation->setEndValue(0);
    m_animation->start();

    QTimer::singleShot(TTK_DN_S2MS, this, SLOT(quit()));
}

void DownloadApplicationObject::appAboutUs()
{
    DownloadMessageAboutDialog().exec();
}

void DownloadApplicationObject::appResetWindow()
{
    const QRect &geometry = TTKDesktopWrapper::geometry();
    G_SETTING_PTR->setValue(DownloadSettingManager::ScreenSize, geometry.size());
    G_SETTING_PTR->setValue(DownloadSettingManager::WidgetSize, QSize(WINDOW_WIDTH_MIN, WINDOW_HEIGHT_MIN));

    QWidget *w = DownloadApplication::instance();
    if(w->isMaximized() || w->isMinimized() || w->isFullScreen())
    {
        w->showNormal();
    }
    w->setGeometry((geometry.width() - WINDOW_WIDTH_MIN) / 2, (geometry.height() - WINDOW_HEIGHT_MIN) / 2, WINDOW_WIDTH_MIN, WINDOW_HEIGHT_MIN);
}
