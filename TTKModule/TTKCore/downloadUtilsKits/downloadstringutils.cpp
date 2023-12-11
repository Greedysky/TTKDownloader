#include "downloadstringutils.h"
#include "downloadsettingmanager.h"

QString TTK::String::downloadPrefix()
{
   QString path = G_SETTING_PTR->value(DownloadSettingManager::DownloadPathDir).toString();
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
