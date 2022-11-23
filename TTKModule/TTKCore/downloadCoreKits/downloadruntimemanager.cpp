#include "downloadruntimemanager.h"
#include "downloadsysconfigmanager.h"
#include "downloadsettingmanager.h"
#include "downloadnetworkthread.h"
#include "downloadcodecutils.h"

#include <QApplication>
#include <QFontDatabase>

namespace DownloadObject
{
static QString languageCore(int index)
{
    QString lan(LANGUAGE_DIR_FULL);
    switch(index)
    {
        case 0: return lan.append("cn.ln");
        case 1: return lan.append("tc.ln");
        case 2: return lan.append("en.ln");
        default: return QString();
    }
}
}


DownloadRunTimeManager::DownloadRunTimeManager()
{

}

void DownloadRunTimeManager::run() const
{
    TTK_INFO_STREAM("DownloadApplication Begin");

    DownloadUtils::Codec::setLocalCodec();

    TTK_INFO_STREAM("Load Translation");
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
    TTK_INFO_STREAM("End load translation");
}

QString DownloadRunTimeManager::translator() const
{
    return DownloadObject::languageCore(0);
}
