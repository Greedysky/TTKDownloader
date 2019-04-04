#include "downloadinitobject.h"

#include <QProcess>

DownloadInitObject::DownloadInitObject(QObject *parent)
    : QObject(parent)
{

}

void DownloadInitObject::checkValid()
{
    checkTheDirectoryExist();
    checkTheFileNeededExist();
}

void DownloadInitObject::init()
{
    checkTheFileNeededExist();

    copyFileOverwrite(":/data/downloadconfig.xml", S_COFIGPATH_FULL);
    copyFileOverwrite(":/data/download.lis", S_LISTPATH_FULL);
    copyFileOverwrite(":/data/downloadhistory.ttk", S_HISTORYPATH_FULL);
}

void DownloadInitObject::dirIsExist(const QString &name)
{
    QDir dir;
    if(!dir.exists(name))
    {
        dir.mkpath(name);
    }
}

void DownloadInitObject::checkTheDirectoryExist()
{
    dirIsExist(S_APPDATA_DIR_FULL);
    dirIsExist(S_DOWNLOADS_DIR_FULL);

    dirIsExist(S_CACHE_DIR_FULL);
    dirIsExist(S_UPDATE_DIR_FULL);

    dirIsExist(S_AVATAR_DIR_FULL);
    dirIsExist(S_USER_THEME_DIR_FULL);

    dirIsExist(S_THEME_DIR_FULL);
    dirIsExist(S_LANGUAGE_DIR_FULL);
}

void DownloadInitObject::checkTheFileNeededExist()
{
    copyFile(":/data/downloadconfig.xml", S_COFIGPATH_FULL);
    copyFile(":/data/download.lis", S_LISTPATH_FULL);
    copyFile(":/data/downloadhistory.ttk", S_HISTORYPATH_FULL);

#ifdef Q_OS_UNIX
    copyLinuxShellFile(":/data/avnets.sh", S_MAKENETS_FULL);
    copyLinuxShellFile(":/data/TTKDownloader.sh", S_TTKDOWNLOADER_FULL);
    copyLinuxShellFile(":/data/TTKService.sh", S_TTKSERVICE_FULL);
    copyLinuxShellFile(":/data/TTKRoutine.sh", S_TTKROUTINE_FULL);
    copyLinuxShellFile(":/data/TTKRoutineCopy.sh", S_TTKROUTINECOPY_FULL);
    copyLinuxShellFile(":/data/TTKConsole.sh", S_TTKCONSOLE_FULL);
    copyLinuxShellFile(":/data/TTKInit.sh", S_TTKINIT_FULL);
#endif

}

void DownloadInitObject::copyFileOverwrite(const QString &origin, const QString &des)
{
    if(QFile::exists(des))
    {
        QFile::remove(des);
    }
    QFile::copy(origin, des);
    QFile::setPermissions(des, QFile::ReadOwner | QFile::WriteOwner);
}

void DownloadInitObject::copyFile(const QString &origin, const QString &des)
{
    if(!QFile::exists(des))
    {
        QFile::copy(origin, des);
        QFile::setPermissions(des, QFile::ReadOwner | QFile::WriteOwner);
    }
}

void DownloadInitObject::copyLinuxShellFile(const QString &name, const QString &path)
{
    copyFileOverwrite(name, path);
    QProcess::execute("chmod", QStringList() << "+x" << path);
}
