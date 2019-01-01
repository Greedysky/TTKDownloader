# =================================================
# * This file is part of the TTK Downloader project
# * Copyright (C) 2015 - 2019 Greedysky Studio
#
# * This program is free software; you can redistribute it and/or modify
# * it under the terms of the GNU General Public License as published by
# * the Free Software Foundation; either version 3 of the License, or
# * (at your option) any later version.
#
# * This program is distributed in the hope that it will be useful,
# * but WITHOUT ANY WARRANTY; without even the implied warranty of
# * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# * GNU General Public License for more details.
#
# * You should have received a copy of the GNU General Public License along
# * with this program; If not, see <http://www.gnu.org/licenses/>.
# =================================================

TEMPLATE = app

contains(CONFIG, DOWNLOAD_BUILD_LIB){
    CONFIG -= DOWNLOAD_BUILD_LIB
}

CONFIG += DOWNLOAD_NO_MSVC_LINK_NEED
win32{
    msvc{
        CONFIG -= DOWNLOAD_NO_MSVC_LINK_NEED
    }
}
include(../TTKDownloader.pri)
unix:VERSION += $$TTKDownloader

win32{
    TARGET = ../../bin/$$TTKDownloader/TTKService
    LIBS += -L../bin/$$TTKDownloader -lTTKCore -lTTKDumper
}
unix{
    TARGET = ../lib/$$TTKDownloader/TTKService
    LIBS += -L./lib/$$TTKDownloader -lTTKCore -lTTKDumper
}


INCLUDEPATH += ../TTKModule

!contains(CONFIG, DOWNLOAD_NO_MSVC_LINK_NEED){
HEADERS  += \
    ../TTKModule/downloadapplication.h

}

SOURCES += \
    downloadservicemain.cpp

win32{
    RC_FILE = TTKService.rc
}
