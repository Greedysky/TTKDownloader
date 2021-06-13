#include "downloadapplicationobject.h"
#include "downloadapplication.h"
#include "downloadsettingmanager.h"
#include "downloadotherdefine.h"
#include "downloadnumberdefine.h"
#include "downloadmessageaboutdialog.h"
#include "downloadwidgetutils.h"
#include "ttkdesktopwrapper.h"

#include <QTimer>
#include <QPropertyAnimation>

DownloadApplicationObject *DownloadApplicationObject::m_instance = nullptr;

DownloadApplicationObject::DownloadApplicationObject(QObject *parent)
    : QObject(parent)
{
    Q_INIT_RESOURCE(TTKDownloader);
    m_instance = this;

    appResetWindow();

    m_animation = new QPropertyAnimation(DownloadApplication::instance(), "windowOpacity", this);

}

DownloadApplicationObject::~DownloadApplicationObject()
{
    cleanUp();
    Q_CLEANUP_RESOURCE(TTKDownloader);
    delete m_animation;
}

DownloadApplicationObject *DownloadApplicationObject::instance()
{
    return m_instance;
}

void DownloadApplicationObject::windowCloseAnimation()
{
    float v = M_SETTING_PTR->value(DownloadSettingManager::BgTransparentChoiced).toInt();
    v = DownloadUtils::Widget::reRenderValue<float>(1.0f, 0.35f, v);
    m_animation->stop();
    m_animation->setDuration(MT_S2MS/2);
    m_animation->setStartValue(v);
    m_animation->setEndValue(0);
    m_animation->start();
    QTimer::singleShot(MT_S2MS, qApp, SLOT(quit()));
}

void DownloadApplicationObject::appAboutUs()
{
    DownloadMessageAboutDialog().exec();
}

void DownloadApplicationObject::appVersionUpdate()
{

}

void DownloadApplicationObject::appResetWindow()
{
    const QRect &geometry = TTKDesktopWrapper::geometry();
    M_SETTING_PTR->setValue(DownloadSettingManager::ScreenSize, geometry.size());
    M_SETTING_PTR->setValue(DownloadSettingManager::WidgetSize, QSize(WINDOW_WIDTH_MIN, WINDOW_HEIGHT_MIN));

    QWidget *w = DownloadApplication::instance();
    if(w->isMaximized() || w->isMinimized() || w->isFullScreen())
    {
        w->showNormal();
    }
    w->setGeometry((geometry.width() - WINDOW_WIDTH_MIN)/2, (geometry.height() - WINDOW_HEIGHT_MIN)/2, WINDOW_WIDTH_MIN, WINDOW_HEIGHT_MIN);
}

void DownloadApplicationObject::cleanUp()
{
    QFile::remove(TEMPORARY_DIR);
    QFile::remove(DOWNLOAD_COLOR_FILE);
    QFile::remove(DOWNLOAD_IMAGE_FILE);
    QFile::remove(DOWNLOAD_RECORD_FILE);
    QFile::remove(DOWNLOAD_RECORD_IN_FILE);
    QFile::remove(DOWNLOAD_RECORD_OUT_FILE);
    QFile::remove(DOWNLOAD_NETWORK_TEST_FILE);
}
