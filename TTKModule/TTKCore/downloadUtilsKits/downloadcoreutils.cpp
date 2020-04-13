#include "downloadcoreutils.h"
#include "downloadsettingmanager.h"
#include "ttkversion.h"

#include <QDirIterator>

QString DownloadUtils::Core::downloadPrefix()
{
   QString path = M_SETTING_PTR->value(DownloadSettingManager::DownloadPathDirChoiced).toString();
   if(path.isEmpty())
   {
       path = TDDOWNLOAD_DIR_FULL;
   }
   else
   {
       if(!QDir(path).exists())
       {
           QDir().mkpath(path);
       }
   }
   return path;
}

QString DownloadUtils::Core::fileSuffix(const QString &name)
{
    return name.right(name.length() - name.lastIndexOf(".") - 1);
}

quint64 DownloadUtils::Core::dirSize(const QString &dirName)
{
    quint64 size = 0;
    if(QFileInfo(dirName).isDir())
    {
        QDir dir(dirName);
        QFileInfoList list = dir.entryInfoList(QDir::Files | QDir::Dirs |  QDir::Hidden |
                                               QDir::NoSymLinks | QDir::NoDotAndDotDot);
        foreach(const QFileInfo &fileInfo, list)
        {
            if(fileInfo.isDir())
            {
                size += dirSize(fileInfo.absoluteFilePath());
            }
            else
            {
                size += fileInfo.size();
            }
        }
    }
    return size;
}

void DownloadUtils::Core::checkCacheSize(quint64 cacheSize, bool disabled, const QString &path)
{
    if(disabled)
    {
        quint64 size = dirSize(path);
        if(size > cacheSize)
        {
            QFileInfoList fileList = QDir(path).entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot);
            foreach(const QFileInfo &fileInfo, fileList)
            {
                size -= fileInfo.size();
                QFile::remove(fileInfo.absoluteFilePath());
                if(size <= cacheSize)
                {
                    break;
                }
            }
        }
    }
}

QFileInfoList DownloadUtils::Core::findFile(const QString &path, const QStringList &filter)
{
    ///Find the corresponding suffix name
    QDir dir(path);
    if(!dir.exists())
    {
        return QFileInfoList();
    }

    QFileInfoList fileList = dir.entryInfoList(filter, QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    QFileInfoList folderList = dir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot);

    foreach(const QFileInfo &folder, folderList)
    {
        fileList.append(findFile(folder.absoluteFilePath(), filter));
    }
    return fileList;
}

QString DownloadUtils::Core::getLanguageName(int index)
{
    QString lan(LANGUAGE_DIR_FULL);
    switch(index)
    {
        case 0 : return lan.append("cn.ln");
        case 1 : return lan.append("cn_c.ln");
        case 2 : return lan.append("en.ln");
        default: return QString();
    }
}

bool DownloadUtils::Core::removeRecursively(const QString &dir)
{
    QDir dr(dir);
    if(!dr.exists())
    {
        return true;
    }

    bool success = true;
    const QString dirPath = dr.path();
    // not empty -- we must empty it first
    QDirIterator di(dirPath, QDir::AllEntries | QDir::Hidden | QDir::System | QDir::NoDotAndDotDot);
    while(di.hasNext())
    {
        di.next();
        const QFileInfo &fi = di.fileInfo();
        const QString &filePath = di.filePath();
        bool ok;
        if(fi.isDir() && !fi.isSymLink())
        {
            ok = DownloadUtils::Core::removeRecursively(filePath); // recursive
        }
        else
        {
            ok = QFile::remove(filePath);
            if(!ok)
            {
                // Read-only files prevent directory deletion on Windows, retry with Write permission.
                const QFile::Permissions permissions = QFile::permissions(filePath);
                if(!(permissions & QFile::WriteUser))
                {
                    ok = QFile::setPermissions(filePath, permissions | QFile::WriteUser)
                      && QFile::remove(filePath);
                }
            }
        }

        if(!ok)
        {
            success = false;
        }
    }

    if(success)
    {
        success = dr.rmdir(dr.absolutePath());
    }

    return success;
}

bool DownloadUtils::Core::appVersionCheck(const QStringList &ol, const QStringList &dl, int depth)
{
    if(depth >= ol.count())
    {
        return false;
    }

    if(dl[depth].toInt() >= ol[depth].toInt())
    {
        if(dl[depth].toInt() == ol[depth].toInt())
        {
            return appVersionCheck(ol, dl, depth + 1);
        }
        else
        {
            return true;
        }
    }
    else
    {
        return false;
    }
}

bool DownloadUtils::Core::appVersionCheck(const QString &o, const QString &d)
{
    QStringList ol = o.split(".");
    QStringList dl = d.split(".");

    if(ol.isEmpty() || dl.isEmpty() || ol.count() != dl.count())
    {
        return false;
    }

    return appVersionCheck(ol, dl, 0);
}
