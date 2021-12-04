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

void DownloadRunTimeManager::run() const
{
    TTK_LOGGER_INFO("DownloadApplication Begin");

#if !TTK_QT_VERSION_CHECK(5,0,0)
    DownloadUtils::Codec::setLocalCodec();
#endif

    TTK_LOGGER_INFO("Load Translation");
    DownloadSysConfigManager *xml = new DownloadSysConfigManager;
    xml->readXMLConfig();
    xml->readSysLoadConfig();

    ///////////////////////////////////////////////////////
    QFont font;
    QStringList fts(QFontDatabase().families(QFontDatabase::Any));
    int index = G_SETTING_PTR->value(DownloadSettingManager::SkinFontChoiced).toInt();
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
    G_NETWORK_PTR->start();
    index = G_SETTING_PTR->value(DownloadSettingManager::CloseNetWorkChoiced).toInt();
    G_NETWORK_PTR->setBlockNetWork(index);

    delete xml;
    TTK_LOGGER_INFO("End load translation");
}

QString DownloadRunTimeManager::translator() const
{
    return DownloadUtils::Core::languageName(0);
}
