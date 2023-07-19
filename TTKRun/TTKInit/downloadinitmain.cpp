#include <QCoreApplication>
#include "downloadconfigobject.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    QCoreApplication::setOrganizationName(APP_NAME);
    QCoreApplication::setOrganizationDomain(APP_COME_NAME);
    QCoreApplication::setApplicationName(APP_NAME);

    DownloadConfigObject object;
    object.initialize();
    TTK_INFO_STREAM("Parameter Init success");
    return 0;
}
