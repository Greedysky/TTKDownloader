#include "ttkapplication.h"
#include "downloadapplication.h"
#include "downloadruntimemanager.h"
#include "downloadconfigmodule.h"
#include "downloadotherdefine.h"
#include "ttkobject.h"
#include "ttkdumper.h"
#include "ttkglobalwrapper.h"
#include "ttkplatformsystem.h"

#ifdef Q_OS_UNIX
#  include <malloc.h>
#endif

#include <QTranslator>

static void cleanupCache()
{
    QFile::remove(TTK_COLOR_FILE);
    QFile::remove(TTK_IMAGE_FILE);
    QFile::remove(TTK_RECORD_FILE);
    QFile::remove(TTK_RECORD_IN_FILE);
    QFile::remove(TTK_RECORD_OUT_FILE);
    QFile::remove(DOWNLOAD_NETWORK_TEST_FILE);
    TTK_INFO_STREAM("Application cache cleanup");
}

static void loadApplicationScaleFactor()
{
#if TTK_QT_VERSION_CHECK(6,0,0)
   // do nothing
#elif TTK_QT_VERSION_CHECK(5,4,0)
#  if TTK_QT_VERSION_CHECK(5,12,0)
      QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
      QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
#    if TTK_QT_VERSION_CHECK(5,14,0)
        QApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);
#    endif
#  elif TTK_QT_VERSION_CHECK(5,6,0)
      const float dpi = TTKPlatformSystem::logicalDotsPerInch() / 96.0;
      qputenv("QT_SCALE_FACTOR", QByteArray::number(dpi < 1.0 ? 1.0 : dpi));
#  endif
#endif
}

int main(int argc, char *argv[])
{
    loadApplicationScaleFactor();

    TTKApplication app(argc, argv);

    QCoreApplication::setOrganizationName(TTK_APP_NAME);
    QCoreApplication::setOrganizationDomain(TTK_APP_COME_NAME);
    QCoreApplication::setApplicationName(TTK_APP_NAME);

    if(app.isRunning())
    {
        TTK_INFO_STREAM("One app has already run");
        return -1;
    }

    DownloadConfigModule config;
    config.valid();

    TTKDumper dumper(std::bind(cleanupCache));
    dumper.run();

    DownloadRunTimeManager manager;
    manager.run();

    QTranslator translator;
    if(!translator.load(manager.translator()))
    {
        TTK_ERROR_STREAM("Load translation error");
    }
    app.installTranslator(&translator);

    TTK::setApplicationFont();

    DownloadApplication w;
    w.show();

#ifdef Q_OS_UNIX
    // memory free
    mallopt(M_MMAP_THRESHOLD, 1024 * 1024);   // 1MB mmap
    mallopt(M_TRIM_THRESHOLD, 2 * 1024 * 1024); // 2MB brk
#endif
    return app.exec();
}
