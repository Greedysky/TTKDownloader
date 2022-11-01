#include "downloadapplication.h"
#include "downloadruntimemanager.h"
#include "ttkdumper.h"

#include <QTimer>
#include <QScreen>
#include <QTranslator>
#include <QApplication>

#define TTK_DEBUG

static void loadAppScaledFactor(int argc, char *argv[])
{
#if TTK_QT_VERSION_CHECK(5,4,0)
#  if TTK_QT_VERSION_CHECK(6,0,0)
     // do nothing
#  elif TTK_QT_VERSION_CHECK(5,12,0)
     QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#  elif TTK_QT_VERSION_CHECK(5,6,0)
     QApplication a(argc, argv);
     qputenv("QT_DEVICE_PIXEL_RATIO", "auto");
     QScreen *screen = QApplication::primaryScreen();
     qreal dpi = screen->logicalDotsPerInch() / 96;
     qputenv("QT_SCALE_FACTOR", QByteArray::number(dpi));
     Q_UNUSED(a);
#  else
     qputenv("QT_DEVICE_PIXEL_RATIO", "auto");
#  endif
#endif
    Q_UNUSED(argc);
    Q_UNUSED(argv);
}

int main(int argc, char *argv[])
{
    loadAppScaledFactor(argc, argv);

    QApplication a(argc, argv);
#if !defined TTK_DEBUG && !defined Q_OS_UNIX
    if(argc <= 1 || QString(argv[1]) != APPNAME)
    {
        return -1;
    }
#endif
    ///////////////////////////////////////////////////////
    QCoreApplication::setOrganizationName(APP_NAME);
    QCoreApplication::setOrganizationDomain(APP_COME_NAME);
    QCoreApplication::setApplicationName(APP_NAME);

    TTKDumper dumper;
    dumper.run();

    DownloadRunTimeManager manager;
    manager.run();

    QTranslator translator;
    if(!translator.load(manager.translator()))
    {
        TTK_ERROR_STREAM("Load translation error");
    }
    a.installTranslator(&translator);

    DownloadApplication w;
    w.show();

    return a.exec();
}
