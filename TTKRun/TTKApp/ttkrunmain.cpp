#include "ttkrunapplication.h"
#include "ttkrunobject.h"
#include "downloadobject.h"

int main(int argc, char *argv[])
{
    TTKRunApplication app(argc, argv);

    QCoreApplication::setOrganizationName(APP_NAME);
    QCoreApplication::setOrganizationDomain(APP_COME_NAME);
    QCoreApplication::setApplicationName(APP_NAME);

    if(app.isRunning())
    {
        TTK_LOGGER_INFO("One app has already run");
        return -1;
    }

    TTKRunObject object;
    object.valid();
    object.run(argc, argv);

    return app.exec();
}
