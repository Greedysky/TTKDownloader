#include "downloadconsolemodule.h"
#include "ttkinitialization.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    TTKRegisterOrganization(TTK_APP);

    DownloadConsoleModule console;
    return console.initialize() ? EXIT_SUCCESS : EXIT_FAILURE;
}
