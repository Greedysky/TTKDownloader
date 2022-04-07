#include "downloadinitobject.h"

#include <QProcess>

DownloadInitObject::DownloadInitObject(QObject *parent)
    : QObject(parent)
{

}

void DownloadInitObject::valid() const
{
    checkDirectoryExist();
    checkFileNeededExist();
}

void DownloadInitObject::initialize() const
{
    checkFileNeededExist();

    copyFileOverwrite(":/data/config.xml", TTK_COFIG_PATH_FULL);
    copyFileOverwrite(":/data/list.tkpl", TTK_LIST_PATH_FULL);
    copyFileOverwrite(":/data/history.tkf", TTK_HISTORY_PATH_FULL);
}

void DownloadInitObject::directoryExist(const QString &name) const
{
    QDir dir;
    if(!dir.exists(name))
    {
        dir.mkpath(name);
    }
}

void DownloadInitObject::checkDirectoryExist() const
{
    directoryExist(TTK_APPDATA_DIR_FULL);
    directoryExist(TTK_APPCACHE_DIR_FULL);

    directoryExist(TTK_USER_THEME_DIR_FULL);

    directoryExist(TTK_THEME_DIR_FULL);
    directoryExist(TTK_LANGUAGE_DIR_FULL);
}

void DownloadInitObject::checkFileNeededExist() const
{
    copyFile(":/data/config.xml", TTK_COFIG_PATH_FULL);
    copyFile(":/data/list.tkpl", TTK_LIST_PATH_FULL);
    copyFile(":/data/history.tkf", TTK_HISTORY_PATH_FULL);

#ifdef Q_OS_UNIX
    copyLinuxShellFile(":/data/avnets.sh", TTK_MAKE_NET_PATH_FULL);
    copyLinuxShellFile(":/data/TTKDownloader.sh", TTK_DOWNLOADER_FULL);
    copyLinuxShellFile(":/data/TTKService.sh", TTK_SERVICE_FULL);
    copyLinuxShellFile(":/data/TTKRoutine.sh", TTK_ROUTINE_FULL);
    copyLinuxShellFile(":/data/TTKRoutineCopy.sh", TTK_ROUTINECOPY_FULL);
    copyLinuxShellFile(":/data/TTKConsole.sh", TTK_CONSOLE_FULL);
    copyLinuxShellFile(":/data/TTKInit.sh", TTK_INIT_FULL);
#endif
}

void DownloadInitObject::copyFileOverwrite(const QString &origin, const QString &des) const
{
    if(QFile::exists(des))
    {
        QFile::remove(des);
    }

    QFile::copy(origin, des);
    QFile::setPermissions(des, QFile::ReadOwner | QFile::WriteOwner);
}

void DownloadInitObject::copyFile(const QString &origin, const QString &des) const
{
    if(!QFile::exists(des))
    {
        QFile::copy(origin, des);
        QFile::setPermissions(des, QFile::ReadOwner | QFile::WriteOwner);
    }
}

void DownloadInitObject::copyLinuxShellFile(const QString &name, const QString &path) const
{
    copyFileOverwrite(name, path);
    QProcess::execute("chmod", QStringList() << "+x" << path);
}
