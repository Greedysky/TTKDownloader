#include "downloadruntimemanager.h"
#include "downloadsysconfigmanager.h"
#include "downloadsettingmanager.h"
#include "downloadnetworkthread.h"
#include "downloadcoreutils.h"

#include <QFont>
#include <QApplication>

DownloadRunTimeManager::DownloadRunTimeManager()
{

}

QString DownloadRunTimeManager::getClassName()
{
    return "DownloadRunTimeManager";
}

void DownloadRunTimeManager::run() const
{
    M_LOGGER_INFO("DownloadApplication Begin");

#ifndef DOWNLOAD_GREATER_NEW
    DownloadUtils::Core::setLocalCodec();
#endif

    ///////////////////////////////////////////////////////
#ifdef Q_OS_UNIX
    QFont font;
    font.setPixelSize(13);
    qApp->setFont(font);
#endif
    ///////////////////////////////////////////////////////

    //detect the current network state
    M_NETWORK_PTR->start();

    M_LOGGER_INFO("Load Translation");
    DownloadSysConfigManager *xml = new DownloadSysConfigManager;
    xml->readXMLConfig();
    xml->readSysLoadConfig();

    M_NETWORK_PTR->setBlockNetWork(
                M_SETTING_PTR->value(DownloadSettingManager::CloseNetWorkChoiced).toInt());
    delete xml;

    M_LOGGER_INFO("End load translation");
}

QString DownloadRunTimeManager::translator() const
{
    return DownloadUtils::Core::getLanguageName(0);
}
