#include "downloadruntimemanager.h"
#include "downloadconfigmanager.h"
#include "downloadsettingmanager.h"
#include "downloadnetworkthread.h"

#include <QFont>
#include <QApplication>

namespace TTK
{
    /*!
     * Generate core language resource.
     */
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


void DownloadRunTimeManager::execute() const
{
    TTK_INFO_STREAM("DownloadApplication Run");

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
}

QString DownloadRunTimeManager::translator() const
{
    return TTK::languageCore(0);
}
