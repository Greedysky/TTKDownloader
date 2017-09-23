#include "downloadrunapplication.h"
#include "downloadrunobject.h"
#include "downloadobject.h"

int main(int argc, char *argv[])
{
    DownloadRunApplication app(argc, argv);

    QCoreApplication::setOrganizationName(APPNAME);
    QCoreApplication::setOrganizationDomain(APPCOME);
    QCoreApplication::setApplicationName(APPNAME);

    if(app.isRunning())
    {
        qDebug() << "One app has already run!";
        return -1;
    }

    DownloadRunObject object;
    object.checkValid();
    object.run(argc, argv);

    return app.exec();
}
