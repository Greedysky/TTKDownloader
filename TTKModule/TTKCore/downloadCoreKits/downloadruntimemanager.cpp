#include "downloadruntimemanager.h"
#include "downloadconfigmanager.h"
#include "downloadsettingmanager.h"
#include "downloadnetworkthread.h"
#include "downloadcodecutils.h"

#include <QApplication>
#include <QFontDatabase>

namespace TTK
{
    static QString languageCore(int index);

}

QString TTK::languageCore(int index)
{
    QString lan(LANGUAGE_DIR_FULL);
    switch(index)
    {
        case 0: return lan.append("cn.ln");
        case 1: return lan.append("tc.ln");
        case 2: return lan.append("en.ln");
        default: return {};
    }
}


DownloadRunTimeManager::DownloadRunTimeManager()
{

}

void DownloadRunTimeManager::run() const
{
    TTK_INFO_STREAM("DownloadApplication Begin");

#if !TTK_QT_VERSION_CHECK(5,0,0)
    TTK::Codec::setLocalCodec();
#endif

#ifdef Q_OS_UNIX
    QFont font;
    font.setPixelSize(13);
    qApp->setFont(font);
#endif

    //detect the current network state
    G_NETWORK_PTR->start();

    DownloadConfigManager manager;
    manager.fromFile(COFIG_PATH_FULL);
    manager.readBuffer();

    G_NETWORK_PTR->setBlockNetWork(G_SETTING_PTR->value(DownloadSettingManager::CloseNetWorkMode).toBool());
}

QString DownloadRunTimeManager::translator() const
{
    return TTK::languageCore(0);
}
