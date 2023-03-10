#include "downloadcoreutils.h"
#include "downloadsettingmanager.h"

QString TTK::Core::downloadPrefix()
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
