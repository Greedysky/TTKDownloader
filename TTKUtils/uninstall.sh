#!/bin/sh

username=`logname`
if [ "${username}" = "root" ]; then
  homepath=/root
else
  homepath=/home/${username}
fi

rm -f ${homepath}/.local/share/applications/TTKDownloader.desktop
rm -f ${homepath}/.local/share/metainfo/ttkdownloader.metainfo.xml
