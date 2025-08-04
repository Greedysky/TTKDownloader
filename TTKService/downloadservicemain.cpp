#include "ttkapplication.h"
#include "downloadapplication.h"
#include "downloadruntimemanager.h"
#include "downloadconfigmodule.h"
#include "downloadotherdefine.h"
#include "ttkinitialization.h"

#include <QTranslator>

static void cleanupCache()
{
    QFile::remove(TTK_COLOR_FILE);
    QFile::remove(TTK_IMAGE_FILE);
    TTK_INFO_STREAM("Application cache cleanup");
}


int main(int argc, char *argv[])
{
    TTK::loadApplicationScaleFactor();

    TTKApplication app(argc, argv);
    TTKInitialization ttk(cleanupCache);

    if(app.isRunning())
    {
        TTK_INFO_STREAM("One app has already run");
        return EXIT_FAILURE;
    }

    ttk.generateFont();
    ttk.codecForLocale();
    ttk.execute();

    DownloadConfigModule config;
    config.valid();

    DownloadRunTimeManager manager;
    manager.execute();

    QTranslator translator;
    if(!translator.load(manager.translator()))
    {
        TTK_ERROR_STREAM("Load translation error");
    }
    app.installTranslator(&translator);

    DownloadApplication w;
    w.show();
    return app.exec();
}
