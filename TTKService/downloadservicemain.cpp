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
    TTK::initialize(TTK::Attribute::All);

    TTKApplication app(argc, argv);
    TTKInitialization ttk(cleanupCache);

    // parse command line args
    QStringList args;
    for(int i = 0; i < argc; ++i)
    {
        const QString &arg = QString::fromLocal8Bit(argv[i]);
        if(ttk.argumentValid(arg))
        {
            args << arg;
        }
    }

    ttk.execute(args);

    if(app.isRunning())
    {
        TTK_INFO_STREAM("One app has already run");
        return EXIT_FAILURE;
    }

    DownloadConfigModule config;
    config.execute();

    DownloadRunTimeManager manager;
    manager.execute();

    ttk.generateFont();
    ttk.codecForLocale();

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
