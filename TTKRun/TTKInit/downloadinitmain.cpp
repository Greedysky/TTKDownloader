#include <QCoreApplication>
#include "downloadconfigmodule.h"

#ifdef _MSC_VER // do not show console window
#  pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")
#endif

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    QCoreApplication::setOrganizationName(TTK_APP_NAME);
    QCoreApplication::setOrganizationDomain(TTK_APP_COME_NAME);
    QCoreApplication::setApplicationName(TTK_APP_NAME);

    DownloadConfigModule config;
    config.initialize();
    TTK_INFO_STREAM("Parameter Init success");
    return EXIT_SUCCESS;
}
