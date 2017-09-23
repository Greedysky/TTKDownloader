# =================================================
# * This file is part of the TTK Downloader project
# * Copyright (c) 2016 - 2017 Greedysky Studio
# * All rights reserved!
# * Redistribution and use of the source code or any derivative
# * works are strictly forbiden.
# =================================================

include(../TTKVersion.pri)

QT       += core gui testlib
equals(QT_MAJOR_VERSION, 5){
QT       += widgets
}

win32:msvc{
    CONFIG +=c++11
}else{
    QMAKE_CXXFLAGS += -std=c++11
}

TARGET = TTKTest

TEMPLATE = app
DEFINES += DOWNLOAD_LIBRARY

INCLUDEPATH += $$PWD/../ \
               $$PWD/../TTKModule/TTKCore/downloadCoreKits \
               $$PWD/../TTKModule/TTKCore/downloadUtilsKits

win32{
    LIBS += -L../bin/$$TTKDownloader -lTTKCore
}


HEADERS  += \
    downloadautotest.h \
    tst_codelines.h

SOURCES  += \
    downloadapplicationmain.cpp \
    tst_codelines.cpp

