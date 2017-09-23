#include "downloadapplication.h"
#include "downloadruntimemanager.h"
#include "ttkdumper.h"

#include <QTimer>
#include <QTranslator>
#include <QApplication>

#define DOWNLOAD_DEBUG

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
#if !defined DOWNLOAD_DEBUG && !defined Q_OS_UNIX
    if(argc <= 1 || QString(argv[1]) != APPNAME)
    {
        return -1;
    }
#endif
    ///////////////////////////////////////////////////////
    QCoreApplication::setOrganizationName(APPNAME);
    QCoreApplication::setOrganizationDomain(APPCOME);
    QCoreApplication::setApplicationName(APPNAME);

    TTKDumper dumper;
    dumper.run();

    DownloadRunTimeManager manager;
    manager.run();

    QTranslator translator;
    translator.load(manager.translator());
    a.installTranslator(&translator);

    DownloadApplication w;
    w.show();

    return a.exec();
}
