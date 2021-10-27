#include <QCoreApplication>
#include "downloadinitobject.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    QCoreApplication::setOrganizationName(APP_NAME);
    QCoreApplication::setOrganizationDomain(APP_COME_NAME);
    QCoreApplication::setApplicationName(APP_NAME);

    DownloadInitObject object;
    object.init();
    qDebug() << "Parameter Init success!";

    Q_UNUSED(app);
    return 0;
}
