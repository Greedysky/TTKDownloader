#include "downloadconsoleobject.h"
#include "downloadthreadmanager.h"
#include "downloadsettingmanager.h"

#if TTK_QT_VERSION_CHECK(5,2,0)
#include <QCommandLineOption>
#include <QCommandLineParser>
#endif

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

bool DownloadConsoleObject::init(const QCoreApplication &app)
{
#if TTK_QT_VERSION_CHECK(5,2,0)
    QCommandLineOption op1("u", "", ".");
    QCommandLineOption op2("s", "", ".");

    QCommandLineParser parser;
    parser.addOption(op1);
    parser.addOption(op2);
    parser.process(app);

    if(app.arguments().count() == 1)
    {
        qDebug() << "\nOptions:";
        qDebug() << "-u //download url";
        qDebug() << "-s //download save path, if empty default is .\n";
        return false;
    }

    QString url = parser.value(op1);
    if(url.isEmpty())
    {
        qDebug() << "download url is empty!";
        return false;
    }

    QString path = parser.value(op2);
    if(path.isEmpty())
    {
        path = DownloadObject::getAppDir();
        qDebug() << "download save path is empty, just use default '.' path!";
    }
    M_SETTING_PTR->setValue(DownloadSettingManager::DownloadPathDirChoiced, path);

    m_manager->downloadFile(url);
    qDebug() << "download save path :" << m_manager->getDownloadedPath();
#else
    qDebug() << "Qt version less than 5.2 not support commend line!";
#endif
    return app.exec();
}

void DownloadConsoleObject::progressChanged(qint64 current, qint64 total)
{
    qDebug() << "process: " << TTKStatic_cast(int, (current*100000000.0/total))/1000000.0
             << "% " << current << "kb " << total << "kb";
}
