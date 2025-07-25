#include "downloadapplicationmodule.h"
#include "downloadapplication.h"
#include "downloadsettingmanager.h"
#include "downloadmessageaboutdialog.h"
#include "downloadimageutils.h"
#include "downloadhotkeymanager.h"
#include "ttkdesktopscreen.h"

#include <QTimer>
#include <QPropertyAnimation>

DownloadApplicationModule *DownloadApplicationModule::m_instance = nullptr;

DownloadApplicationModule::DownloadApplicationModule(QObject *parent)
    : QObject(parent)
{
    m_instance = this;

    resetWindowGeometry();

    m_quitAnimation = new QPropertyAnimation(parent, "windowOpacity", this);
    connect(m_quitAnimation, SIGNAL(valueChanged(QVariant)), parent, SLOT(update()));
}

DownloadApplicationModule::~DownloadApplicationModule()
{
    Q_CLEANUP_RESOURCE(TTKModule);
    G_HOTKEY_PTR->unsetShortcut();
    delete m_quitAnimation;
}

DownloadApplicationModule *DownloadApplicationModule::instance()
{
    return m_instance;
}

void DownloadApplicationModule::quit()
{
    qApp->exit();
}

void DownloadApplicationModule::windowCloseAnimation()
{
    float v = G_SETTING_PTR->value(DownloadSettingManager::BackgroundTransparent).toInt();
          v = TTK::Image::boundValue<float>(1.0f, 0.35f, v);

    m_quitAnimation->stop();
    m_quitAnimation->setDuration(TTK_DN_S2MS);
    m_quitAnimation->setStartValue(v);
    m_quitAnimation->setEndValue(0.0f);
    m_quitAnimation->start();

    TTK_SIGNLE_SHOT(TTK_DN_S2MS, this, quit, TTK_SLOT);
}

void DownloadApplicationModule::showAboutWidget()
{
    DownloadMessageAboutDialog().exec();
}

void DownloadApplicationModule::resetWindowGeometry()
{
    const QRect &geometry = TTKDesktopScreen::geometry();
    G_SETTING_PTR->setValue(DownloadSettingManager::ScreenSize, geometry.size());
    G_SETTING_PTR->setValue(DownloadSettingManager::WidgetSize, QSize(WINDOW_WIDTH_MIN, WINDOW_HEIGHT_MIN));

    QWidget *w = DownloadApplication::instance();
    if(w->isMaximized() || w->isMinimized() || w->isFullScreen())
    {
        w->showNormal();
    }
    w->setGeometry((geometry.width() - WINDOW_WIDTH_MIN) / 2, (geometry.height() - WINDOW_HEIGHT_MIN) / 2, WINDOW_WIDTH_MIN, WINDOW_HEIGHT_MIN);
}
