#include "downloadconsoleobject.h"
#include "downloadthreadmanager.h"
#include "downloadsettingmanager.h"
#include "ttkversion.h"

DownloadConsoleObject::DownloadConsoleObject(QObject *parent)
    : QObject(parent)
{
    m_manager = new DownloadThreadManager(this);
    connect(m_manager, SIGNAL(progressChanged(qint64,qint64)), SLOT(progressChanged(qint64,qint64)));
    connect(m_manager, SIGNAL(downloadingFinished(QString)), qApp, SLOT(quit()));
}

DownloadConsoleObject::~DownloadConsoleObject()
{
    delete m_manager;
}

bool DownloadConsoleObject::initialize(const QCoreApplication &app) const
{
    TTK_LOG_STREAM("\n" APP_NAME << "Console Module" << TTK_VERSION_STR "\n");

    TTKCommandLineOption op1("-u", "--url", "download url");
    TTKCommandLineOption op2("-s", "--save", "download save path, if empty default is");

    TTKCommandLineParser parser;
    parser.addOption(op1);
    parser.addOption(op2);
    parser.process(app);

    if(parser.isEmpty())
    {
        parser.printHelp();
        return false;
    }

    QString url, path = DownloadObject::applicationPath();
    if(parser.isSet(op1))
    {
        url = parser.value(op1);
        if(url.isEmpty())
        {
            TTK_LOG_STREAM("download url is empty!");
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

    G_SETTING_PTR->setValue(DownloadSettingManager::DownloadPathDirChoiced, path);

    if(!m_manager->downloadFile(url))
    {
        return false;
    }

    TTK_LOG_STREAM("download save path: " << m_manager->downloadedPath());
    return app.exec();
}

void DownloadConsoleObject::progressChanged(qint64 current, qint64 total)
{
    TTK_LOG_STREAM("process: " << TTKStatic_cast(int, (current * 100000000.0 / total)) / 1000000.0 <<
                   "% " << current << "kb " << total << "kb");
}
