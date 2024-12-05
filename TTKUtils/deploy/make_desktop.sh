#!/bin/sh

path=share/applications
if [ ! -d $path ]; then
  mkdir $path
fi

datapath=$path/TTKDownloader.desktop
packpath="$PWD/$datapath"
userpath=~/.local/$datapath
iconpath="$PWD/share/pixmaps/ttkdownloader.png"
execpath="$PWD/../TTKDownloader"

echo -n "[Desktop Entry]
Type=Application
Version=3.0.0.0
Name=TTKDownloader
Name[zh_CN]=天天下载
Name[zh_TW]=天天下載
GenericName=TTKDownloader
GenericName[zh_CN]=天天下载
GenericName[zh_TW]=天天下載
Comment=TTKDownloader
Comment[zh_CN]=天天下载
Comment[zh_TW]=天天下載
Icon=$iconpath
Exec=$execpath
Terminal=false
Keywords=multimedia;downloader;
Categories=Downloader;Qt;
MimeType=
X-KDE-StartupNotify=false\n" > $packpath

cp -rv $packpath $userpath
chmod +x $userpath
