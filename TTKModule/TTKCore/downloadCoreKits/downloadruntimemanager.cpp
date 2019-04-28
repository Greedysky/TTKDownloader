#include "downloadruntimemanager.h"
#include "downloadsysconfigmanager.h"
#include "downloadsettingmanager.h"
#include "downloadnetworkthread.h"
#include "downloadcoreutils.h"
#include "downloadcodecutils.h"

#include <QApplication>
#include <QFontDatabase>

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

#ifndef TTK_GREATER_NEW
    DownloadUtils::Codec::setLocalCodec();
#endif

    M_LOGGER_INFO("Load Translation");
    DownloadSysConfigManager *xml = new DownloadSysConfigManager;
    xml->readXMLConfig();
    xml->readSysLoadConfig();

    ///////////////////////////////////////////////////////
    QFont font;
    QStringList fts(QFontDatabase().families(QFontDatabase::Any));
    int index = M_SETTING_PTR->value(DownloadSettingManager::SkinFontChoiced).toInt();
    if(index >= 0 && index < fts.count())
    {
        font.setFamily(fts[index]);
    }
#ifdef Q_OS_UNIX
    font.setPixelSize(13);
#endif
    qApp->setFont(font);
    ///////////////////////////////////////////////////////

    //detect the current network state
    M_NETWORK_PTR->start();
    index = M_SETTING_PTR->value(DownloadSettingManager::CloseNetWorkChoiced).toInt();
    M_NETWORK_PTR->setBlockNetWork(index);

    delete xml;
    M_LOGGER_INFO("End load translation");
}

QString DownloadRunTimeManager::translator() const
{
    return DownloadUtils::Core::getLanguageName(0);
}
