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
    if(!QFile::exists(S_TTKDD_FULL))
    {
        QFile::copy(":/data/TTKLDD.sh", S_TTKDD_FULL);
        QFile::setPermissions(S_TTKDD_FULL, QFile::ReadOwner | QFile::WriteOwner);
        QProcess::execute("chmod", QStringList() << "+x" << S_TTKDD_FULL);
    }
    if(!QFile::exists(S_TTKSERVICE_FULL))
    {
        QFile::copy(":/data/TTKService.sh", S_TTKSERVICE_FULL);
        QFile::setPermissions(S_TTKSERVICE_FULL, QFile::ReadOwner | QFile::WriteOwner);
        QProcess::execute("chmod", QStringList() << "+x" << S_TTKSERVICE_FULL);
    }
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
