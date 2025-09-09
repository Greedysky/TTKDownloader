#include "downloadconfigmodule.h"

#include <QProcess>

DownloadConfigModule::DownloadConfigModule(QObject *parent)
    : QObject(parent)
{

}

void DownloadConfigModule::valid() const
{
    checkDirectoryExist();
    checkFileNeededExist();
}

void DownloadConfigModule::initialize() const
{
    valid();

    copyFileOverwrite(":/data/config.xml", TTK_COFIG_PATH_FULL);
    copyFileOverwrite(":/data/list.tkpl", TTK_LIST_PATH_FULL);
    copyFileOverwrite(":/data/history.tkf", TTK_HISTORY_PATH_FULL);
    copyFileOverwrite(":/data/recycle.tkf", TTK_RECYCLE_PATH_FULL);
}

void DownloadConfigModule::reset() const
{
    copyFileOverwrite(":/data/config.xml", TTK_COFIG_PATH_FULL);
}

void DownloadConfigModule::directoryExist(const QString &name) const
{
    QDir dir;
    if(!dir.exists(name))
    {
        dir.mkpath(name);
    }
}

void DownloadConfigModule::checkDirectoryExist() const
{
    directoryExist(TTK_USER_THEME_DIR_FULL);

    directoryExist(TTK_THEME_DIR_FULL);
    directoryExist(TTK_LANGUAGE_DIR_FULL);
}

void DownloadConfigModule::checkFileNeededExist() const
{
    copyFile(":/data/config.xml", TTK_COFIG_PATH_FULL);
    copyFile(":/data/list.tkpl", TTK_LIST_PATH_FULL);
    copyFile(":/data/history.tkf", TTK_HISTORY_PATH_FULL);
    copyFile(":/data/recycle.tkf", TTK_RECYCLE_PATH_FULL);

#ifdef Q_OS_UNIX
    if(!QFile::exists(MAIN_DIR_FULL + "ttk_runtime"))
    {
        copyLinuxShellFile(":/data/TTKRoutine.sh", TTK_ROUTINE_FULL);
        copyLinuxShellFile(":/data/TTKDownloader.sh", TTK_APP_MAIN_FULL);
        copyLinuxShellFile(":/data/TTKRoutineCopy.sh", TTK_ROUTINECOPY_FULL);
        copyLinuxShellFile(":/data/avnets", TTK_TRAFFIC_PATH_FULL);
        copyLinuxShellFile(":/data/TTKInit.sh", TTK_INIT_FULL);
        copyLinuxShellFile(":/data/TTKConsole.sh", TTK_CONSOLE_FULL);
        copyLinuxShellFile(":/data/TTKService.sh", TTK_SERVICE_FULL);
    }
#endif
}

void DownloadConfigModule::copyFileOverwrite(const QString &origin, const QString &des) const
{
    if(QFile::exists(des))
    {
        QFile::remove(des);
    }

    QFile::copy(origin, des);
    QFile::setPermissions(des, QFile::ReadOwner | QFile::WriteOwner);
}

void DownloadConfigModule::copyFile(const QString &origin, const QString &des) const
{
    if(!QFile::exists(des))
    {
        QFile::copy(origin, des);
        QFile::setPermissions(des, QFile::ReadOwner | QFile::WriteOwner);
    }
}

#ifdef Q_OS_UNIX
void DownloadConfigModule::copyLinuxShellFile(const QString &name, const QString &path) const
{
    copyFileOverwrite(name, path);
    QProcess::execute("chmod", {"+x", path});
}
#endif
