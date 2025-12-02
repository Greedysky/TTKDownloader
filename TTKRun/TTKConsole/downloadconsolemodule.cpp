#include "downloadconsolemodule.h"
#include "downloadthreadmanager.h"
#include "downloadsettingmanager.h"
#include "ttkversion.h"

DownloadConsoleModule::DownloadConsoleModule(QObject *parent)
    : QObject(parent)
{
    m_manager = new DownloadThreadManager(this);
    connect(m_manager, SIGNAL(progressChanged(qint64,qint64)), SLOT(progressChanged(qint64,qint64)));
    connect(m_manager, SIGNAL(downloadFinished(QString)), qApp, SLOT(quit()));
}

DownloadConsoleModule::~DownloadConsoleModule()
{
    delete m_manager;
}

bool DownloadConsoleModule::initialize() const
{
    QString text = TTK_STR_CAT("\n", TTK_APP_NAME, " Console Module v", TTK_VERSION_STR, "\n");
            text += "Offical web page: https://github.com/Greedysky/TTKDownloader\n";
            text += "Copyright(C) 2015 - 2026 Greedysky All Rights Reserved\n";
            text += "TTKDownloader imitates xunlei downloader, based on Qt for windows and linux\n\n";

    TTKCommandLineOption op1("-u", "--url", "download url");
    TTKCommandLineOption op2("-s", "--save", "download save path, if empty default is");

    TTKCommandLineParser parser;
    parser.addOption(op1);
    parser.addOption(op2);
    parser.setDescription(text);
    parser.process();

    if(parser.isEmpty())
    {
        parser.showHelp();
        return false;
    }

    QString url, path = TTK::applicationPath();
    if(parser.isSet(op1))
    {
        url = parser.value(op1);
        if(url.isEmpty())
        {
            TTK_LOG_STREAM("download url is empty");
            return false;
        }
    }

    if(url.isEmpty())
    {
        return false;
    }

    if(parser.isSet(op2))
    {
        const QString &v = parser.value(op2);
        if(!v.isEmpty())
        {
            path = v + TTK_SEPARATOR;
        }
    }

    G_SETTING_PTR->setValue(DownloadSettingManager::DownloadPathDir, path);

    if(!m_manager->download(url))
    {
        return false;
    }

    TTK_LOG_STREAM("download save path: " << m_manager->path());
    return QCoreApplication::exec();
}

void DownloadConsoleModule::progressChanged(qint64 current, qint64 total)
{
    TTK_LOG_STREAM("process: " << TTKStaticCast(int, (current * 100000000.0 / total)) / 1000000.0 <<
                   "% " << current << "kb " << total << "kb");
}
