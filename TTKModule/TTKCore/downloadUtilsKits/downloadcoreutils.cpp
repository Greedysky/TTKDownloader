#include "downloadcoreutils.h"
#include "downloadsettingmanager.h"

#include <QDirIterator>

QString DownloadUtils::Core::downloadPrefix()
{
   QString path = G_SETTING_PTR->value(DownloadSettingManager::DownloadPathDirChoiced).toString();
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

QString DownloadUtils::Core::languageName(int index)
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
        const QFileInfo &fin = di.fileInfo();
        const QString &filePath = di.filePath();
        bool ok;
        if(fin.isDir() && !fin.isSymLink())
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
