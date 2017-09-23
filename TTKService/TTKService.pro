# =================================================
# * This file is part of the TTK Downloader project
# * Copyright (c) 2016 - 2017 Greedysky Studio
# * All rights reserved!
# * Redistribution and use of the source code or any derivative
# * works are strictly forbiden.
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
