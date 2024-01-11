#include "downloadconfigobject.h"

#include <QProcess>

DownloadConfigObject::DownloadConfigObject(QObject *parent)
    : QObject(parent)
{

}

void DownloadConfigObject::valid() const
{
    checkDirectoryExist();
    checkFileNeededExist();
}

void DownloadConfigObject::initialize() const
{
    valid();

    copyFileOverwrite(":/data/config.xml", TTK_COFIG_PATH_FULL);
    copyFileOverwrite(":/data/list.tkpl", TTK_LIST_PATH_FULL);
    copyFileOverwrite(":/data/history.tkf", TTK_HISTORY_PATH_FULL);
}

void DownloadConfigObject::reset() const
{
    copyFileOverwrite(":/data/config.xml", TTK_COFIG_PATH_FULL);
}

void DownloadConfigObject::directoryExist(const QString &name) const
{
    QDir dir;
    if(!dir.exists(name))
    {
        dir.mkpath(name);
    }
}

void DownloadConfigObject::checkDirectoryExist() const
{
    directoryExist(TTK_USER_THEME_DIR_FULL);

    directoryExist(TTK_THEME_DIR_FULL);
    directoryExist(TTK_LANGUAGE_DIR_FULL);
}

void DownloadConfigObject::checkFileNeededExist() const
{
    copyFile(":/data/config.xml", TTK_COFIG_PATH_FULL);
    copyFile(":/data/list.tkpl", TTK_LIST_PATH_FULL);
    copyFile(":/data/history.tkf", TTK_HISTORY_PATH_FULL);

#ifdef Q_OS_UNIX
    if(!QFile::exists(MAIN_DIR_FULL + ".ttk_runtime"))
    {
        copyLinuxShellFile(":/data/TTKRoutine.sh", TTK_ROUTINE_FULL);
        copyLinuxShellFile(":/data/TTKDownloader.sh", TTK_APP_MAIN_FULL);
        copyLinuxShellFile(":/data/TTKRoutineCopy.sh", TTK_ROUTINECOPY_FULL);
        copyLinuxShellFile(":/data/avnets.sh", TTK_MAKE_NET_PATH_FULL);
        copyLinuxShellFile(":/data/TTKInit.sh", TTK_INIT_FULL);
        copyLinuxShellFile(":/data/TTKConsole.sh", TTK_CONSOLE_FULL);
        copyLinuxShellFile(":/data/TTKService.sh", TTK_SERVICE_FULL);
    }
#endif
}

void DownloadConfigObject::copyFileOverwrite(const QString &origin, const QString &des) const
{
    if(QFile::exists(des))
    {
        QFile::remove(des);
    }

    QFile::copy(origin, des);
    QFile::setPermissions(des, QFile::ReadOwner | QFile::WriteOwner);
}

void DownloadConfigObject::copyFile(const QString &origin, const QString &des) const
{
    if(!QFile::exists(des))
    {
        QFile::copy(origin, des);
        QFile::setPermissions(des, QFile::ReadOwner | QFile::WriteOwner);
    }
}

#ifdef Q_OS_UNIX
void DownloadConfigObject::copyLinuxShellFile(const QString &name, const QString &path) const
{
    copyFileOverwrite(name, path);
    QProcess::execute("chmod", {"+x", path});
}
#endif
