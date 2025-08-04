#include <QCoreApplication>
#include "downloadconfigmodule.h"
#include "ttkinitialization.h"

#ifdef _MSC_VER // do not show console window
#  pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")
#endif

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    RegisterOrganization(TTK_APP);

    DownloadConfigModule config;
    config.initialize();
    TTK_INFO_STREAM("Parameter Init success");
    return EXIT_SUCCESS;
}
