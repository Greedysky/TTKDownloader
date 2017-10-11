# =================================================
# * This file is part of the TTK Downloader project
# * Copyright (c) 2016 - 2017 Greedysky Studio
# * All rights reserved!
# * Redistribution and use of the source code or any derivative
# * works are strictly forbiden.
# =================================================

QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

include(../../TTKVersion.pri)
unix:VERSION += $$TTKDownloader

win32{
    TARGET = ../../../bin/$$TTKDownloader/TTKExtras
    msvc{
        CONFIG += staticlib
        LIBS += -luser32
    }
}
unix:TARGET = ../../lib/$$TTKDownloader/TTKExtras
TEMPLATE = lib

win32:msvc{
    CONFIG +=c++11
}else{
    QMAKE_CXXFLAGS += -std=c++11
}

include(../TTKExtrasDefine.pri)

include(qaes/QAes.pri)
include(qjson/QJson.pri)
include(qshortcut/QShortCut.pri)

win32{
    RC_FILE = TTKExtras.rc
}
