# =================================================
# * This file is part of the TTK Downloader project
# * Copyright (c) 2016 - 2017 Greedysky Studio
# * All rights reserved!
# * Redistribution and use of the source code or any derivative
# * works are strictly forbiden.
# =================================================

QT       += core
unix:VERSION += 1.0.0.0

win32:TARGET = ../../../bin/TTKInit
unix:TARGET = ../../lib/TTKInit

TEMPLATE = app

win32:msvc{
    CONFIG +=c++11
}else{
    QMAKE_CXXFLAGS += -std=c++11
}

INCLUDEPATH += \
    ../ \
    ../../ \
    ../../TTKModule/TTKCore/downloadCoreKits

SOURCES += \
    downloadinitmain.cpp \
    downloadinitobject.cpp

HEADERS += \
    ../downloadrunglobaldefine.h \
    downloadinitobject.h

RESOURCES += \
    ../../TTKQrc/DownloaderApp.qrc

win32{
    RC_FILE = TTKInit.rc
}
