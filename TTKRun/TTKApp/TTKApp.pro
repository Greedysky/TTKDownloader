# =================================================
# * This file is part of the TTK Downloader project
# * Copyright (c) 2016 - 2017 Greedysky Studio
# * All rights reserved!
# * Redistribution and use of the source code or any derivative
# * works are strictly forbiden.
# =================================================

QT       += core gui network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

include(../../TTKVersion.pri)
unix:VERSION += $$TTKDownloader

win32:TARGET = ../../../bin/TTKDownloader
unix:TARGET = ../../lib/TTKDownloader

TEMPLATE = app

win32:msvc{
    CONFIG +=c++11
}else{
    QMAKE_CXXFLAGS += -std=c++11
}

INCLUDEPATH += \
    ../ \
    ../TTKInit \
    ../../ \
    ../../TTKModule/TTKCore/downloadCoreKits

SOURCES += \
    ../TTKInit/downloadinitobject.cpp \
    downloadlocalpeer.cpp \
    downloadrunapplication.cpp \
    downloadrunmain.cpp \
    downloadrunobject.cpp


HEADERS += \
    ../downloadrunglobaldefine.h \
    downloadrunapplication.h \
    ../TTKInit/downloadinitobject.h \
    downloadlocalpeer.h \
    downloadrunobject.h


RESOURCES += \
    ../../TTKQrc/DownloaderApp.qrc

win32{
    RC_FILE = TTKApp.rc
}
