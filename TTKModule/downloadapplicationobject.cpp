#include "downloadapplicationobject.h"
#include "downloadsettingmanager.h"
#include "downloadotherdefine.h"

#include <QApplication>
#include <QDesktopWidget>

DownloadApplicationObject *DownloadApplicationObject::m_instance = nullptr;

DownloadApplicationObject::DownloadApplicationObject(QObject *parent)
    : QObject(parent)
{
    Q_INIT_RESOURCE(TTKDownloader);
    m_instance = this;

    QWidget *widget = QApplication::desktop();
    M_SETTING_PTR->setValue(DownloadSettingManager::ScreenSize, widget->size());
    M_SETTING_PTR->setValue(DownloadSettingManager::WidgetSize, QSize(WINDOW_WIDTH_MIN, WINDOW_HEIGHT_MIN));
}

DownloadApplicationObject::~DownloadApplicationObject()
{
    cleanUp();
    Q_CLEANUP_RESOURCE(TTKDownloader);
}

QString DownloadApplicationObject::getClassName()
{
    return staticMetaObject.className();
}

DownloadApplicationObject *DownloadApplicationObject::instance()
{
    return m_instance;
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
