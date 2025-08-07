#!/bin/sh

dirpath=`dirname $0`
tmp="${dirpath#?}"

if [ "${dirpath%${tmp}}" != "/" ]; then
  dirpath=$PWD/${dirpath}
fi

username=`logname`
if [ "${username}" = "root" ]; then
  homepath=/root
else
  homepath=/home/${username}
fi

packvern=3.1.0.0
packpath=${dirpath}/TTKDownloader.desktop
userpath=${homepath}/.local/share/applications
iconpath="${dirpath}/share/pixmaps/ttkdownloader.png"
execpath="${dirpath}/../TTKDownloader"

echo -n "[Desktop Entry]
Type=Application
Version=${packvern}
Name=TTKDownloader
Name[zh_CN]=天天下载
Name[zh_TW]=天天下載
GenericName=TTKDownloader
GenericName[zh_CN]=天天下载
GenericName[zh_TW]=天天下載
Comment=TTKDownloader
Comment[zh_CN]=天天下载
Comment[zh_TW]=天天下載
Icon=${iconpath}
Exec=${execpath}
Terminal=false
Keywords=multimedia;downloader;
Categories=Downloader;Qt;
MimeType=
X-KDE-StartupNotify=false\n" > ${packpath}

mv -fv ${packpath} ${userpath}
chmod +x ${userpath}
